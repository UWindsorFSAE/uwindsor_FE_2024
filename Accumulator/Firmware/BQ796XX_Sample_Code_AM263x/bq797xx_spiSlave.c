/*
 *  @file bq79616.c
 *
 *  @author Vince Toledo - Texas Instruments Inc.
 *  @date 20-April-2020
 *  @version 1.0
 *  @note Built with CCS for Hercules Version: 8.1.0.00011
 */

/*****************************************************************************
 **
 **  Copyright (c) 2011-2017 Texas Instruments
 **
 ******************************************************************************/

#include "bq796xx_spiSlave.h"
#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include "bq796xx.h"
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/HwiP.h>

#define APP_MCSPI_MSGSIZE                   (1200U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (10U)
#define delayms(x) ClockP_usleep((x)*1000)
#define delayus(x) ClockP_usleep((x))
uint8_t gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint8_t gMcspiRxBuffer[APP_MCSPI_MSGSIZE];
int WriteType = FRMWRT_SGL_W;
int ReadType = FRMWRT_SGL_R;
int PrintEnabled = TRUE;

HwiP_Object         gGpioHwiObject;

static void GPIO_bankIsrFxn(void *args);

extern void Board_gpioInit(void);
extern void Board_gpioDeinit(void);
extern uint32_t Board_getGpioButtonIntrNum(void);
extern uint32_t Board_getGpioButtonSwitchNum(void);
extern void spiRead(uint8_t * cmdBuf, uint8_t cmdSize, uint8_t * rxBuf, uint16_t rxCount);
extern void spiWrite(uint8_t * txBuf, uint16_t count);
void spiRead2(uint8_t * txBuf, uint8_t * rxBuf, uint16_t rxCount);
#define APP_MCSPI_MSGSIZE                   (1200U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (10U)

uint8_t gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint8_t gMcspiRxBuffer[APP_MCSPI_MSGSIZE];
#define TRUE 1
#define FALSE 0

//GLOBAL VARIABLES (use these to avoid stack overflows by creating too many function variables)
//avoid creating variables/arrays in functions, or you will run out of stack space quickly
uint16 response_frame2[(MAXBYTES+6)*TOTALBOARDS]; //response frame to be used by every read
uint16 fault_frame[39*TOTALBOARDS]; //hold fault frame if faults are printed
extern int currentBoard;
extern int currentCell;
extern int bRes;
extern BYTE bReturn;
extern int count;
extern const uint16 crc16_table[256];
BYTE bBuf[8];
uint8 pFrame[64];
static volatile unsigned int delayval = 0; //for delayms and delayus functions
extern int UART_RX_RDY;
extern int RTI_TIMEOUT;
int topFoundBoard = 0;
int baseCommunicating = 0;
int otpPass = 0;
BYTE* currCRC;
uint16 wCRC2 = 0xFFFF;
int crc16_i = 0;

uint8 autoaddr_response_frame[(1+6)*TOTALBOARDS]; //response frame for auto-addressing sequence
int numReads = 0;
int channel = 0;

//SpiWriteFrame
uint8 spiBuf[8];
uint8 spiFrame[64];
int spiPktLen = 0;
uint8 * spiPBuf = spiFrame;
uint16 spiWCRC;

//SpiReadReg
uint16 spiReturn = 0;
int M = 0; //expected total response bytes
int i = 0; //number of groups of 128 bytes
int K = 0; //number of bytes remaining in the last group of 128

//******
//PINGS
//******

