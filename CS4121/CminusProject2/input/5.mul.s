	.data 
var0:	.word 100
var1:	.word 100
var2:	.word 100
var3:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s5, 10
	li $s6, 20
	mult $s5, $s6
	mflo $s7
	move $a0, $s7
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $t0, 7
	sw $t0, var0
	li $t1, 3
	sw $t1, var2
	li $t2, 4
	sw $t2, var3
	lw $s0, var0
	lw $s2, var2
	mult $s0, $s2
	mflo $t3
	lw $s3, var3
	mult $t3, $s3
	mflo $t0
	sw $t0, var1
	lw $s1, var1
	move $a0, $s1
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
