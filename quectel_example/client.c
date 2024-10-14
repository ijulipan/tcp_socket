#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define QUECTEL_TIME_MAX_LEN 128
#define SA struct sockaddr

int main(int argc, char *argv[]){
    // Initialise the file descriptors to -1
    int connectfd = -1;
    int connfd = -1;

    char buff[QUECTEL_TIME_MAX_LEN];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int n;

    // Create a new socket called connectfd
    connectfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if(connectfd < 0){
        printf("socket creation error: %s %d\n", strerror(errno), errno);
        exit(0);
    } else{
        printf("Socket creation successful!\n");
    }

    // Set the memory blocks of server and client's address to 0
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // Set the IP and port of the client address
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(9981);

    // Bind the client address to the file descriptor
    if(bind(connectfd, (SA*)&client_addr, sizeof(client_addr)) == -1){
        printf("bind error: %s %d\n", strerror(errno), errno);
    } else{
        printf("bind successful!\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9980);

    if(connect(connectfd, (SA*)&server_addr, sizeof(server_addr)) == -1){
        printf("connect error: %s %d", strerror(errno), errno);
        exit(0);
    } else {
        printf("connection successful!\n");
    }

    while((n = read(connectfd, buff, QUECTEL_TIME_MAX_LEN))){
        buff[n] = 0;
        printf("%s\r\n", buff);
    }

    if(n < 0){
        printf("recv error");
    }
    close(connectfd);

    return 0;
}