spiTransmitData( uint8_t *tx_buf, uint32_t len)
{

      int32_t             status = SystemP_SUCCESS;
      uint32_t            i, j;
      int32_t             transferOK;
      MCSPI_Transaction   spiTransaction;
      uint64_t            startTimeInUSec, elapsedTimeInUsecs;
      uint8_t     test[] =  { 0x90, 0x03, 0x09, 0x20, 0x13, 0x95 };

      Drivers_open();
      Board_driversOpen();

      /* Initiate transfer */
      MCSPI_Transaction_init(&spiTransaction);
      spiTransaction.channel  = gConfigMcspi0ChCfg[0].chNum;
      spiTransaction.dataSize = 8;
      spiTransaction.csDisable = TRUE;
      spiTransaction.count    = len;
      spiTransaction.txBuf    = (void *)tx_buf;
      spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
      spiTransaction.args     = NULL;
      startTimeInUSec = ClockP_getTimeUsec();
      //for(j = 0U; j < APP_MCSPI_TRANSFER_LOOPCOUNT; j++)
      {
          transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
      }

}

void SpiWake79600(void) {
    uint8_t *buf;

    buf = malloc(1400);
    memset(buf, 0, 1400);
    spiWrite(buf, 1400);
    free(buf);
}


void SpiCommClear(void) {
    uint8_t buf = 0;


    spiWrite(&buf, 1);
}

//**********
//END PINGS
//**********

//**********************
//AUTO ADDRESS SEQUENCE
//**********************
void SpiAutoAddress()
{
    //DUMMY WRITE TO SNCHRONIZE ALL DAISY CHAIN DEVICES DLL (IF A DEVICE RESET OCCURED PRIOR TO THIS)
     SpiWriteReg(0, OTP_ECC_DATAIN1, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN2, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN3, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN4, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN5, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN6, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN7, 0X00, 1, FRMWRT_STK_W);
     SpiWriteReg(0, OTP_ECC_DATAIN8, 0X00, 1, FRMWRT_STK_W);

     //ENABLE AUTO ADDRESSING MODE
     SpiWriteReg(0, CONTROL1, 0X01, 1, FRMWRT_ALL_W);

     //SET ADDRESSES FOR EVERY BOARD
     for(currentBoard=0; currentBoard<TOTALBOARDS; currentBoard++)
     {
         SpiWriteReg(0, DIR0_ADDR, currentBoard, 1, FRMWRT_ALL_W);
     }

     //BROADCAST WRITE TO SET ALL DEVICES AS STACK DEVICE
     SpiWriteReg(0, COMM_CTRL, 0x02, 1, FRMWRT_ALL_W);

     //SET THE HIGHEST DEVICE IN THE STACK AS BOTH STACK AND TOP OF STACK
     SpiWriteReg(TOTALBOARDS-1, COMM_CTRL, 0x03, 1, FRMWRT_SGL_W);
     for(currentBoard=0; currentBoard<TOTALBOARDS; currentBoard++)
          {
              SpiReadReg(currentBoard, DIR0_ADDR, autoaddr_response_frame, 1, 0, FRMWRT_SGL_R);
          }
     //SYNCRHONIZE THE DLL WITH A THROW-AWAY READ
     SpiReadReg(0, OTP_ECC_DATAIN1, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN2, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN3, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN4, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN5, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN6, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN7, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);
     SpiReadReg(0, OTP_ECC_DATAIN8, autoaddr_response_frame, 1, 0, FRMWRT_STK_R);

     //OPTIONAL: read back all device addresses


     //OPTIONAL: read register address 0x2001 and verify that the value is 0x14
     SpiReadReg(0, 0x2001, autoaddr_response_frame, 1, 0, FRMWRT_SGL_R);

    return;
}

//**************************
//END AUTO ADDRESS SEQUENCE
//**************************


