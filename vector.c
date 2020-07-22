#include "why_lib.h"
#include "vector.h"
#include "string.h"

struct vector *new_vector(int item_size, int number_of_items)
{
    if (number_of_items < 0)
        number_of_items = 0;
    struct vector *vector = mallokill(sizeof(struct vector));
    vector->item_size = item_size;
    vector->number_of_items = number_of_items;
    vector->last_item_index = -1;
    if (number_of_items)
        vector->content = mallokill(item_size * number_of_items);
    else
        vector->content = NULL;
    return vector;
}

void destroy_vector(struct vector **vector, void (*item_destructor)(void *))
{
    int n = 0;
    if (!vector || !*vector)
        return ;
    if (item_destructor)
    {
        while (n < (*vector)->last_item_index + 1)
        {
            item_destructor((*vector)->content[n]);
            n ++;
        }
    }
    free((*vector)->content);
    free(*vector);
    *vector = NULL;
}

void display_int(const void *item)
{
    printf("%d", *(int *)item);
}

void display_char_array(const void *item)
{
    printf("\"%s\"", (char *)item);
}

void display_string(const void *string)
{
    display_char_array(((struct string *)string)->string);
    printf("\n");
}

void display_vector(const struct vector *vector, void (*display_item)(const void *))
{
    int n = 0;
    while (n < vector->last_item_index + 1)
    {
        display_item(vector->content[n]);
        n ++;
        printf("\n");
    }
    printf("\n");
}

struct vector *reallocate_vector(struct vector *vector, int n_extra_items)
{
    if (n_extra_items <= 0)
        return vector;
    struct vector *augmented_vector = new_vector(vector->item_size, vector->number_of_items + n_extra_items);
    copy_memory(augmented_vector->content,
    vector->content, (vector->last_item_index + 1) * vector->item_size);
    augmented_vector->last_item_index = vector->last_item_index;
    destroy_vector(&vector, NULL);
    return augmented_vector;
}

//push does not copy the item
struct vector *push(struct vector *vector, void *item)
{
    int next_index = vector->last_item_index + 1;
    if (next_index + 1 > vector->number_of_items)
    {
        vector = reallocate_vector(vector, vector->number_of_items ? vector->number_of_items : 1);
    }
    vector->content[next_index] = item;
    vector->last_item_index = next_index;
    return vector;
}

