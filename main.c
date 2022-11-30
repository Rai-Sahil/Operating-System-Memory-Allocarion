#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char type[5];
    int baseMemoryLocation;
    int limitMemoryLocation;
    struct Node *next;
}typedef Memory;

void mergeHoles(Memory* head)
{
    Memory* current = head;
    struct Node* forward;

    if (current == NULL) return;

    while (current->next != NULL){
        switch (strcmp(current->type , current->next->type)) {
            case 0:{
                forward = current->next->next;
                current->limitMemoryLocation += current->next->limitMemoryLocation;
                free(current->next);
                current->next = forward;
                break;
            }
            default:
                current = current->next;
        }
    }
}

void addProcess(Memory** head_ref, char *P_H , int base , int limit) {
    Memory* tmp = (Memory*) malloc(sizeof(struct Node));

    struct Node *last = *head_ref;

    strcpy(tmp->type , P_H);
    tmp->baseMemoryLocation = base;
    tmp->limitMemoryLocation = limit;

    tmp->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = tmp;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = tmp;
    return;
}

/* function prototypes */
struct Node* SortedMerge(Memory* a, Memory* b);
void FrontBackSplit(Memory* source,
                    Memory** frontRef, Memory** backRef);

void trv(struct Node* head){
    struct Node* temp = head;
    temp->baseMemoryLocation = 0;
    while(temp->next != NULL){
        temp->next->baseMemoryLocation = temp->baseMemoryLocation + temp->limitMemoryLocation;
        temp = temp-> next;
    }

}

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(Memory** headRef)
{
    Memory* head = *headRef;
    Memory* a;
    Memory* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
    trv(head);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
Memory* SortedMerge(struct Node* a, struct Node* b)
{
    Memory* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
//    && (a->type == "H" && b->type != "H") || (a->type != "H" && b->type == "H")
    if (strcmp(a->type, b->type) >= 0 && (a->type[0] != "H" && b->type[0] != "H")) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else{
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
	and return the two lists using the reference parameters.
	If the length is odd, the extra node should go in the front list.
	Uses the fast/slow pointer strategy. */
void FrontBackSplit(Memory * source,
                    Memory ** frontRef, Memory** backRef)
{
    Memory* fast;
    Memory* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}


void printOptions() {
    printf("\n\n------------------------------------------------------------\n");
    printf("---------Please select one of the following Options---------\n");
    printf("1. Take Input From the File\n");
    printf("2. Merge the Holes\n");
    printf("3.Compact The Inputs\n");
    printf("4. Print The Nodes\n");
    printf("5. Exit the Program\n");
}

void printList(struct Node* node)
{
    while (node != NULL) {
        printf("%s ", node->type);
        node = node->next;
    }
}

int main()
{
    Memory* head = NULL;

    int userInput = 0;
    while(userInput != 5){
        printOptions();
        scanf("%d", &userInput);

        switch(userInput){
            case 1:{
                char *fileName;
                fileName = (char*) malloc(100*sizeof(char*));
                printf("Please Enter your file location: ");
                scanf("%s", fileName);
                FILE *file = fopen (fileName, "r");

                if (file == NULL) {
                    printf("File is Null");
                    return 1;
                }

                while(!feof(file))
                {
                    char s[5];
                    int base;
                    int limit;
                    fscanf(file, "%s %d %d",s,&base,&limit);
                    addProcess(&head, s, base, limit);
                }
                printf("Operation Done...");
                break;
            }
                /**
                 * Case 2
                 */
            case 2: {
                mergeHoles(head);
                printf("Operation Successful");
                break;
            }
                /**
                 * Case 3
                 */
            case 3: {
                MergeSort(&head);
                mergeHoles(head);
                break;
            }
                /**
                 * Case 4
                 */
            case 4:{
                struct Node *current = head;
                int i=1;
                while(current != NULL)
                {
                    printf("Node %d : %s, base = %d, limit = %d\n", i, current->type, current->baseMemoryLocation, current->limitMemoryLocation);
                    current = current->next;
                    i++;
                }
                break;
            }
                /**
                 * Case 5
                 */
            case 5:{
                printf("Thank You For The Time...");
                break;
            }
            default:
                printf("Invalid Input");
        }
        printf("\n\n\n");
    }
    return 0;
}
