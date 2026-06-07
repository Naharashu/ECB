section .bss
	x resw 1
section .data
section .text
global _start
_start:
	call main
	mov rdi, rax
	mov rax, 60
	syscall
main:
	mov rax, 30
	add rax, 10
	mov [x], rax
	mov rax, [x]
	ret
