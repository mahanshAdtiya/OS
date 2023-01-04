#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

char character[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
struct datasent{
    char string[5][5];
    int index[5];
};

void randomString(char arr[][5], int index){
    for(int i = 0 ; i < 5; i ++){;
        arr[index][i] = character[rand() % (int)(sizeof(character) -1)];
        printf("%c",arr[index][i]);
    }
    printf("\n");

}

int main(){
    int x = 0;
    srand(time(NULL));
    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME, &start);
    for(int loop = 0 ; loop < 10 ; loop ++){
        char arr[5][5] = {0};

        struct datasent data;
        printf("\nStrings sent: \n");
        for(int i = 0 ; i < 5; i ++){
            randomString(data.string,i);
            data.index[i] = i + x + 1;
        }
        
        int fd;
        fd = open("ipc",O_WRONLY);
        if(fd == -1){ exit(1);return 1;}

        write(fd, &data, sizeof(data));
        close(fd);

        sleep(2);

        fd = open("ipc",O_RDONLY);
        if(fd == -1){ exit(1);return 2;}
        int index;
        read(fd,&index,sizeof(int));
        close(fd);
        printf("In Sender's process\nHighest Index: %d\n",index);
        x += 5;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken: %f: \n",time);
    return 0;
}
