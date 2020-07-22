#ifndef VECTOR_H
#define VECTOR_H

#define DEFAULT_VECTOR_SIZE 8

struct vector
{
    int item_size;
    int number_of_items;
    int last_item_index;
    void **content;
};

struct vector *new_vector(int item_size, int number_of_items);
void destroy_vector(struct vector **vector, void (*item_destructor)(void *));
void display_vector(const struct vector *vector, void (*display_item)(const void *));
struct vector *push(struct vector *vector, void *item);

#endif