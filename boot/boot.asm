; boot/boot.asm
; Bootloader Multiboot → appelle le kernel C

BITS 32

section .multiboot
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002)

section .text
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    call kernel_main
.hang:
    hlt
    jmp .hang

section .bss
    resb 16384
stack_top:

