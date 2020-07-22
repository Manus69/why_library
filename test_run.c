#include "why_lib.h"
#include "fancy_buffer.h"
#include "vector.h"


int main(void)
{
    // struct vector *vector = new_vector(sizeof(int *), 0);
    // int array[] = {-1, 0, 1337, 2};
    // vector = push(vector, &array[0]);
    // vector = push(vector, &array[0]);
    // vector = push(vector, &array[2]);
    // vector = push(vector, &array[2]);
    // vector = push(vector, &array[2]);
    // display_vector(vector, display_int);
    // destroy_vector(&vector, NULL);

    // struct string *string = new_string_from_literal("0 1 2 3 4 5");
    // struct vector *vector = string_split(string, ' ');
    // display_vector(vector, display_string);
    // destroy_string(&string);
    // destroy_vector(&vector, destroy_string_dumb);

    struct fancy_buffer *buffer = new_fancy_buffer(DEFAULT_CAPACITY, "file.txt");
    char character = ' ';
    struct string *string = get_next_sequence(buffer, character);
    struct vector *vector = new_vector(sizeof(struct string *), DEFAULT_VECTOR_SIZE);
    while (string)
    {
        // display_string(string);
        // destroy_string_dumb(string);
        vector = push(vector, string);
        string = get_next_sequence(buffer, character);
    }

    // display_vector(vector, display_string);
    destroy_vector(&vector, destroy_string_dumb);

    destroy_fancy_buffer(&buffer);

    return 0;
}