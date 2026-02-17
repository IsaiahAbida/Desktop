.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
str6: .asciiz "All scores dropped!"

.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores to drop removed.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	la $a0, str0 
	li $v0, 4 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	
	# Your code here to handle invalid number of scores (can't be less than 1 or greater than 25)
read_numScores:
    move $s0, $v0        # $s0 = numScores (tentative)
    blt  $s0, 1, read_retry   # if numScores < 1 → retry
    bgt  $s0, 25, read_retry  # if numScores > 25 → retry
    # valid, continue
    j read_scores

read_retry:
    la $a0, str0
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    j read_numScores

read_scores:
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig base address
	la $s2, sorted	# $s2 = sorted base address
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	move $a1, $s0
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	
	# Your code here to handle invalid number of (lowest) scores to drop (can't be less than 0, or 
	# greater than the number of scores). Also, handle the case when number of (lowest) scores to drop 
	# equals the number of scores. 
read_drop:
    move $t1, $v0       # t1 = drop value

    # INVALID: drop < 0
    bltz $t1, invalid_drop

    # INVALID: drop > numScores
    bgt  $t1, $s0, invalid_drop

    # SPECIAL CASE: drop == numScores → all dropped
    beq  $t1, $s0, all_dropped

    # valid: compute remaining count and call calcSum
    j drop_ok

invalid_drop:
    # Re-print prompt and read again (NO NEW STRINGS ADDED)
    li $v0, 4
    la $a0, str4
    syscall

    li $v0, 5          # read again
    syscall
    j read_drop

all_dropped:
    li $v0, 4
    la $a0, str6
    syscall
    j end

drop_ok:
    move $a1, $t1
    sub $a1, $s0, $a1	# a1 = numScores - drop (remaining count)
    move $a0, $s2      # a0 = sorted array base
    jal calcSum	# returns sum in $v0

    move $t0, $v0      # save sum in t0
    move $t1, $a1      # remaining count in t1

    li $v0, 4
    la $a0, str5
    syscall

    # integer division sum / remaining_count
    move $a0, $t0
    move $a1, $t1
    div $a0, $a1
    mflo $a0
    li $v0, 1
    syscall

    # newline
    li $v0, 11
    li $a0, 10
    syscall

end:	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
    # preserve ra if needed and any saved regs we use
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $s0, 0($sp)

    move $t0, $zero    # index = 0
    move $t2, $a0      # copy base address to t2 (do not overwrite $a0)

print_loop:
    beq  $t0, $a1, print_done   # if index == count → done

    sll  $t1, $t0, 2           # offset = index * 4
    add  $t3, $t1, $t2         # addr = base + offset
    lw   $t4, 0($t3)           # value = array[index]

    # print integer in t4
    move $a0, $t4
    li   $v0, 1
    syscall

    # print space
    li   $v0, 11
    li   $a0, 32
    syscall

    addi $t0, $t0, 1
    j    print_loop

print_done:
    # final newline
    li   $v0, 11
    li   $a0, 10
    syscall

    lw   $s0, 0($sp)
    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
# selSort($a0 = length)
selSort:
    # preserve stack and callee-saved registers we'll use
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $s0, 4($sp)
    sw   $s3, 0($sp)

    move $t0, $zero    # i = 0
    move $t2, $s1      # orig base
    move $t3, $s2      # sorted base

# copy orig -> sorted
copyloop:
    beq $t0, $a0, copy_done
    sll $t1, $t0, 2
    add $t4, $t1, $t2
    add $t5, $t1, $t3
    lw $t6, 0($t4)
    sw $t6, 0($t5)
    addi $t0, $t0, 1
    j copyloop

copy_done:
    # selection sort descending on sorted[]
    move $t0, $zero    # i = 0
    move $t2, $a0      # len in t2
    move $t3, $s2      # sorted base

outerLoop:
    sub  $t4, $t2, 1
    bge  $t0, $t4, doneSort   # if i >= len-1 -> done
    move $t1, $t0             # maxIndex = i

    addi $t4, $t0, 1          # j = i+1

innerLoop:
    bge $t4, $t2, endInner    # if j >= len -> end inner

    # sorted[j]
    sll $t5, $t4, 2
    add $t5, $t5, $t3
    lw $t5, 0($t5)

    # sorted[maxIndex]
    sll $t6, $t1, 2
    add $t6, $t6, $t3
    lw $t6, 0($t6)

    bgt $t5, $t6, setNewMax
    addi $t4, $t4, 1
    j innerLoop

setNewMax:
    move $t1, $t4
    addi $t4, $t4, 1
    j innerLoop

endInner:
    # swap sorted[i] and sorted[maxIndex]
    sll $t7, $t1, 2
    add $t7, $t7, $t3
    lw $t4, 0($t7)     # sorted[maxIndex]

    sll $t6, $t0, 2
    add $t6, $t6, $t3
    lw $t5, 0($t6)     # sorted[i]

    sw $t5, 0($t7)
    sw $t4, 0($t6)

    addi $t0, $t0, 1
    j outerLoop

doneSort:
    lw   $s3, 0($sp)
    lw   $s0, 4($sp)
    lw   $ra, 8($sp)
    addi $sp, $sp, 12
    jr $ra
	
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
    addi $sp, $sp, -8      
    sw $ra, 0($sp)
    sw $a1, 4($sp)      

    # Base case if len <= 0 -> return 0
    ble $a1, $zero, baseCase

    # recursion: calcSum(arr, len-1)
    addi $a1, $a1, -1
    jal calcSum

    # after return, restore original len from stack
    lw $t0, 4($sp)        # original len
    sll $t1, $t0, 2       # t1 = len * 4
    sub $t1, $t1, 4       # t1 = (len-1) * 4
    add $t1, $a0, $t1     # address of arr[len - 1]
    lw $t2, 0($t1)        # t2 = arr[len - 1]

    add $v0, $v0, $t2     # result += arr[len-1]
    b end_calcSum

baseCase:
    li $v0, 0           	# return 0

end_calcSum:
    lw $ra, 0($sp)       	
    lw $a1, 4($sp)
    addi $sp, $sp, 8      	# clean up stack
    jr $ra              	# return

newMaxIndex:
	move $t1, $t4 		# maxIndex = j
	j innerLoop

allDrop:
	li $v0, 4 
	la $a0, str6 
	syscall
	j end
