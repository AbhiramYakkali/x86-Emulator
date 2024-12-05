bits 32

section .text
global _start

_start:
    mov [10], ecx
    mov ecx, 10
    hlt