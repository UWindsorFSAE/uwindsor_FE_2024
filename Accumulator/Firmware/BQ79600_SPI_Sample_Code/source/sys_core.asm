;-------------------------------------------------------------------------------
; sys_core.asm
;
; Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com
;
;
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
;
;    Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;
;    Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the
;    distribution.
;
;    Neither the name of Texas Instruments Incorporated nor the names of
;    its contributors may be used to endorse or promote products derived
;    from this software without specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;
;
;

    .text
    .arm

;-------------------------------------------------------------------------------
; Initialize CPU Registers
; SourceId : CORE_SourceId_001
; DesignId : CORE_DesignId_001
; Requirements: HL_SR477, HL_SR476, HL_SR492

    .def     _coreInitRegisters_
    .asmfunc


_coreInitRegisters_


    ; After reset, the CPU is in the Supervisor mode (M = 10011)
        mov r0, lr
        mov r1, #0x0000
        mov r2, #0x0000
        mov r3, #0x0000
        mov r4, #0x0000
        mov r5, #0x0000
        mov r6, #0x0000
        mov r7, #0x0000
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mov r13, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to FIQ mode (M = 10001)
        cps #17
        mov lr, r0
        mov r8, #0x0000
        mov r9, #0x0000
        mov r10, #0x0000
        mov r11, #0x0000
        mov r12, #0x0000
        mrs r1, cpsr
        msr spsr_cxsf, r1
        ; Switch to IRQ mode (M = 10010)
        cps #18
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Abort mode (M = 10111)
        cps #23
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to Undefined Instruction Mode (M = 11011)
        cps #27
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1
        ; Switch to System Mode ( Shares User Mode registers ) (M = 11111)
        cps #31
        mov lr, r0
        mrs r1,cpsr
        msr spsr_cxsf, r1


        mrc   p15,     #0x00,      r2,       c1, c0, #0x02
        orr   r2,      r2,         #0xF00000
        mcr   p15,     #0x00,      r2,       c1, c0, #0x02
        mov   r2,      #0x40000000
        fmxr  fpexc,   r2

        fmdrr d0,         r1,     r1
        fmdrr d1,         r1,     r1
        fmdrr d2,         r1,     r1
        fmdrr d3,         r1,     r1
        fmdrr d4,         r1,     r1
        fmdrr d5,         r1,     r1
        fmdrr d6,         r1,     r1
        fmdrr d7,         r1,     r1
        fmdrr d8,         r1,     r1
        fmdrr d9,         r1,     r1
        fmdrr d10,        r1,     r1
        fmdrr d11,        r1,     r1
        fmdrr d12,        r1,     r1
        fmdrr d13,        r1,     r1
        fmdrr d14,        r1,     r1
        fmdrr d15,        r1,     r1
        bl    next1
next1
        bl    next2
next2
        bl    next3
next3
        bl    next4
next4
        bx    r0

    .endasmfunc


;-------------------------------------------------------------------------------
; Initialize Stack Pointers
; SourceId : CORE_SourceId_002
; DesignId : CORE_DesignId_002
; Requirements: HL_SR478

    .def     _coreInitStackPointer_
    .asmfunc

_coreInitStackPointer_

        cps   #17
        ldr   sp,       fiqSp
        cps   #18
        ldr   sp,       irqSp
        cps   #19
        ldr   sp,       svcSp
        cps   #23
        ldr   sp,       abortSp
        cps   #27
        ldr   sp,       undefSp
        cps   #31
        ldr   sp,       userSp
        bx    lr

userSp  .word 0x08000000+0x00002000
svcSp   .word 0x08000000+0x00002000+0x00000200
fiqSp   .word 0x08000000+0x00002000+0x00000200+0x00000200
irqSp   .word 0x08000000+0x00002000+0x00000200+0x00000200+0x00000200
abortSp .word 0x08000000+0x00002000+0x00000200+0x00000200+0x00000200+0x00000200
undefSp .word 0x08000000+0x00002000+0x00000200+0x00000200+0x00000200+0x00000200+0x00000200

    .endasmfunc

