#ifndef MR_ERROR
#define MR_ERROR
#include<stdint.h>
#include<mr/exports.h>
typedef struct MRError
{
	char* message;
} MRError;

MRError*
mr_error_new();

#endif // !MR_ERROR
