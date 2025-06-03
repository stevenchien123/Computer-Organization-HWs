"loop_mul_improved:				\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"beq %[arr_size], zero, end_loop_mul_improved	\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"vsetvli t0, %[arr_size], e32			\n\t"

"addi %[lw_cnt], %[lw_cnt], 1			\n\t"
"vle32.v v0, (%[h])				\n\t"

"addi %[lw_cnt], %[lw_cnt], 1			\n\t"
"vle32.v v1, (%[x])				\n\t"

"addi %[fmul_cnt], %[fmul_cnt], 1		\n\t"
"vfmul.vv v2, v0, v1				\n\t"

"addi %[fadd_cnt], %[fadd_cnt], 1		\n\t"
"vfadd.vf v2, v2, %[id]				\n\t"

"addi %[sw_cnt], %[sw_cnt], 1			\n\t"
"vse32.v v2, (%[y])				\n\t"

"addi %[sub_cnt], %[sub_cnt], 1			\n\t"
"sub %[arr_size], %[arr_size], t0		\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"slli t0, t0, 2					\n\t"

"addi %[add_cnt], %[add_cnt], 1			\n\t"
"add %[h], %[h], t0				\n\t"

"addi %[add_cnt], %[add_cnt], 1			\n\t"
"add %[x], %[x], t0				\n\t"

"addi %[add_cnt], %[add_cnt], 1			\n\t"
"add %[y], %[y], t0				\n\t"

"addi %[others_cnt], %[others_cnt], 1		\n\t"
"jal x0, loop_mul_improved			\n\t"

"end_loop_mul_improved:				\n\t"
