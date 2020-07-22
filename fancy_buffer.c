#include "why_lib.h"
#include "fancy_buffer.h"

struct fancy_buffer *new_fancy_buffer(int capacity, const char *filename)
{
    if (capacity <= 0)
        capacity = DEFAULT_CAPACITY;
    struct fancy_buffer *buffer = mallokill(sizeof(struct fancy_buffer));
    buffer->capacity = capacity;
    buffer->file = filename ? open(filename, O_RDONLY) : STDIN_FILENO;
    buffer->left_index = 0;
    buffer->right_index = 0;
    buffer->last_read_size = -1;
    buffer->current_content_size = 0;
    buffer->search_start_index = 0;
    buffer->status = GREEN;
    buffer->content = mallokill(capacity + 1);
    set_memory(buffer->content, capacity + 1, 0);
    if (buffer->file < 0)
        buffer->status |= FILE_ERROR;
    return buffer;
}

void destroy_fancy_buffer(struct fancy_buffer **buffer)
{
    if (!buffer)
        return ;
    free((*buffer)->content);
    free(*buffer);
    *buffer = NULL;
}

void reset_fancy_buffer(struct fancy_buffer *buffer)
{
    buffer->left_index = 0;
    buffer->right_index = 0;
    buffer->last_read_size = -1;
    buffer->current_content_size = 0;
    buffer->search_start_index = 0;
    buffer->status = GREEN;
}

static int get_current_content_size(struct fancy_buffer *buffer)
{
    return buffer->right_index - buffer->left_index;
}

void read_into_fancy_buffer(struct fancy_buffer *buffer)
{
    if (buffer->status & FULL)
        return ;
    int current_read_size = DEFAULT_READ_SIZE;
    int leftover_capacity = buffer->capacity - buffer->right_index;
    if (leftover_capacity < current_read_size)
        current_read_size = leftover_capacity;
    buffer->last_read_size =
    read(buffer->file, buffer->content + buffer->right_index, current_read_size);
    buffer->right_index += buffer->last_read_size;
    if (buffer->right_index == buffer->capacity)
        buffer->status |= FULL;
    if (buffer->last_read_size == 0)
        buffer->status |= END_OF_FILE;
    if (buffer->last_read_size < 0)
        buffer->status |= FILE_ERROR;
    buffer->current_content_size = get_current_content_size(buffer);
}

struct string *read_from_fancy_buffer(struct fancy_buffer *buffer, int number_of_bytes)
{
    int bytes_available = buffer->right_index - buffer->left_index;
    if (number_of_bytes > bytes_available)
        number_of_bytes = bytes_available;
    struct string *substring =
    new_string_from_substring(buffer->content, buffer->left_index, number_of_bytes);
    buffer->left_index += number_of_bytes;
    buffer->current_content_size = get_current_content_size(buffer);
    if (buffer->current_content_size == 0)
        buffer->status |= END_OF_BUFFER;
    return substring;
}

struct string *append_fancy_buffer_content
(struct string *string, struct fancy_buffer *buffer, int number_of_bytes)
{
    if (!string)
        return read_from_fancy_buffer(buffer, number_of_bytes);
    struct string *buffer_content = read_from_fancy_buffer(buffer, number_of_bytes);
    struct string *result = concatenate_strings(string, 0, buffer_content);
    destroy_string(&buffer_content);
    destroy_string(&string);
    return result;
}

int search_fancy_buffer(struct fancy_buffer *buffer, const char character)
{
    int index =
    get_index_in_range(buffer->content, buffer->search_start_index, buffer->right_index, character);
    if (index >= 0)
        buffer->search_start_index = index + 1;
    else
        buffer->search_start_index = buffer->right_index; //?
    return index;
}

//make it so the terminator is a set? 
struct string *get_next_sequence(struct fancy_buffer *buffer, const char terminator)
{
    struct string *sequence = NULL;
    int index = -1;

    while (true)
    {
        read_into_fancy_buffer(buffer);
        index = search_fancy_buffer(buffer, terminator);
        if (index == -1)
        {
            if (buffer->status & END_OF_FILE || buffer->status & FILE_ERROR)
                return append_fancy_buffer_content(sequence, buffer, buffer->current_content_size);
            else
                sequence =
                append_fancy_buffer_content(sequence, buffer, buffer->current_content_size);
        }
        else
        {
            sequence = append_fancy_buffer_content(sequence, buffer, index - buffer->left_index + 1);
            return sequence;
        }
        if (buffer->status & END_OF_BUFFER)
            reset_fancy_buffer(buffer);
    }
}