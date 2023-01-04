#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
  
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

int main(int argc, char *argv[]) {
    int x = 0;
    int fd;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }
    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "my_socket");

    if (connect(fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("connect");
        exit(1);
    }

    struct timespec start,end;
    clock_gettime(CLOCK_REALTIME, &start);
    for(int loop = 0 ; loop < 10; loop ++){
        char arr[5][5] = {0};
        struct datasent data;
        printf("\nStrings sent: \n");
        for(int i = 0 ; i < 5; i ++){
            randomString(data.string,i);
            data.index[i] = i + x +1;
        }

        if (write(fd, &data, sizeof(data)) < 0) {
            perror("write");
            exit(1);
        }

        int index = 0;
        if (read(fd, &index, sizeof(int)) < 0) {
            perror("read");
            exit(1);
        }
        printf("In Sender's process\nHighest index: %d\n",index);
        x += 5;
    }

    close(fd);
    clock_gettime(CLOCK_REALTIME, &end);
    double time = (end.tv_sec - start.tv_sec) +(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken: %f: \n",time);
    return 0;
}
