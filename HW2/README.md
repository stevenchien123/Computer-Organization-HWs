# **HW2 Performance Modeling**
## **25/04/17**
* Download HW2 file from firefox.

## **25/04/22**
```C=
// complex_add
"fadd %[C_Re], %[A_Re], %[B_Re]         \n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1       \n\t"
"fadd %[C_Im], %[A_Im], %[B_Im]         \n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1       \n\t"
```
```C=
// complex_sub
"fsub %[C_Re], %[A_Re], %[B_Re]         \n\t"
"addi %[fsub_cnt], %[fsub_cnt], 1       \n\t"
"fsub %[C_Im], %[A_Im], %[B_Im]         \n\t"
"addi %[fsub_cnt], %[fsub_cnt], 1       \n\t"
```
```C=
// complex_mul
"fmul f1, %[A_Re], %[B_Re]      \n\t"
"addi fmul_cnt, fsub_cnt, 1     \n\t"
"fmul f2, %[A_Im], %[B_Im]      \n\t"
"addi fmul_cnt, fsub_cnt, 1     \n\t"
"fmul f3, %[A_Re], %[B_Im]      \n\t"
"addi fmul_cnt, fsub_cnt, 1     \n\t"
"fmul f4, %[A_Im], %[B_Re]      \n\t"
"addi fmul_cnt, fsub_cnt, 1     \n\t"
"fsub f1, f1, f2                \n\t"
"addi fsub_cnt, fsub_cnt, 1     \n\t"
"fadd f3, f3, f4                \n\t"
"addi fadd_cnt, fsub_cnt, 1     \n\t"
"fadd %[C_Re], %[C_Re], f1      \n\t"
"addi fadd_cnt, fsub_cnt, 1     \n\t"
"fadd %[C_Im], %[C_Im], f3      \n\t"
"addi fadd_cnt, fsub_cnt, 1     \n\t"
```
* Finish functions: complex_add, complex_sub, complex_mul.

## **25/04/26**
```C=
// log2
"beq %[N], zero, end_z			        \n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi t0, zero, zero			        \n\t"
"addi %[add_cnt], %[add_cnt], 1		    \n\t"

"loop:					                \n\t"

"addi t0, t0, 1				            \n\t"
"addi %[add_cnt], %[add_cnt], 1		    \n\t"

"srl %[N], %[N], 1			            \n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"bne %[N], zero, loop			        \n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi %[log], t0, -1			        \n\t"
"addi %[add_cnt], %[add_cnt], 1		    \n\t"

"j end_loop					            \n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"end_z:					                \n\t"

"addi %[log], zero, 0			        \n\t"
"addi %[add_cnt], %[add_cnt], 1		    \n\t"

"end_loop:				                \n\t"
```
```C=
// pi
"fmv.s.x %[pi], x0                      \n\t"
"addi %[others_cnt], %[others_cnt], 1   \n\t"

"addi t1, x0, 0                         \n\t"
"addi t2, x0, 1                         \n\t"
"addi %[add_cnt], %[add_cnt], 2         \n\t"

"loop:                                  \n\t"

"bge t1, %[N], end_loop                 \n\t"
"slli t3, t1, 1                         \n\t"
"addi %[others_cnt], %[others_cnt], 2   \n\t"

"addi t3, t3, 1                         \n\t"
"addi %[add_cnt], %[add_cnt], 1         \n\t"

"fcvt.s.x f1, t3                        \n\t"
"fcvt.s.x f2, t2                        \n\t"
"addi %[others_cnt], %[others_cnt], 2   \n\t"

"fdiv.s f2, f2, f1                      \n\t"
"addi %[fdiv_cnt], %[fdiv_cnt], 1       \n\t"

"fadd.s %[pi], %[pi], f2                \n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1       \n\t"

"addi t1, t1, 1                         \n\t"
"addi %[add_cnt], %[add_cnt], 1         \n\t"

"sub t2, x0, t2                         \n\t"
"addi %[sub_cnt], %[sub_cnt], 1         \n\t"

"j loop                                 \n\t"
"addi %[others_cnt], %[others_cnt], 1   \n\t"

"end_loop:                              \n\t"
```
* Finish functions: log2, pi.

