	.data 
var0:	.word 100
var1:	.word 100
var2:	.word 100
var3:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s5, 1
	sw $s5, var0
	li $s6, 0
	sw $s6, var1
	li $s7, 0
	sw $s7, var2
	li $t0, 1
	sw $t0, var3
	lw $s0, var0
	lw $s1, var1
	or $t1, $s0, $s1
	move $a0, $t1
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	lw $s0, var0
	or $t2, $s0, $s0
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s3, var3
	lw $s2, var2
	or $t2, $s3, $s2
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s2, var2
	lw $s1, var1
	or $t2, $s2, $s1
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
