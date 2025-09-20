.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    addi t1, x0, 1
    beq a0 x0 done
loop :
    mul t1, t1, a0
    addi a0, a0, -1
    bne a0, x0, loop
done :
    add a0, t1, x0
    jr ra