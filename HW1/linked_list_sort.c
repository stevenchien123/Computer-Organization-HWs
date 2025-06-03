#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

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
        "beq t2, zero, split_loop_end           \n\t"  // if(fast == NULL) break loop
        "ld  t3, 8(t2)                          \n\t"  // t3 = fast->next
        "beq t3, zero, split_loop_end           \n\t"  // if(fast->next == NULL) break loop

        // Update slow & fast
        "ld t1, 8(t1)                           \n\t"  // slow = slow->next
        "ld t2, 8(t2)                           \n\t"  // fast = fast->next
        "ld t2, 8(t2)                           \n\t"  // fast = fast->next->next
        "j loop                                 \n\t"

        "split_loop_end:"

        // Set *firstHalf = head
        "mv %[firstHalf], %[head]               \n\t"

        // Set *secondHalf = slow->next
        "ld t0, 8(t1)				\n\t"  // t0 = slow->next
        "mv %[secondHalf], t0 			\n\t"

        // Break the link： slow->next = NULL
        "sd zero, 8(t1)				\n\t"
        "j end_split				\n\t"

	// if !head || !head->next, then *firstHalf = head, *secondHalf = NULL
        "set_result_null:"
        "mv %[firstHalf], %[head]		\n\t"
        "mv %[secondHalf], zero			\n\t"

        "end_split:"
        : [firstHalf] "+r"(*firstHalf),
	  [secondHalf] "+r"(*secondHalf)
        : [head] "r"(head)
        : "t0", "t1", "t2", "t3"
    );

    return;
}

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

// Merge Sort function for linked list
Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head; // Return directly if there is only one node

    Node *firstHalf, *secondHalf;

    splitList(head, &firstHalf,
              &secondHalf); // Split the list into two sublists

    firstHalf = mergeSort(firstHalf);   // Recursively sort the left half
    secondHalf = mergeSort(secondHalf); // Recursively sort the right half

    return mergeSortedLists(firstHalf, secondHalf); // Merge the sorted sublists
}

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
    int list_size;
    fscanf(input, "%d", &list_size);
    Node *head = (list_size > 0) ? (Node *)malloc(sizeof(Node)) : NULL;
    Node *cur = head;
    for (int i = 0; i < list_size; i++) {
        fscanf(input, "%d", &(cur->data));
        if (i + 1 < list_size)
            cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }
    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);

	// C code
        // cur = cur->next;
        

        asm volatile(
            
           // Block C (Move to the next node), which updates the pointer to
           // traverse the linked list
            
	    "mv %[CUR], %[CURN]\n\t"
	    :[CUR] "+r"(cur)
	    :[CURN] "r"(cur->next)
	);

    }
    printf("\n");
    return 0;
}
