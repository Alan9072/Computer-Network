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
void func(int sockfd) {
    char buff[MAX]; // Buffer to store messages
    int n;
    
    for (;;) { // Infinite loop for continuous communication
        bzero(buff, sizeof(buff)); // Clear the buffer before taking input
        printf("Enter the string : ");
        n = 0;
        
        // Read user input character by character until Enter is pressed
        while ((buff[n++] = getchar()) != '\n');
        
        // Send the user input to the server
        write(sockfd, buff, sizeof(buff));
        
        bzero(buff, sizeof(buff)); // Clear the buffer before reading server response
        read(sockfd, buff, sizeof(buff)); // Receive message from the server
        printf("From Server : %s", buff); // Display server response
        
        // Check if the received message is "exit", if so, terminate the connection
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    } else {
        printf("Socket successfully created..\n");
    }
    
    bzero(&servaddr, sizeof(servaddr)); // Clear the server address structure

    // Assign IP and PORT
    servaddr.sin_family = AF_INET; // Set address family to IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost IP
    servaddr.sin_port = htons(PORT); // Convert port number to network byte order

    // Connect the client socket to the server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Connection with the server failed...\n");
        exit(0);
    } else {
        printf("Connected to the server..\n");
    }

    // Call function to handle communication
    func(sockfd);

    // Close the socket after communication ends
    close(sockfd);
}
