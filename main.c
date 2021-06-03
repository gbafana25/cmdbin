#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <ctype.h>
#include <sys/poll.h>
#include <stddef.h>
#include <sys/stat.h>

#include "database.h"
#include "linkgen.h"

#define SHORT_LINK_SIZE 8
#define RECV_BUF_SIZE 1024
#define LINK_OFFSET 7

int main() {
	int server, client;
	int opt = 1;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	char short_link[SHORT_LINK_SIZE], buf[RECV_BUF_SIZE];
	char sendbuf[RECV_BUF_SIZE];
	char *retrieve_req = "GET /f/";
	char *line;
	size_t size = 0;
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
		memset(&sendbuf, 0, sizeof(sendbuf));
		if(strncmp(buf, retrieve_req, strlen(retrieve_req)) == 0) {
			FILE *db;
			db = fopen("test.db", "r");
			while(getline(&line, &size, db) != -1) {
				printf("%s", line);
				char sh[SHORT_LINK_SIZE];
				strncpy(sh, buf+LINK_OFFSET, SHORT_LINK_SIZE);
				if(strncmp(line, sh, SHORT_LINK_SIZE) == 0) {
					printf("got match\n");	
					char *path[15];
					memset(&path, 0, sizeof(path));
					strncat((char * restrict) &path, "pastes/", 7);
					strncat((char * restrict) &path, line, strlen(line) - 1);
					//printf("%s", path);
					char *output;
					memset(&output, 0, sizeof(output));
					FILE *val;
					val = fopen(path, "r");
					while(getline(&output, &size, val) != -1) {
						//printf("%s", output);
						strncat((char * restrict) &sendbuf, output, strlen(output));
					}
					send(client, sendbuf, sizeof(sendbuf), 0);
					
				}
			}
			//printf("%s", buf+LINK_OFFSET);
			close(client);
			memset(&buf, 0, sizeof(buf));
		} else {
			mkdir("pastes", S_IRWXU);
			char fullpath[15]; 
			make_short_link(SHORT_LINK_SIZE, short_link);
			strncat((char * restrict) &fullpath, "pastes/", 7);
			strncat((char * restrict) &fullpath, short_link, strlen(short_link));
			write_link(short_link);
			FILE *paste;
			paste = fopen(fullpath, "w+");
			fprintf(paste, "%s\n", buf);
			fclose(paste);
			close(client);
			memset(&buf, 0, sizeof(buf));
			memset(&short_link, 0, sizeof(short_link));
			memset(&fullpath, 0, sizeof(fullpath));
		}

	}	

}

