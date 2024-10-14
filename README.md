# TCP Socket Programming

This repo serves as an introductory repo to showcase how to do basic programming using TCP protocol. Relevant documents and knowledge will be shared in this readme.

## What is Socket Programming?

Socket programming is a way of connecting two nodes on a network to communicat with each other. One socket(node) listens on a particular port and IP while the other reaches out to form a connection. Refer to diagram below:-

![TCP handshake](/etc/tcp-handshake-diagram.png)

As shown above, it is a connection between two nodes where one listens and one talks. The listener is generally called the **server** node while the talker is the **client** node.


## How to start programming a Server and Client Model?

![State Diagram Model](/etc/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png)

As shown above, there are mainly two similar processes that is done to create a TCP connection; **Server Process** and **Client Process**. We will focus on each component separately.

### Server Process

1. `socket()`

The `socket()` function creates the socket for the server. The function is declared as follows:-

```C
int sockfd = socket(domain, type, protocol)`
```

- **sockfd**: Socket file descriptor
- **domain**: Specifies communication domain. For the same host but different processes, use `AF_LOCAL`. For different hosts, use `AF_INET` for hosts connected by IPV4 and `AF_INET6` for hosts connected by IPV6.
- **type**: Specifies communication type. `SOCK_STREAM` is used for TCP(connection-oriented). `SOCK_DGRAM` is used for UDP(connectionless).
- **protocol**: Protocol value for Internet Protocol (IP), which is 0.

2. `bind()`

The `bind()` function binds the socket to the address and port number specified. The function is declared as follows:-

```C
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- **sockfd**: Socket file descriptor created previously
- **addr**: pointer to the memory location of the socket address
- **addrlen**: Size of the socket

3. `listen()`

The `listen()` function puts the server socket into passive mode where it waits for the client to approach the server to make a connection. The function is declared as follows:-

```C
int listen(int sockfd, int backlog);
```

- **backlog**: Is the maximum length to which the queue of pending connections for sockfd to grow.

4. `accept()`

The `accept()` function will extract the first connection request on the queue of pending connections for the listening socket and return a file descriptor referring to that socket.

```C
int new_socket=accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
- **sockfd**: The file descriptor for the new connected socket
- **addr**: Address for the new connected socket
- **addrlen**: Address length for the new connected socket


### Client Process

1. `socket()`

This function is exactly the same as the server process function.

2. `connect()`

The `connect()` function connects the socket referred to by the file descriptor to the address specified by addr. The function is declared as follow:-

```C
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```
