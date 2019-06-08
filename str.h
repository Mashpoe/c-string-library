//
//  str.h
//
//  Created by Mashpoe on 2/28/19.
//

#ifndef str_h
#define str_h

#include <stdlib.h>
#include <stdbool.h>

typedef char* string;

string string_create(const char* str);

void string_add_char(string* s, char c);

void string_add(string* s, const char* str);

void string_insert(string* s, size_t pos, const char* str);

void string_replace(string* s, size_t pos, size_t len, const char* str);

void string_remove(string s, size_t pos, size_t len); // removing elements does not require reallocation

void string_free(string s);

size_t string_size(string s);

size_t string_get_alloc(string s);

#endif /* str_h */
