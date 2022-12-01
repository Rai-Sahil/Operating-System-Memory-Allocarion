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
//    (a->type[0] >= b->type[0])
    if ((a->type[0] >= b->type[0])) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else{
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void FrontBackSplit(Memory * source,
                    Memory ** frontRef, Memory** backRef)
{
    Memory* fast;
    Memory* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

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

void changeHole(struct Node* head, int holeSize){
    Memory *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->limitMemoryLocation = holeSize;
}

int main()
{
    Memory* head = NULL;
    int i = 0;
    int holeSize = 0;

    int userInput = 0;
    while(userInput != 5){
        printOptions();
        scanf("%d", &userInput);

        switch(userInput){
            case 1:{
                if(i == 0){
                    char *fileName;
                    fileName = (char*) malloc(100*sizeof(char*));
                    printf("Please Enter your file location: ");
                    scanf("%s", fileName);
                    FILE *file = fopen (fileName, "r");

                    if (file == NULL) {
                        printf("File is Null");
                        return 1;
                    }
                    char *stringLimit;
                    char *stringBase;
                    char *stringType;

                    while(!feof(file))
                    {
                        stringLimit = (char *) malloc(sizeof(char*));
                        stringBase = (char *) malloc(sizeof(char*));
                        char s[5];
                        char base[64];
                        char limit[64];
                        fscanf(file, "%s %s %s",s,base,limit);
                        int limitPtr = strtol(limit, &stringLimit, 10);
                        int basePtr = strtol(base, &stringBase, 10);
                        int typePtr = strtol(s, &stringType, 10);

                        if(strlen(stringLimit) != 0 || strlen(stringBase) != 0 || basePtr < 0 || limitPtr <= 0){
                            printf("ERROR: INVALID BASE OR LIMIT VALUE");
                            return 0;
                        }

                        printf("%llu", strlen(stringType));

                        if(strcmp(s, "H") == 0) {
                            holeSize = holeSize + limitPtr;
                        }

                        addProcess(&head, s, basePtr, limitPtr);
                    }

                    i = i +1;
                    printf("Operation Done...");
                } else{
                    printf("File Cannot be Inputed Again");
                }
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
                trv(head);
                changeHole(head, holeSize);
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
