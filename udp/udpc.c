#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define PORT 4000
#define MAX 1024

int main() {
    int sockfd, n, len;
    char buf[MAX + 1];  // +1 for null termination
    struct sockaddr_in server;

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        printf("Error in creating socket\n");
    else
        printf("Socket successfully created\n");

    // Zero out server struct
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    len = sizeof(server);  // Set len before loop

    printf("Connecting to server...\n");

    while (1) {
        printf("Message to be sent: ");
        scanf("%s", buf);

        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&server, len);

        if (strcmp(buf, "quit") == 0)
            break;

        printf("Message sent. Waiting for the response...\n");

        n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&server, &len);
        buf[n] = '\0';

        if (n > 1)
            printf("Received: %s\n", buf);
    }

    close(sockfd);
    return 0;
}
