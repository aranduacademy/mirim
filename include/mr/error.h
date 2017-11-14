#ifndef MR_ERROR
#define MR_ERROR
#include<stdint.h>
#include<mr/exports.h>
typedef struct MRError
{
  const char* message;
} MRError;

MRError*
mr_error_new(const char *message);

#endif // !MR_ERROR
