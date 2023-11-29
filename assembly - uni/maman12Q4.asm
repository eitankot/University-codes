.data 
	TheCode: .word 0x00430820, 0xac200040, 0x00601827, 0xac240040, 0x10840000, 0x8c070040, 0xffffffff
	OpcodeCounter: .space 16 # 4 Counters for 4 kinds of insturctions
	RegCounter: .space 128 # 4 bytes * 32 registers
	
	InvalidOpcodeErr: .asciiz "\n warning: invalid opcode in word\n"
	DestIsZero: .asciiz "\n warning: $rd=0 in R-type instruction \n"
	BranchEnsured: .asciiz "\n warning: encountered $rs=$rt case in beq instruction \n"
	TargetIsZero: .asciiz "\n warning: $rt=0 in lw instruction \n"
	
	TableHeader: .asciiz "\nInst code/ Reg \t appearances\n"
	RType: .asciiz "R-Type"
	Beq: .asciiz "beq"
	LW: .asciiz "lw"
	SW: .asciiz "sw"
.text
	# Saved temps
	# $s0 - The offset from address of word
	# $s1 - The current word
	# $s2 - The opcode
	# $s3 - The rs value
	# $s4 - The rt value
	# $s5 - The rd value, if opcode=0
	# $s6 - terminator 0xffffffff
	# $s7 - The "index" in OpcodeCounter to increase
	
	.globl main
	
	main:
	la $s0, TheCode
	addi $s0, $s0, -4
	li $s6, 0xffffffff
	L1:
		addi $s0, $s0, 4
		lw $s1, 0($s0)
		beq $s1, $s6, endloop
		# Processing the word
		move $a0, $s1
		jal getOpcode
		move $s2, $v0
		jal findRegisters
		move $s3, $v0
		move $s4, $v1
		# Increase register counters
		la $a0, RegCounter
		move $a1, $s3
		jal increaseCounter
		move $a1, $s4
		jal increaseCounter
		# check the opcode
		beq $s2, 0, checkRType
		beq $s2, 0x4, checkBeq
		beq $s2, 0x23, checkLW
		beq $s2, 0x2b, checkSW
		# Invalid opcode: Print the error
		li $v0, 4
		la $a0, InvalidOpcodeErr
		syscall
		j L1
	checkRType:
		li $s7, 0 # reseting the index.
		# Continue processing - take rd
		move $a0, $s1
		jal findDst
		move $s5, $v0
		# increase the register counter for rd
		la $a0, RegCounter
		move $a1, $s5
		jal increaseCounter
		# Special case - if rd=0 
		bne $s5, 0, secondLoop
		li $v0, 4
		la $a0, DestIsZero
		syscall
		j secondLoop
	checkBeq:
		li $s7, 1 # seting the index.
		# Special case - rt=rs
		bne $s3, $s4, secondLoop
		li $v0, 4
		la $a0, BranchEnsured
		syscall
		j secondLoop
	checkLW:
		li $s7, 2 # seting the index.
		# Special case - rt=0
		bne $s4, $zero, secondLoop
		li $v0, 4
		la $a0, TargetIsZero
		syscall
		j secondLoop
	checkSW:
		li $s7, 3 # Index to increase later
	secondLoop:
		# Increasing the matching instruction counter
		la $a0, OpcodeCounter
		move $a1, $s7
		jal increaseCounter
		j L1
	
	# this code gets the specific bits that we want.
	# Input:
	# 	$a0 - a 32-bit long word
	# 	$a1 - the minumum bit, 0-31
	# 	$a2 - the maximum bit, 0-31, $a2 >= $a1
	# Output $a0[$a2:$a1]
	getBits:
		li $t0, 31 # The maximum num of the bits
		# Creating a mask
		sub $t1, $a2, $a1 # t1 - (the number of bits-1 )
		sub $t2, $t0, $a2 # t2 - the number of bits that we need to shift right
		li $t3, 0x80000000
		srav $t3, $t3, $t1
		srlv $t3, $t3, $t2
		# using the mask to get the input
		and $t4, $a0, $t3
		srlv $v0, $t4, $a1
		jr $ra
		
	# This function gets returns the bits of the opcode
	# Input:
	# 	$a0 - a 32-bit word
	# Output $a0[31:26]
	getOpcode:
		# get the two sides of the arguments
		li $a1, 26
		li $a2, 31
		# Saves the $ra part to return for the next part.
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		jal getBits
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
	# this code finds the in the raw instruction format the registers rs, rt and gets the opcode
	# Input:
	# 	$a0 - a 32-bit word
	# Output $v0=$a0[25:21], $v1=$a0[20:16]
	findRegisters:
		# gets the arguments
		li $a1, 16
		li $a2, 20
		# Saves the $ra to go back after the jal
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		jal getBits
		add $v1, $zero, $v0
		li $a1, 21
		li $a2, 25
		jal getBits
		# moving back to the main code.
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
	# Take destination register for R-type instructions
	# Input:
	# 	$a0 - a 32-bit word
	# Output $a0[15:11]
	findDst:
		# finds the arguments
		li $a1, 11
		li $a2, 15
		# Saves $ra to go back after the jal
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		jal getBits
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
	# this function Adds 1 to the counter
	# Input:
	#	$a0 - the base code for the instruction format by the bits. 
	# 	$a1 - the index to increase, starting from 0, in words
	increaseCounter:
		# Load current value
		sll $t0, $a1, 2 # t0 = the offset in bytes at the start
		add $t1, $a0, $t0 # t1 = the address of word that we need to increase
		lw $t2, 0($t1)
		addi $t2, $t2, 1
		sw $t2, 0($t1)
		jr $ra
	
	
	endloop:
	# Print results
	li $v0, 4
	la $a0, TableHeader
	syscall
	# Print instructions
	la $s0, OpcodeCounter
	li $a1, 4
	
	la $a0, RType
	lw $a2, 0($s0)
	jal PrintRow
	
	la $a0, Beq
	lw $a2, 4($s0)
	jal PrintRow
	
	la $a0, LW
	lw $a2, 8($s0)
	jal PrintRow
	
	la $a0, SW
	lw $a2, 12($s0)
	jal PrintRow
	
	# Print registers
	li $a1, 1
	la $s0, RegCounter
	li $s1, -1 # Register name
	
	# this code prints all the variables that the program needs to prin.
	# Input:
	# 	$a2 - row result
	# Output:
	#  prints the whole registers and the requsted commands 
	printLoop:
		addi $s1, $s1, 1
		beq $s1, 32, terminate
		sll $t0, $s1, 2 # t0 is the offset
		add $t1, $s0, $t0
		lw $a2, 0($t1)
		beq $a2, $zero, printLoop # do not print row if it has 0 in its variables
		move $a0, $s1
		jal PrintRow
		j printLoop
	
	
	# Print the row in the specific part of the table
	# Input
	# 	$a0 - row title (int/string)
	#	$a1 - row title type (int=1, string=4 just like syscalls)
	# 	$a2 - row result
	# output: v0=11
	PrintRow:
		move $t0, $a0
		li $v0, 11
		li $a0, '\n'
		syscall
		move $v0, $a1
		move $a0, $t0
		syscall
		li $v0, 11
		li $a0, '\t'
		syscall
		li $v0, 1
		move $a0, $a2
		syscall
		jr $ra
	
	terminate:
