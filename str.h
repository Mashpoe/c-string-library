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
typedef size_t str_size;

string string_create(const char* str);

void string_add_char(string* s, char c);

void string_add(string* s, const char* str);

void string_insert(string* s, str_size pos, const char* str);

void string_replace(string* s, str_size pos, str_size len, const char* str);

void string_remove(string s, str_size pos, str_size len); // removing elements does not require reallocation

void string_free(string s);

str_size string_size(string s);

str_size string_get_alloc(string s);

#endif /* str_h */