## **25/04/27**
```C=
// complex_add
"fadd.s %[C_Re], %[A_Re], %[B_Re]	\n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1	\n\t"

"fadd.s %[C_Im], %[A_Im], %[B_Im]	\n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1	\n\t"
```
```C=
// complex_sub
"fsub.s %[C_Re], %[A_Re], %[B_Re]	\n\t"
"addi %[fsub_cnt], %[fsub_cnt], 1	\n\t"

"fsub.s %[C_Im], %[A_Im], %[B_Im]	\n\t"
"addi %[fsub_cnt], %[fsub_cnt], 1	\n\t"
```
```C=
// complex_mul
"fmul.s f1, %[A_Re], %[B_Re]		\n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1	\n\t"

"fmul.s f2, %[A_Im], %[B_Im]		\n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1	\n\t"

"fmul.s f3, %[A_Re], %[B_Im]		\n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1	\n\t"

"fmul.s f4, %[A_Im], %[B_Re]		\n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1	\n\t"

"fsub.s %[C_Re], f1, f2			\n\t"
"addi %[fsub_cnt], %[fsub_cnt], 1	\n\t"

"fadd.s %[C_Im], f3, f4			\n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1	\n\t"
```
```C=
// Log2
"beq %[N], zero, end_zero_log2		\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi t0, zero, 0			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"loop_log2:				\n\t"

"addi t0, t0, 1				\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"srl %[N], %[N], 1			\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"bne %[N], zero, loop_log2		\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi %[log], t0, -1			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"j end_loop_log2			\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"end_zero_log2:				\n\t"

"addi %[log], zero, 0			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"end_loop_log2:				\n\t"
```
```C=
// PI
"fmv.w.x %[pi], x0			\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi t1, x0, 0				\n\t"
"addi t2, x0, 1				\n\t"
"addi %[add_cnt], %[add_cnt], 2		\n\t"

"loop_pi:				\n\t"

"bge t1, %[N], end_loop_pi		\n\t"
"slli t3, t1, 1				\n\t"
"addi %[others_cnt], %[others_cnt], 2	\n\t"

"addi t3, t3, 1				\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"fcvt.s.w f1, t3			\n\t"
"fcvt.s.w f2, t2			\n\t"
"addi %[others_cnt], %[others_cnt], 2	\n\t"

"fdiv.s f2, f2, f1			\n\t"
"addi %[fdiv_cnt], %[fdiv_cnt], 1	\n\t"

"fadd.s %[pi], %[pi], f2		\n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1	\n\t"

"addi t1, t1, 1				\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"sub t2, x0, t2				\n\t"
"addi %[sub_cnt], %[sub_cnt], 1		\n\t"

"j loop_pi				\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"end_loop_pi:				\n\t"
```
```C=
// bit_reverse
"addi t0, zero, 0			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"addi t2, zero, 0			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"loop_reverse:				\n\t"

"slli t2, t2, 1				\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"andi t1, %[b], 1			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"or t2, t2, t1				\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"srli %[b], %[b], 1			\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi t0, t0, 1				\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"

"bne t0, %[m], loop_reverse		\n\t"
"addi %[others_cnt], %[others_cnt], 1	\n\t"

"addi %[b], t2, 0			\n\t"
"addi %[add_cnt], %[add_cnt], 1		\n\t"
```
* Fix some bugs for each function.
* Label cannot duplicate, even function call using include.

```C=
// Log2
"addi %[log], zero, 3		\n\t"
"addi %[add_cnt], %[add_cnt], 1	\n\t"
```
* Inputs must be 8 pairs single floating-point numbers, so I guess the value of log must be 3?

