"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi t0, zero, 0			\n\t"

"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi t2, zero, 0			\n\t"

"loop_reverse:				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"slli t2, t2, 1				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"andi t1, %[b], 1			\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"or t2, t2, t1				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"srli %[b], %[b], 1			\n\t"

"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi t0, t0, 1				\n\t"

"addi %[others_cnt], %[others_cnt], 1	\n\t"
"bne t0, %[m], loop_reverse		\n\t"

"addi %[add_cnt], %[add_cnt], 1		\n\t"
"addi %[b], t2, 0			\n\t"
