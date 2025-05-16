/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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
 */

/* This example demonstrates the McSPI RX and TX operation configured
 * in blocking, interrupt mode of operation.
 *
 * This example sends a known data in the TX mode of length APP_MCSPI_MSGSIZE
 * and then receives the same in RX mode. Internal pad level loopback mode
 * is enabled to receive data.
 * To enable internal pad level loopback mode, D0 pin is configured to both
 * TX Enable as well as RX input pin in the SYSCFG.
 *
 * When transfer is completed, TX and RX buffer data are compared.
 * If data is matched, test result is passed otherwise failed.
 */

#include <kernel/dpl/DebugP.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"
#include <kernel/dpl/AddrTranslateP.h>
#include <kernel/dpl/HwiP.h>
#include "bq796xx_spiSlave.h"

#define APP_MCSPI_MSGSIZE                   (740U)
#define APP_MCSPI_TRANSFER_LOOPCOUNT        (10U)

uint8_t gMcspiTxBuffer[APP_MCSPI_MSGSIZE];
uint8_t gMcspiRxBuffer[APP_MCSPI_MSGSIZE];

uint32_t            gGpioBaseAddr = GPIO_PUSH_BUTTON_BASE_ADDR;
HwiP_Object         gGpioHwiObject;
volatile uint32_t   gGpioIntrDone = 0;

static void GPIO_bankIsrFxn(void *args);

extern void Board_gpioInit(void);
extern void Board_gpioDeinit(void);
extern uint32_t Board_getGpioButtonIntrNum(void);
extern uint32_t Board_getGpioButtonSwitchNum(void);

void Driver_init()
{
    Drivers_open();
    Board_driversOpen();
}

void Driver_deinit()
{
    Board_driversClose();
    Drivers_close();
}

void spiWrite(uint8_t * txBuf, uint16_t count)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs;

    ClockP_usleep(30);
    /* Initiate transfer */
    MCSPI_Transaction_init(&spiTransaction);
    spiTransaction.channel  = gConfigMcspi0ChCfg[0].chNum;
    spiTransaction.dataSize = 8;
    spiTransaction.csDisable = TRUE;
    spiTransaction.count    = count;
    spiTransaction.txBuf    = (void *)txBuf;
    spiTransaction.rxBuf    = (void *)gMcspiRxBuffer;
    spiTransaction.args     = NULL;
    //startTimeInUSec = ClockP_getTimeUsec();

    transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
    ClockP_usleep(30);

}



void spiRead2(uint8_t * txBuf, uint8_t * rxBuf, uint16_t rxCount)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs;
    uint8_t     test[] = { 0x80, 0x00, 0x03, 0x06, 0x00, 0xD6, 0x7E };// { 0x90, 0x03, 0x09, 0x20, 0x13, 0x95 };


       spiTransaction.channel  = gConfigMcspi0ChCfg[0].chNum;
           spiTransaction.dataSize = 8;
           spiTransaction.csDisable = TRUE;
           spiTransaction.count    = rxCount;
           memset(gMcspiTxBuffer, 0xFF, rxCount);
           spiTransaction.txBuf    = (void *)txBuf;
           spiTransaction.rxBuf    = (void *)rxBuf;
           spiTransaction.args     = NULL;
           startTimeInUSec = ClockP_getTimeUsec();
           transferOK = MCSPI_transfer(gMcspiHandle[CONFIG_MCSPI0], &spiTransaction);
}

