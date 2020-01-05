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
	slt $t2, $s0, $s1
	sw $t2, var4
	lw $s4, var4
	li $t3, 1
	and $t4, $s4, $t3
	move $a0, $t4
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s3, var3
	lw $s2, var2
	sgt $t3, $s3, $s2
	move $a0, $t3
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s3, var3
	lw $s2, var2
	sgt $t3, $s3, $s2
	sltiu $t5, $t3, 1
	move $a0, $t5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $t3, 0
	lw $s0, var0
	lw $s1, var1
	slt $t5, $s0, $s1
	lw $s2, var2
	lw $s3, var3
	sne $t3, $s2, $s3
	and $t6, $t5, $t3
	or $t7, $t3, $t6
	move $a0, $t7
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
