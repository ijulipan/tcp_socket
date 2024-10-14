#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define QUECTEL_TIME_MAX_LEN 128
#define SA struct sockaddr

int main(int argc, char *argv[]){
    // Initialise the file descriptors
    int listenfd = -1;
    int connfd = -1;

    char buff[QUECTEL_TIME_MAX_LEN];
    time_t ticks;

    // Declare the server and client addresses
    struct sockaddr_in server_addr, client_addr;

    int sin_size;

    // Step 1: Create the server socket and verify
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(listenfd < 0){
        printf("socket creation error: %s %d\n", strerror(errno), errno);
        exit(0);
    } else {
        printf("socket creation successful!\n");
    }

    // Initialise the server address memory block
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    // Set the IP, PORT
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9980);

    // Bind the listenfd to the server address
    if(bind(listenfd, (SA*)&server_addr, sizeof(server_addr)) == -1){
        printf("bind error: %s %d\n", strerror(errno), errno);
        exit(0);
    }
    else{
        printf("bind successful!\n");
    }

    // Start listening for the client
    if(listen(listenfd, 5) == -1){
        printf("listen error: %s %d\n", strerror(errno), errno);
        exit(0);
    }

    while(1){
        // Set connfd as the new connected socket
        connfd = accept(listenfd, NULL, NULL);
        if(connfd == -1){
            printf("accept error: %s %d\n", strerror(errno), errno);
            exit(0);
        }
        else{
            printf("Accepted new connection!\n");
        }
        ticks = time(NULL);
        snprintf(buff, QUECTEL_TIME_MAX_LEN, "%.24s\r\n", ctime(&ticks));
        printf("buff=%s\r\n", buff);

        write(connfd,QUECTEL_TIME_MAX_LEN, strlen(buff));
        close(connfd);
        connfd = -1;
    }
    return 0;
}