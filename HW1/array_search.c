#include <stdio.h>

int arraySearch(int *p_a, int arr_size, int target)
{
    int result = -1;

    // array search
    // C code
    /*
    for(int i=0; i<arr_size; i++){
    	if(*(p_a + i) == target){
	    return i;
	}
    }
    
    */ 

    asm volatile(
        // Your code
	"addi t0, zero, 0\n\t"          // initialize t0 to 0 (i=0)
        "beq %[AS], zero, EXIT\n\t"     // if arr_size == 0, then exit

        "LOOP:"
        "slli t1, t0, 2\n\t"            // t1 = t0 * 4
        "add t2, %[PA], t1\n\t"      	// move array pointer forward
        "lw t3, 0(t2)\n\t"           	// load *(p_a + i)
        "beq t3, %[TG], EXIT\n\t"       // if *(p_a + i) == target, then exit
        "addi t0, t0, 1\n\t"            // t0 += 1 (i++)
        "bne t0, %[AS], LOOP\n\t"       // if t0 < arr_size, then keep searching (jump to LOOP label)

	"EXIT:"
        "mv %[RS], t0\n\t"      	// result = t0
        :[RS] "+r"(result)
        :[AS] "r"(arr_size), [TG] "r"(target), [PA] "r"(p_a)
        :"t0", "t1", "t2", "t3"
	);

    return result;
}

// Main function to test the implementation
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
    int target;
    fscanf(input, "%d", &target);
    fclose(input);

    int *p_a = &arr[0];

    int index = arraySearch(p_a, arr_size, target);

    // Print the result
    printf("%d ", index);
    printf("\n");

    return 0;
}
