# **HW1_1: Array Bubble Sort**

## **25/03/21**
* Download HW1 file from firefox.

## **25/03/22**
### 1
```C=
asm volatile(
        "bge %[b], %[a], Exit\n\t"	// if(*(p_a+j+1) >= *(p_a+j))
						            // jump to Exit:
						            //
		"addi t0, %[a], 0\n\t"		// int tmp = *(p_a+j)
		"addi %[a], %[b], 0\n\t"	// *(p_a+j) = *(p_a+j+1)
		"addi %[b], t0, 0\n\t"		// *(p_a+j+1) = tmp
		"Exit:"
		:
		:[a] "r"(*(p_a + j)), [b] "r"(*(p_a + j + 1))
		:"t0"
	    );
```
* If you don't use output operand, you still have to add ":" into your code.

### 2
```C=
asm volatile(
		// Your code
        "lw t0, 0(%[pa])\n\t"
		"lw t1, 4(%[pa])\n\t"
		"bge t1, t0, Exit\n\t"
		"sw t0, 4(%[pa])\n\t"
		"sw t1, 0(%[pa])\n\t"
		"addi %[pa], %[pa], 4\n\t"
		"Exit:"
		:
		:[pa] "r"(p_a)
		:"t0", "t1"
	    );

```
* The previous code is like call by value, so the actual values wouldn't swap.
* Then I directly load the value in array, then store the value into array.

### 3
```C=
asm volatile(
                // Your code
                "lw t0, 0(%[pa])\n\t"           // t0 = *(p_a + j)
                "lw t1, 0(%[pb])\n\t"           // t1 = *(p_a + j + 1)
                "bge t1, t0, Exit\n\t"          // if *(p_a+j+1) >= *(p_a+j)
                                                // jump to Exit, don't swap
                "sw t0, 0(%[pb])\n\t"           // swap t0 & t1
                "sw t1, 0(%[pa])\n\t"
                "Exit:"
                :
                :[pa] "r"(p_a+j), [pb] "r"(p_a+j+1)
                :"t0", "t1"
            );
```
* Cannot move array pointer.
### Finish HW1_1 at 25/03/22 16:44
---
# **HW1_2: Array Search**
## **25/03/23**
### 1
```C=
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
        "addi t0, zero, 0\n\t"
        "beq %[AS], zero, EXIT\n\t"
        "LOOP:"
        ""
        "addi t0, t0, 1\n\t"
        "bne t0, %[AS], LOOP\n\t"
        "EXIT:"
        );

```
* Write C code inside the "arraySearch" function.

## **25/03/24**
### 1
```C=
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
        "add %[PA], %[PA], t1\n\t"      // move array pointer forward
        "lw t2, 0(%[PA])\n\t"           // load *(p_a + i)
        "beq t2, %[TG], EXIT\n\t"       // if *(p_a + i) == target, then exit
        "addi t0, t0, 1\n\t"            // t0 += 1 (i++)
        "bne t0, %[AS], LOOP\n\t"       // if t0 < arr_size, then keep searching (jump to LOOP label)
        "EXIT:"
        "add %[RS], %[RS], t0\n\t"      // result = t0
        :[PA] "+r"(p_a), [RS] "+r"(result)
        :[AS] "r"(arr_size), [TG] "r"(target)
        :"t0", "t1", "t2"
        );

```
* testcase 2_1.txt pass, but 2_2.txt no output.
### 2
```C=
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
        "add t2, %[PA], t1\n\t"         // move array pointer forward
        "lw t3, 0(t2)\n\t"              // load *(p_a + i)
        "beq t3, %[TG], FOUND\n\t"      // if *(p_a + i) == target, then exit
        "addi t0, t0, 1\n\t"            // i++
        "blt t0, %[AS], LOOP\n\t"       // if i < arr_size, then keep searching (jump to LOOP label)

        "EXIT:"
        "li %[RS], -1\n\t"              // result = -1, not found target value
        "j END\n\t"

        "FOUND:"
        "mv %[RS], t0\n\t"              // result = i, found target value, return target index

        "END:"
        :[RS] "+r"(result)
        :[PA] "r"(p_a), [AS] "r"(arr_size), [TG] "r"(target)
        :"t0", "t1", "t2", "t3"
        );

```
* Because tesetcase 2_2.txt can't pass, I asked Chatgpt to help me see what is wrong with the original code.
* I haven't found the problem in my code yet, but I found that my orininal code may fall into infinite loop (line: bne t0, %[AS], LOOP).

