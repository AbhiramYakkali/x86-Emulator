bits 32

section .text
global _start

_start:
    mov eax, 0x89ABCDEF
    mov ecx, 0x05
    hlt