/*

Database mockup for termbin clone (pastebin application)
store data in binary form --> index (?), link, code
use fseek to step through the file

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINK_SIZE 8
#define MAX_CODE_SIZE 50

typedef struct {
	char link[LINK_SIZE + 1];
	char code[MAX_CODE_SIZE + 1];

} Entry;

void read_data(FILE *storage, Entry *result) {
	storage = fopen("test.db", "rb");
	fread(result->link, sizeof(char) * LINK_SIZE, 1, storage);
	fseek(storage, sizeof(char) * LINK_SIZE + 1, SEEK_SET);
	fread(result->code, sizeof(char) * MAX_CODE_SIZE + 1, 1, storage);
	fclose(storage);
	printf("%s\n", result->link);
	printf("%s\n", result->code);
	
}

int main() {
	Entry *test = malloc(sizeof(Entry));
	Entry *results = malloc(sizeof(Entry));
	scanf("%s %s", test->link, test->code);
	if(strlen(test->link) > LINK_SIZE || strlen(test->code) > MAX_CODE_SIZE) {
		exit(1);
	} else {

	}
	FILE *db;
	db = fopen("test.db", "ab");
	fwrite(test, sizeof(Entry), 1, db);
	fclose(db);
	FILE *store;
	Entry *read_s = malloc(sizeof(Entry));
	read_data(store, read_s);

}
