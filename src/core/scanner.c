/*
 * This file is part of the Mirim project.
 *
 * Copyright 2018 Arandu Academy
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <mr/core.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define IS_LOWER(x) (x >= 'a' && x <= 'z')
#define IS_UPPER(x) (x >= 'A' && x <= 'Z')
#define IS_LETTER(x) (IS_LOWER(x) || IS_UPPER(x))
#define IS_DIGIT(x) (x >= '0' && x <= '9')

typedef enum State {
	ST_START,
  ST_ID,
  ST_LT,
  ST_EQ,
  ST_LQ,
  ST_LITERAL_START,
  ST_LITERAL_ESCAPE,
} State;

MR_EXPORTS MrToken*
mr_scanner_scan(const char* contents, uint16_t *nTokens, MrError** error) {
  char*    curp = (char*)contents;
  char*    start = curp;
	char*    rowStart = start;
  MrToken* tokens = malloc(sizeof(MrToken) * 256);
  uint16_t curToken = 0;
	uint16_t row = 0;
  uint8_t  levels[32];
  uint8_t  children[32];
  uint8_t  state = 0;
  uint8_t  levelIndex = 0;
  uint8_t  length;
  char     cur;
	char     errorMessage[128];
  memset(levels, 0, 32);
  memset(children, 0, 32);
	while (cur = *curp) {
		switch (state) {
		case ST_START:
      switch(cur) {
      case ' ':
        break;
      case '(':
			case ')':
			case '[':
			case ']':
			case '*':
			case '/':
			case '-':
			case '+':
			case '{':
			case '}':
        mr_token_set(&tokens[curToken++], start, curp, cur);
        state = ST_START;
				break;
			case '\n':
				row++;
        start = curp;
				rowStart = start;
				// Advance to non-space character or end-of-line
        do curp++; while (*curp == ' ');
        if(*curp != '\n' && *curp != '\0'){
          length = (uint8_t)(curp-start-1);
					// Is a child?
          if(length > levels[levelIndex]) {
            levels[++levelIndex] = length;
            mr_token_set(&tokens[curToken++], start, curp, '{');
            children[levelIndex]++;
          } else if (length == levels[levelIndex]){
            mr_token_set(&tokens[curToken++], start, curp, ';');
            children[levelIndex]++;
          } else while(length < levels[levelIndex]) { // Not a child
            if(children[levelIndex] == 0) {
              curToken--;
            } else {
              mr_token_set(&tokens[curToken++], start, curp, '}');
              children[levelIndex] = 0;
            }
            --levelIndex;
          }
        }
        curp--;
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
					sprintf(errorMessage, "Unexpected character in (%d,%d): ", row, curp-rowStart);
          *error = mr_error_new(errorMessage);
          free(tokens);
          return NULL;
        }
        break;
      }
      break;
		case ST_ID:
      if (!(IS_LETTER(cur) || cur == '-' || IS_DIGIT(cur))) {
        curp--;
        // Generate ID token
        mr_token_set(&tokens[curToken++], start, curp, TK_ID);
        state = ST_START;
      }
			break;
    case ST_EQ:
      if(cur == '>'){
        mr_token_set(&tokens[curToken++], start, curp, TK_EG);
        state = ST_START;
      } else {
        mr_token_set(&tokens[curToken++], start, curp, '=');
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
        mr_token_set(&tokens[curToken++], start, curp, TK_LEG);
        state = ST_START;
      } else {
        mr_token_set(&tokens[curToken++], start, curp, TK_LE);
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
        mr_token_set(&tokens[curToken++], start, curp, TK_LITERAL);
        state = ST_START;
        break;
      }
      break;
    case ST_LITERAL_ESCAPE:
      if(cur == '"'){
        state = ST_LITERAL_START;
      }
      break;
		default:
			
			break;
		}
		printf("%c", cur);
		curp++;
	}
  do {
    if(children[levelIndex] == 0) {
      curToken--;
    } else {
      mr_token_set(&tokens[curToken++], start, curp, '}');
    }
  } while(--levelIndex);
	*nTokens = curToken;
	return tokens;
}

MR_EXPORTS MrToken*
mr_scanner_scan_file(const char* filename, uint16_t *nTokens, MrError** error) {
	// Read source code from file
	char* contents = mr_file_read(filename, error);
	// Get tokens
  MrToken* tokens = NULL;
	if (!error || !(*error))
		tokens = mr_scanner_scan(contents, nTokens, error);

  // return
  return tokens;
}
