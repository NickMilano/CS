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
	sub $s7, $s5, $s6
	move $a0, $s7
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $t0, 77
	sw $t0, var0
	li $t1, 3
	sw $t1, var2
	li $t2, 4
	sw $t2, var3
	lw $s0, var0
	lw $s2, var2
	sub $t3, $s0, $s2
	lw $s3, var3
	sub $t0, $t3, $s3
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
