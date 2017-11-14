#include <mr/scanner.h>
#include <mr/file.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define IS_LOWER(x) (x >= 'a' && x <= 'z')
#define IS_UPPER(x) (x >= 'A' && x <= 'Z')
#define IS_LETTER(x) (IS_LOWER(x) || IS_UPPER(x))
#define IS_DIGIT(x) (x >= '0' && x <= '9')
#define TOKEN_ADD(list, i, s, e, t) \
list[i].start = s; \
list[i].end = e; \
list[i++].type = t;

typedef enum State {
	ST_START,
  ST_ID,
  ST_LT,
  ST_EQ,
  ST_LQ,
  ST_LITERAL_START,
  ST_LITERAL_ESCAPE,
} State;

typedef enum MRTokenType {
  TK_ID,
  TK_LEG,
  TK_EG,
  TK_LE,
  TK_LITERAL,
  TK_BLK_OPEN,
  TK_BLK_CLOSE
} MRTokenType;

typedef struct MRToken {
  char* start;
  char* end;
  MRTokenType type;
} MRToken;

void MR_EXPORTS
mr_parser_scan(const char* contents, MRError** error) {
  char*    curp = (char*)contents;
  char     cur;
  char*    start = curp;
  MRToken* tokens = malloc(sizeof(MRToken) * 256);
  uint16_t curToken = 0;
  uint8_t  state = 0;
  uint8_t  levels[32];
  uint8_t  levelIndex = 0;
  uint8_t  length;
  memset(levels, 0, 32);
	while (cur = *curp) {
		switch (state) {
		case ST_START:
      switch(cur) {
      case ' ':
        break;
      case '{':
        TOKEN_ADD(tokens, curToken, start, curp, TK_BLK_OPEN);
        state = ST_START;
        break;
      case '}':
        TOKEN_ADD(tokens, curToken, start, curp, TK_BLK_CLOSE);
        state = ST_START;
        break;
      case '\n':
        start = curp;
        do curp++; while (*curp == ' ');
        if(*curp != '\n'){
          length = curp-start-1;
          if(length > levels[levelIndex]) {
            levels[++levelIndex] = length;
            TOKEN_ADD(tokens, curToken, start, curp, TK_BLK_OPEN);
          } else while(length < levels[levelIndex]) {
            --levelIndex;
            TOKEN_ADD(tokens, curToken, start, curp, TK_BLK_CLOSE);
          }
        } else curp--;
        break;
      case '<':
        state = ST_LT;
        start = curp;
        break;
      case '"':
        state = ST_LITERAL_START;
        start = curp;
        break;
      case '=':
        state = ST_EQ;
        start = curp;
        break;
      default:
        if (IS_LETTER(cur)) {
          state = ST_ID;
          start = curp;
        } else {
          *error = mr_error_new("Expected letter");
          free(tokens);
          return;
        }
        break;
      }
      break;
		case ST_ID:
      if (!(IS_LETTER(cur) || cur == '-')) {
        curp--;
        // Generate ID token
        TOKEN_ADD(tokens, curToken, start, curp, TK_ID);
        state = ST_START;
      }
			break;
    case ST_EQ:
      if(cur == '>'){
        TOKEN_ADD(tokens, curToken, start, curp, TK_EG);
        state = ST_START;
      } else {
        TOKEN_ADD(tokens, curToken, start, curp, '=');
        state = ST_START;
        curp--;
      }
      break;
    case ST_LT:
      if(cur == '='){
        state = ST_LQ;
      }
      break;
    case ST_LQ:
      if(cur == '>'){
        TOKEN_ADD(tokens, curToken, start, curp, TK_LEG);
        state = ST_START;
      } else {
        TOKEN_ADD(tokens, curToken, start, curp, TK_LE);
        state = ST_START;
        curp--;
      }
      break;
    case ST_LITERAL_START:
      switch(cur){
      case '\\':
        state = ST_LITERAL_ESCAPE;
        break;
      case '"':
        TOKEN_ADD(tokens, curToken, start, curp, TK_LITERAL);
        state = ST_START;
        break;
      }
      break;
    case ST_LITERAL_ESCAPE:
      if(cur == '"'){
        state = ST_LITERAL_START;
      }
      break;
		}
		printf("%c", cur);
		curp++;
	}
}

MR_EXPORTS
void mr_parser_scan_file(const char* filename, MRError** error) {
	char* contents = mr_file_read(filename, error);
	if (!error || !(*error))
		mr_parser_scan(contents, error);
	free(contents);
}

