#ifndef FANCY_BUFFER_H
#define FANCY_BUFFER_H

#include "why_lib.h"

enum buffer_status
{
    FULL = 1, END_OF_FILE = 2, END_OF_BUFFER = 4, FILE_ERROR = 8, GREEN = 0,
};

#define DEFAULT_CAPACITY 1024
#define DEFAULT_READ_SIZE 512

struct fancy_buffer
{
    int capacity;
    int left_index;
    int right_index;
    int file;
    int last_read_size;
    int search_start_index;
    int current_content_size;
    unsigned int status;
    char *content;  
};

struct fancy_buffer *new_fancy_buffer(int capacity, const char *filename);
void destroy_fancy_buffer(struct fancy_buffer **buffer);
void read_into_fancy_buffer(struct fancy_buffer *buffer);
struct string *read_from_fancy_buffer(struct fancy_buffer *buffer, int number_of_bytes);
struct string *get_next_sequence(struct fancy_buffer *buffer, const char terminator);

#endif