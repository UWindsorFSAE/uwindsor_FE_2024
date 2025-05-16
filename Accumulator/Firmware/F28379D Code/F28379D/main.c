#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "gpio.h"
#include "pin_map.h"
#include "spi.h"
#include "sysctl.h"

#define CPU_FREQ_MHZ 200U
#define DELAY_US(x) SysCtl_delay(((CPU_FREQ_MHZ) * (x)) / 3U)


// CRC Check Function

uint16_t crc16_ibm(uint8_t *data, uint16_t len){
    uint16_t crc = 0x0000; 
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


//
// Main
//
void main(void)
{
    
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();

    EINT;
    ERTM;


    while (1)
    {
        wakeupSequence();
    }
}

//
// End File
//
