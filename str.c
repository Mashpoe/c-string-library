//
//  str.c
//
//  Created by Mashpoe on 2/28/19.
//

#include "str.h"
#include <stdio.h>
#include <string.h>

typedef struct string_data string_data;

struct string_data {
	str_size alloc; // stores the number of bytes allocated
	str_size length;
	char buff[];
};

string_data* string_alloc(str_size length) {
	string_data* s_data = malloc(sizeof(string_data) + length + 1); // plus 1 for null terminator
	s_data->alloc = length+1;
	s_data->length = length;
	return s_data;
}

string_data* string_get_data(string s) {
	return (string_data*)&s[-sizeof(string_data)];
}

string string_create(const char* str) {
	string_data* s_data = NULL;
	
	if (str != NULL) {
		str_size str_length = strlen(str);
		s_data = string_alloc(str_length);
		memcpy(&s_data->buff, str, str_length);
		s_data->buff[str_length] = '\0';
	} else {
		s_data = string_alloc(0); // will only allocate enough for a null terminator
		s_data->buff[0] = '\0';
	}
	
	return s_data->buff;
}

bool string_has_space(string_data* s_data) {
	// allocate based on s_data->length + 1 to account for the null terminator
	return s_data->alloc - (s_data->length + 1) > 0;
}

void string_add_char(string* s, char c) {
	string_data* s_data = string_get_data(*s);
	
	if (!string_has_space(s_data)) {
		str_size new_alloc = s_data->alloc * 2;
		s_data = realloc(s_data, sizeof(string_data) + new_alloc);
		s_data->alloc = new_alloc;
	}
	s_data->buff[s_data->length++] = c;
	s_data->buff[s_data->length] = '\0'; // add the new null terminator
	
	*s = s_data->buff;
}

void string_add(string* s, const char* str) {
	string_data* s_data = string_get_data(*s);
	
	str_size str_length = strlen(str);
	
	str_size new_length = s_data->length + str_length;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		s_data = realloc(s_data, sizeof(string_data) + new_length);
		s_data->length = new_length;
		s_data->alloc = new_length + 1;
	}
	
	// copy str chars
	memcpy(&s_data->buff[s_data->length-1], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void string_insert(string* s, str_size pos, const char* str) {
	string_data* s_data = string_get_data(*s);
	
	str_size str_length = strlen(str);
	
	str_size new_length = s_data->length + str_length;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = string_alloc(new_length);
		
		memcpy(new_s_data->buff, s_data->buff, pos); // copy leading characters
		memcpy(&new_s_data->buff[pos+str_length], &s_data->buff[pos], s_data->length-pos); // copy trailing characters
		
		free(s_data);
		s_data = new_s_data;
		
	} else {
		memmove(&s_data->buff[pos], &s_data->buff[pos+str_length], s_data->length - pos); // move trailing characters
	}
	
	s_data->length = new_length;
	
	// copy str chars
	memcpy(&s_data->buff[pos], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void string_replace(string* s, str_size pos, str_size len, const char* str) {
	string_data* s_data = string_get_data(*s);
	
	str_size str_length = strlen(str);
	
	str_size new_length = s_data->length + str_length - len;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = string_alloc(new_length);
		
		memcpy(new_s_data->buff, s_data->buff, pos); // copy leading characters
		memcpy(&new_s_data->buff[pos+str_length], &s_data->buff[pos+len], s_data->length-pos-len); // copy trailing characters
		
		free(s_data);
		
		s_data = new_s_data;
		
	} else {
		memmove(&s_data->buff[pos+str_length], &s_data->buff[pos+len], s_data->length-pos-len); // move trailing characters
	}
	
	s_data->length = new_length;
	
	// copy str chars
	memcpy(&s_data->buff[pos], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void string_remove(string s, str_size pos, str_size len) {
	string_data* s_data = string_get_data(s);
	// anyone who puts in a bad index can face the consequences on their own
	memmove(&s_data->buff[pos], &s_data->buff[pos+len], s_data->length - pos);
	s_data->length -= len;
	s_data->buff[s_data->length] = '\0';
}

void string_free(string s) {
	free(string_get_data(s));
}

str_size string_size(string s) {
	return ((str_size*)s)[-1];
}

str_size string_get_alloc(string s) {
	return ((str_size*)s)[-2];
}
