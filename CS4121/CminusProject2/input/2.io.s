	.data 
var0:	.word 100
.newl: .asciiz "\n"
.string0: .asciiz "input an integer:"
	.text 
	.globl main 
main:	nop
	la $a0, .string0
	li $v0, 4
syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 5
	syscall
	sw $v0, var0
	lw $s0, var0
	move $a0, $s0
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $s3, 1
	move $a0, $s3
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $s3, 1
	li $s4, 2
	add $s5, $s3, $s4
	move $a0, $s5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
