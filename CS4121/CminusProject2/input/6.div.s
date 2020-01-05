	.data 
var0:	.word 100
var1:	.word 100
var2:	.word 100
var3:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s5, 51
	li $s6, 17
	div $s5, $s6
	mflo $s7
	move $a0, $s7
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $t0, 100
	sw $t0, var0
	li $t1, 2
	sw $t1, var2
	li $t2, 5
	sw $t2, var3
	lw $s0, var0
	lw $s2, var2
	div $s0, $s2
	mflo $t3
	lw $s3, var3
	div $t3, $s3
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
