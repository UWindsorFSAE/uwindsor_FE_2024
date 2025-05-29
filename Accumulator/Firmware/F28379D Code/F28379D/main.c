#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "gpio.h"
#include "pin_map.h"
#include "spi.h"
#include "sysctl.h"

#include <stdint.h>
#include <stdio.h>

#define CPU_FREQ_MHZ 200U
#define DELAY_US(x) SysCtl_delay(((CPU_FREQ_MHZ) * (x)) / 3U)

// -- register addresses --
#define REG_OTP_ECC_DATAIN1  0x0343
#define REG_CONTROL1         0x0309
#define REG_DIR0_ADDR        0x0306
#define REG_DIR1_ADDR        0x0307
#define REG_COMM_CTRL        0x0308

#define REG_ACTIVE_CELL      0x0003
#define REG_ADC_CTRL_1       0x030D
#define REG_VCELL16_HI       0x0568
#define REG_VCELL16_LO       0x0569


// use the same CS pin you already have
#define CS_PIN     61
#define NUM_CELLS  16
#define ADC_RESOLUTION_UV 190.73f 

// Variables 
float cellVoltages[NUM_CELLS];


// CRC Check Function

uint16_t crc16_ibm(uint8_t *data, uint16_t len){
    uint16_t crc = 0xFFFF; 
    uint16_t i,j; 

    for (i = 0; i <len; i++){ 
        crc ^= (uint16_t)data[i]; 
        for (j = 0; j < 8; j++){ 
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001; 
            else
                crc >>= 1; 
        }
    }   
    return crc; 
} 


