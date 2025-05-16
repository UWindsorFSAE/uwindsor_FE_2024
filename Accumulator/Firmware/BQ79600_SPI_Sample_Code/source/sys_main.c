/** @file sys_main.c 
*   @brief Application main file
*   @date July 2020
*   @version 2.0
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
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


/* USER CODE BEGIN (0) */


/*
 * CONNECTIONS BETWEEN BQ79600EVM-030 AND LAUNCHXL2-TMS57012 (TMS570LS1224):
 * See BQ79600EVM-030 User's Guide, section 4.3 "Connecting the BQ79600EVM to TMS570 LaunchPad" for instructions on how to directly plug-in the BQ79600EVM to the MCU LaunchPad
 * **********NOTE: Make sure R8 and R10 are populated, and R7 and R9 are removed from the BQ79600EVM***********
 *
 * RELEVANT MODIFIED FILES:
 * bq79616.h        must change TOTALBOARDS in this file (based on setup) for code to function
 * bq79616.c        contains all relevant functions used in the sample code
 * notification.c   sets UART_RX_RDY and RTI_TIMEOUT when their respective interrupts happen
 * .dil/.hcg        used for generating the basic TMS570LS1224 code files, can be used to make changes to the microcontroller
 */

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "bq79616.h"
#include "bq79600.h"
#include "system.h"
#include "gio.h"
#include "sci.h"
#include "spi.h"
#include "rti.h"
#include "sys_vim.h"
#include <math.h>
#include <stdio.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
int UART_RX_RDY = 0;
int RTI_TIMEOUT = 0;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    //INITIALIZE TMS570LS1224
    systemInit();
    gioInit();
    sciInit();
    spiInit();
    rtiInit();
    sciSetBaudrate(sciREG, 1000000);
    vimInit();
    _enable_IRQ();

    //write 0xFF during read commands, initialize this 0xFF buffer
    memset(FFBuffer, 0xFF, sizeof(FFBuffer));

    //configure SPI behavior
    dataconfig1_t.CS_HOLD = 1;
    dataconfig1_t.WDEL    =  FALSE;

    //VARIABLES
    uint16 response_frame[(128+6)*TOTALBOARDS]; //store 128 bytes + 6 header bytes for each board

    printf("\n\n\nBeginning Program\n");

    //INITIALIZE 600
    //two wakes in case the MCU had nCS and MOSI = 0 at start (which would put the device in shutdown) or in case the device was previously put in shutdown through a shutdown ping
    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //wait tSU(WAKE_SHUT), at least 3.5ms
    SpiWake79600(); //send wake ping to bridge device
    delayus(3500); //tSU(WAKE_SHUT), at least 3.5ms

    //INITIALIZE BQ79616-Q1 STACK
    SpiWriteReg(0, CONTROL1, 0x20, 1, FRMWRT_SGL_W); //send wake tone to stack devices
    delayms(11.6*TOTALBOARDS); //wake tone duration is ~1.6ms per board + 10ms per board for each device to wake up from shutdown = 11.6ms per 616 board.

    //AUTO-ADDRESS
    SpiAutoAddress(); //auto address sequence

    //RESET ANY COMM FAULT CONDITIONS FROM STARTUP
    SpiWriteReg(0, FAULT_RST1, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
    SpiWriteReg(0, FAULT_RST2, 0xFF, 1, FRMWRT_STK_W); //Reset faults on stacked devices
    SpiWriteReg(0, Bridge_FAULT_RST, 0x22, 1, FRMWRT_SGL_W); //Reset FAULT_COMM and FAULT_SYS on bridge device

    //ENABLE BQ79616-Q1 MAIN ADC
    SpiWriteReg(0, ACTIVE_CELL, 0x0A, 1, FRMWRT_STK_W); //set all cells to active
    SpiWriteReg(0, ADC_CTRL1, 0x06, 1, FRMWRT_STK_W);   //continuous run and MAIN_GO
    delayus(5*TOTALBOARDS + 192);                       //5us reclocking per board and 192us for round robin to complete

    //LOOP VARIABLES
    int channel = 0;            //iterators
    int currentBoard = 0;
    do
    {
        channel = 0;
        currentBoard = 0;
        delayus(192+5*TOTALBOARDS);
        SpiReadReg(0, VCELL16_HI+(16-ACTIVECHANNELS)*2, response_frame, ACTIVECHANNELS*2, 0, FRMWRT_STK_R);

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

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
