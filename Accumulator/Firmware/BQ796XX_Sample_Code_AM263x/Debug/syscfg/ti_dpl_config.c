/*
 *  Copyright (C) 2022 Texas Instruments Incorporated
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
/*
 * Auto generated file
 */
#include <stdio.h>
#include <drivers/soc.h>
#include <kernel/dpl/AddrTranslateP.h>
#include "ti_dpl_config.h"
#include "ti_drivers_config.h"

/* ----------- HwiP ----------- */
HwiP_Config gHwiConfig = {
    .intcBaseAddr = 0x50F00000u,
};

/* ----------- ClockP ----------- */
#define RTI0_CLOCK_SRC_MUX_ADDR (0x53208114u)
#define RTI0_CLOCK_SRC_WUCPUCLK (0x0u)
#define RTI0_BASE_ADDR     (0x52180000u)

ClockP_Config gClockConfig = {
    .timerBaseAddr = RTI0_BASE_ADDR, 
    .timerHwiIntNum = 84,
    .timerInputClkHz = 25000000,
    .timerInputPreScaler = 1,
    .usecPerTick = 1000,
};

/* ----------- DebugP ----------- */
void putchar_(char character)
{
    /* Output to CCS console */
    putchar(character);
    /* Output to UART console */
    DebugP_uartLogWriterPutChar(character);
}


/* ----------- CacheP ----------- */
const CacheP_Config gCacheConfig = {
    .enable = 1,
    .enableForceWrThru = 0,
};

/* ----------- MpuP_armv7 ----------- */
#define CONFIG_MPU_NUM_REGIONS  (7u)

const MpuP_Config gMpuConfig = {
    .numRegions = CONFIG_MPU_NUM_REGIONS,
    .enableBackgroundRegion = 0,
    .enableMpu = 1,
};

const MpuP_RegionConfig gMpuRegionConfig[CONFIG_MPU_NUM_REGIONS] =
{
    {
        .baseAddr = 0x0u,
        .size = MpuP_RegionSize_2G,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 0,
            .isBufferable = 0,
            .isSharable = 1,
            .isExecuteNever = 1,
            .tex = 0,
            .accessPerm = MpuP_AP_S_RW_U_R,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x0u,
        .size = MpuP_RegionSize_32K,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 1,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 1,
            .accessPerm = MpuP_AP_S_RW_U_R,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x41010000u,
        .size = MpuP_RegionSize_32K,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 1,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 1,
            .accessPerm = MpuP_AP_S_RW_U_R,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x70000000u,
        .size = MpuP_RegionSize_2M,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 1,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 1,
            .accessPerm = MpuP_AP_S_RW_U_R,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x60000000u,
        .size = MpuP_RegionSize_256M,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 1,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 1,
            .accessPerm = MpuP_AP_ALL_R,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x80000000u,
        .size = MpuP_RegionSize_2G,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 1,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 1,
            .accessPerm = MpuP_AP_ALL_RW,
            .subregionDisableMask = 0x0u
        },
    },
    {
        .baseAddr = 0x52200000u,
        .size = MpuP_RegionSize_32K,
        .attrs = {
            .isEnable = 1,
            .isCacheable = 0,
            .isBufferable = 1,
            .isSharable = 0,
            .isExecuteNever = 0,
            .tex = 0,
            .accessPerm = MpuP_AP_ALL_RW,
            .subregionDisableMask = 0x0u
        },
    },
};


#define BOOT_SECTION __attribute__((section(".text.boot")))

/* This function is called by _c_int00 */
void BOOT_SECTION __mpu_init() 
{
    MpuP_init();
    
    CacheP_init();
}

void Dpl_init(void)
{
    /* initialize Hwi but keep interrupts disabled */
    HwiP_init();

    /* init debug log zones early */
    /* Debug log init */
    DebugP_logZoneEnable(DebugP_LOG_ZONE_ERROR);
    DebugP_logZoneEnable(DebugP_LOG_ZONE_WARN);
    /* UART console to use for reading input */
    DebugP_uartSetDrvIndex(CONFIG_UART_CONSOLE);


    /* set timer clock source */
    SOC_controlModuleUnlockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);
    *(volatile uint32_t*)(RTI0_CLOCK_SRC_MUX_ADDR) = RTI0_CLOCK_SRC_WUCPUCLK;
    SOC_controlModuleLockMMR(SOC_DOMAIN_ID_MAIN, MSS_RCM_PARTITION0);
    /* initialize Clock */
    ClockP_init();



    /* Enable interrupt handling */
    HwiP_enable();
}

void Dpl_deinit(void)
{
}
