.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:
    addi t0, x0 ,1
    blt a2, t0, error1
    blt a3, t0, error2
    blt a4, t0, error2
    # Prologue
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    
    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3
    mv s4, a4
    
    slli s3, s3, 2
    slli s4, s4, 2
    
    add t0, x0, x0  #the count
    add t1, x0, x0  #the sum
loop_start:
    beq s2, t0, loop_end
    lw t2, 0(s0) #the element of v0
    lw t3, 0(s1) #the element of v1
    add t4, x0, x0
    mul t4, t2, t3
    add t1 t1 t4
    
    addi t0 t0 1
    add s0 s0 s3
    add s1 s1 s4
    j loop_start
loop_end:
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    addi sp, sp, 20
    
    mv a0 t1
    # Epilogue

    
    ret
error1:
    li a1 75
    j exit2
error2:
    li a1 76
    j exit2
    