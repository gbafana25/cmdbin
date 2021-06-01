#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/poll.h>
#include <stddef.h>

//#include "database.h"

void make_short_link(int length, char result[]) {
	char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
	char *output[length];
	memset(&output, 0, sizeof(output));
	srand(time(NULL));
	for(int i = 0; i < length; i++) {
		int index = (rand() % strlen(alphabet));
		//output[i] = &alphabet[index];
		strncat((char *) &output, (const char * restrict) &alphabet[index], 1);
	}
	strncat(result, output, strlen(output));
	//send(fd, (const void *) &response, strlen((const void *) &response), 0);

}

int main() {
	int server, client;
	int opt = 1;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	char msg[8];
	memset(&msg, 0, sizeof(msg));
	
	server = socket(AF_INET, SOCK_STREAM, 0);
	if(server == -1) {
		perror("Couldn't create socket");
		exit(0);
	}

	setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5678);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		perror("Couldn't bind socket");
		exit(1);
	}

	if(listen(server, 5) == -1) {
		perror("couldn't start listening");
		exit(1);
	}
	
	socklen_t client_size = sizeof(serv_addr);
	while (1) {
		client = accept(server, (struct sockaddr *) &client_addr, &client_size);
		make_short_link(8, msg);
		send(client, msg, strlen(msg), 0);
		memset(&msg, 0, sizeof(msg));
		//recv(client, data, 1024, 0);

	}	

}

