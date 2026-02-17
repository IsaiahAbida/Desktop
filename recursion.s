# recursion.s
# Fully translated version of the recursion function and main
# from your earlier TPS 2 steps.

.data
prompt:   .asciiz "Please enter a number: "
newline:  .asciiz "\n"

.text
.globl main


recursion:
    addi $sp, $sp, -8      # allocate stack frame
    sw   $ra, 0($sp)       # save return address
    sw   $s0, 4($sp)       # save s0

    move $s0, $a0          # s0 = m

    # if (m == -1) return 3;
    li $t0, -1
    beq $s0, $t0, RET_3

    # else if (m <= -2)
    li $t0, -2
    ble $s0, $t0, NEG_CASE

    # else return recursion(m-3) + m + recursion(m-2);

    # recursion(m - 3)
    addi $a0, $s0, -3
    jal recursion
    move $t1, $v0          # first recursive result

    # recursion(m - 2)
    addi $a0, $s0, -2
    jal recursion
    move $t2, $v0          # second recursive result

    # sum = t1 + m + t2
    add $t3, $t1, $s0
    add $v0, $t3, $t2
    j RECURSION_END


# CASE: m == -1
RET_3:
    li $v0, 3
    j RECURSION_END

# CASE: m <= -2
NEG_CASE:
    # if (m < -2) return 2
    li $t0, -2
    blt $s0, $t0, RET_2

    # else return 1
    li $v0, 1
    j RECURSION_END

RET_2:
    li $v0, 2
    j RECURSION_END


# Restore + Return
RECURSION_END:
    lw   $ra, 0($sp)
    lw   $s0, 4($sp)
    addi $sp, $sp, 8
    jr   $ra


main:

    # print prompt
    li $v0, 4
    la $a0, prompt
    syscall

    # read int
    li $v0, 5
    syscall
    move $s0, $v0          # x

    # call recursion(x)
    move $a0, $s0
    jal recursion

    # print returned value
    li $v0, 1
    move $a0, $v0
    syscall

    # newline
    li $v0, 4
    la $a0, newline
    syscall

    # exit
    li $v0, 10
    syscall


