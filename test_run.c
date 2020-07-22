#include "why_lib.h"
// #include "buffer.h"
#include "fancy_buffer.h"


int main(void)
{
    // struct buffer *buffer = new_buffer(DEFAULT_BUFFER_CAPACITY);

    // int file = open("Makefile", O_RDONLY);
    // // int file = STDIN_FILENO;
    // // int file = open("file.txt", O_RDONLY);
    // struct string *string = get_line_from_file(buffer, file);
    // while (string)
    // {
    //     display_string(string);
    //     destroy_string(&string);
    //     string = get_line_from_file(buffer, file);
    // }

    // #include "simple_buffer.h"
    // struct simple_buffer *buffer = new_simple_buffer(BUFFER_SIZE, "file2.txt");
    // struct simple_buffer *buffer = new_simple_buffer(BUFFER_SIZE, "file.txt");
    // // // struct simple_buffer *buffer = new_simple_buffer(BUFFER_SIZE, NULL);
    // char terminator = '\n';
    // struct string *sequence = get_next_sequence_sb(buffer, terminator);
    // while (sequence)
    // {
    //     // display_string(sequence);
    //     // printf("%s", sequence->string);
    //     // printf("\n-------\n");
    //     // destroy_string(&sequence);
    //     sequence = get_next_sequence_sb(buffer, terminator);
    // }
    // destroy_simple_buffer(&buffer);

    // struct string *test_string = new_string_from_substring("0123456789", 1, 1);

    // struct fancy_buffer *buffer = new_fancy_buffer(DEFAULT_CAPACITY, "Makefile");
    struct fancy_buffer *buffer = new_fancy_buffer(DEFAULT_CAPACITY, "file.txt");
    // struct fancy_buffer *buffer = new_fancy_buffer(DEFAULT_CAPACITY, "file2.txt");
    char terminator = '\n';
    struct string *string = get_next_sequence(buffer, terminator);
    while (string)
    {
        // display_string(string);
        destroy_string(&string);
        string = get_next_sequence(buffer, terminator);
    }
    destroy_string(&string);
    destroy_fancy_buffer(&buffer);

    return 0;
}