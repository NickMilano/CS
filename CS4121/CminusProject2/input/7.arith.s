	.data 
var0:	.word 100
var1:	.word 100
var2:	.word 100
var3:	.word 100
var4:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s6, 1
	sw $s6, var0
	li $s7, 2
	sw $s7, var1
	li $t0, 3
	sw $t0, var2
	li $t1, 4
	sw $t1, var3
	lw $s0, var0
	lw $s1, var1
	add $t2, $s0, $s1
	lw $s2, var2
	lw $s3, var3
	mult $s2, $s3
	mflo $t3
	add $t4, $t2, $t3
	move $a0, $t4
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	lw $s3, var3
	lw $s0, var0
	sub $t3, $s3, $s0
	lw $s2, var2
	div $t3, $s2
	mflo $t5
	add $t4, $s0, $t5
	lw $s1, var1
	add $t3, $t4, $s1
	move $a0, $t3
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
