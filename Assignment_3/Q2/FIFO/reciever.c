#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct datareceived{
    char string[5][5];
    int index[5];
};

int main(){
    int index = 0;
    for(int i =0 ; i < 10; i ++){
        sleep(2);
        int fd;
        fd = open("ipc",O_RDONLY);
        if(fd == -1){ exit(1);return 1;}

        struct datareceived data;
        read(fd,&data,sizeof(data));
        printf("\nStrings Received:\n");
        for(int i = 0 ; i < 5; i ++){
            printf("%d. ",index + i + 1);
            for(int j = 0 ; j < 5; j ++){
            printf("%c",data.string[i][j]);
            }
            printf("\n");
        }
        close(fd);

        fd = open("ipc",O_WRONLY);
        if(fd == -1){ exit(1);return 2;}
        write(fd,&data.index[4],sizeof(int));
        close(fd);
        index += 5;
    }
    return 0;
}
