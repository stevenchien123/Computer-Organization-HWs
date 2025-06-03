"addi %[others_cnt], %[others_cnt], 1	\n\t"
"fmv.w.x %[pi], x0			\n\t"

"addi %[add_cnt], %[add_cnt], 2		\n\t"
"addi t1, x0, 0				\n\t"
"addi t2, x0, 1				\n\t"

"loop_pi:				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"bge t1, %[N], end_loop_pi		\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"slli t3, t1, 1				\n\t"

"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi t3, t3, 1				\n\t"

"addi %[others_cnt], %[others_cnt], 2	\n\t"
"fcvt.s.w f1, t3			\n\t"
"fcvt.s.w f2, t2			\n\t"

"addi %[fdiv_cnt], %[fdiv_cnt], 1	\n\t"
"fdiv.s f2, f2, f1			\n\t"

"addi %[fadd_cnt], %[fadd_cnt], 1	\n\t"
"fadd.s %[pi], %[pi], f2		\n\t"

"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi t1, t1, 1				\n\t"

"addi %[sub_cnt], %[sub_cnt], 1		\n\t"
"sub t2, x0, t2				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"jal x0,  loop_pi			\n\t"

"end_loop_pi:				\n\t"
