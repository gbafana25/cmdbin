#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/poll.h>
#include <stddef.h>

#include "database.h"
#include "linkgen.h"

#define SHORT_LINK_SIZE 8
#define RECV_BUF_SIZE 1024

int main() {
	int server, client;
	int opt = 1;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	char short_link[SHORT_LINK_SIZE], buf[RECV_BUF_SIZE];
	char *retrieve_req = "GET /f/";
	memset(&short_link, 0, sizeof(short_link));
	memset(&buf, 0, sizeof(buf));
	
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
		recv(client, buf, sizeof(buf), 0);	
		if(strncmp(buf, retrieve_req, strlen(retrieve_req)) == 0) {
			send(client, "test", sizeof(char) * 4, 0);
			close(client);
			memset(&buf, 0, sizeof(buf));
		} else {
			for(int i = 0; i < strlen(buf); i++) {
				printf("%c", buf[i]);
			}
			printf("\n");
			make_short_link(SHORT_LINK_SIZE, short_link);
			write_link(short_link);
			close(client);
			memset(&buf, 0, sizeof(buf));
			memset(&short_link, 0, sizeof(short_link));
		}

	}	

}

