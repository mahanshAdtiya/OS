#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char *argv[],char *envp[]){

    if(argv[2] == NULL){
        int check = mkdir(argv[1], S_IRWXU);
        if(check){
            printf("msh: Error !.😔🥲\n");
            if(errno == EEXIST){
                printf("Directory Already Exists\n");
            }
            else if(errno == ENOSPC){
                printf("Not enough space to create a directory\n");
            }
            else if(errno == EROFS){
                printf("Directory is a read only, can't modify.\n");
            }
            else if(errno == 2){
                printf("No such file or directory Exits.\n");
            }
            else{
                perror(" ");
            }
            exit(EXIT_FAILURE);
        }
    }
    else if(strcmp(argv[1],"-v") == 0){
        int check = mkdir(argv[2], S_IRWXU);
        if(check){
            printf("msh: Error !.😔🥲");
            if(errno == EEXIST){
                printf("Directory Already Exists\n");
            }
            else if(errno == ENOSPC){
                printf("Not enough space to create a directory\n");
            }
            else if(errno == EROFS){
                printf("Directory is a read only, can't modify.\n");
            }
            else if(errno == 2){
                printf("No such file or directory Exits.\n");
            }
            else{
                perror(" ");
            }
            exit(EXIT_FAILURE);
        }
        printf("New directory created: %s\n",argv[2]);
    }

    else if(argv[1][0] == '-' && argv[1][1] == 'p'){
        int check = mkdir(argv[2], S_IRWXU);
        if(check){
            char *temp = argv[2];
            char *directory;
            directory = strtok(temp,"/"); 
            while(directory != NULL){
                int check = mkdir(directory, S_IRWXU);
                if(check){
                    printf("msh: Error !.😔🥲\n");
                    if(errno == EEXIST){
                        printf("Directory Already Exists\n");
                    }
                    else if(errno == ENOSPC){
                        printf("Not enough space to create a directory\n");
                    }
                    else if(errno == EROFS){
                        printf("Directory is a read only, can't modify.\n");
                    }
                    else if(errno == 2){
                        printf("No such file or directory Exits.\n");
                    }
                    else{
                        printf("%d\n",errno);
                        perror(" ");
                    }
                    exit(EXIT_FAILURE);
                }
                chdir(directory);
                directory = strtok(NULL, "/");
            }   
        }
        
    }
    else{
        printf("msh: Error !.😔🥲]\nNo such operation exists for mkdir\n");
    }
}
