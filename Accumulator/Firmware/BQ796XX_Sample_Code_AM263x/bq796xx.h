/*
 *  @file bq796xx.h
 *
 *  @author Vince Toledo - Texas Instruments Inc.
 *  @date February 2020
 *  @version 1.2
 *  @note Built with CCS for Hercules Version: 8.1.0.00011
 *  @note Built for TMS570LS1224 (LAUNCH XL2)
 */

/*****************************************************************************
**
**  Copyright (c) 2011-2019 Texas Instruments
**
******************************************************************************/


#ifndef BQ796xx_H_
#define BQ796xx_H_


#include "string.h"
#include <stdio.h>
#include <math.h>
#include "bq796xx_spiSlave.h"
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include "bq79631_debug_types.h"
//****************************************************
// ***Register defines, choose one of the following***
// ***based on your device silicon revision:       ***
//****************************************************
//#include "A0_reg.h"
//#include "B0_reg.h"
#include "BQ796XXA0_reg.h"
#define TRUE 1
#define FALSE 0
/* Set SPI_COMM  to 'TRUE' if the communication type used is SPI, for UART keep it 'FALSE' */
#define SPI_COMM      TRUE

/* **** NO NEED TO CHANGE 'UART_COMM', setting the value of 'SPI_COMM' is enough */
#if SPI_COMM == FALSE
#define UART_COMM     FALSE
#else
#define UART_COMM     FALSE
#endif

#define BYTE uint8_t
#define uint16 uint16_t
#define uint64 uint64_t


#define IS_79600_BRIDGE TRUE

#define MAXBYTES (16*2)     //maximum number of bytes to be read from the devices (for array creation)
#define BAUDRATE 1000000    //device + uC baudrate

#if IS_79600_BRIDGE == TRUE
#define TOTALBOARDS 2       //boards in stack
#else
#define TOTALBOARDS 1       //boards in stack
#endif

#define FRMWRT_SGL_R	0x00    //single device READ
#define FRMWRT_SGL_W	0x10    //single device WRITE
#define FRMWRT_STK_R	0x20    //stack READ
#define FRMWRT_STK_W	0x30    //stack WRITE
#define FRMWRT_ALL_R	0x40    //broadcast READ
#define FRMWRT_ALL_W	0x50    //broadcast WRITE
#define FRMWRT_REV_ALL_W 0x60   //broadcast WRITE reverse direction
int WriteRegUART(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType);
int ReadRegUART(BYTE bID, uint16 wAddr, BYTE * pData, BYTE bLen, uint32 dwTimeOut,
        BYTE bWriteType);
#if SPI_COMM == TRUE
#define ReadReg(bID,  wAddr, pData,  bLen,  dwTimeOut, bWriteType) \
                  SpiReadReg(bID, wAddr, pData, bLen, dwTimeOut, bWriteType);
#define WriteReg(bID, wAddr, dwData, bLen, bWriteType) \
                  SpiWriteReg(bID, wAddr, dwData, bLen, bWriteType);
#elif UART_COMM == TRUE
#define ReadReg(bID,  wAddr, pData,  bLen,  dwTimeOut, bWriteType) \
                  ReadRegUART(bID, wAddr, (BYTE *)pData, bLen, dwTimeOut, bWriteType);
#define WriteReg(bID, wAddr, dwData, bLen, bWriteType) \
                  WriteRegUART(bID, wAddr, dwData, bLen, bWriteType);
#endif
                  
// Function Prototypes
void Wake79616();
void AutoAddress();
uint8_t GetFaultStat();

uint16 CRC16(BYTE *pBuf, int nLen);

//int  WriteReg(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType);
//int  ReadReg(BYTE bID, uint16 wAddr, uint16 * pData, BYTE bLen, uint32 dwTimeOut, BYTE bWriteType);

int  WriteFrame(BYTE bID, uint16 wAddr, BYTE * pData, BYTE bLen, BYTE bWriteType);
int  ReadFrameReq(BYTE bID, uint16 wAddr, BYTE bByteToReturn,BYTE bWriteType);
int  WaitRespFrame(BYTE *pFrame, uint32 bLen, uint32 dwTimeOut);

void delayms(uint16 ms);
void delayus(uint16 us);

void ResetAllFaults(BYTE bID, BYTE bWriteType);
void MaskAllFaults(BYTE bID, BYTE bWriteType);

void RunCB();
void ReverseAddressing();

void Wake796XX(void);
#if UART_COMM == TRUE
int ReadDeviceStat2(BYTE *response_frame);
#elif SPI_COMM == TRUE
int ReadDeviceStat2(uint8 *response_frame);
#endif
#if UART_COMM == TRUE
void ReadCoulumbCount(BYTE *response_frame, BYTE rshunt_u8);
#elif SPI_COMM == TRUE
void ReadCoulumbCount(uint8 *response_frame, BYTE rshunt_u8);
#endif
void ConfigureOverCurrent();
void set_SW_CTRL(BYTE pinNum, BYTE value );
void set_GPIO_Out_Val(BYTE gpioNum, uint8_t val);
void set_GPIO_As_PWM(BYTE gpioNum, uint8_t val);



#endif /* BQ79606_H_ */
//EOF
