#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int forks[5] = {0};
int chopsticks[5];
int bowls[2];

void Lock(int index){
    while(chopsticks[index] == 1){}
    chopsticks[index] = 1;
}

void Unlock(int index){
    chopsticks[index] = 0;
    while(chopsticks[index] == 1){}
}

void Trylock(int index){
    if(bowls[0] == 0){
        printf("Philosopher %d has taken up the bowl 1\n",index);
        bowls[0] = 1;
    }
    else if(bowls[1] == 0){
        printf("Philosopher %d has taken up the bowl 2\n",index);
        bowls[1] = 1;
    }
    else if(bowls[0] == 1){
        while(bowls[0] == 1){}
    }
    else if(bowls[1] == 1){
        while(bowls[1] == 1){}
    }

}

void Tryunlock(int index){
    if(bowls[0] == 1){
        bowls[0] = 0;
        printf("Philosopher %d has taken up the bowl 1\n",index);
    }
    else if (bowls[1] == 1){
        bowls[1] = 1;
        printf("Philosopher %d has taken up the bowl 2\n",index);
    }
}

void * philosopher(void * number){
    while(1){
        if((*(int*)number)%2 == 0){
            printf("Philosopher %d is thinking\n",*(int*)(number) + 1); // Thinking phase

            Lock(*(int*)number); // Taking chopsticks
            printf("Philosopher %d has taken the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);
            Lock(((*(int *)number)+1)%5);
            printf("Philosopher %d has taken the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);

            Trylock(*(int *)number + 1);

            printf("Philosopher %d is eating.\n",*(int*)(number) + 1);
           
            Tryunlock(*(int *)number + 1);

            pthread_mutex_unlock(&chopsticks[*(int*)number]); // Putting down chopsticks
            printf("Philosopher %d has put down the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);
            pthread_mutex_unlock(&chopsticks[((*(int *)number)+1)%5]);
            printf("Philosopher %d has put down the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);

        }
        else{
            printf("Philosopher %d is thinking\n",*(int*)(number) + 1); // Thinking phase

            pthread_mutex_lock(&chopsticks[((*(int *)number)+1)%5]); // Taking chopsticks
            printf("Philosopher %d has taken the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);
            pthread_mutex_lock(&chopsticks[*(int*)number]);
            printf("Philosopher %d has taken the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);
            
            Trylock(*(int *)number + 1);
    
            printf("Philosopher %d is eating.\n",*(int*)(number) + 1); // Eating

            Tryunlock(*(int *)number + 1);

            pthread_mutex_unlock(&chopsticks[((*(int *)number)+1)%5]);  // Putting down chopsticks 
            printf("Philosopher %d has put down the fork to it's right, i.e. fork number %d.\n",*(int*)(number) + 1,(((*(int *)number)+1)%5) + 1);
            pthread_mutex_unlock(&chopsticks[*(int*)number]);
            printf("Philosopher %d has put down the fork to it's left, i.e. fork number %d.\n",*(int*)(number) + 1,*(int *)number + 1);

        }

    }
}

void * philosopher2(void * number ){

}

int main(){
    int philosopher_number[5];
    pthread_t philosopher_thread[5];
    
    for(int i = 0 ; i < 5; i++){
        philosopher_number[i] = i;
        chopsticks[i] = 0;
        bowls[i] = 0;
    }

    for(int i = 0 ; i< 5; i ++){
        pthread_create(&philosopher_thread[i],NULL,philosopher,(void *)(&philosopher_number[i]));
    }
    for(int i = 0 ; i < 5; i++){
        pthread_join(philosopher_thread[i],NULL);
    }

    for(int i = 0 ; i < 5; i ++){
        pthread_mutex_destroy(&chopsticks[i]);
    }
    return 0;
}