void wakeupSequence(){ 

    // Switch Pin from SPI to GPIO
    GPIO_setPinConfig(GPIO_61_GPIO61); //nCS
    GPIO_setDirectionMode(61,GPIO_DIR_MODE_OUT);
    GPIO_setPinConfig(GPIO_58_GPIO58); //MOSI
    GPIO_setDirectionMode(58,GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(58, GPIO_PIN_TYPE_STD);
    GPIO_setPadConfig(61, GPIO_PIN_TYPE_STD);
    
    

    // Pull nCS line low, and wait 2 us
    GPIO_writePin(61,0);
    DEVICE_DELAY_US(2);

    // PUll MOSI/RX line low for 2.75 ms, then pull high
    GPIO_writePin(58,0); 
    DEVICE_DELAY_US(2750); 
    GPIO_writePin(58,1); 

    // Wait 2us, pull nCS pin high 
    DEVICE_DELAY_US(2);
    GPIO_writePin(61, 1);

    GPIO_setPinConfig(GPIO_58_SPISIMOA); 
    GPIO_setPinConfig(GPIO_61_SPISTEA);
    
}

void sendWakePing(void) {
    uint8_t tx[5] = {
        0x90,       // command: single-device write
        0x00,       // broadcast device ID
        0x03, 0x09, // address: 0x0309 (CONTROL1)
        0x20,       // data: SEND_WAKE = 1 << 5
        //0x13,
        //0x95
    };

    uint16_t crc = crc16_ibm(tx, 5);

    // Pull nCS low
    GPIO_writePin(61, 0);
    DEVICE_DELAY_US(2);

    // Send 5 bytes + 2 CRC bytes
    uint16_t i;
    for (i = 0; i < 5; i++) {
        SPI_writeDataBlockingNonFIFO(SPIA_BASE, tx[i]);
    }
    SPI_writeDataBlockingNonFIFO(SPIA_BASE, crc & 0xFF);        // CRC LSB
    SPI_writeDataBlockingNonFIFO(SPIA_BASE, (crc >> 8) & 0xFF); // CRC MSB

    // Small delay then pull nCS high
    DEVICE_DELAY_US(2);
    GPIO_writePin(61, 1);
}


// low-level frame sender: header + payload[ ] of length `len`
static void sendFrame(const uint8_t *payload, uint16_t len) {
    uint16_t crc = crc16_ibm((uint8_t*)payload, len);

    // assert CS
    GPIO_writePin(CS_PIN, 0);
    DEVICE_DELAY_US(2);

    uint16_t i;

    // send payload
    for (i = 0; i < len; i++) {
        SPI_writeDataBlockingNonFIFO(SPIA_BASE, payload[i]);
    }
    // send CRC (MSB then LSB)
    SPI_writeDataBlockingNonFIFO(SPIA_BASE, crc & 0xFF);
    SPI_writeDataBlockingNonFIFO(SPIA_BASE, (crc >> 8) & 0xFF);
    

    // deassert CS
    DEVICE_DELAY_US(2);
    GPIO_writePin(CS_PIN, 1);
}

// “stack write” (header = 0xB0)
static void stackWrite(uint16_t regAddr, uint8_t value) {
    uint8_t frame[4] = {
        0xB0,
        (uint8_t)(regAddr >> 8),
        (uint8_t)(regAddr & 0xFF),
        value
    };
    sendFrame(frame, 4);
}

// “broadcast write” (header = 0xD0)
static void broadcastWrite(uint16_t regAddr, uint8_t value) {
    uint8_t frame[4] = {
        0xD0,
        (uint8_t)(regAddr >> 8),
        (uint8_t)(regAddr & 0xFF),
        value
    };
    sendFrame(frame, 4);
}

// “single device write” (header = 0x90)
static void singleDeviceWrite(uint8_t deviceId, uint16_t regAddr, uint8_t value) {
    uint8_t frame[5] = {
        0x90,
        deviceId,
        (uint8_t)(regAddr >> 8),
        (uint8_t)(regAddr & 0xFF),
        value
    };
    sendFrame(frame, 5);
}

// “stack read” (header = 0xA0) — dummy, we ignore the returned byte
static void stackRead(uint16_t regAddr, uint8_t length){ 
    uint8_t frame[4] = { 
        0xA0,
        (uint8_t)(regAddr >> 8), 
        (uint8_t)(regAddr & 0xFF), 
        (uint8_t)(length-1)
    }; 

    sendFrame(frame, sizeof(frame)); 
}

void receiveFrame(uint8_t *buffer, uint16_t length) {
    int i;
    for (i = 0; i < length; i++) {
        while (!SPI_getRxFIFOStatus(SPIA_BASE)); // Wait for data
            buffer[i] = SPI_readDataBlockingNonFIFO(SPIA_BASE);
        
    }
}

// The full auto-addressing sequence:
void autoAddressingSequence(uint8_t numDevices) {
    // 1) Dummy stack writes to 8 OTP_ECC_DATAINx
    int i;
    for (i = 0; i < 8; i++) {
        stackWrite(REG_OTP_ECC_DATAIN1 + i, 0x00);
    }

    // 2) Broadcast write: CONTROL1 = 0x01 (enable auto-address)
    broadcastWrite(REG_CONTROL1, 0x01);

    // 3) Broadcast write DIR0_ADDR = 0,1,2,...,numDevices
    uint8_t addr;
    for (addr = 0; addr <= numDevices; addr++) {
        broadcastWrite(REG_DIR0_ADDR, addr);
    }

    // 4) Broadcast write COMM_CTRL = 0x02 (all as “stack”)
    broadcastWrite(REG_COMM_CTRL, 0x02);

    // 5) Single-device write to the top device (deviceId = numDevices)
    singleDeviceWrite(numDevices, REG_COMM_CTRL, 0x03);

    // 6) Dummy stack reads to OTP_ECC_DATAINx
    for (i = 0; i < 8; i++) {
        stackRead(REG_OTP_ECC_DATAIN1 + i,1);
    }
}

void readCellVoltages(uint8_t numDevices){ 

    // Set used cells to active
    stackWrite(REG_ACTIVE_CELL, 0x0A); // 16 active cell for testing (will change per module) 

    // Set desired run mode (currently continuous) 
    stackWrite(REG_ADC_CTRL_1,0x06);

    // Wait required time delay [192us + (5us x TOTALBOARDS)]
    // TOTALBOARDS = 1 
    DEVICE_DELAY_US(197);

    stackRead(REG_VCELL16_HI,32); 
    stackRead(REG_VCELL16_LO,32);
    
    //uint8_t rawData[NUM_CELLS *2]; 
    //receiveFrame(rawData, sizeof(rawData)); 

    //int i;

    /*
    for (i = 0; i < NUM_CELLS; i++) {
        uint16_t raw = ((uint16_t)rawData[i*2] << 8) | rawData[i*2 + 1]; 
        int16_t signedRaw = (int16_t)raw;
        float voltage_uV = signedRaw * ADC_RESOLUTION_UV;
        cellVoltages[i] = voltage_uV / 1e6f;// Convert to volts
    }
    */

}   

void broadcastWriteReverse(uint16_t regAddr, uint8_t value) {
    uint8_t frame[4] = {
        0xE0,                           // Broadcast write reverse
        (uint8_t)(regAddr >> 8),       // Register address high byte
        (uint8_t)(regAddr & 0xFF),     // Register address low byte
        value                          // Data byte
    };
    sendFrame(frame, sizeof(frame));
}


void reverseAddressing(uint8_t numDevices){
    // Write to BQ79600-Q1, set CONTROL1[DIR_SEL]=1 (CONTROL1=0x80)
    singleDeviceWrite(0x00, REG_CONTROL1 , 0x80);

    //Single Device write to BQ79600-Q1 to set CONTROL1[SEND_WAKE]=1
    singleDeviceWrite(0x00, REG_CONTROL1, 0xA0); 

    // Dummy Write register OTP_ECC_DATA
    int i;
    for (i = 0; i < 8; i++) {
        stackWrite(REG_OTP_ECC_DATAIN1 + i, 0x00);
    }

    // Send a broadcast write reverse command to change direction of stacked devices 
    broadcastWriteReverse(REG_CONTROL1, 0x80); 

    // Broadcast write to set all devices as stack device 
    broadcastWrite(REG_COMM_CTRL, 0x02); 

    // Broadcast wirte to enable auto-addressing
    broadcastWrite(REG_CONTROL1,0x81); 

    // Broadcast write consecutively to DIR1_ADDR
    uint8_t j; 
    for (j = 0; j<4; j++){ 
        broadcastWrite(REG_DIR1_ADDR, j);
    }

    // Broadcast write to set all devices as stack device first 
    broadcastWrite(REG_COMM_CTRL, 0x02); 

    // Single device write, top of stack, confirm stack 
    singleDeviceWrite(numDevices, REG_COMM_CTRL, 0x03);

    // Dummy stack read registers OTP_ECC_DATAIN1

    int k;
    for (k = 0; k < 8; k++) {
        stackRead(REG_OTP_ECC_DATAIN1 + k, 1);
    }
    
}

void main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();

    EINT;
    ERTM;

    while(1)
    {
        wakeupSequence();               // Wakeup tone via GPIO
        DEVICE_DELAY_US(3500);          // Wait 3.5ms
        sendWakePing();                 // Send SPI wake broadcast
        DEVICE_DELAY_US(11600);         // Wait 11.6ms (safe margin for ACTIVE state)
        autoAddressingSequence(3);      // Auto-addressing for 3 devices 
        DEVICE_DELAY_US(1000);          // Delay 1ms 
        readCellVoltages(1);  
        DEVICE_DELAY_US(1000);          // Read Cell Voltage s
        reverseAddressing(3);
        DEVICE_DELAY_US(1000);
    }
}

//
// End File
