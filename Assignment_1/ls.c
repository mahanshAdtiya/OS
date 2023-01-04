#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc,char *argv[],char *envp[]){

    DIR* directory = opendir(argv[1]); // opendir opens the directory of the specifeid path. "." means current directory and pointer directory points to that directory
    if(directory == NULL){
        printf("msh: Error ! 😔🥲\nNo such directory exists\n");
        exit(EXIT_FAILURE);
    }
    struct dirent* file_folder = readdir(directory); // either returns NULL or points on the file/folder of the directory
    
    while(file_folder != NULL){
        if(argv[2] == NULL){ // prints the unhidden files
            if(file_folder->d_name[0] != '.'){ // .. and . means current directory and previous directory
            printf("%s  ", file_folder->d_name);
            }
            file_folder = readdir(directory);    
        }   

        else if(strcmp(argv[2],"-a") == 0){ // Prints all the files and folder even if it's hidden
            printf("%s  ", file_folder->d_name);
            file_folder = readdir(directory);
        }

        else if(strcmp(argv[2],"-p") == 0){ // tells whether it's a file or folder by printing / at the end
            if(file_folder->d_name[0] != '.'){ // .. and . means current directory and previous directory
                if(file_folder->d_type == 8){
                    printf("%s  ", file_folder->d_name);
                }
                else{
                    printf("%s/  ", file_folder->d_name);
                }
            }   
            file_folder = readdir(directory); 
        }
        else if(strcmp(&argv[2][0], "-")!= 0){
            char path [1000];
            char back[] = "/";
            strcat(path,argv[1]);
            strcat(path,back);
            strcat(path,argv[2]);
            execl("/Users/mahansh/Downloads/Practice/OS/Shell/ls","BUFFER(char*)(argument)",path,NULL);
        }
        else if(strcmp(argv[1],"-p") != 0 || strcmp(argv[1],"-a") != 0){
            printf("msh: Error ! 😔🥲\nNo such operator Exists for ls.\n");
            break;
            exit(EXIT_FAILURE);
        }
    }
    printf("\n");
    
    closedir(directory); //closing file like io in python
    return 0;
}