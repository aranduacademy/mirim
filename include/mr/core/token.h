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

#if !defined(MR_CORE_H_INSIDE)
#error "Only <mr/core.h> can be included directly."
#endif
#ifndef MR_TOKEN_H
#define MR_TOKEN_H

/**
 * Type of some complex tokens.
 */
typedef enum MRTokenType {
  TK_ID,
  TK_LEG,
  TK_EG,
  TK_LE,
  TK_LITERAL,
} MRTokenType;

/**
 * Info about a single token
 */
typedef struct MrToken {
  char* start;
  char* end;
  MRTokenType type;
} MrToken;

/**
 * @brief Set token
 * @param token
 * @param start
 * @param end
 * @param type
 */
void
mr_token_set(MrToken* token, char* start, char* end, MRTokenType type);

#endif // !MR_TOKEN_H
