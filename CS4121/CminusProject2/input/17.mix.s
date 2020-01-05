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
	lw $s2, var2
	lw $s1, var1
	lw $s3, var3
	add $t2, $s1, $s3
	slt $t3, $s2, $t2
	sw $t3, var4
	lw $s4, var4
	move $a0, $s4
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	lw $s3, var3
	mult $s0, $s3
	mflo $t4
	lw $s1, var1
	lw $s2, var2
	mult $s1, $s2
	mflo $t4
	sgt $t3, $t4, $t4
	move $a0, $t3
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s2, var2
	lw $s3, var3
	mult $s2, $s3
	mflo $t4
	lw $s1, var1
	lw $s2, var2
	add $t3, $s1, $s2
	lw $s3, var3
	add $t3, $t3, $s3
	sgt $t5, $t4, $t3
	move $a0, $t5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s2, var2
	lw $s3, var3
	lw $s1, var1
	sgt $t4, $s3, $s1
	mult $s2, $t4
	mflo $t3
	lw $s2, var2
	add $t5, $t3, $s2
	lw $s3, var3
	add $t6, $t5, $s3
	move $a0, $t6
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