;-------------------------------------------------------------------------------
; Get CPSR Value
; SourceId : CORE_SourceId_003
; DesignId : CORE_DesignId_003
; Requirements:

    .def     _getCPSRValue_
    .asmfunc

_getCPSRValue_

        mrs   r0, CPSR
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Take CPU to IDLE state
; SourceId : CORE_SourceId_004
; DesignId : CORE_DesignId_004
; Requirements: HL_SR493

    .def     _gotoCPUIdle_
    .asmfunc

_gotoCPUIdle_

        WFI
        nop
        nop
        nop
        nop
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable VFP Unit
; SourceId : CORE_SourceId_005
; DesignId : CORE_DesignId_006
; Requirements: HL_SR492, HL_SR476

    .def     _coreEnableVfp_
    .asmfunc

_coreEnableVfp_

        mrc   p15,     #0x00,      r0,       c1, c0, #0x02
        orr   r0,      r0,         #0xF00000
        mcr   p15,     #0x00,      r0,       c1, c0, #0x02
        mov   r0,      #0x40000000
        fmxr  fpexc,   r0
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Enable Event Bus Export
; SourceId : CORE_SourceId_006
; DesignId : CORE_DesignId_007
; Requirements: HL_SR479

    .def     _coreEnableEventBusExport_
    .asmfunc

_coreEnableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        orr   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Event Bus Export
; SourceId : CORE_SourceId_007
; DesignId : CORE_DesignId_008
; Requirements: HL_SR481


    .def     _coreDisableEventBusExport_
    .asmfunc

_coreDisableEventBusExport_

        mrc   p15, #0x00, r0,         c9, c12, #0x00
        bic   r0,  r0,    #0x10
        mcr   p15, #0x00, r0,         c9, c12, #0x00
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable RAM ECC Support
; SourceId : CORE_SourceId_008
; DesignId : CORE_DesignId_009
; Requirements: HL_SR480

    .def     _coreEnableRamEcc_
    .asmfunc

_coreEnableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable RAM ECC Support
; SourceId : CORE_SourceId_009
; DesignId : CORE_DesignId_010
; Requirements: HL_SR482

    .def     _coreDisableRamEcc_
    .asmfunc

_coreDisableRamEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x0C000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Flash ECC Support
; SourceId : CORE_SourceId_010
; DesignId : CORE_DesignId_011
; Requirements: HL_SR480, HL_SR458

    .def     _coreEnableFlashEcc_
    .asmfunc

_coreEnableFlashEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        orr   r0,  r0,    #0x02000000
        dmb
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Disable Flash ECC Support
; SourceId : CORE_SourceId_011
; DesignId : CORE_DesignId_012
; Requirements: HL_SR482

    .def     _coreDisableFlashEcc_
    .asmfunc

_coreDisableFlashEcc_

        mrc   p15, #0x00, r0,         c1, c0,  #0x01
        bic   r0,  r0,    #0x02000000
        mcr   p15, #0x00, r0,         c1, c0,  #0x01
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Enable Offset via Vic controller
; SourceId : CORE_SourceId_012
; DesignId : CORE_DesignId_005
; Requirements: HL_SR483, HL_SR491

    .def     _coreEnableIrqVicOffset_
    .asmfunc

_coreEnableIrqVicOffset_

        mrc   p15, #0, r0,         c1, c0,  #0
        orr   r0,  r0,    #0x01000000
        mcr   p15, #0, r0,         c1, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault status register
; SourceId : CORE_SourceId_013
; DesignId : CORE_DesignId_013
; Requirements: HL_SR495

    .def     _coreGetDataFault_
    .asmfunc

_coreGetDataFault_

        mrc   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault status register
; SourceId : CORE_SourceId_014
; DesignId : CORE_DesignId_014
; Requirements: HL_SR495

    .def     _coreClearDataFault_
    .asmfunc

_coreClearDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault status register
; SourceId : CORE_SourceId_015
; DesignId : CORE_DesignId_015
; Requirements: HL_SR495

    .def     _coreGetInstructionFault_
    .asmfunc

_coreGetInstructionFault_

        mrc   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault status register
