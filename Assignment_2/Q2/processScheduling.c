#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
    int pid1, p_wait,pid2,pid3,p_wait1,p_wait2,p_wait3;
    struct timespec start1,end1,start2,end2,start3,end3;
    clock_gettime(CLOCK_REALTIME, &start1);
    pid1 = fork();
    if(pid1 < 0){
        printf("msh: Error - Fork Failed !. 😔🥲\n");
        exit(EXIT_FAILURE);
    }
  
    else if(pid1 == 0){
        execl("/bin/bash","/bin/bash","bashscript1.sh");
    }
    else{
        clock_gettime(CLOCK_REALTIME, &start2);
        pid2 = fork();
        if(pid2<0){
            printf("msh: Error - Fork Failed !. 😔🥲\n");
            exit(EXIT_FAILURE);
        }
        else if(pid2 == 0){
            execl("/bin/bash","/bin/bash","bashscript2.sh");
        }
        else{
            clock_gettime(CLOCK_REALTIME, &start2);
            pid3 = fork();
            if(pid3 <0){
                printf("msh: Error - Fork Failed !. 😔🥲\n");
                exit(EXIT_FAILURE);
            }
            else if(pid3 == 0){
                execl("/bin/bash","/bin/bash","bashscript3.sh");
            }
            else{
                p_wait1 = waitpid(pid1,NULL,0);
                clock_gettime(CLOCK_REALTIME, &end1);
                p_wait2 = waitpid(pid2,NULL,0);
                clock_gettime(CLOCK_REALTIME, &end2);
                p_wait3 = waitpid(pid3,NULL,0);
                clock_gettime(CLOCK_REALTIME, &end3);
            }
        }
    }
    return 0;
}