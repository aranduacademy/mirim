#include <mr/scanner.h>
#include <stdio.h>
int main(int argc, char** argv) {
	MRError* error = NULL;
	mr_parser_scan_file("test.mr", &error);
	if (error) {
		fprintf(stderr, "Error\n");
	}
	return 0;
}