//************************
//WRITE AND READ FUNCTIONS
//************************
int SpiWriteReg(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType) {
    // device address, register start address, data bytes, data length, write type (single, broadcast, stack)
    bRes = 0;
    memset(spiBuf,0,sizeof(spiBuf));
    while(GPIO_pinRead(GPIO_PUSH_BUTTON_BASE_ADDR, GPIO_PUSH_BUTTON_PIN) == 0) ClockP_usleep(10); //wait until SPI_RDY is ready

    switch (bLen) {
    case 1:
        spiBuf[0] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 1, bWriteType);
        break;
    case 2:
        spiBuf[0] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[1] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 2, bWriteType);
        break;
    case 3:
        spiBuf[0] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[1] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[2] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 3, bWriteType);
        break;
    case 4:
        spiBuf[0] = (dwData & 0x00000000FF000000) >> 24;
        spiBuf[1] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[2] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[3] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 4, bWriteType);
        break;
    case 5:
        spiBuf[0] = (dwData & 0x000000FF00000000) >> 32;
        spiBuf[1] = (dwData & 0x00000000FF000000) >> 24;
        spiBuf[2] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[3] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[4] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 5, bWriteType);
        break;
    case 6:
        spiBuf[0] = (dwData & 0x0000FF0000000000) >> 40;
        spiBuf[1] = (dwData & 0x000000FF00000000) >> 32;
        spiBuf[2] = (dwData & 0x00000000FF000000) >> 24;
        spiBuf[3] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[4] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[5] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 6, bWriteType);
        break;
    case 7:
        spiBuf[0] = (dwData & 0x00FF000000000000) >> 48;
        spiBuf[1] = (dwData & 0x0000FF0000000000) >> 40;
        spiBuf[2] = (dwData & 0x000000FF00000000) >> 32;
        spiBuf[3] = (dwData & 0x00000000FF000000) >> 24;
        spiBuf[4] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[5] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[6] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 7, bWriteType);
        break;
    case 8:
        spiBuf[0] = (dwData & 0xFF00000000000000) >> 56;
        spiBuf[1] = (dwData & 0x00FF000000000000) >> 48;
        spiBuf[2] = (dwData & 0x0000FF0000000000) >> 40;
        spiBuf[3] = (dwData & 0x000000FF00000000) >> 32;
        spiBuf[4] = (dwData & 0x00000000FF000000) >> 24;
        spiBuf[5] = (dwData & 0x0000000000FF0000) >> 16;
        spiBuf[6] = (dwData & 0x000000000000FF00) >> 8;
        spiBuf[7] = dwData & 0x00000000000000FF;
        bRes = SpiWriteFrame(bID, wAddr, spiBuf, 8, bWriteType);
        break;
    default:
        break;
    }
    return bRes;
}


int SpiWriteFrame(uint16 bID, uint16 wAddr, uint8 * pData, uint16 bLen, uint8 bWriteType) {
    spiPktLen = 0;
    spiPBuf = spiFrame;
    memset(spiFrame, 0x7F, sizeof(spiFrame));
    *spiPBuf++ = 0x80 | (bWriteType) | ((bWriteType & 0x10) ? bLen - 0x01 : 0x00); //Only include blen if it is a write; Writes are 0x90, 0xB0, 0xD0
    if (bWriteType == FRMWRT_SGL_R || bWriteType == FRMWRT_SGL_W)
    {
        *spiPBuf++ = (bID & 0x00FF);
    }
    *spiPBuf++ = (wAddr & 0xFF00) >> 8;
    *spiPBuf++ = wAddr & 0x00FF;

    while (bLen--)
        *spiPBuf++ = *pData++;

    spiPktLen = spiPBuf - spiFrame;

    spiWCRC = CRC16(spiFrame, spiPktLen);
    *spiPBuf++ = spiWCRC & 0x00FF;
    *spiPBuf++ = (spiWCRC & 0xFF00) >> 8;
    spiPktLen += 2;

    spiWrite(spiFrame, spiPktLen);

    return spiPktLen;
}

int SpiCommClear2()
{
    spiPktLen = 1;
    spiPBuf = spiFrame;
    uint16 bID = 0;
    uint16 wAddr = 0;
    uint8 * pData = &bID;
    uint16 bLen = 1;

    memset(spiFrame, 0x0, sizeof(spiFrame));
    //*spiPBuf++ = 0x00; //Only include blen if it is a write; Writes are 0x90, 0xB0, 0xD0

    spiWrite(spiFrame, spiPktLen);

    return spiPktLen;
}

