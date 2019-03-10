//
//  str.h
//
//  Created by Mashpoe on 2/28/19.
//  Copyright © 2019 Mashpoe. All rights reserved.
//

#ifndef str_h
#define str_h

#include <stdlib.h>
#include <stdbool.h>

typedef char* string;
typedef size_t str_size;

string STRING_CREATE(const char* str);

void STRING_ADD_CHAR(string* s, char c);

void STRING_ADD(string* s, const char* str);

void STRING_INSERT(string* s, str_size pos, const char* str);

void STRING_REPLACE(string* s, str_size pos, str_size len, const char* str);

void STRING_REMOVE(string s, str_size pos, str_size len); // removing elements does not require reallocation

void STRING_FREE(string s);

str_size STRING_SIZE(string s);

str_size STRING_GET_ALLOC(string s);

#endif /* str_h */
