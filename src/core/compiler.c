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
#include <stdio.h>
int main(int argc, char** argv) {
	MRError* error = NULL;
	uint16_t nTokens;
	uint16_t i;
	// Get tokens from file
	MRToken* tokens = mr_scanner_scan_file("test.mr", &nTokens, &error);

	// Print error
	if (error) {
		fprintf(stderr, "Error: %s\n", error->message);
	}

	// Print tokens
	for (i = 0; i < nTokens; i++) {
		switch (tokens[i].type) {
		case TK_EG: printf(" => "); break;
		case TK_LEG: printf(" <=> "); break;
		case TK_LE: printf(" <= "); break;
		case TK_ID: printf(" ID "); break;
		case TK_LITERAL: printf(" LITERAL "); break;
		default: printf(" %c ", *tokens[i].start); break;
		}
	}

	return 0;
}
