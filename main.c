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

void printOptions() {
    printf("\n\n------------------------------------------------------------\n");
    printf("---------Please select one of the following Options---------\n");
    printf("1. Take Input From the File\n");
    printf("2. Merge the Holes\n");
    printf("3.Compact The Inputs\n");
    printf("4. Print The Nodes\n");
    printf("5. Exit the Program\n");
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