## **25/03/31**
### 1
```C=
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
        "add t2, %[PA], t1\n\t"         // move array pointer forward
        "lw t3, 0(t2)\n\t"              // load *(p_a + i)
        "beq t3, %[TG], EXIT\n\t"       // if *(p_a + i) == target, then exit
        "addi t0, t0, 1\n\t"            // t0 += 1 (i++)
        "bne t0, %[AS], LOOP\n\t"       // if t0 < arr_size, then keep searching (jump to LOOP label)

        "EXIT:"
        "mv %[RS], t0\n\t"              // result = t0
        :[RS] "+r"(result)
        :[AS] "r"(arr_size), [TG] "r"(target), [PA] "r"(p_a)
        :"t0", "t1", "t2", "t3"
        );
```
* I change my code by referring to chatgpt code, there're two problem in my previous code
    * Do not change array pointer directly. Instead, using the temp register to store array pointer and change the temp register.
    * assign value to [RS]: result, don't use "add %[RS], %[RS], value", use "mv %[RS], value".
### Finish HW1_2 at 25/03/31 16:30
---
# **HW1_3: Linked-List Merge Sort**
## **25/04/01**
### 1
### Block A
```C=
// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    /* C code
    if(!head || !head->next){
        *firstHalf = head;
        *secondHalf = NULL;
        return;
    }
    Node* slow = head;
    Node* fast = head->next;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    *firstHalf = head;
    *secondHalf = slow->next;
    slow->next = NULL;
    */

    asm volatile(
        /*
        Block A (splitList), which splits the linked list into two halves
        */
        ""
    );

    return;
}
```
### Block B
```C=
// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;

    /* C code
    if(a == NULL) result = b;
    else if(b == NULL) result = a;
    else{
        if(a->data <= b->data){
            result = a;
            a = a->next;
        }
        else {
            result = b;
            b = b->next;
        }
    }

    tail = result;

    while(a != NULL && b != NULL){
        if(a->data <= b->data){
            tail->next = a;
            a = a->next;
        }
        else{
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    while(a != NULL){
        tail->next = a;
        a = a->next;
        tail = tail->next;
    }

    while(b != NULL){
        tail->next = b;
        b = b->next;
        tail = tail->next;
    }
    */

    asm volatile(
        /*        
        Block B (mergeSortedList), which merges two sorted lists into one
        */
        ""
    );

    return result;
}
```
### Block C
```C=
/* C code
        cur = cur->next;
        */

        asm volatile(
            /*
            Block C (Move to the next node), which updates the pointer to
            traverse the linked list
            */
            ""
        );
```
* Write C code for each Block.

## **25/04/07**
### 1
```C=
// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    
    // C code
/*    if(!head || !head->next){
        *firstHalf = head;
        *secondHalf = NULL;
        return;
    }
    Node* slow = head;
    Node* fast = head->next;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }

    *firstHalf = head;
    *secondHalf = slow->next;
    slow->next = NULL;
    
*/
    asm volatile(
        
        // Block A (splitList), which splits the linked list into two halves
        "beq %[head], zero, set_result_null     \n\t"  // if(head == NULL) goto set_result_null
        "ld  t0, 8(%[head])                     \n\t"  // t0 = head->next
        "beq t0, zero, set_result_null          \n\t"  // if(head->next == NULL) goto set_result_null

        // Initialize slow & fast
        "mv t1, %[head]                         \n\t"  // t1 = slow = head
        "mv t2, t0                              \n\t"  // t2 = fast = head->next

        "loop:"
        "beq t2, zero, done_loop                \n\t"  // if(fast == NULL) break loop
        "ld  t3, 8(t2)                          \n\t"  // t3 = fast->next
        "beq t3, zero, done_loop                \n\t"  // if(fast->next == NULL) break loop

        // Update slow & fast
        "ld t1, 8(t1)                           \n\t"  // slow = slow->next
        "ld t2, 8(t2)                           \n\t"  // fast = fast->next
        "ld t2, 8(t2)                           \n\t"  // fast = fast->next->next
        "j loop                                 \n\t"

        "done_loop:"

        // Set *firstHalf = head
        "mv %[firstHalf], %[head]            \n\t"

        // Set *secondHalf = slow->next
        "ld t0, 8(t1)				\n\t"  // t0 = slow->next
        "mv %[secondHalf], t0 		\n\t"

        // Break the link： slow->next = NULL
        "sd zero, 8(t1)				\n\t"
        "j end_split				\n\t"

    	// if !head || !head->next, then *firstHalf = head, *secondHalf = NULL
        "set_result_null:"
        "mv %[firstHalf], %[head]		\n\t"
        "mv %[secondHalf], zero		\n\t"

        "end_split:"
        : [firstHalf] "+r"(*firstHalf),
	      [secondHalf] "+r"(*secondHalf)
        : [head] "r"(head)
        : "t0", "t1", "t2", "t3"
    );

    return;
}
```

