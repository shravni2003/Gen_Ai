// 2. Write a program for UDP to demonstrate the socket system calls in c/python

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int sockfd;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in servaddr, cliaddr;

	// Create UDP socket
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    	perror("socket creation failed");
    	exit(EXIT_FAILURE);
	}

	// Initialize server address structure
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind socket with server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    	perror("bind failed");
    	exit(EXIT_FAILURE);
	}

	int len, n;
	len = sizeof(cliaddr); // len is value/result

	// Receive message from client
	n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);

	// Reply to client
	const char *message = "Hello from server";
	sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
	printf("Message sent to client\n");

	// Close the socket
	close(sockfd);
	return 0;
}


//first run udpserver then run udpclient

// gcc -o udp_server udp_server.c
// gcc -o udp_client udp_client.c

// ./udp_server
// ./udp_client