; SourceId : CORE_SourceId_016
; DesignId : CORE_DesignId_016
; Requirements: HL_SR495

    .def     _coreClearInstructionFault_
    .asmfunc

_coreClearInstructionFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c0, #1
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get data fault address register
; SourceId : CORE_SourceId_017
; DesignId : CORE_DesignId_017
; Requirements: HL_SR495

    .def     _coreGetDataFaultAddress_
    .asmfunc

_coreGetDataFaultAddress_

        mrc   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear data fault address register
; SourceId : CORE_SourceId_018
; DesignId : CORE_DesignId_018
; Requirements: HL_SR495

    .def     _coreClearDataFaultAddress_
    .asmfunc

_coreClearDataFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0,  #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get instruction fault address register
; SourceId : CORE_SourceId_019
; DesignId : CORE_DesignId_019
; Requirements: HL_SR495

    .def     _coreGetInstructionFaultAddress_
    .asmfunc

_coreGetInstructionFaultAddress_

        mrc   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear instruction fault address register
; SourceId : CORE_SourceId_020
; DesignId : CORE_DesignId_020
; Requirements: HL_SR495

    .def     _coreClearInstructionFaultAddress_
    .asmfunc

_coreClearInstructionFaultAddress_

        mov   r0,  #0
        mcr   p15, #0, r0, c6, c0, #2
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary data fault status register
; SourceId : CORE_SourceId_021
; DesignId : CORE_DesignId_021
; Requirements: HL_SR496

    .def     _coreGetAuxiliaryDataFault_
    .asmfunc

_coreGetAuxiliaryDataFault_

        mrc   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Clear auxiliary data fault status register
; SourceId : CORE_SourceId_022
; DesignId : CORE_DesignId_022
; Requirements: HL_SR496

    .def     _coreClearAuxiliaryDataFault_
    .asmfunc

_coreClearAuxiliaryDataFault_

        mov   r0,  #0
        mcr   p15, #0, r0, c5, c1, #0
        bx    lr

    .endasmfunc


;-------------------------------------------------------------------------------
; Get auxiliary instruction fault status register
; SourceId : CORE_SourceId_023
; DesignId : CORE_DesignId_023
; Requirements: HL_SR496

    .def     _coreGetAuxiliaryInstructionFault_
    .asmfunc

_coreGetAuxiliaryInstructionFault_

        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Clear auxiliary instruction fault status register
; SourceId : CORE_SourceId_024
; DesignId : CORE_DesignId_024
; Requirements: HL_SR496

    .def     _coreClearAuxiliaryInstructionFault_
    .asmfunc

_coreClearAuxiliaryInstructionFault_

        mov   r0,  #0
        mrc   p15, #0, r0, c5, c1, #1
        bx    lr

    .endasmfunc

;-------------------------------------------------------------------------------
; Disable interrupts - R4 IRQ & FIQ
; SourceId : CORE_SourceId_025
; DesignId : CORE_DesignId_025
; Requirements: HL_SR494

        .def _disable_interrupt_
        .asmfunc

_disable_interrupt_

        cpsid if
        bx    lr

        .endasmfunc

;-------------------------------------------------------------------------------
; Disable FIQ interrupt
; SourceId : CORE_SourceId_026
; DesignId : CORE_DesignId_026
; Requirements: HL_SR494

        .def _disable_FIQ_interrupt_
        .asmfunc

_disable_FIQ_interrupt_

        cpsid f
        bx    lr

        .endasmfunc

;-------------------------------------------------------------------------------
; Disable FIQ interrupt

        .def _disable_IRQ_interrupt_
        .asmfunc

_disable_IRQ_interrupt_

        cpsid i
        bx    lr

        .endasmfunc

;-------------------------------------------------------------------------------
; Enable interrupts - R4 IRQ & FIQ

       .def _enable_interrupt_
       .asmfunc

_enable_interrupt_

        cpsie if
        bx    lr

        .endasmfunc


;-------------------------------------------------------------------------------
; Clear ESM CCM errorss

       .def _esmCcmErrorsClear_
       .asmfunc