void *mcspi_loopback_main(void *args)
{
    int32_t             status = SystemP_SUCCESS;
    uint32_t            i, j;
    int32_t             transferOK;
    MCSPI_Transaction   spiTransaction;
    uint64_t            startTimeInUSec, elapsedTimeInUsecs;
    uint8_t     test[] = { 0x80, 0x00, 0x03, 0x06, 0x00, 0xD6, 0x7E };// { 0x90, 0x03, 0x09, 0x20, 0x13, 0x95 };

    Driver_init();

    gGpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(gGpioBaseAddr);
    /* Setup GPIO for interrupt generation */
    GPIO_setDirMode(gGpioBaseAddr, GPIO_PUSH_BUTTON_PIN, GPIO_PUSH_BUTTON_DIR);

    DebugP_log("[MCSPI] Loopback example started ...\r\n");


    test2();
    spiWrite(gMcspiTxBuffer, APP_MCSPI_MSGSIZE);


    while (1)
        ;

    return NULL;
}



void gpio_input_interrupt_main(void *args)
{
    int32_t         retVal;
    uint32_t        pinNum, intrNum;
    uint32_t        bankNum, waitCount = 5;
    HwiP_Params     hwiPrms;

    /* Open drivers to open the UART driver for console */
    Drivers_open();
    Board_driversOpen();
    Board_gpioInit();

    DebugP_log("GPIO Input Interrupt Test Started ...\r\n");
    DebugP_log("GPIO Interrupt Configured for Rising Edge (Button release will trigger interrupt) ...\r\n");

    pinNum          = GPIO_PUSH_BUTTON_PIN;
    intrNum         = Board_getGpioButtonIntrNum();
    bankNum         = GPIO_GET_BANK_INDEX(pinNum);

    /* Address translate */
    gGpioBaseAddr = (uint32_t) AddrTranslateP_getLocalAddr(gGpioBaseAddr);

    /* Setup GPIO for interrupt generation */
    GPIO_setDirMode(gGpioBaseAddr, pinNum, GPIO_PUSH_BUTTON_DIR);
    GPIO_setTrigType(gGpioBaseAddr, pinNum, GPIO_PUSH_BUTTON_TRIG_TYPE);
    GPIO_bankIntrEnable(gGpioBaseAddr, bankNum);

    /* Register pin interrupt */
    HwiP_Params_init(&hwiPrms);
    hwiPrms.intNum   = intrNum;
    hwiPrms.callback = &GPIO_bankIsrFxn;
    hwiPrms.args     = (void *) pinNum;
    retVal = HwiP_construct(&gGpioHwiObject, &hwiPrms);
    DebugP_assert(retVal == SystemP_SUCCESS );

    DebugP_log("Press and release SW%d button on EVM to trigger GPIO interrupt ...\r\n", Board_getGpioButtonSwitchNum());
    while(gGpioIntrDone < waitCount)
    {
        /* Keep printing the current GPIO value */
        DebugP_log("Key is pressed %d times\r\n", gGpioIntrDone);
        ClockP_sleep(1);
    }
    DebugP_log("Key is pressed %d times\r\n", gGpioIntrDone);

    /* Unregister interrupt */
    GPIO_bankIntrDisable(gGpioBaseAddr, bankNum);
    GPIO_setTrigType(gGpioBaseAddr, pinNum, GPIO_TRIG_TYPE_NONE);
    GPIO_clearIntrStatus(gGpioBaseAddr, pinNum);
    HwiP_destruct(&gGpioHwiObject);

    DebugP_log("GPIO Input Interrupt Test Passed!!\r\n");
    DebugP_log("All tests have passed!!\r\n");

    Board_gpioDeinit();
    Board_driversClose();
    Drivers_close();
}

static void GPIO_bankIsrFxn(void *args)
{
    uint32_t    pinNum = (uint32_t) args;
    uint32_t    bankNum =  GPIO_GET_BANK_INDEX(pinNum);
    uint32_t    intrStatus, pinMask = GPIO_GET_BANK_BIT_MASK(pinNum);

    /* Get and clear bank interrupt status */
    intrStatus = GPIO_getBankIntrStatus(gGpioBaseAddr, bankNum);
    GPIO_clearBankIntrStatus(gGpioBaseAddr, bankNum, intrStatus);

    /* Per pin interrupt handling */
    if(intrStatus & pinMask)
    {
        gGpioIntrDone++;
    }
}

