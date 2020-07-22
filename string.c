#include "why_lib.h"
#include <limits.h>
#include "vector.h"

int string_length(const char *literal)
{
    long n = 0;
    while (literal[n])
        n ++;
    if (n >= INT_MAX)
        return -1;
    return (int)n;
}

struct string *new_zero_string(int length)
{
    if (length < 0)
        length = 0;
    struct string *new_string = mallokill(sizeof(struct string));
    new_string->string = (char *)mallokill(length + 1);
    new_string->length = length;
    set_memory(new_string->string, length + 1, 0);
    return new_string;
}

struct string *new_string_from_literal(const char *literal)
{
    int length = string_length(literal);
    if (length < 0)
        length = 0;
    struct string *new_string = mallokill(sizeof(struct string));
    new_string->string = mallokill(length + 1);
    new_string->length = length;
    copy_memory(new_string->string, literal, length);
    new_string->string[length] = 0;
    return new_string;
}

struct string *new_string_from_substring(const char *literal, int left_index, int size)
{
    if (!size)
        return NULL;
    struct string *string = mallokill(sizeof(struct string));
    string->string = mallokill(size + 1);
    string->length = size;
    copy_memory(string->string, literal + left_index, size);
    string->string[size] = 0;
    return string;
}

void display_string_debug(const struct string *string)
{
    if (!string)
    {
        printf("null string;\n");
        return ;
    }
    printf("%s%d;\n", "string length: ", string->length);
    printf("%s\"%s\";\n", "string: ", string->string);
}

void destroy_string(struct string **string)
{
    if (!string || !*string)
        return ;
    free((*string)->string);
    free(*string);
    *string = NULL;
}

void destroy_string_dumb(void *string)
{
    if (!string)
        return;
    free(((struct string *)string)->string);
    free(string);
}

struct string *copy_string(struct string *string)
{
    if (!string)
        return NULL;
    struct string *new_string = new_string_from_literal(string->string);
    return new_string;
}

struct string *concatenate_strings(struct string *lhs, char joint, struct string *rhs)
{
    struct string *result = NULL;
    char *current_position = NULL;
    if (!lhs && !rhs)
        return NULL;
    if (!lhs)
        return copy_string(rhs);
    if (!rhs)
        return copy_string(lhs);
    long total_length = lhs->length + rhs->length;
    total_length = joint ? total_length + 1 : total_length;
    if (total_length >= INT_MAX)
        return NULL; //why?
    result = new_zero_string(total_length);
    current_position = result->string;
    copy_memory(current_position, lhs->string, lhs->length);
    current_position = current_position + lhs->length;
    if (joint)
    {
        *current_position = joint;
        current_position ++;
    }
    copy_memory(current_position, rhs->string, rhs->length);
    return result;
}

struct string *new_substring(const struct string *string, int left_index, int right_index)
{
    if (right_index - left_index < 0)
        left_index = right_index = 0;
    if (left_index > string->length)
        left_index = right_index = 0;
    if (right_index >= string->length)
        right_index = string->length;
    int length = right_index - left_index;
    struct string *substring = new_zero_string(length);
    copy_memory(substring->string, string->string + left_index, length);
    return substring;
}

int get_index_after(const struct string *string, int index, const char character)
{
    int n = index;
    while (n < string->length)
    {
        if (string->string[n] == character)
            return n;
        n ++;
    }
    return -1;
}

int get_index_in_range
(const char *literal, int left_index, int right_index, const char character)
{
    int n = left_index;
    while (n < right_index)
    {
        if (literal[n] == character)
            return n;
        n ++;
    }
    return -1;
}

struct vector *string_split(const struct string *source, char separator)
{
    struct vector *vector = new_vector(sizeof(struct string *), DEFAULT_VECTOR_SIZE);
    struct string *substring = NULL;
    int left_index = 0;
    int right_index = 0;
    while (right_index < source->length)
    {
        if (source->string[right_index] == separator)
        {
            substring = new_string_from_substring(source->string, left_index, right_index - left_index);
            vector = push(vector, substring);
            left_index = right_index + 1;
        }
        right_index ++;
    }
    return vector;
}