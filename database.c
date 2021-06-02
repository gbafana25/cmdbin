#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_link(char *link) {
	FILE *db;
	db = fopen("test.db", "a+");
	fprintf(db, "%s\n", link);
	fclose(db);

}
