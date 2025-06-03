#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int arr_size;
    fscanf(input, "%d", &arr_size);
    int arr[arr_size];

    // Read integers from input file into the array
    for (int i = 0; i < arr_size; i++) {
        int data;
        fscanf(input, "%d", &data);
        arr[i] = data;
    }
    fclose(input);

    int *p_a = &arr[0];

    // array a bubble sort
    /* Original C code segment
    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; j < arr_size - i -1; j++) {
            if (*(p_a + j) > *(p_a + j + 1)) {
                int tmp = *(p_a + j);
                *(p_a + j) = *(p_a + j + 1);
                *(p_a + j + 1) = tmp;
            }
        }
    }
    */

    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; j < arr_size - i - 1; j++) {
            asm volatile(
		// Your code
                "lw t0, 0(%[pa])\n\t"		// t0 = *(p_a + j)
		"lw t1, 0(%[pb])\n\t"		// t1 = *(p_a + j + 1)
		"bge t1, t0, Exit\n\t"		// if *(p_a+j+1) >= *(p_a+j)
						// jump to Exit, don't swap
		"sw t0, 0(%[pb])\n\t"		// swap t0 & t1
		"sw t1, 0(%[pa])\n\t"
		"Exit:"
		:
		:[pa] "r"(p_a+j), [pb] "r"(p_a+j+1)
		:"t0", "t1"
	    );
        }
    }
    p_a = &arr[0];
    for (int i = 0; i < arr_size; i++)
        printf("%d ", *p_a++);
    printf("\n");
    return 0;
}
