"addi %[others_cnt], %[others_cnt], 1   \n\t"
"beq %[N], zero, end_zero_log2      	\n\t"

"addi %[add_cnt], %[add_cnt], 1     	\n\t"
"addi t0, zero, 0           		\n\t"

"loop_log2:             		\n\t"

"addi %[add_cnt], %[add_cnt], 1     	\n\t"
"addi t0, t0, 1             		\n\t"

"addi %[others_cnt], %[others_cnt], 1   \n\t"
"srl %[N], %[N], 1          		\n\t"

"addi %[others_cnt], %[others_cnt], 1   \n\t"
"bne %[N], zero, loop_log2      	\n\t"

"addi %[add_cnt], %[add_cnt], 1     	\n\t"
"addi %[log], t0, -1            	\n\t"

"addi %[others_cnt], %[others_cnt], 1   \n\t"
"jal x0, end_loop_log2            	\n\t"

"end_zero_log2:             		\n\t"

"addi %[add_cnt], %[add_cnt], 1     	\n\t"
"addi %[log], zero, 0           	\n\t"

"end_loop_log2:             		\n\t"
