.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:
    ble a1, x0, m0_invalid_dimensions
    ble a2, x0, m0_invalid_dimensions
    
    ble a4, x0, m1_invalid_dimensions
    ble a5, x0, m1_invalid_dimensions
    
    bne a2, a4, dimensions_mismatch 
    # Error checks
    addi sp, sp, -36
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw ra, 32(sp)
    
    # Prologue
    mv s0, a0    # m0 pointer
    mv s1, a3    # m1 pointer
    mv s2, a6    # d pointer
    mv s3, a1    # height of m0 (rows)
    mv s4, a2    # width of m0 (cols) = height of m1 (rows)
    mv s5, a5    # width of m1 (cols)
    
    li t0, 0    #i = 0 (the row index for m0) 
outer_loop_start:
    beq t0 s3 outer_loop_end    #if the i >= rows of m0, outer_loop end
    li t1, 0    #j = 0(the column index for m1)
inner_loop_start:
    beq t1 s5 inner_loop_end    # if the j >= columns of m1, inner_loop end
    
    mul t2, t0, s4  # calculate m0 + i * width_m0 * 4 and m1 + j * 4
    slli t2, t2, 2
    add a0, s0, t2
    
    slli t3, t1, 2
    add a1, s1, t3

    # Set up arguments for dot
    mv a2, s4         # length = width of m0 = height of m1
    li a3, 1          # stride of m0 = 1 (consecutive elements in row)
    mv a4, s5         # stride of m1 = width of m1 (to move to next element in column)
    
    #Prologue
    addi sp, sp, -12
    sw t0, 0(sp)
    sw t1, 4(sp)
    sw t2, 8(sp)
    
     # Call dot product
    jal ra, dot
    
    # Epilogue
    lw t0, 0(sp)
    lw t1, 4(sp)
    lw t2, 8(sp)
    addi sp, sp, 12
    
    # Store result in d
    # Calculate position: d + (i * width_m1 + j) * 4
    mul t4, t0, s5    # i * width_m1
    add t4, t4, t1    # + j
    slli t4, t4, 2    # * 4 bytes per int
    add t5, s2, t4    # d + offset
    sw a0, 0(t5)      # store result
    
    addi t1, t1, 1    # j++
    j inner_loop_start

inner_loop_end:
     addi t0, t0, 1    # i++
    j outer_loop_start



outer_loop_end:
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw ra, 32(sp)
    addi sp, sp, 36

    # Epilogue
    
    
    ret
m0_invalid_dimensions:
    li a1, 72
    j exit2
m1_invalid_dimensions:
    li a1, 73
    j exit2
dimensions_mismatch:
    li a1, 74
    j exit2