#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <unistd.h> // read(), write(), close() functions

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed to chat between client and server
void func(int connfd){
    char buff[MAX];
    int n;

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To Client: ", buff);
        bzero(buff, MAX);
        n = 0;
        // Copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // Send that buffer to client
        write(connfd, buff, sizeof(buff));

        // If msg contains "Exit" then exit server and end the chat
        if(strncmp("exit", buff, 4) == 0){
            printf("Server exit..\n");
            break;
        }
    }
}

// Main Driver Function
int main(){
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket creation and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        printf("socket creation failed...\n");
        exit(0);
    } else {
        printf("socket successfully created...\n");
    }
    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind newly created socket to given IP and verify
    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
        printf("socket bind failed...\n");
        exit(0);
    }
    else{
        printf("Socket successfully binded...\n");
    }

    // Listen to server and verify
    if((listen(sockfd, 5)) != 0){
        printf("Listen failed...\n");
        exit(0);
    }
    else{
        printf("Server listening...\n");
    }
    len = sizeof(cli);

    // Accept the data packet from client and verify
    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd < 0){
        printf("server accept failed...\n");
        exit(0);
    }
    else{
        printf("server accept the client...\n");
    }

    // Function for chatting between client and server
    func(connfd);

    // After chatting finished, close the socket
    close(sockfd);

}