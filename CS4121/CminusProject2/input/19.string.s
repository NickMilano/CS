	.data 
.newl: .asciiz "\n"
.string0: .asciiz "Your grader"
.string1: .asciiz "will put"
.string2: .asciiz "a random"
.string3: .asciiz "string here"
	.text 
	.globl main 
main:	nop
	la $a0, .string0
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	la $a0, .string1
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	la $a0, .string2
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	la $a0, .string3
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
