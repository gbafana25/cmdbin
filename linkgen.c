#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "database.h"
#include "linkgen.h"

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
