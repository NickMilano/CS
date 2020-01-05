	.data 
var0:	.word 100
var1:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s3, 1
	sw $s3, var0
	li $s4, 0
	sw $s4, var1
	lw $s0, var0
	move $a0, $s0
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s1, var1
	sltiu $s5, $s1, 1
	move $a0, $s5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s1, var1
	move $a0, $s1
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	sltiu $s5, $s0, 1
	move $a0, $s5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
