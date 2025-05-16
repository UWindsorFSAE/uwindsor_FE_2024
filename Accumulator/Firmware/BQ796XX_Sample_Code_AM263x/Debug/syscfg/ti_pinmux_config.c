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

/*
 * Auto generated file
 */
#include "ti_drivers_config.h"
#include <drivers/pinmux.h>

static Pinmux_PerCfg_t gPinMuxMainDomainCfg[] = {
            /* GPIO0 pin config */
    /* GPIO24 -> I2C1_SDA (C8) */
    {
        PIN_I2C1_SDA,
        ( PIN_MODE(7) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW | PIN_QUAL_SYNC | PIN_GPIO_R5SS0_0 )
    },

            /* SPI0 pin config */
    /* SPI0_CLK -> SPI0_CLK (A11) */
    {
        PIN_SPI0_CLK,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW )
    },
    /* SPI0_D0 -> SPI0_D0 (C10) */
    {
        PIN_SPI0_D0,
        ( PIN_MODE(0) | PIN_PULL_DOWN | PIN_SLEW_RATE_LOW )
    },
    /* SPI0_D1 -> SPI0_D1 (B11) */
    {
        PIN_SPI0_D1,
        ( PIN_MODE(0) | PIN_PULL_DOWN | PIN_SLEW_RATE_LOW )
    },

            /* SPI0_CS0 pin config */
    /* SPI0_CS0 -> SPI0_CS0 (C11) */
    {
        PIN_SPI0_CS0,
        ( PIN_MODE(0) | PIN_PULL_DISABLE )
    },

            /* UART0 pin config */
    /* UART0_RXD -> UART0_RXD (A7) */
    {
        PIN_UART0_RXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW )
    },
    /* UART0_TXD -> UART0_TXD (A6) */
    {
        PIN_UART0_TXD,
        ( PIN_MODE(0) | PIN_PULL_DISABLE | PIN_SLEW_RATE_LOW )
    },

    {PINMUX_END, PINMUX_END}
};


/*
 * Pinmux
 */
void Pinmux_init(void)
{
    Pinmux_config(gPinMuxMainDomainCfg, PINMUX_DOMAIN_ID_MAIN);
}

