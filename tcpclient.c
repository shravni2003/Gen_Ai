#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE] = {0};

	// Create TCP socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    	perror("socket failed");
    	exit(EXIT_FAILURE);
	}

	// Prepare sockaddr_in structure
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    	perror("inet_pton");
    	exit(EXIT_FAILURE);
	}

	// Connect to server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    	perror("connect");
    	exit(EXIT_FAILURE);
	}

	// Receive message from server
	read(sock, buffer, BUFFER_SIZE);
	printf("Message from server: %s\n", buffer);

	// Close the socket
	close(sock);
	return 0;
}