uint8 response_frame[(128+6)*TOTALBOARDS]; //store 128 bytes + 6 header bytes for each board
void test2()
{



    memset(response_frame,0,sizeof(response_frame));
    printf("\n\n\nBeginning Program\n");
    printConsole("Hello world");


    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //tSU(WAKE_SHUT), at least 3.5ms


    /*INITIALIZE BQ796XX-Q1*/
    //need 2 wakes as this particular microcontroller outputs RX=0 by default, and so puts devices into hardware reset while the program is being loaded
#if UART_COMM == TRUE
    Wake796XX();
    delayms(12*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board (rounded to 12ms since variable used is an integer)
    Wake796XX();
    delayms(12*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board (rounded to 12ms since variable used is an integer)
#endif

    //delayms(10);
#if IS_79600_BRIDGE == TRUE
    //WriteReg(0, 0x2004, 0x0000,2, FRMWRT_SGL_W);
    delayus(100);
    delayus(100);
#if AUTO_ADDR == FORWARD
    WriteReg(0, 0x309, 0x20, 1, FRMWRT_SGL_W);
#else
    WriteReg(0, 0x309, 0x80, 1, FRMWRT_SGL_W);
    delayus(100);
    WriteReg(0, 0x309, 0xA0, 1, FRMWRT_SGL_W);
#endif
    delayus(50);
    WriteType = FRMWRT_STK_W;
    ReadType = FRMWRT_STK_R;

    delayms(80);

    WriteReg(0, 0xC00, 0x94, 1, FRMWRT_ALL_W);
    WriteReg(0, 0xDFF, 0xA3, 1, FRMWRT_ALL_W);
    WriteReg(0, 0x83E, 0x14, 1, FRMWRT_ALL_W);
    WriteReg(0, 0xDFF, 0x00, 1, FRMWRT_ALL_W);


#if AUTO_ADDR == FORWARD
    AutoAddress();
#else
    ReverseAddressing();
#endif
#endif

    WriteReg(0, 0x2005, 0x0, 1, FRMWRT_SGL_W);
    WriteReg(0, 0x700, 0XA5, 1, FRMWRT_ALL_W);
    delayms(20);
    WriteReg(0, 0x701, 0X20, 1, FRMWRT_ALL_W);

    delayus(4000); //4ms total required after shutdown to wake transition for AFE settling time, this is for top device only
    WriteReg(0, FAULT_MSK2, 0x40, 1, WriteType); //MASK CUST_CRC SO CONFIG CHANGES DON'T FLAG A FAULT

    //VARIABLES
    int i = 0;




#if (GPIO_READ_EN == TRUE)
    // 0x12 = 00 010 010 = GPIO2 + GPIO1 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF1, 0x09, 1, FRMWRT_STK_W); // GPIO_CONF1 = 0x01E
    // 0x12 = 00 010 010 = GPIO4 + GPIO3 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF2, 0x09, 1, FRMWRT_STK_W); // GPIO_CONF2 = 0x01F
    // 0x12 = 00 010 010 = GPIO6 + GPIO5 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF3, 0x09, 1, FRMWRT_STK_W); // GPIO_CONF3 = 0x020
    // 0x12 = 00 010 010 = GPIO8 + GPIO7 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF4, 0x09, 1, FRMWRT_STK_W); // GPIO_CONF4 = 0x021
    // 0x12 = 00 010 010 = GPIO10 + GPIO9 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF5, 0x09, 1, FRMWRT_STK_W); // GPIO_CONF5 = 0x022
    // 0x02 = 00 000 010 = GPIO11 As ADC only input (absolute).
    WriteReg(0, GPIO_CONF6, 0x01, 1, FRMWRT_STK_W); // GPIO_CONF6 = 0x023

#endif
    //**********
    //MAIN LOOP
    //**********
    //set up the main ADC
    //RESET ANY COMM FAULT CONDITIONS FROM STARTUP
        WriteReg(0, FAULT_RST1, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
        WriteReg(0, FAULT_RST2, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
        WriteReg(0, Bridge_FAULT_RST, 0x22, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge device

        //ENABLE BQ79616-Q1 MAIN ADC
        WriteReg(0, ACTIVE_CELL, 0x0A, 1, FRMWRT_STK_W); //set all cells to active
        WriteReg(0, ADC_CTRL1, 0x06, 1, FRMWRT_STK_W);   //continuous run and MAIN_GO
        delayus(5*TOTALBOARDS + 192);                    //5us reclocking per board and 192us for round robin to complete

        //LOOP VARIABLES
        int channel = 0;            //iterators
        int currentBoard = 0;

        do
        {
            channel = 0;
            currentBoard = 0;
            delayus(192+5*TOTALBOARDS);
            ReadReg(0, VCELL16_HI+(16-ACTIVECHANNELS)*2, response_frame, ACTIVECHANNELS*2, 0, FRMWRT_STK_R);

            /*
             * ***********************************************
             * NOTE: SOME COMPUTERS HAVE ISSUES RECEIVING
             * A LARGE AMOUNT OF DATA VIA printf STATEMENTS.
             * THE FOLLOWING PRINTOUT OF THE RESPONSE DATA
             * IS NOT GUARANTEED TO WORK ON ALL SYSTEMS.
             * ***********************************************
            */

            printf("\n"); //start with a newline to add some extra spacing between each loop
            //only read/print the base device's data if there is no bridge device
            for(currentBoard=0; currentBoard<( BRIDGEDEVICE==1 ? TOTALBOARDS-1 : TOTALBOARDS); currentBoard++)
            {
                printf("BOARD %d:\t",TOTALBOARDS-currentBoard-1);
                //print the data from each active channel (2 bytes each channel)
                for(channel=0; channel<(ACTIVECHANNELS*2); channel+=2)
                {
                    int boardByteStart = (ACTIVECHANNELS*2+6)*currentBoard;
                    uint16 rawData = (response_frame[boardByteStart+channel+4] << 8) | response_frame[boardByteStart+channel+5];
                    float cellVoltage = rawData*0.00019073; //rawData*VLSB_ADC
                    printf("%f\t", cellVoltage);
                }
                printf("\n"); //newline per board
            }
        }while(1);
    //**************
    //END MAIN LOOP
    //**************
}
int SpiReadReg(BYTE bID, uint16 wAddr, uint8_t * pData, BYTE bLen, uint32 dwTimeOut, BYTE bWriteType) {
    // device address, register start address, byte frame pointer to store data, data length, read type (single, broadcast, stack)
    uint8 cnt = 0;
    bRes = 0; //total bytes received
    uint8 breakTheLoop = 0;

    while(GPIO_pinRead(GPIO_PUSH_BUTTON_BASE_ADDR, GPIO_PUSH_BUTTON_PIN) == 0) ClockP_usleep(10); //wait until SPI_RDY is ready

    memset ( FFBuffer, 0xFF, sizeof(FFBuffer));
    //send the read request to the 600
    spiReturn = bLen - 1;
    SpiWriteFrame(bID, wAddr, &spiReturn, 1, bWriteType); //send the read request command frame
    delayus(5*TOTALBOARDS); //wait propagation time for each board

    uint16 * movingPointer = pData;

    //prepare the correct number of bytes for the device to read
    if (bWriteType == FRMWRT_SGL_R)
    {
        M = bLen + 6;
    }
    else if (bWriteType == FRMWRT_STK_R)
    {
        M = (bLen + 6) * (TOTALBOARDS - 1);
    }
    else if (bWriteType == FRMWRT_ALL_R)
    {
        M = (bLen + 6) * TOTALBOARDS;
    }
    else
    {
        while(1); //infinite loop to catch error
    }

    //prepare the number of loops of 128-byte reads that need to occur
    i = (int)(M/128);
    //prepare the remainder that is left over after the last full 128-byte read
    K = M - i*128;

    //loop until we've read all data bytes
    while(i>(-1))
    {
        while(GPIO_pinRead(GPIO_PUSH_BUTTON_BASE_ADDR, GPIO_PUSH_BUTTON_PIN) == 0) //ClockP_usleep(10);
        {
            if ( cnt > 15)
            {
                SpiCommClear2();
                breakTheLoop = 1;
                cnt = 0;
                break;
            }
            else
            {
               delayus(100); //wait until SPI_RDY is ready
               cnt++;
            }

        }
        if ( breakTheLoop == 1)
        {
            breakTheLoop = 0;
            break;
        }

        //if there is more than 128 bytes remaining
        if(i>0)
        {
            if (bWriteType == FRMWRT_SGL_R)
            {
                spiRead2(FFBuffer,  movingPointer, 128);
            }
            else if (bWriteType == FRMWRT_STK_R)
            {
                spiRead2(FFBuffer,  movingPointer, 128);
            }
            else if (bWriteType == FRMWRT_ALL_R)
            {
                spiRead2(FFBuffer,  movingPointer, 128);
            }
            movingPointer+=128;
        }

        //else if there is less than 128 bytes remaining
        else
        {
            if (bWriteType == FRMWRT_SGL_R)
            {

                spiRead2(FFBuffer,  movingPointer, K);
                bRes = bLen + 6;
            }
            else if (bWriteType == FRMWRT_STK_R)
            {
                spiRead2(FFBuffer,  movingPointer, K);
                bRes = (bLen + 6) * (TOTALBOARDS - 1);
            }
            else if (bWriteType == FRMWRT_ALL_R)
            {
                spiRead2(FFBuffer,  movingPointer, K);
                bRes = (bLen + 6) * TOTALBOARDS;
            }
        }

        i--; //decrement the number of groups of 128 bytes
    }
    numReads++;
    return bRes;
}


uint32 SpiCRC16(uint16 *pBuf, int nLen)
{
    uint32 wCRC = 0xFFFF;
    int i;

    for (i = 0; i < nLen; i++) {
        wCRC ^= (uint16)(*pBuf++) & 0x00FF;
        wCRC = crc16_table[wCRC & 0x00FF] ^ (wCRC >> 8);
    }

    return wCRC;
}
//****************************
//END WRITE AND READ FUNCTIONS
//****************************

//************************
//MISCELLANEOUS FUNCTIONS
//************************
void SpiDisableTimeout_600_616(void)
{
    //Disable timeout 600
    SpiWriteReg(0, 0x2005, 0x00, 1, FRMWRT_SGL_W);
    //Disable timeout 616
    SpiWriteReg(0, COMM_CTRL, 0x00, 1, FRMWRT_STK_W);
}

float Complement(uint16 rawData, float multiplier)
{
    return -1*(~rawData+1)*multiplier;
}



uint16_t volt2Byte(float volt)
{
    return (uint16_t)~((int16_t)((-volt/0.00019073)-1.0));
}

unsigned printConsole(const char *_format, ...)
{
   char str[128];
   int length = -1, k = 0;

   va_list argList;
   va_start( argList, _format );

   length = vsnprintf(str, sizeof(str), _format, argList);

   va_end( argList );

//   if (length > 0)
//   {
//      for(k=0; k<length; k++)
//      {
//          HetUART1PutChar(str[k]);
//      }
//   }
   //sciSend(scilinREG, length, str);

   return (unsigned)length;
}

//***************************
//END MISCELLANEOUS FUNCTIONS
//***************************

//EOF

