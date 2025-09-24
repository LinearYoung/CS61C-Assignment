.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    addi t0 ,x0 ,1
    blt a1 ,t0 ,error
    # Prologue
    addi sp ,sp ,-8
    sw s0 ,0(sp)
    sw s1 ,4(sp)
    
    mv s0 ,a0
    mv s1 ,a1
    
    addi t1 ,x0 ,1   #the current index
    addi t0 ,s0 ,4   #the point
    lw t3 ,0(s0)     #the maxvalue
    addi t4 ,x0 ,0   #the index of maxvalue
loop_start:
    beq t1 ,s1 ,loop_end
    lw t5 ,0(t0)
    bge t3 ,t5 ,loop_continue
    mv t3 ,t5
    mv t4 ,t1
loop_continue:
    addi t1 ,t1 ,1
    addi t0 ,t0 ,4
    j loop_start

loop_end:
    lw s0 ,0(sp)
    lw s1 ,4(sp)
    addi sp ,sp ,8
    mv a0 ,t4
    # Epilogue


    ret
error:
    li a1 ,77
    jal exit2