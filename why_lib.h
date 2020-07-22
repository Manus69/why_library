#ifndef WHY_LIB_H
#define WHY_LIB_H
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifdef unix
#include <unistd.h>
#endif

typedef int bool;
enum {false, true};

struct string
{
    int length;
    char *string;
};

//memory
void *mallokill(unsigned int size);
void set_memory(void *pointer, int number_of_bytes, unsigned char value);
void *copy_memory(void *destination, const void *source, int number_of_bytes);

//string
int string_length(const char *literal);
int get_index_after(const struct string *string, int index, const char character);
struct string *new_string_from_literal(const char *literal);
struct string *new_zero_string(int length);
struct string *concatenate_strings(struct string *lhs, char joint, struct string *rhs);
struct string *new_substring(const struct string *string, int left_index, int right_index);
struct string *new_string_from_substring(const char *literal, int left_index, int right_index);
void display_string_debug(const struct string *string);
void display_string(const void *string);
void destroy_string(struct string **string);
void destroy_string_dumb(void *string);
int get_index_in_range
(const char *literal, int left_index, int right_index, const char character);
struct vector *string_split(const struct string *source, char separator);


//display
void display_int(const void *item);
void display_char_array(const void *item);

#endif