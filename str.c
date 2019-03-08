//
//  str.c
//
//  Created by Mashpoe on 2/28/19.
//  Copyright © 2019 Mashpoe. All rights reserved.
//

#include "str2.h"
#include <stdio.h>
#include <string.h>

typedef struct string_data string_data;

struct string_data {
	size_t alloc; // stores the number of bytes allocated
	size_t length;
	char buff[];
};

string_data* STRING_ALLOC(size_t length) {
	string_data* s_data = malloc(sizeof(string_data) + length + 1); // plus 1 for null terminator
	s_data->alloc = length+1;
	s_data->length = length;
	return s_data;
}

string_data* STRING_DATA(string s) {
	return (string_data*)&s[-sizeof(string_data)];
}

string STRING_CREATE(const char* str) {
	string_data* s_data = NULL;
	
	if (str != NULL) {
		size_t str_length = strlen(str);
		s_data = STRING_ALLOC(str_length);
		memcpy(&s_data->buff, str, str_length);
		s_data->buff[str_length] = '\0';
	} else {
		s_data = STRING_ALLOC(0); // will only allocate enough for a null terminator
		s_data->buff[0] = '\0';
	}
	
	return s_data->buff;
}

string_data* STRING_REALLOC(string_data* s_data) {
	size_t new_alloc = s_data->alloc * 2;
	
	string_data* new_s_data = malloc(sizeof(string_data) + new_alloc);
	
	new_s_data->alloc = new_alloc;
	new_s_data->length = s_data->length;
	
	memcpy(new_s_data->buff, s_data->buff, s_data->length);
	
	free(s_data);
	
	return new_s_data;
}

bool STRING_HAS_SPACE(string_data* s_data) {
	// allocate based on s_data->length + 1 to account for the null terminator
	return s_data->alloc - (s_data->length + 1) > 0;
}

void STRING_ADD_CHAR(string* s, char c) {
	string_data* s_data = STRING_DATA(*s);
	
	if (!STRING_HAS_SPACE(s_data)) {
		s_data = STRING_REALLOC(s_data);
	}
	s_data->buff[s_data->length++] = c;
	s_data->buff[s_data->length] = '\0'; // add the new null terminator
	
	*s = s_data->buff;
}

void STRING_ADD(string* s, const char* str) {
	string_data* s_data = STRING_DATA(*s);
	
	size_t str_length = strlen(str);
	
	size_t new_length = s_data->length + str_length;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = STRING_ALLOC(new_length);
		
		memcpy(new_s_data->buff, s_data->buff, s_data->length - 1); // copy characters
		
		free(s_data);
		
		s_data = new_s_data;
	}
	
	// copy str chars
	memcpy(&s_data->buff[s_data->length-1], str, str_length);
	
	s_data->buff[new_length] = '\0'; // add new null terminator
	
	*s = s_data->buff;
}

void STRING_INSERT(string* s, size_t pos, const char* str) {
	string_data* s_data = STRING_DATA(*s);
	
	size_t str_length = strlen(str);
	
	size_t new_length = s_data->length + str_length;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = STRING_ALLOC(new_length);
		
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

void STRING_REPLACE(string* s, size_t pos, size_t len, const char* str) {
	string_data* s_data = STRING_DATA(*s);
	
	size_t str_length = strlen(str);
	
	size_t new_length = s_data->length + str_length - len;
	
	// make sure there is enough room for new characters and null terminator
	if (s_data->alloc <= new_length + 1) {
		string_data* new_s_data = STRING_ALLOC(new_length);
		
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

void STRING_REMOVE(string s, size_t pos, size_t len) {
	string_data* s_data = STRING_DATA(s);
	// anyone who puts in a bad index can face the consequences on their own
	memmove(&s_data->buff[pos], &s_data->buff[pos+len], s_data->length - pos);
	s_data->length -= len;
	s_data->buff[s_data->length] = '\0';
}

void STRING_FREE(string s) {
	free(STRING_DATA(s));
}

size_t STRING_SIZE(string s) {
	return ((size_t*)s)[-1];
}

size_t STRING_GET_ALLOC(string s) {
	return ((size_t*)s)[-2];
}
