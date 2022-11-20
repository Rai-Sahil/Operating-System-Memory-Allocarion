#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
    int userInput = 0;
    while(userInput != 4){
        printf("\n\n------------------------------------------------------------\n");
        printf("---------Please select one of the following Options---------\n");
        printf("1. Take Input From the File\n");
        printf("2. Merge the Holes\n");
        printf("3.Compact The Inputs\n");
        scanf("%d", &userInput);

        switch(userInput){
            case 1:{
                printf("Operation Done...");
                break;
            } case 2: {
                printf("Operation Successful");
                break;
            }
            case 3: {
                printf("Operation");
                break;
            }
            case 4:{
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
