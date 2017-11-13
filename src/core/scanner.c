#include <mr/scanner.h>
#include <mr/file.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define IS_LOWER(x) (x >= 'a' && x <= 'z')
#define IS_UPPER(x) (x >= 'A' && x <= 'Z')
#define IS_LETTER(x) (IS_LOWER(x) || IS_UPPER(x))
#define IS_DIGIT(x) (x >= '0' && x <= '9')

typedef enum State {
	ST_START,
	ST_ID
};

void MR_EXPORTS
mr_parser_scan(const char* contents, MRError** error) {
	char* curp = (char*)contents;
	char  cur;
	uint8_t state = 0;
	while (cur = *curp) {
		switch (state) {
		case ST_START:
			if (IS_LETTER(cur)) {
				state = ST_ID;
			} else {
				*error = mr_error_new("Expected letter");
			}
			break;
		case ST_ID:
			if (IS_LETTER(cur) || cur == '-') {

			} else {

				curp--;
			}
			break;
		}
		printf("%c", cur);
		curp++;
	}
}

void MR_EXPORTS
mr_parser_scan_file(const char* filename, MRError** error) {
	char* contents = mr_file_read(filename, error);
	if (!error || !(*error))
		mr_parser_scan(contents, error);
	free(contents);
}

