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
    char buf[MAX];
    struct sockaddr_in server, cli;

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

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Socket bind failed...\n");
        return 1;
    } else {
        printf("Socket successfully binded...\n");
    }

    printf("Waiting for client...\n");

    len = sizeof(cli);  // Set len before the loop

    do {
        n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &len);
        buf[n] = '\0';

        if (n > 1)
            printf("received : %s \n", buf);

        scanf("%s", buf);
        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, len);

    } while (strcmp(buf, "quit") != 0);

    close(sockfd);
    return 0;
}
