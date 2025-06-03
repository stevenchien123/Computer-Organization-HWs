"addi %[add_cnt], %[add_cnt], 1			\n\t"
"addi t0, zero, 1				\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"fcvt.s.w f0, t0				\n\t"

"loop_mul_float:				\n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"beq %[arr_size], zero, end_loop_mul_float	\n\t"

"flw f1, 0(%[h])                                \n\t"
"addi %[flw_cnt], %[flw_cnt], 1                 \n\t"

"flw f2, 0(%[x])                                \n\t"
"addi %[flw_cnt], %[flw_cnt], 1                 \n\t"

"fmul.s f1, f1, f2                              \n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1               \n\t"

"fmul.s f0, f0, f1                              \n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1               \n\t"

"addi %[h], %[h], 4                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[x], %[x], 4                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[arr_size], %[arr_size], -1              \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"jal x0, loop_mul_float                         \n\t"

"end_loop_mul_float:                            \n\t"

"addi %[add_cnt], %[add_cnt], 1			\n\t"
"addi t0, zero, 0				\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"fcvt.s.w f3, t0				\n\t"

"addi %[fadd_cnt], %[fadd_cnt], 1		\n\t"
"fadd.s %[result], f0, f3			\n\t"


