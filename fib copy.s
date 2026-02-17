.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "

.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	la $a0, str0 
	li $v0, 4 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	
	# Your code here to handle invalid number of scores (can't be less than 1 or greater than 25)
read_numScores:          # add this label here
    	move $s0, $v0        # $s0 = numScores
    	blt  $s0, 1, read_numScores   # if numScores < 1 → retry
    	bgt  $s0, 25, read_numScores  # if numScores > 25 → retry
	
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
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

	# SPECIAL CASE: drop == numScores → average = 0, skip recursion
	beq  $t1, $s0, all_dropped

	j drop_ok

invalid_drop:
	# Re-print prompt and read again (NO NEW STRINGS ADDED)
	li $v0, 4
	la $a0, str4       # reuse "Enter number of lowest scores to drop:"
	syscall

	li $v0, 5          # read again
	syscall
	j read_drop

all_dropped:
	# Print "Average = "
	li $v0, 4
	la $a0, str4
	syscall

	# Print 0
	li $a0, 0
	li $v0, 1
	syscall

	j end

drop_ok:
    move $a1, $t1
    sub $a1, $s0, $a1   # remaining count = numScores - drop
    move $a0, $s2
    jal calcSum          # returns sum in $v0

    move $t0, $v0        # save sum
    li $v0, 4
    la $a0, str5
    syscall

    move $a0, $t0        # sum
    move $a1, $a1        # remaining count
    div $a0, $a1
    mflo $a0
    li $v0, 1
    syscall

    j end
	
	# Your code here to compute average and print it (you may also end up having some code here to help 
	# handle the case when number of (lowest) scores to drop equals the number of scores
	
end:	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
    addi $sp, $sp, -8
    sw   $ra, 4($sp)
    sw   $s0, 0($sp)

    move $s0, $zero      # i = 0

print_loop:
    beq  $s0, $a1, print_done   # if i == count → done

    sll  $t0, $s0, 2            # t0 = i * 4
    add  $t0, $t0, $a0          # t0 = base + i*4
    lw   $t1, 0($t0)            # t1 = array[i]

    # Print value using $t1 (do NOT modify $a0)
    move $a0, $t1
    li   $v0, 1
    syscall

    # Print space
    li   $v0, 11
    li   $a0, 32
    syscall

    addi $s0, $s0, 1
    j    print_loop

print_done:
    # Print newline
    li $v0, 11
    li $a0, 10
    syscall

    lw   $s0, 0($sp)
    lw   $ra, 4($sp)
    addi $sp, $sp, 8
    jr $ra

	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Your implementation of selSort here
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $s0, 4($sp)
    sw   $s3, 0($sp)

    move $s0, $a0        # s0 = n
    move $s3, $zero      # s3 = i (outer loop index)
copy_loop:
    beq  $s3, $s0, sort_outer   # if i == n → go to sort

    sll  $t0, $s3, 2            # t0 = i*4
    add  $t1, $s1, $t0          # &orig[i]
    lw   $t2, 0($t1)            # t2 = orig[i]

    add  $t3, $s2, $t0          # &sorted[i]
    sw   $t2, 0($t3)

    addi $s3, $s3, 1
    j    copy_loop
sort_outer:
    move $s3, $zero             # i = 0

outer_loop:
    beq  $s3, $s0, sel_done     # if i == n → done

    move $t4, $s3               # minIndex = i

    addi $t5, $s3, 1            # j = i+1

inner_loop:
    beq  $t5, $s0, inner_done   # if j == n → done inner loop

    # Load sorted[j]
    sll  $t0, $t5, 2
    add  $t1, $s2, $t0
    lw   $t6, 0($t1)

    # Load sorted[minIndex]
    sll  $t0, $t4, 2
    add  $t1, $s2, $t0
    lw   $t7, 0($t1)

    # if sorted[j] < sorted[minIndex] → minIndex = j
    slt  $t8, $t6, $t7
    beq  $t8, $zero, no_change
    move $t4, $t5              # minIndex = j

no_change:
    addi $t5, $t5, 1
    j    inner_loop

inner_done:
    # Swap sorted[i] and sorted[minIndex] if needed
    bne  $t4, $s3, do_swap
    j    skip_swap

do_swap:
    # Load sorted[i]
    sll  $t0, $s3, 2
    add  $t1, $s2, $t0
    lw   $t6, 0($t1)

    # Load sorted[minIndex]
    sll  $t0, $t4, 2
    add  $t2, $s2, $t0
    lw   $t7, 0($t2)

    # Swap
    sw   $t7, 0($t1)           # sorted[i] = sorted[minIndex]
    sw   $t6, 0($t2)           # sorted[minIndex] = sorted[i]

skip_swap:
    addi $s3, $s3, 1
    j    outer_loop

sel_done:
    lw   $s3, 0($sp)
    lw   $s0, 4($sp)
    lw   $ra, 8($sp)
    addi $sp, $sp, 12
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
    addi $sp, $sp, -12
    sw   $ra, 8($sp)
    sw   $a0, 4($sp)       # save array pointer
    sw   $a1, 0($sp)       # save original length

    blez $a1, calc_done     # if len <= 0, return 0
    li   $v0, 0
    beq  $a1, $zero, calc_done

    # Recursive case
    addi $a1, $a1, -1       # len - 1
    jal  calcSum             # sum of arr[0..len-2]

    # After returning, add arr[len-1]
    lw   $t0, 4($sp)        # restore array pointer
    lw   $t1, 0($sp)        # restore original length
    addi $t1, $t1, -1       # offset = len-1
    sll  $t1, $t1, 2
    add  $t2, $t0, $t1
    lw   $t3, 0($t2)
    add  $v0, $v0, $t3

calc_done:
    lw   $a0, 4($sp)
    lw   $a1, 0($sp)
    lw   $ra, 8($sp)
    addi $sp, $sp, 12
	jr $ra
	
