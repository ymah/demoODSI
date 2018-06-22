#define __ASSEMBLY__
#include <pip/vidt.h>


.section .text.entry
.global _start
.extern main
.extern Pip_VCLI
_start:
    push %ebx
    call Pip_VCLI
    call main

loop:
    jmp loop



.globl serviceRoutineAsm
.extern vcli
.align 4
serviceRoutineAsm :
    push %ecx
    push %ebx
    push %eax
    .extern serviceRoutine
    call serviceRoutine
