.section .text
.global _start
_start:
    la sp,stack_top
    call kernel_main
loop:
    j loop

.global interrupt_trap
interrupt_trap:
    addi sp, sp, -256

    sd x1, 0(sp)
    sd x5, 8(sp)
    sd x6, 16(sp)
    sd x7, 24(sp)
    sd x10, 32(sp)
    sd x11, 40(sp)
    sd x12, 48(sp)
    sd x13, 56(sp)
    sd x14, 64(sp)
    sd x15, 72(sp)
    sd x16, 80(sp)
    sd x17, 88(sp)
    sd x28, 96(sp)
    sd x29, 104(sp)
    sd x30, 112(sp)
    sd x31, 120(sp)

    call interrupt_handler

    ld x1, 0(sp)
    ld x5, 8(sp)
    ld x6, 16(sp)
    ld x7, 24(sp)
    ld x10, 32(sp)
    ld x11, 40(sp)
    ld x12, 48(sp)
    ld x13, 56(sp)
    ld x14, 64(sp)
    ld x15, 72(sp)
    ld x16, 80(sp)
    ld x17, 88(sp)
    ld x28, 96(sp)
    ld x29, 104(sp)
    ld x30, 112(sp)
    ld x31, 120(sp)

    addi sp, sp, 256
    mret