#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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


int main(){
	sem_init(&semaphore1, 0, 1);
	sem_init(&semaphore2, 0, 1);

	while(true){
		sleep(1);
		int shmFD;
		void* ptr;

		struct shm *shared = malloc(sizeof(base));
		struct shm *received = malloc(sizeof(base));

		shmFD = shm_open("FileSHM", O_RDONLY, 0666);
		ptr = mmap(0, sizeof(base), PROT_READ, MAP_SHARED, shmFD, 0);

		sem_wait(&semaphore1);
		memcpy(received, ptr, sizeof(base));
		sem_post(&semaphore1);

		for(int i = 0; i < 5; i++){
			printf("%d %s\n", received -> id[i], received -> arr[i]);
		}

		shmFD = shm_open("FileSHM", O_CREAT | O_RDWR, 0666);
		ftruncate(shmFD, sizeof(base));
		ptr = mmap(0, sizeof(base), PROT_WRITE, MAP_SHARED, shmFD, 0);

		sem_wait(&semaphore2);
		memcpy(ptr, shared, sizeof(base));
		sem_post(&semaphore2);

		if(received -> id[4] == 49){
			shm_unlink("FileSHM");
			break;
		}
	}
	return 0;
}