#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>


void forkExecution(char **commands, char *og);
void sysExecution(char **commands,char *og);

// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

char *taking_input(){ // why are we using pointer
  char * line;  // actual line
  size_t length; // we will store the actual size of our input line in this variable
  size_t size = 1; // initial size to take an input using getline()

  line = (char *) malloc (size * length); // dynamically allocating the memory to the size of the input since we don't know the lenght, so we can incraese it later if we want to
  length = getline(&line,&size, stdin); // returns the lenght of the actual length of the input

  if(length == -1){ // getline returns -1 if it cannot allocate any more space
    printf("msh: Sorry, Some error occured 😔.\n");
    exit(EXIT_FAILURE);
  }
  line[strcspn(line, "\n")] = 0;
   return line;
}
// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

char **breaking_into_smaller_pieces(char* line){  // why are we using double pointer
  int index = 0,line_size = 1024; // index for storing the parts of the input
  char **executable_commands = malloc(sizeof(char)*line_size);  // dynamically allocating the space for character array to store the parts
  char *small_commands;
  small_commands = strtok(line," "); // returns the first instance of the delimiter
  while(small_commands != NULL){
    executable_commands[index++] = small_commands;
    small_commands = strtok(NULL, " ");
  }  
  return executable_commands;
}
// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void cd(char ** commands){ // only 1 arguement working
  if(commands[1] == NULL){
    printf("msh: Error 🥲!!.\nInvalid syntax: Expects some arguement to the command cd\n");
  }

  else if(commands[2] != NULL){
    printf("msh: Error 🥲!!.\nInvalid syntax: Too many arguments to cd\n");
  }

  else if(strcmp(commands[1],"~") == 0){
    char s[1000];
    chdir("/home");
    printf("Directory updated to %s\n", getcwd(s,1000));
  }
  
  else if(chdir(commands[1]) != 0){ // checknig if a directory even exist or not
    printf("msh: Error !.😔🥲\nNo such directory Exist\n");
  }

  else{
    char s[1000];
    printf("Directory updated to %s\n", getcwd(s,1000));
  }
}
// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void echo(char ** commands){

  if (!commands[1]){
    printf("msh: Error 🥲!!.\nInvalid syntax: Expects some arguement to the command echo\n");
  }

  else if(strcmp(commands[1],"*") == 0){
    DIR* directory = opendir(".");
    struct dirent* file_folder = readdir(directory); // either returns NULL or points on the file/folder of the directory
    while(file_folder != NULL){
        if(file_folder->d_name[0] != '.'){ // .. and . means current directory and previous directory
        printf("%s  ", file_folder->d_name);
        }
        file_folder = readdir(directory);    
    } 
  }
  else if(strcmp(commands[1],"-n") == 0){
    int index = 2;
    while(commands[index] != NULL){
      if(commands[index] != NULL){
        printf("%s ", commands[index]);
      }
      index++;
    }
  }
  else if(commands[1][0] != '-'){
    int index = 1;
    while(commands[index] != NULL){
      if(commands[index] != NULL){
        printf("%s ", commands[index]);
      }
      index++;
    }
    printf("\n");
  }
  else{
    printf("msh: Error !.😔🥲.\nNo such operator exists for echo\n");
  }
  

}
// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void pwd( char** commands){
  if(commands[1] != NULL && commands[1][0] != '-'){
    printf("msh: Error 🥲!!.\nInvalid syntax: Too many arguments for pwd\n");
  }
  else{
    if(commands[1] == NULL||strcmp(commands[1],"-P") == 0){
      char s[1000];
      printf("Current Directory: %s\n", getcwd(s,1000));
    }
    else if(strcmp(commands[1],"-L") == 0){
      char s[1000];
      printf("Current Directory: %s\n",realpath(getcwd(s,100),NULL));
    }
    else{
      printf("msh: Error !.😔🥲\nNo such operation exists for pwd\n");
    }
  }
  
}
// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void execution(char ** commands,char *s){
    if(strcmp(commands[0], "cd") == 0){ // current directory command
        cd(commands);
    }

    else if(strcmp(commands[0], "echo") == 0){ // echo command
      echo(commands);
    }

    else if (strcmp(commands[0], "pwd") == 0){ // pwd command
      pwd(commands);
    }

    else{

      if(commands[0][strlen(*commands)-2] == '&' && commands[0][strlen(*commands)-1] == 't'){
        sysExecution(commands,s); 
      }
      else{
        forkExecution(commands,s);
      }
    }
    
}

// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void forkExecution(char **commands, char *og){
  int pid, p_wait;
  pid = fork();
  if(pid < 0){
    printf("msh: Error - Fork Failed !. 😔🥲\n");
    exit(EXIT_FAILURE);
  }
  
  else if(pid == 0){
    char s[100];
    getcwd(s,100);
    char path[60] = {0};
    if(strcmp(commands[0],"ls") == 0){
      strcat(path,og);
      strcat(path,"/ls");
      char buffer[] = "buffer";
      if(commands[2]){
        printf("msh: Error!. 😔🥲\nInlvaid syntax: Too many arguments for ls.\n");
      }
      else{
        execl(path,buffer,s,commands[1],NULL);
      }
    }
    else if(strcmp(commands[0],"cat") == 0){
      strcat(path,og);
      strcat(path,"/cat");
      char buffer[] = "buffer";

      if(!commands[1] || commands[1] != NULL && commands[1][0] == '-' && commands[2] == NULL){
        printf("msh: Error !.😔🥲\nInvalid syntax: expects some argument to cat\n");
      }
      else{
        if(commands[2] != NULL && commands[1][0] != '-'){
          printf("msh: Error !.😔🥲\nInvalid syntax: Too many arguments for cat\n");
        }
        else{
            execl(path,buffer,commands[1],commands[2],NULL);
        }
      }
    }
    
    else if(strcmp(commands[0],"date") == 0){

      strcat(path,og);
      strcat(path,"/date");
      char buffer[] = "buffer";
      if(commands[2]){
        printf("msh: Error !. 😔🥲\nInvalid syntxa: Too many arguments for date.\n");

      }
      else{
        if(commands[1] != NULL && commands[1][0] != '-'){
            printf("msh: Error !. 😔🥲\nInvalid syntxa: Too many arguments for date.\n");
        }
        else{
          execl(path,buffer,commands[1],NULL);
        }
      }
    }
    
    else if(strcmp(commands[0],"rm") == 0){
      strcat(path,og);
      strcat(path,"/rm");
      char buffer[] = "buffer";
      if(commands[2] != NULL && commands[1][0] != '-'){
        printf("msh: Error!. 😔🥲\nInlvaid syntax: Too many arguments for rm.\n");
      }
      else{
        execl(path,buffer,s,commands[1],commands[2],NULL);
      }
    }
    else if(strcmp(commands[0],"mkdir") == 0){
      if(!commands[1] || commands[1] != NULL && commands[1][0] == '-' && commands[2] == NULL){
        printf("msh: Error !.😔🥲\nInvalid syntax: expects some argument to mkdir\n");
      }
      else{
        if (commands[2] != NULL && commands[1][0] != '-'){
          printf("msh: Error !. 😔🥲\nInvalid syntax: Too many arguments to mkdir\n");
        }
        else{
          strcat(path,og);
          strcat(path,"/mkdir");
          char buffer[] = "buffer";
          execl(path,buffer,commands[1],commands[2],NULL);
        }
      }
    }
    else{
      printf("msh: Error !. 😔🥲.\nNo such command exits in msh shell\n");
      exit(EXIT_FAILURE);
    }
  }
  else{
    p_wait = wait(NULL);
  }
}

// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
void *thread_execution(void *argument){
  // printf("1. %s\n",(char *)(argument));
  system((char*)(argument));
  return NULL;
}
void sysExecution(char **commands,char *og){
  pthread_t thread;
  char s[100],argument[1000] = {0},space[] = " ";
  getcwd(s,100);
  if(commands[0][0] == 'l' && commands[0][1] == 's'){
    // char path[] = "/Users/mahansh/Downloads/Practice/OS/Shell/ls";
    char path[] = "./ls ";
    strcat(argument,path);
    strcat(argument,s);
    if(commands[1] != NULL){;
      strcat(argument,space);
      strcat(argument,commands[1]);
    }

    if(commands[2]){
        printf("msh: Error\nInlvaid syntax: Too many arguments for ls.\n");
      }
      else{
      pthread_create(&thread,NULL,thread_execution,(void *)(argument));
    }
  }

  else if(commands[0][0] == 'c' && commands[0][1] == 'a' && commands[0][2] == 't'){
    // char path[] = "/Users/mahansh/Downloads/Practice/OS/Shell/cat";
    if(commands[1] == NULL){
      printf("msh: Error !.😔🥲\nInvalid syntax: expects some argument to cat\n");
    }
    else if(commands[2] != NULL && commands[1][0] != '-'){
      printf("msh: Error !.😔🥲\nInvalid syntax: Too many arguments for cat\n");
    }
    else{
      char path[] = "./cat ";
      strcat(argument,path);
      strcat(argument,space);
      strcat(argument,commands[1]);
      strcat(argument,space);
      if(commands[2] != NULL){
        strcat(argument,commands[2]);
      }
      pthread_create(&thread,NULL,thread_execution,(void *)(argument)); 
       
    }
  }
  
  else if(commands[0][0] == 'd' && commands[0][1] == 'a' && commands[0][2] =='t' &&commands[0][3] == 'e' ){

    if(commands[1] == NULL){
      char path[] = "./date ";
      strcat(argument,path);
      pthread_create(&thread,NULL,thread_execution,(void *)(argument));
    }
    else{
      if(commands[1] != NULL & commands[1][0] != '-'){
        printf("msh: Error !. 😔🥲\nInvalid syntxa: Too many arguments for date.\n");
      }
      else if(commands[2]){
        printf("msh: Error !. 😔🥲\nInvalid syntxa: Too many arguments for date.\n");
      }
      else{
        char path[] = "./date ";
        strcat(argument,path);
        if(commands[1] != NULL){
          strcat(argument,space);
          strcat(argument,commands[1]);
        }
        pthread_create(&thread,NULL,thread_execution,(void *)(argument));
      }
    }
  }

  else if(commands[0][0] == 'r' && commands[0][1] == 'm'){
    // char path[] = "/Users/mahansh/Downloads/Practice/OS/Shell/rm";
    char path[] = "./rm ";
    if(!commands[1]){
        printf("msh: Error!. 😔🥲\nInlvaid syntax: Expects some argument to rm.\n");
    }
    else{
      strcat(argument,path);
      strcat(argument,s);
      strcat(argument,space);
      strcat(argument,commands[1]);
      strcat(argument,space);
      if(commands[2] != NULL){
        strcat(argument,commands[2]);
      }

      if(commands[2] != NULL && commands[1][0] != '-'){
          printf("msh: Error!. 😔🥲\nInlvaid syntax: Too many arguments for rm.\n");
        }
      else{

        pthread_create(&thread,NULL,thread_execution,(void *)(argument));
      }    
    }

  }

  else if(commands[0][0] == 'm' && commands[0][1] == 'k' && commands[0][2] == 'd' && commands[0][3] == 'i' && commands[0][4] =='r'){
    // char path[] = "/Users/mahansh/Downloads/Practice/OS/Shell/mkdir";
    if(commands[1] == NULL){
      printf("msh: Error !.😔🥲\nInvalid syntax: expects some argument to mkdir\n");
    }
    else if(commands[2] != NULL && commands[1][0] != '-'){
      printf("msh: Error !.😔🥲\nInvalid syntax: Too many arguments for mkdir\n");
    }
    else{
      char path[] = "./mkdir ";
      strcat(argument,path);
      strcat(argument,space);
      strcat(argument,commands[1]);
      strcat(argument,space);
      if(commands[2] != NULL){
        strcat(argument,commands[2]);
      }
      pthread_create(&thread,NULL,thread_execution,(void *)(argument));
    }  
  }
  else{
    printf("msh: Error !. 😔🥲\nNo such command exits in msh shell\n");
    exit(EXIT_FAILURE);
  }
  pthread_join(thread,NULL);
  }

// _______________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int main(){
  printf("Welcome to msh 🥳.\nMight crash while running 🥲.\n");
  int boolean = 1;
  char s[100];
  getcwd(s,100);
  while(boolean){
    printf("\n>_ ");
    char *line = taking_input(); // taking input
    char **executable_comands = breaking_into_smaller_pieces(line); // breaking it into smaller executable commands
    if(strcmp(executable_comands[0],"exit") == 0){
      printf("Thanks for using msh !.🙇🏻‍♂️\n");
      break;
      exit(EXIT_SUCCESS);
    }
    execution(executable_comands,s); // executing commands

    free(line);
    free(executable_comands);

  }
  return EXIT_SUCCESS;
}
