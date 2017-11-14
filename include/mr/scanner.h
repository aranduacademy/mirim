#ifndef MR_SCANNER
#define MR_SCANNER

#include<mr/error.h>

/**
 * Scan file and generate the token
 */
MR_EXPORTS void
mr_parser_scan_file(const char* filename, MRError** error);

/**
 * Scan text and return list of tokens
 */
void MR_EXPORTS
mr_parser_scan(const char* contents, MRError** error);

#endif