### 2
```C=
        // C code
        // cur = cur->next;

        asm volatile(

           // Block C (Move to the next node), which updates the pointer to
           // traverse the linked list

            "mv %[CUR], %[CURN]\n\t"
            :[CUR] "+r"(cur)
            :[CURN] "r"(cur->next)
        );
```
* Block A: At first I thought it is RV32, but then I found that it is RV64, so when I try to load the next pointer, it reads the wrong value.
* Finish Block A & C.

## **25/04/08**
### 1
```C=
// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;

    // C code
/*  if(a == NULL) result = b;
    else if(b == NULL) result = a;
    else{
        if(a->data <= b->data){
            result = a;
            a = a->next;
        }
        else {
            result = b;
	        b = b->next;
        }
    }

    tail = result;

    while(a != NULL && b != NULL){
	    if(a->data <= b->data){
	        tail->next = a;
	        a = a->next;
	    }
	    else{
	        tail->next = b;
	        b = b->next;
	    }

	    tail = tail->next;
    }

    while(a != NULL){
        tail->next = a;
	    a = a->next;
	    tail = tail->next;
    }

    while(b != NULL){
        tail->next = b;
        b = b->next;
        tail = tail->next;
    }
*/    

    asm volatile(
	        
        // Block B (mergeSortedList), which merges two sorted lists into one
        "beq %[a], zero, set_result_b       \n\t"  // if(a == NULL) goto set_result_b
        "beq %[b], zero, set_result_a       \n\t"  // else if(b == NULL) goto set_result_a

        // both a and b are not null, compare a->data and b->data
        "lw t0, 0(%[a])                     \n\t"  // t0 = a->data
        "lw t1, 0(%[b])                     \n\t"  // t1 = b->data
        "ble t0, t1, a_less_or_equal        \n\t"  // if(a->data <= b->data) goto a_less_or_equal

        "mv %[result], %[b]                 \n\t"  // result = b
        "ld %[b], 8(%[b])                   \n\t"  // b = b->next
        "j set_tail	                    \n\t"

        "a_less_or_equal:                   \n\t"
        "mv %[result], %[a]                 \n\t"  // result = a
        "ld %[a], 8(%[a])                   \n\t"  // a = a->next
        "j set_tail	                    \n\t"

        "set_result_a:                      \n\t"
        "mv %[result], %[a]                 \n\t"  // if b == NULL, result = a
        "j set_tail	                    \n\t"

        "set_result_b:                      \n\t"
        "mv %[result], %[b]                 \n\t"  // if a == NULL, result = b
        "j set_tail	                    \n\t"

        "set_tail:	                    \n\t"
        "mv %[tail], %[result]              \n\t"  // tail = result

        // while(a != NULL && b != NULL)
        "merge_loop:                        \n\t"
        "beq %[a], zero, merge_loop_end     \n\t"  // if(a == NULL) break loop
        "beq %[b], zero, merge_loop_end     \n\t"  // if(b == NULL) break loop

        "lw t0, 0(%[a])                     \n\t"  // t0 = a->data
        "lw t1, 0(%[b])                     \n\t"  // t1 = b->data
        "ble t0, t1, a_case                 \n\t"  // if(a->data <= b->data) goto a_case

        "sd %[b], 8(%[tail])                \n\t"  // tail->next = b
        "ld %[b], 8(%[b])                   \n\t"  // b = b->next
        "j update_tail                      \n\t"

        "a_case:                            \n\t"
        "sd %[a], 8(%[tail])                \n\t"  // tail->next = a
        "ld %[a], 8(%[a])                   \n\t"  // a = a->next

        "update_tail:                       \n\t"
        "ld %[tail], 8(%[tail])             \n\t"  // tail = tail->next
        "j merge_loop                       \n\t"

        "merge_loop_end:                    \n\t"
        
        "attach_loop:"
        "bne %[a], zero, attach_a           \n\t"  // if (a != NULL) tail->next = a
        "bne %[b], zero, attach_b           \n\t"  // else if (b != NULL) tail->next = b
        "j end_merge                        \n\t"

        "attach_a:"
        "sd %[a], 8(%[tail])                \n\t"  // tail->next = a
	    "ld %[a], 8(%[a])		    \n\t"  // a = a->next
	    "ld %[tail], 8(%[tail])		    \n\t"  // tail = tail->next
        "j attach_loop                      \n\t"

        "attach_b:"
        "sd %[b], 8(%[tail])                \n\t"  // tail->next = b
	    "ld %[b], 8(%[b])		    \n\t"  // b = b->next
	    "ld %[tail], 8(%[tail])		    \n\t"  // tail = tail->next
	    "j attach_loop                      \n\t"

	    "end_merge:                             \n\t"
        : [result] "+r" (result), [a] "+r" (a), [b] "+r" (b), [tail] "+r" (tail)
        :
        : "t0", "t1"
    );

    return result;
}

```
* I found that the label cannot duplicate, even in different functions.
* Finish Block B.
### Finish HW1_3 at 25/04/08 22:26
