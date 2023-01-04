#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc,char *argv[],char *envp[]){
    if(argv[2] == NULL){
        printf("msh: Error !.😔🥲\nInvalid syntax: Expects Some arguement to rm\n");
        exit(EXIT_FAILURE);
    }

    DIR* directory = opendir(argv[1]); // opendir opens the directory of the specifeid path. "." means current directory and pointer directory points to that directory
    struct dirent* file_folder = readdir(directory); // either returns NULL or points on the file/folder of the directory
    if(argv[3] == NULL){
        while(file_folder != NULL){
            if(strcmp(file_folder->d_name,argv[2]) == 0){
                if(file_folder->d_type == 8){
                    char path [1000];
                    char back[] = "/";
                    strcat(path,argv[1]);
                    strcat(path,back);
                    strcat(path,argv[2]);
                    remove(path);
                    exit(EXIT_SUCCESS);
                }
                else if(file_folder->d_type == 4){
                    printf("msh: Error !.😔🥲\nIt's a directory. Can't delete a Directory with rm.\n");
                    exit(EXIT_FAILURE);
                }
            }
            file_folder = readdir(directory);
        }
        printf("msh: Error !.😔🥲\nNo such file exists.\n");
    }
    else if(strcmp(argv[2],"-i") == 0){
        while(file_folder != NULL){
            if(strcmp(file_folder->d_name,argv[3]) == 0){
                if(file_folder->d_type == 8){
                    char choice[10];
                    printf("\nDo you want to remove %s: y (YES) or n (NO)?: %s",file_folder->d_name,choice);
                    scanf("%s",choice);
                    if(strcmp(choice,"y") == 0){
                        char path [1000];
                        char back[] = "/";
                        strcat(path,argv[1]);
                        strcat(path,back);
                        strcat(path,argv[3]);
                        remove(path);
                    }
                    exit(EXIT_SUCCESS);
                }
                printf("msh: Error !.😔🥲\nIt's a directory. Can't delete a Directory with rm -i.\n");
                exit(EXIT_FAILURE);
            }
            file_folder = readdir(directory);
        }
        printf("msh: Error !.😔🥲\nNo such file exists.\n");
    }

    else if(strcmp(argv[2],"-v") == 0){
        while(file_folder != NULL){
            if(strcmp(file_folder->d_name,argv[3]) == 0){
                if(file_folder->d_type == 8){
                    printf("Deleting %s\n",file_folder->d_name);
                    char path [1000];
                    char back[] = "/";
                    strcat(path,argv[1]);
                    strcat(path,back);
                    strcat(path,argv[3]);
                    remove(path);
                    exit(EXIT_SUCCESS);
                }
                printf("msh: Error !.😔🥲\nIt's a directory. Can't delete a Directory with rm -i.\n");
                exit(EXIT_FAILURE);
            }
            file_folder = readdir(directory);
        }
        printf("msh: Error !.😔🥲\nNo such file exists.\n");
    }

    else{
        printf("msh: Error ! 😔🥲\nNo such operation exists for rm.\n");
        exit(EXIT_FAILURE);
    }
   
}