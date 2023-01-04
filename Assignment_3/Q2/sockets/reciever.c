#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

struct datarecieved{
char string[5][5];
int index[5];
};

int main(int argc, char *argv[]) {
    
    int fd;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_un serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, "my_socket");


    if (bind(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, 5) < 0) {
        perror("listen");
        exit(2);
    }

    struct sockaddr_un clientAddress;
    socklen_t client_len = sizeof(clientAddress);
    int client_sockfd = accept(fd, (struct sockaddr *)&clientAddress, &client_len);
    if (client_sockfd < 0) {
        perror("accept");
        exit(1);
    }
    
    int index = 0;
    for(int loop = 0 ; loop < 10; loop ++){
        struct datarecieved data;
        if (read(client_sockfd, &data, sizeof(data)) < 0) {
            perror("read");
            exit(1);
        }
        printf("\nStrings Received:\n");
        for(int i = 0 ; i < 5; i ++){
            printf("%d. ",i  + index + 1);
            for(int j = 0 ; j < 5; j ++){
            printf("%c",data.string[i][j]);
            }
            printf("\n");
        }
        index += 5;
        int arr[1];
        arr[0] = data.index[4];
        if (write(client_sockfd, arr, sizeof(int)) < 0) {
            perror("Error writing message to client");
            exit(EXIT_FAILURE);
        }
    }

    close(client_sockfd);
    close(fd);

    return 0;
}