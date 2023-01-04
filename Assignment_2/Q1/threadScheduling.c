#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>


void *countA(){
    struct sched_param a;
    a.sched_priority = 0;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &a);
    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME, &start);
    long int i = pow(2,32);
    while(i >=0){
        i--;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    double * returnValue = malloc(sizeof(double));
    *returnValue = time;
    return (void*) returnValue;
}
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void *countB(void * priority){
    struct sched_param b;
    b.sched_priority = (int*)priority;
    pthread_setschedparam(pthread_self(), SCHED_OTHER, &b);
    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME, &start);
    long int i = pow(2,32);
    while(i >=0){
        i--;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    double * returnValue = malloc(sizeof(double));
    *returnValue = time;
    return (void*) returnValue;
}
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void *countC(void * priority){
    struct sched_param c;
    c.sched_priority = (int*)priority;
    pthread_setschedparam(pthread_self(), SCHED_RR, &c);
    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME, &start);
    long int i = pow(2,32);
    while(i >=0){
        i--;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    double * returnValue = malloc(sizeof(double));
    *returnValue = time;
    return (void*) returnValue;
}
// _____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int main(){
    FILE* file_pointerA = fopen("threadA.txt", "w");
    FILE* file_pointerB = fopen("threadB.txt", "w");
    FILE* file_pointerC = fopen("threadC.txt", "w");
    if(!(file_pointerA)){
        perror("Error :");
    }
    if(!(file_pointerB)){
        perror("Error :");
    }
    if(!(file_pointerC)){
        perror("Error :");
    }
    for(int i = 1; i < 20; i++){
        printf("\n%d. Loop\n",i);
        pthread_t threadA, threadB, threadC;
        double* time;
        double arrTime[3];
        pthread_create(&threadA,NULL,countA,(void*) i); 
        pthread_create(&threadB,NULL,countB,(void*) i); 
        pthread_create(&threadC,NULL,countC,(void*) i); 

        pthread_join(threadA, (void *)&time);
        arrTime[0] = *time;
        *time = 0;
        pthread_join(threadB, (void *)&time);
        arrTime[1] = *time;
        *time = 0;
        pthread_join(threadC, (void *)&time);
        arrTime[2] = *time;
        *time = 0;

        for(int i = 0 ; i < 3; i ++){
            printf("       >> %lf",arrTime[i]);
            printf("\n");
        }
        fprintf(file_pointerA,"%lf\n",arrTime[0]);
        // fprintf(file_pointerA,"%lf\n");
        fprintf(file_pointerB,"%lf\n",arrTime[1]);
        // fprintf(file_pointerB,"%lf\n");
        fprintf(file_pointerC,"%lf\n",arrTime[2]);
        // fprintf(file_pointerC,"%lf\n");
    }
    fclose(file_pointerA);
    fclose(file_pointerB);
    fclose(file_pointerC);
    return 0;
}
