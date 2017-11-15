#include <mr/core.h>

void
mr_token_set(MrToken *token, char *start, char *end, MRTokenType type) {
  token->start = start;
  token->end = end;
  token->type = type;
}