## **25/04/30**
### 1
```C=
// arraymul_baseline (without V Extension)
"loop_mul_baseline:                             \n\t"

"flw f0, 0(%[h])                                \n\t"
"addi %[flw_cnt], %[flw_cnt], 1                 \n\t"

"flw f1, 0(%[x])                                \n\t"
"addi %[flw_cnt], %[flw_cnt], 1                 \n\t"

"fmul.s f0, f0, f1                              \n\t"
"addi %[fmul_cnt], %[fmul_cnt], 1               \n\t"

"fadd.s f0, f0, %[id]                           \n\t"
"addi %[fadd_cnt], %[fadd_cnt], 1               \n\t"

"fsw f0, 0(%[y])                                \n\t"
"addi %[fsw_cnt], %[fsw_cnt], 1                 \n\t"

"addi %[h], %[h], 4                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[x], %[x], 4                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[y], %[y], 4                             \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[arr_size], %[arr_size], -1              \n\t"
"addi %[add_cnt], %[add_cnt], 1                 \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"bne %[arr_size], zero, loop_mul_baseline       \n\t"
```
```C=
// arraymul_improved (with V Extension)
"loop_arraymul_improved:                        \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"vsetvli t0, %[arr_size], e32                   \n\t"

"addi %[lw_cnt], %[lw_cnt], 1                   \n\t"
"vle32.v v0, (%[h])                             \n\t"

"addi %[lw_cnt], %[lw_cnt], 1                   \n\t"
"vle32.v v1, (%[x])                             \n\t"

"addi %[fmul_cnt], %[fmul_cnt], 1               \n\t"
"vfmul.vv v2, v0, v1                            \n\t"

"addi %[fadd_cnt], %[fadd_cnt], 1               \n\t"
"vfadd.vf v2, v2, %[id]                         \n\t"

"addi %[sw_cnt], %[sw_cnt], 1                   \n\t"
"vse32.v v2, (%[y])                             \n\t"

"addi %[sub_cnt], %[sub_cnt], 1                 \n\t"
"sub %[arr_size], %[arr_size], t0               \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"slli t0, t0, 2                                 \n\t"

"addi %[add_cnt], %[add_cnt], 1                 \n\t"
"add %[h], %[h], t0                             \n\t"

"addi %[add_cnt], %[add_cnt], 1                 \n\t"
"add %[x], %[x], t0                             \n\t"

"addi %[add_cnt], %[add_cnt], 1                 \n\t"
"add %[y], %[y], t0                             \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"bne %[arr_size], zero, loop_arraymul_improved  \n\t"
```
* Understand what the requirements of the assignment are.
* It's better to put counter in front of the command.
* Finish Exercise 1, 2_1, 2_2.
* I descript each Exercise1's function below:
* For log2:
    * If N == 0, log = 0, then finish log2.
    * Initialize t0 for log value.
    * Shift right N & accumulate t0 until N == 0.
    * Assign t0 to log.
* For pi:
    * Because it's a floating-point operation, you have to convert the integer to floating-point first, and then use the floating-point instruction to get the correct value.
    * Initialize pi, t1, t2 to 0.0, 0, 1.
    * t1 is number of iteration, t2 is sign bit (numerator), t3 is 2k+1 (denominator).
    * Convert t2 & t3 to floating point, and do floating point operation.
    * Accumulate t1, change t2's value.
    * Repeat the steps above until t1 == N (iter).
* For bit_reverse:
    * Input: b,m , Output: reverse(b)
    * Initialize t0, t2 to 0.
    * t0 for iteration, t2 for temp value.
    * Use AND operation to extract first bit of b.
    * Assign first bit of b to t2, then shift left t2.
    * Accumulate t0, repeat the steps above until t0 == m (iter).
    * Assign t2 to b.

### 2
```C=
// arraymul_float
"addi %[add_cnt], %[add_cnt], 1         \n\t"
"addi t0, zero, 1               \n\t"

"addi %[others_cnt], %[others_cnt], 1       \n\t"
"fcvt.s.w f0, t0                \n\t"

"loop_mul_float:                \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"beq %[arr_size], zero, end_loop_mul_float  \n\t"

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
"j loop_mul_float                               \n\t"

"end_loop_mul_float:                            \n\t"

"addi %[add_cnt], %[add_cnt], 1         \n\t"
"addi t0, zero, 0               \n\t"

"addi %[others_cnt], %[others_cnt], 1       \n\t"
"fcvt.s.w f3, t0                \n\t"

"addi %[fadd_cnt], %[fadd_cnt], 1       \n\t"
"fadd.s %[result], f0, f3           \n\t"
```
```C=
// arraymul_double
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
"j loop_mul_float                               \n\t"

"end_loop_mul_float:                            \n\t"

"addi %[add_cnt], %[add_cnt], 1                 \n\t"
"addi t0, zero, 0                               \n\t"

"addi %[others_cnt], %[others_cnt], 1           \n\t"
"fcvt.d.w f3, t0                                \n\t"

"addi %[dadd_cnt], %[dadd_cnt], 1               \n\t"
"fadd.d %[result], f0, f3                       \n\t"

```
* Finish Exercise 3_1, 3_2.
* For Exercise 3_1:
    * Initialize f0 to 1.0.
    * Load floating-point number from array: h & x, then mul together.
    * Decrease arr_size by 1, repeat until arr_size == 0.
    * Assign f0 to result.
* For Exercise 3_2:
    * Same steps as Exercise 3_1.
    * Replace single floating-point instruction with double floating-point instruction.

### Finish HW2 at 25/04/30 18:20
