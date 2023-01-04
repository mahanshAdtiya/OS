#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
int main(int argc, char *argv[], char* envp[]){
    FILE* file_pointer;
    if(!argv[2]){
        file_pointer = fopen(argv[1], "r");
    }
    else{
        file_pointer = fopen(argv[2], "r");
    }
;
    if (!file_pointer) { // Not working
        printf("msh: Error !.😔🥲\n");
        if(errno == 2){
            printf("No such file exits \n");
        }
        else if(errno ==EINVAL ){
            printf("File can't be opened\n");
        }
        else if(errno == 21){
            printf("It's a directory\n");
        }
        exit(EXIT_FAILURE);
    }
    char ch = fgetc(file_pointer);
    if(!argv[2]){
        while(ch != EOF){ // till end of file
            printf("%c",ch);
            ch = fgetc(file_pointer);
        }
        printf("\n");
    }
    else if(strcmp(argv[1],"-E") == 0){
        while(ch != EOF){ // till end of file
            if(ch == '\n'){
                printf("$");
            }
            printf("%c",ch);
            ch = fgetc(file_pointer);
        }
        printf("$\n");
        exit(EXIT_SUCCESS);
    }

    else if(strcmp(argv[1],"-n") == 0){
        int index = 1;
        printf("%d ", index++);
        while(ch != EOF){ // till end of file
            if(ch == '\n'){
                printf("%c",ch);
                ch = fgetc(file_pointer);
                printf("%d ", index++);
                continue;;
            }
            printf("%c",ch);
            ch = fgetc(file_pointer);
        }
        printf("\n");
        exit(EXIT_SUCCESS);
    }

    else{
        printf("msh: Error !. 😔🥲\nNo such operation exists for cat\n");
    }
 
    fclose(file_pointer);
    return 0;
}