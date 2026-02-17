.data
prompt:     .asciiz "Please enter an integer: "
ret1msg:    .asciiz "Returning 1\n"
ret3msg:    .asciiz "Returning 3\n"

.text
main:
    # Print prompt
    la   $a0, prompt
    li   $v0, 4
    syscall

    # Read integer from user
    li   $v0, 5
    syscall
    move $a0, $v0         # argument for recursion(m)

    # Call recursion
    jal  recursion

    # recursion returned value in $v0
    move $t0, $v0         # save return value so syscall can use $a0

    # Print returned integer
    move $a0, $t0
    li   $v0, 1
    syscall

    # Exit program
    li   $v0, 10
    syscall

# recursion(m)
# if m == -1 → print "Returning 1" → return 1
# if m == 0  → print "Returning 3" → return 3
# else return recursion(m-2) + recursion(m-1)

recursion:
    addi $sp, $sp, -12      # reserve 3 words
    sw   $ra, 8($sp)        # store return address
    sw   $a0, 4($sp)        # store original argument m

    # if (m == -1)
    li   $t0, -1
    beq  $a0, $t0, ret_m1

    # if (m == 0)
    beq  $a0, $zero, ret_0

    # else: recursion(m-2) + recursion(m-1)
not_base:
    # First recursive call: recursion(m - 2)
    lw   $a0, 4($sp)        # reload m
    addi $a0, $a0, -2
    jal  recursion
    move $t1, $v0           # save first return value

    # Second recursive call: recursion(m - 1)
    lw   $a0, 4($sp)        # reload m (important!)
    addi $a0, $a0, -1
    jal  recursion
    move $t2, $v0           # save second return value

    # Combine results
    add  $v0, $t1, $t2
    j    end_recur


ret_m1:
    la   $a0, ret1msg
    li   $v0, 4
    syscall

    li   $v0, 1             # return 1
    j    end_recur

ret_0:
    la   $a0, ret3msg
    li   $v0, 4
    syscall

    li   $v0, 3             # return 3
    j    end_recur

end_recur:
    lw   $ra, 8($sp)        # restore return address
    addi $sp, $sp, 12       # pop stack frame
    jr   $ra                # return to caller

