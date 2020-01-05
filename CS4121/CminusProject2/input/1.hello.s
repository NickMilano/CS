	.data 
.newl: .asciiz "\n"
.string0: .asciiz "Hello world!"
	.text 
	.globl main 
main:	nop
	la $a0, .string0
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
