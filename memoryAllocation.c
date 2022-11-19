#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char type[5];
    int base;
    int limit;
    struct Node *next;
}typedef Memory;

void loadMemory();

//void addNode(Memory **pNode, char s[5], int base, int limit);

void addnode(struct Node** head_ref, char *P_H , int base , int limit);

int main(int argc, char **argv){
    Memory *head = NULL;

    int user_Options;
    printf("Please Select One Of The Options From Below");
    printf("1\n2\n3\n4");
    scanf("%d", &user_Options);

    switch (user_Options) {
        case 1: {
            char fileNameInput[1000];
            //fileNameInput = (char*)malloc(sizeof(char*));
            printf("Please Input The File Name : \n");
            scanf("%s", fileNameInput);

            FILE *file = fopen("C:\\Users\\raisa\\CLionProjects\\practice\\input.txt", "+");

            while(!feof(file)){
                char s[5];
                int base;
                int limit;
                fscanf("%s %d %d", s, &base, &limit);
                addnode(&head, s, base, limit);
            }
            printf("---------Operation Successfully Done---------");
            break;
        }
        case 2: {
            //mergeHoles();
            break;
        }
        case 3: {
            //compactMemory();
            break;
        }
        case 4: {
            //printMemoryView();
            int i=1;
            Memory *current = head; // temporary node pointing to head
            while(current != NULL)
            {
                printf("Node %d : %s, base = %d, limit = %d\n", i,current->type, current->base, current->limit);
                current = current->next;
                i++;
            }
            break;
        }
        default:
            printf("Error: Invalid Option Choose");
    }
    return 0;
}

void loadMemory(Memory *head) {

}

//void addNode(Memory **headNode, char *type, int base, int limit) {
//    Memory *newNode = (Memory*) malloc(sizeof(Memory));
//    Memory *lastPointer = *headNode;
//
//    strcpy(newNode->type, type);
//    newNode->base = base;
//    newNode->limit = limit;
//    newNode->next = NULL;
//
//    if(*headNode == NULL){
//        *headNode = newNode;
//        return;
//    }
//
//    while(lastPointer->next != NULL){ lastPointer = lastPointer->next;}
//
//    lastPointer->next = newNode;
//    return;
//}

void addnode(struct Node** head_ref, char *P_H , int base , int limit) // function to add a node to end of the list.
{

    struct Node* tmp = (struct Node*) malloc(sizeof(struct Node)); // allocating a node tmp which is inserted at the end

    struct Node *last = *head_ref; // last node used for pointing to last node of the current list

    strcpy(tmp->type , P_H); // current tmp's type store the type paased in function
    tmp->base = base; // tmp node base store base
    tmp->limit = limit; // tmp node limit store limit

    tmp->next = NULL; //This new node is going to be the last node, so making next of it as NULL.


    if (*head_ref == NULL) // 4. If the Linked List is empty, then make the new node as head
    {
        *head_ref = tmp;
        return;
    }

    while (last->next != NULL) // Else traverse till the last node
        last = last->next;

    last->next = tmp; //Change the next of last node to tmp.
    return;
}
