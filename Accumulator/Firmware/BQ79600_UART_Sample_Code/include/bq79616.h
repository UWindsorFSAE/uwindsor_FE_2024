/*
 *  @file bq79606.h
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

#include "datatypes.h"
#include "hal_stdtypes.h"

//****************************************************
// ***Register defines, choose one of the following***
// ***based on your device silicon revision:       ***
//****************************************************
//#include "A0_reg.h"
#include "B0_reg.h"

// User defines
#define TOTALBOARDS 2       //boards in stack including bridge device
#define ACTIVECHANNELS 16   //channels to activate (incomplete, does not work right now)
#define BRIDGEDEVICE 1   //
#define MAXBYTES (16*2)     //maximum number of bytes to be read from the devices (for array creation)
#define BAUDRATE 1000000    //device + uC baudrate

#define FRMWRT_SGL_R	0x00    //single device READ
#define FRMWRT_SGL_W	0x10    //single device WRITE
#define FRMWRT_STK_R	0x20    //stack READ
#define FRMWRT_STK_W	0x30    //stack WRITE
#define FRMWRT_ALL_R	0x40    //broadcast READ
#define FRMWRT_ALL_W	0x50    //broadcast WRITE
#define FRMWRT_REV_ALL_W 0x60   //broadcast WRITE reverse direction
                  
// Function Prototypes
void AutoAddress();
BOOL GetFaultStat();
float Complement(uint16 rawData, float multiplier);

uint16 CRC16(BYTE *pBuf, int nLen);

int  WriteReg(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType);
int  ReadReg(BYTE bID, uint16 wAddr, BYTE * pData, BYTE bLen, uint32 dwTimeOut, BYTE bWriteType);

int  WriteFrame(BYTE bID, uint16 wAddr, BYTE * pData, BYTE bLen, BYTE bWriteType);
int  ReadFrameReq(BYTE bID, uint16 wAddr, BYTE bByteToReturn,BYTE bWriteType);

void delayms(uint16 ms);
void delayus(uint16 us);

void DisableTimeout_600_616(void);

unsigned printConsole(const char *_format, ...);

uint16_t volt2Byte(float volt);

#endif /* BQ79606_H_ */
//EOF
