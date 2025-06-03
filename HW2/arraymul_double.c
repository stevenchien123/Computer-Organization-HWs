"addi %[add_cnt], %[add_cnt], 1         \n\t"
"addi t0, zero, 1               \n\t"

"addi %[others_cnt], %[others_cnt], 1       \n\t"
"fcvt.d.w f0, t0                \n\t"

"loop_mul_float:                \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"beq %[arr_size], zero, end_loop_mul_float  \n\t"

"fld f1, 0(%[h])                                \n\t"
"addi %[dlw_cnt], %[dlw_cnt], 1                 \n\t"

"fld f2, 0(%[x])                                \n\t"
"addi %[dlw_cnt], %[dlw_cnt], 1                 \n\t"

"fmul.d f1, f1, f2                              \n\t"
"addi %[dmul_cnt], %[dmul_cnt], 1               \n\t"

"fmul.d f0, f0, f1                              \n\t"
"addi %[dmul_cnt], %[dmul_cnt], 1               \n\t"

"addi %[h], %[h], 8                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[x], %[x], 8                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[arr_size], %[arr_size], -1              \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"jal x0, loop_mul_float                         \n\t"

"end_loop_mul_float:                            \n\t"

"addi %[add_cnt], %[add_cnt], 1         	\n\t"
"addi t0, zero, 0               		\n\t"

"addi %[others_cnt], %[others_cnt], 1       	\n\t"
"fcvt.d.w f3, t0                		\n\t"

"addi %[dadd_cnt], %[dadd_cnt], 1       	\n\t"
"fadd.d %[result], f0, f3           		\n\t"

