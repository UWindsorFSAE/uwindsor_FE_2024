/*
 *  @file bq79616.h
 *
 *  @author Vince Toledo - Texas Instruments Inc.
 *  @date 20-April-2020
 *  @version 1.0 beta version
 *  @note Built with CCS for Hercules Version: 8.1.0.00011
 *  @note Built for TMS570LS1224 (LAUNCH XL2)
 */

/*****************************************************************************
**
**  Copyright (c) 2011-2017 Texas Instruments
**
******************************************************************************/


#ifndef BQ79616_H_
#define BQ79616_H_


//****************************************************
// ***Register defines, choose one of the following***
// ***based on your device silicon revision:       ***
//****************************************************
//#include "A0_reg.h"
#include "BQ796XXA0_reg.h"
#include "bq796xx.h"
#include <stdint.h>

//USER DEFINES
// User defines

#define ACTIVECHANNELS 16   //channels to activate
#define BRIDGEDEVICE 1      //
#define MAXBYTES (16*2)     //maximum number of bytes to be read from the devices (for array creation)
#define BAUDRATE 1000000    //device + uC baudrate

#define FRMWRT_SGL_R	0x00    //single device READ
#define FRMWRT_SGL_W	0x10    //single device WRITE
#define FRMWRT_STK_R	0x20    //stack READ
#define FRMWRT_STK_W	0x30    //stack WRITE
#define FRMWRT_ALL_R	0x40    //broadcast READ
#define FRMWRT_ALL_W	0x50    //broadcast WRITE
#define FRMWRT_REV_ALL_W 0x60   //broadcast WRITE reverse direction
#define BYTE uint8_t
#define uint8 uint8_t
#define uint16 uint16_t
#define uint64 uint64_t
#define uint32 uint32_t

//FUNCTION PROTOTYPES
void SpiAutoAddress();

int SpiWriteReg(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType);
int SpiWriteFrame(uint16 bID, uint16 wAddr, uint8 * pData, uint16 bLen, uint8 bWriteType) ;
int SpiReadReg(BYTE bID, uint16 wAddr, uint8_t * pData, BYTE bLen, uint32 dwTimeOut, BYTE bWriteType);

uint32 SpiCRC16(uint16 *pBuf, int nLen);

void delayus(uint16 us);
void delayms(uint16 ms);
void test2();
void SpiDisableTimeout_600_616(void);

float Complement(uint16 rawData, float multiplier);
uint8_t GetFaultStat();
uint16_t volt2Byte(float volt);

unsigned printConsole(const char *_format, ...);

//SPI variables
uint16 FFBuffer[128];

//#include "datatypes.h"
//#include "hal_stdtypes.h"

//BQ79600-Q1 REGISTER DEFINES
#define Bridge_DIAG_CTRL               0x2000
#define Bridge_DEV_CONF1               0X2001
#define Bridge_DEV_CONF2               0X2002
#define Bridge_TX_HOLD_OFF             0X2003
#define Bridge_SLP_TIMEOUT             0X2004
#define Bridge_COMM_TIMEOUT            0X2005
#define Bridge_SPI_FIFO_UNLOCK         0X2010
#define Bridge_FAULT_MSK               0X2020
#define Bridge_FAULT_RST               0X2030
#define Bridge_FAULT_SUMMARY           0X2100
#define Bridge_FAULT_REG               0X2101
#define Bridge_FAULT_SYS               0X2102
#define Bridge_FAULT_PWR               0X2103
#define Bridge_FAULT_COMM1             0X2104
#define Bridge_FAULT_COMM2             0X2105
#define Bridge_DEV_DIAG_STAT           0X2110
#define Bridge_PARTID                  0X2120
#define Bridge_DIE_ID1                 0X2121
#define Bridge_DIE_ID2                 0X2122
#define Bridge_DIE_ID3                 0X2123
#define Bridge_DIE_ID4                 0X2124
#define Bridge_DIE_ID5                 0X2125
#define Bridge_DIE_ID6                 0X2126
#define Bridge_DIE_ID7                 0X2127
#define Bridge_DIE_ID8                 0X2128
#define Bridge_DIE_ID9                 0X2129
#define Bridge_DEBUG_CTRL_UNLOCK       0X2200
#define Bridge_DEBUG_COMM_CTRL         0X2201
#define Bridge_DEBUG_COMM_STAT         0X2300
#define Bridge_DEBUG_SPI_PHY           0X2301
#define Bridge_DEBUG_SPI_FRAME         0X2302
#define Bridge_DEBUG_UART_FRAME        0X2303
#define Bridge_DEBUG_COMH_PHY          0X2304
#define Bridge_DEBUG_COMH_FRAME        0X2305
#define Bridge_DEBUG_COML_PHY          0X2306
#define Bridge_DEBUG_COML_FRAME        0X2307

//FUNCTION PROTOTYPES
void SpiWake79600(void);
void SpiSD79600(void);
void SpiStA79600(void);
void SpiCommClear79600(void);
#endif /* BQ79606_H_ */
//EOF
