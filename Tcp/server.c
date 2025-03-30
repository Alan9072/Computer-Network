#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function to handle communication between client and server
void func(int connfd) {
    char buff[MAX]; // Buffer to store messages
    int n;
    
    for (;;) { // Infinite loop for continuous communication
        bzero(buff, MAX); // Clear the buffer before reading input
        
        // Read the message from client
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\t To client : ", buff);
        
        bzero(buff, MAX); // Clear the buffer before taking server input
        n = 0;
        
        // Read server response from stdin
        while ((buff[n++] = getchar()) != '\n');
        
        // Send server response to client
        write(connfd, buff, sizeof(buff));
        
        // If the message is "exit", terminate communication
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main() {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    
    bzero(&servaddr, sizeof(servaddr)); // Clear server address structure

    // Assign IP and PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Bind socket to the given IP and PORT
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    } else {
        printf("Socket successfully binded..\n");
    }

    // Start listening for client connections
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else {
        printf("Server listening..\n");
    }
    len = sizeof(cli);

    // Accept client connection
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server accept failed...\n");
        exit(0);
    } else {
        printf("Server accepted the client...\n");
    }

    // Handle client communication
    func(connfd);

    // Close socket after communication ends
    close(sockfd);
}
