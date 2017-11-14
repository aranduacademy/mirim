#include <mr/error.h>
#include <mr/macro.h>
#include <stdlib.h>

MRError*
mr_error_new(const char* message) {
  MRError* error = (MRError*) malloc(sizeof(MRError));
  error->message = message;
  return error;
}
