/*

Database mockup for termbin clone (pastebin application)
store data in binary form --> index (?), link, code
use fseek to step through the file

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_link(char *link) {
	FILE *db;
	db = fopen("test.db", "a+");
	fprintf(db, "%s\n", link);
	fclose(db);

}
