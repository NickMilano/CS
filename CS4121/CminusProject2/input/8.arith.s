	.data 
var0:	.word 100
var1:	.word 100
var2:	.word 100
var3:	.word 100
var4:	.word 100
var5:	.word 100
.newl: .asciiz "\n"
	.text 
	.globl main 
main:	nop
	li $s7, 1
	sw $s7, var0
	li $t0, 2
	sw $t0, var1
	li $t1, 3
	sw $t1, var2
	li $t2, 4
	sw $t2, var3
	lw $s0, var0
	li $t3, 7
	add $t4, $s0, $t3
	sw $t4, var4
	lw $s4, var4
	move $a0, $s4
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s3, var3
	li $t5, 5
	sub $t6, $s3, $t5
	sw $t6, var5
	lw $s5, var5
	move $a0, $s5
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s1, var1
	lw $s2, var2
	mult $s1, $s2
	mflo $t5
	lw $s3, var3
	mult $t5, $s3
	mflo $t6
	move $a0, $t6
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s1, var1
	lw $s2, var2
	mult $s1, $s2
	mflo $t5
	lw $s3, var3
	sub $t6, $t5, $s3
	move $a0, $t6
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	lw $s1, var1
	add $t5, $s0, $s1
	lw $s2, var2
	lw $s3, var3
	mult $s2, $s3
	mflo $t5
	add $t6, $t5, $t5
	move $a0, $t6
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s2, var2
	lw $s3, var3
	mult $s2, $s3
	mflo $t5
	lw $s1, var1
	div $t5, $s1
	mflo $t6
	lw $s0, var0
	sub $t6, $t6, $s0
	move $a0, $t6
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	lw $s0, var0
	lw $s1, var1
	add $t5, $s0, $s1
	lw $s2, var2
	lw $s0, var0
	lw $s4, var4
	mult $s0, $s4
	mflo $t5
	add $t5, $s2, $t5
	mult $t5, $t5
	mflo $t6
	lw $s5, var5
	div $t6, $s5
	mflo $t7
	move $a0, $t7
	li $v0, 1
	syscall
	la $a0, .newl
	li $v0, 4
syscall
	li $v0, 10
	syscall
