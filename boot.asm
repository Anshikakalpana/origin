
MBALIGN  equ  1<<0              ; modules ko page-align karo
MEMINFO  equ  1<<1               ; memory map GRUB se maango
MBFLAGS  equ  MBALIGN | MEMINFO  ; dono flags combine karo
MAGIC    equ  0x1BADB002         ; GRUB yahi number dhoondta hai
CHECKSUM equ -(MAGIC + MBFLAGS)  ; in teeno ka sum zero aana chahiye

section .multiboot
align 4
    dd MAGIC
    dd MBFLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384                   ; 16 KB stack reserve karo
stack_top:

section .text
global _start
_start:
    mov esp, stack_top           ; stack pointer ko set karo

    extern kernel_main
    call kernel_main              ; C kernel ko call karo

    cli
.hang:
    hlt
    jmp .hang