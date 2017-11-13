#include <mr/file.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char*
mr_file_read(const char* filename, MRError** error) {
	FILE *f = fopen(filename, "r");
	if (f) {
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);  //same as rewind(f);

		char *string = malloc(fsize + 1);
		fread(string, fsize, 1, f);
		fclose(f);
		string[fsize] = 0;
		return string;
	}
	else {
		return NULL;
	}
}