#include "why_lib.h"

void set_memory(void *pointer, int number_of_bytes, unsigned char value)
{
    if (number_of_bytes <= 0) return ;
    int n = 0;
    while (n < number_of_bytes)
    {
        *(unsigned char *)pointer = value;
        pointer = (unsigned char *)pointer + sizeof(unsigned char);
        n = n + sizeof(unsigned char);
    }
}

void *copy_memory(void *destination, const void *source, int number_of_bytes)
{
    if (number_of_bytes <= 0) return destination;
    int n = 0;
    unsigned char *current_byte = (unsigned char *)source;
    while (n < number_of_bytes)
    {
        *(unsigned char *)destination = *current_byte;
        destination = (unsigned char *)destination + sizeof(unsigned char);
        current_byte ++;
        n = n + sizeof(unsigned char);
    }
    return (unsigned char *)destination - number_of_bytes * sizeof(unsigned char);
}

void *mallokill(unsigned int size)
{
    void *object = malloc(size);
    const char *message = "malloc failed;\n";
    if (!object)
    {
        write(STDERR_FILENO, message, string_length(message));
        exit(1);
    }
    return object;
}