_esmCcmErrorsClear_

        stmfd sp!, {r0-r2}
        ldr   r0, ESMSR1_REG    ; load the ESMSR1 status register address
        ldr   r2, ESMSR1_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR1 register

        ldr   r0, ESMSR2_REG    ; load the ESMSR2 status register address
        ldr   r2, ESMSR2_ERR_CLR
        str   r2, [r0]         ; clear the ESMSR2 register

        ldr   r0, ESMSSR2_REG    ; load the ESMSSR2 status register address
        ldr   r2, ESMSSR2_ERR_CLR
        str   r2, [r0]             ; clear the ESMSSR2 register

        ldr   r0, ESMKEY_REG    ; load the ESMKEY register address
        mov   r2, #0x5             ; load R2 with 0x5
        str   r2, [r0]             ; clear the ESMKEY register

        ldr   r0, VIM_INTREQ    ; load the INTREQ register address
        ldr   r2, VIM_INT_CLR
        str   r2, [r0]         ; clear the INTREQ register
        ldr   r0, CCMR4_STAT_REG    ; load the CCMR4 status register address
        ldr   r2, CCMR4_ERR_CLR
        str   r2, [r0]         ; clear the CCMR4 status register
        ldmfd sp!, {r0-r2}
        bx    lr

ESMSR1_REG        .word 0xFFFFF518
ESMSR2_REG        .word 0xFFFFF51C
ESMSR3_REG        .word 0xFFFFF520
ESMKEY_REG        .word 0xFFFFF538
ESMSSR2_REG       .word 0xFFFFF53C
CCMR4_STAT_REG    .word 0xFFFFF600
ERR_CLR_WRD       .word 0xFFFFFFFF
CCMR4_ERR_CLR     .word 0x00010000
ESMSR1_ERR_CLR    .word 0x80000000
ESMSR2_ERR_CLR    .word 0x00000004
ESMSSR2_ERR_CLR   .word 0x00000004
VIM_INT_CLR       .word 0x00000001
VIM_INTREQ        .word 0xFFFFFE20

        .endasmfunc

;-------------------------------------------------------------------------------
; Work Around for Errata CORTEX-R4#57:
;
; Errata Description:
;            Conditional VMRS APSR_Nzcv, FPSCR May Evaluate With Incorrect Flags
; Workaround:
;            Disable out-of-order single-precision floating point
;            multiply-accumulate instruction completion

        .def     _errata_CORTEXR4_57_
        .asmfunc

_errata_CORTEXR4_57_

        mrc p15, #0, r0, c15, c0, #0 ; Read Secondary Auxiliary Control Register
        orr r0, r0, #0x10000         ; Set BIT 16 (Set DOOFMACS)
        mcr p15, #0, r0, c15, c0, #0 ; Write Secondary Auxiliary Control Register
        bx lr
    .endasmfunc

;-------------------------------------------------------------------------------
; Work Around for Errata CORTEX-R4#66:
;
; Errata Description:
;            Register Corruption During A Load-Multiple Instruction At
;            an Exception Vector
; Workaround:
;            Disable out-of-order completion for divide instructions in
;            Auxiliary Control register

        .def     _errata_CORTEXR4_66_
        .asmfunc

_errata_CORTEXR4_66_

        mrc p15, #0, r0, c1, c0, #1 ; Read Auxiliary Control register
          orr r0, r0, #0x80           ; Set BIT 7 (Disable out-of-order completion
                                    ; for divide instructions.)
           mcr p15, #0, r0, c1, c0, #1 ; Write Auxiliary Control register
        bx lr
    .endasmfunc
;-------------------------------------------------------------------------------
; C++ construct table pointers

    .def    __TI_PINIT_Base, __TI_PINIT_Limit
    .weak   SHT$$INIT_ARRAY$$Base, SHT$$INIT_ARRAY$$Limit

__TI_PINIT_Base  .long SHT$$INIT_ARRAY$$Base
__TI_PINIT_Limit .long SHT$$INIT_ARRAY$$Limit


    
;-------------------------------------------------------------------------------

