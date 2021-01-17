#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
	printf("client: Simple Socket Clilent\n");

	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	char ip_address[] = "127.0.0.1";
	int port_number = 8888;

	// Create a socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error\n");
		return -1;
	}

	// Initialize a socket
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_number);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	//Connect a client socket to a server socket
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed\n");
		return -1;
	}

	send(sock, hello, strlen(hello), 0);
	printf("client: Hello msg sent\n");
	valread = read(sock, buffer, 1024);
	printf("client: received - %s\n", buffer);

	close(sock);

	return 0;
}
