//
//  str.h
//
//  Created by Mashpoe on 2/28/19.
//  Copyright © 2019 Mashpoe. All rights reserved.
//

#ifndef str_h
#define str_h

#include <stdlib.h>

#define bool int
#define true 1
#define false 0

typedef char* string;

string STRING_CREATE(const char* str);

void STRING_ADD_CHAR(string* s, char c);

void STRING_ADD(string* s, const char* str);

void STRING_INSERT(string* s, size_t pos, const char* str);

void STRING_REPLACE(string* s, size_t pos, size_t len, const char* str);

void STRING_REMOVE(string s, size_t pos, size_t len); // removing elements does not require reallocation

void STRING_FREE(string s);

size_t STRING_SIZE(string s);

size_t STRING_GET_ALLOC(string s);

#endif /* str_h */
