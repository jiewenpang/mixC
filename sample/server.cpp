#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <netinet/in.h>
using namespace std;

#define MAXPENDING 5 
#define BUFFSIZE 1024
void services(int sock) {
	char buffer[BUFFSIZE];
	int received = -1;

	if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
		perror("Failed to receive");
		exit(1);
	}

	while (received > 0) {
		if (send(sock, buffer, received, 0) != received) {
			perror("Failed to send  back");
			exit(1);
		}

		if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
			perror("Failed to receive");
			exit(1);
		}
	}
	close(sock);
}

int main(int argc, char *argv[]) {
	int serversock, clientsock;
	struct sockaddr_in echoserver, echoclient;

	if (argc != 2) {
		fprintf(stderr, "USAGE: server <port>\n");
		exit(1);
	}

	if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Failed to create socket");
		exit(1);
	}

	memset(&echoserver, 0, sizeof(echoserver));
	echoserver.sin_family = AF_INET;
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);
	echoserver.sin_port = htons(atoi(argv[1]));

	if (bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
		perror("Failed to bind the server socket");
		exit(1);
	}	

	if (listen(serversock, MAXPENDING) < 0) {
		perror("Failed to listen on server socket");
		exit(1);
	}

	while (1) {
		unsigned int clientlen = sizeof(echoclient);
		if ((clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen)) < 0) {
			perror("Failed to accept client connection");
			exit(1);
		}
		fprintf(stdout, "Client connected: %s\n", inet_ntoa(echoclient.sin_addr));
		services(clientsock);
	}
}
