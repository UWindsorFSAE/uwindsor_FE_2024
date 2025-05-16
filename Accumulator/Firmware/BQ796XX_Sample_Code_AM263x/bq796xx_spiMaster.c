/*
 *  @file bq796xx_spiMaster.c
 *
 *  @author Ravichandra Sereddy - Texas Instruments Inc.
 *  @date April 2022
 *  @version 1.2
 *  @note Built with CCS for Hercules Version: 8.1.0.00011
 *  @note Built for TMS570LS1224 (LAUNCH XL2)
 */

/* 
* Copyright (C) 2022 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "bq796xx.h"
#include "bq796xx_spiMaster.h"

#define SS_GPIO_MIN_NUM  3U
#define SS_GPIO_MAX_NUM  9U
#define SPI_EXE_SS_ADDR_OFFSET   3U
#define SPI_CTRL_CPOL_POS  6U
#define SPI_CTRL_CPHA_POS  5U
#define SPI_CTRL_CPOL    0U
#define SPI_CTRL_CPHA    0U


#if 0
/** @fn void bq796xx_spiMasterInit(BYTE )
*   @brief Initialize the spi master on BQ796xx, select the chip select
*
*   The function selects the polarity and phase for SPI master on BQ796xx device 
*   feature is enabled.
*/

void bq796xx_spiMasterInit(BYTE gpioNumForCS)
{
   BYTE value = 0;

   
   if ( (gpioNumForCS > SS_GPIO_MAX_NUM) || (gpioNumForCS < SS_GPIO_MIN_NUM) )
   {
       printf("Gpio number for slave select is invalid \n");
   }
   else
   {
      value = (0x1U << ( gpioNumForCS - SS_GPIO_MIN_NUM)); /*Set gpioNumForCS as a CS*/
      value |= 0x80U; /* set MSPI_EN to enable master SPI */
      printf("Writing value %x to MSPI_CONF\n", value);
      WriteReg(0, MSPI_CONF, value, 1U, FRMWRT_SGL_W);

      value |= (SPI_CTRL_CPOL << SPI_CTRL_CPOL_POS); /* set CPOL */
      value |= (SPI_CTRL_CPHA << SPI_CTRL_CPHA_POS); /* set CPHA */ 
      value |= 0x3U; /* set number of bits to 8-bit word */
      WriteReg(0, MSPI_CTRL, value, 1U, FRMWRT_SGL_W);

   }
}

/** @fn void bq796xx_spiMasterWrite(BYTE )
*   @brief set the spi master TX registers and initiate data transmission 
*        selects the chip select ( GPIO number ) to use for transmission
*/

void bq796xx_spiMasterWrite(BYTE *data, BYTE numBytes, BYTE gpioNumForCS)
{
    BYTE i = 0;
    BYTE value;
    BYTE ss_addr;
    if ( (NULL == data) || (numBytes > 4U) 
		    || (gpioNumForCS > SS_GPIO_MAX_NUM) || (gpioNumForCS < SS_GPIO_MIN_NUM) )
    {
        printf("spiWrite args invalid \n");
    }
    else
    {
       /* Write data to tx registers */
       for ( i = 0; i < numBytes; i++ )
       {
           WriteReg(0, MSPI_TX1, data[i], 1, FRMWRT_SGL_W);
           /* calculate the ss_addr, which stores the gpio number used for SPI CS */
           ss_addr = gpioNumForCS - SS_GPIO_MIN_NUM + 1U;
           value = 0x03U | ( ss_addr << SPI_EXE_SS_ADDR_OFFSET ); /* set ss_add and 'MSPI_GO' in SPI_EXE */
           printf("Writing value %x to MSPI_EXE\n", value);
           WriteReg(0, MSPI_EXE, value, 1U, FRMWRT_SGL_W);
       }

    }
}

/** @fn void bq796xx_spiMasterWrite(BYTE )
*   @brief initiate data reception and read the spi master RX registers 
*        selects the chip select ( GPIO number ) to use for reception
*/

void bq796xx_spiMasterRead(BYTE *data, BYTE numBytes, BYTE gpioNumForCS)
{
    BYTE i = 0;
    BYTE value;
    BYTE ss_addr;
    if ( (NULL == data) || (numBytes > 4U) 
		    || (gpioNumForCS > SS_GPIO_MAX_NUM) || (gpioNumForCS < SS_GPIO_MIN_NUM) )
    {
        printf("spiRead args invalid \n");
    }
    else
    {
       /* calculate the ss_addr, which stores the gpio number used for SPI CS */
       ss_addr = gpioNumForCS - SS_GPIO_MIN_NUM + 1U;
       value = 0x03U | ( ss_addr << SPI_EXE_SS_ADDR_OFFSET ); /* set ss_add and 'MSPI_GO' in SPI_EXE */
       printf("Writing value %x to MSPI_EXE\n", value);
         
       /* Read data from RX registers */
       for ( i = 0; i < numBytes; i++ )
       {
           WriteReg(0, MSPI_EXE, value, 1U, FRMWRT_SGL_W);
	   delayus(10U);
           ReadReg(0, MSPI_RX1, &data[i], 1, 0, FRMWRT_SGL_R);
	   printf("Read value is %x \n", data[i] );
       }

    }
}
#endif

