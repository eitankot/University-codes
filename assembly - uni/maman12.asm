.data
buf: .space 21
buf1: .space 20
EnterAString:  .asciiz "Enter a string:\n"
youWrote:  .asciiz "\nyou wrote:\n"
numberWithSameSign:  .asciiz "\nThe number of identical char in a row is:"
backslashn:  .asciiz "\n"
.text	
.globl main

# Saved temps
# $s1 - The highest sequence of a signed operators
# $s2 - The current sequence of a signed operators
main:
	la $a0,EnterAString #Load and print a string asking for the string
        li $v0,4
        syscall
         
	li $v0,8 #takes the input
        la $a0, buf #load byte space into address
        li $a1, 20 # allot the byte space for string
        move $t0,$a0 #save string to t0
        syscall

        la $a0, buf #reload byte space to primary address
        move $a0,$t0 # primary address = t0 address (load pointer)
        li $v0,4 # print string
        syscall
        
        move $a0,$t0 #save string to a0
	
	move $t1, $zero
	L1: # runs on the loop
	move $t2, $t1
	addi $t1, $t1, 1
	lbu $t3, buf($t1) #$t3 - get the variable in buf[$t1]
	lbu $t4, buf($t2)#$t4 - get the variable in buf[$t2]
	beq $t3, $zero,end #checks if its the end of the word
	beq $t3, 10,end #checks if its the end of the word
	
	blt $t4,$t3 ,minus#checks if t4 is lower than t3.
	beq $t3,$t4,equal#checks if there are equal
	j plus
	
	equal:#sets the temp var to be equal.
 	addi $t8, $zero, 61 
 	j loopContinue
 	
 	plus:#sets the temp var to be plus.
 	addi $t8, $zero, 43
 	j loopContinue
 	
 	minus:#sets the temp var to be minus.
 	addi $t8, $zero, 45
 	j loopContinue
	
	loopContinue:
	sb $t8, buf1($t2)#adds the selected temp var($t8) to buf1.
	beq $t8,$t7,addToSum #checks if before sign and after sign are the same.
	j diffrentSum#if before sign and after sign are not the same.
	

	addToSum:
	addi $s2, $s2, 1 #adds one to the total sum
	blt $s1, $s2, changeSum #checks if the sum is avove the last one
	j L1
	
	diffrentSum:# resets the sum in $s2
	move $t7, $t8
	li $s2, 1
	j L1
	
	changeSum:# changes the sum
	move $s1,$s2
	li  $s6, 1000
	j L1
	
	end:
	
	li $v0, 4 # Print arg
	la $a0, youWrote
	syscall
	li $v0, 4 # Print arg
	la $a0, buf1
	syscall
	li $v0, 4 # Print arg
	la $a0, numberWithSameSign
	syscall
	li $v0, 1 # Print arg
	la $a0, ($s1)
	syscall
	li $v0, 4 # Print arg
	la $a0, backslashn
	syscall
        li $v0,10 #end program
        syscall

 	
 
