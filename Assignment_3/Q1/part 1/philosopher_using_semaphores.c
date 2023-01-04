#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t chopsticks[5];

void * philosopher(void * number){

    while(1){
        if((*(int*)number)%2 == 0){
            printf("Philosopher %d is thinking\n",*(int*)(number) + 1); // Thinking phase

            sem_wait(&chopsticks[*(int*)number]); // Taking chopsticks
            printf("Philosopher %d has taken the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);
            sem_wait(&chopsticks[((*(int *)number)+1)%5]);
            printf("Philosopher %d has taken the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);

            printf("Philosopher %d is eating.\n",*(int*)(number) + 1);

            sem_post(&chopsticks[*(int*)number]); // Putting down chopsticks
            printf("Philosopher %d has put down the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);
            sem_post(&chopsticks[((*(int *)number)+1)%5]);
            printf("Philosopher %d has put down the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);


        }
        else{
            printf("Philosopher %d is thinking\n",*(int*)(number) + 1); // Thinking phase

            sem_wait(&chopsticks[((*(int *)number)+1)%5]); // Taking chopsticks
            printf("Philosopher %d has taken the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);
            sem_wait(&chopsticks[*(int*)number]);
            printf("Philosopher %d has taken the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);

            printf("Philosopher %d is eating.\n",*(int*)(number) + 1); // Eating

            sem_post(&chopsticks[((*(int *)number)+1)%5]);  // Putting down chopsticks 
            printf("Philosopher %d has put down the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);
            sem_post(&chopsticks[*(int*)number]);
            printf("Philosopher %d has put down the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);

        }
    }

}
int main(){
    int philosopher_number[5];
    pthread_t philosopher_thread[5];
    
    for(int i = 0 ; i < 5; i++){
        philosopher_number[i] = i;
        sem_init(&chopsticks[i],0,1);
    }
    for(int i = 0 ; i< 5; i ++){
        pthread_create(&philosopher_thread[i],NULL,philosopher,(void *)(&philosopher_number[i]));
    }
    for(int i = 0 ; i < 5; i++){
        pthread_join(philosopher_thread[i],NULL);
    }

    for(int i = 0 ; i < 5; i ++){
        sem_destroy(&chopsticks[i]);
    }
    return 0;
} 