#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

sem_t semaphore1, semaphore2;

struct shm{
	char arr[5][10];
	int id[5];
}base;


char *randomStringGenerator(int length){
	static char charSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *randomString = NULL;
	if (length){
        randomString = malloc(length + 1); 
        if (randomString){
            int l = (int) (sizeof(charSet) - 1); 
            int key; 
            for (int n = 0 ; n < length ; n++)
            {        
                key = rand() % l;   
                randomString[n] = charSet[key];
            }
            randomString[length] = '\0';
        }
	return randomString;
    }
}


int main(){
	int id = 0;
    struct timespec begin, end;
    long double diff;
	sem_init(&semaphore1, 0, 1);
	sem_init(&semaphore2, 0, 1);

	while(true){
		int shmFD;
		void* ptr;
		struct shm *shared = malloc(sizeof(base));
		struct shm *received = malloc(sizeof(base));

		clock_gettime(CLOCK_REALTIME, &begin);
		for(int i = 0; i < 5; i++){
			strcpy(shared -> arr[i], randomStringGenerator(5));
			shared -> id[i]=id;
			id++;
		}

		shmFD = shm_open("FileSHM", O_CREAT | O_RDWR, 0666); // open 
		ftruncate(shmFD, sizeof(base)); // mem link
		ptr = mmap(0, sizeof(base), PROT_WRITE, MAP_SHARED, shmFD, 0); // specific allocate

		sem_wait(&semaphore1);
		memcpy(ptr, shared, sizeof(base));
		sem_post(&semaphore1);

		shmFD = shm_open("FileSHM", O_RDONLY, 0666);
		ptr = mmap(0, sizeof(base), PROT_READ, MAP_SHARED, shmFD, 0);

		sem_wait(&semaphore2);
		memcpy(received, ptr, sizeof(base));
		sem_post(&semaphore2);

		
		if(received -> id[4] == 49)
		{
			clock_gettime(CLOCK_REALTIME, &end);
            diff = (end.tv_sec - begin.tv_sec) + (double)(end.tv_nsec - begin.tv_nsec) / (double) (1000000000);
			printf("\nHighest ID Recieved - %d\nTIme Taken - %Lf s\n", 49, diff);
			break;
		}
		
		printf("\nHighest ID Recieved - %d\n\n", received -> id[4]);

		sleep(1);

	}
	return 0;
}