#include "headers/lib.h"

void stack_create(stack_t *s, int size)
{
    s->array = (vertex_t **)malloc(sizeof(vertex_t*) * size);
    s->top = 0;
}

void stack_push(stack_t *s, vertex_t *element)
{
    s->array[s->top] = element;
    s->top = s->top + 1;
}

vertex_t *stack_pop(stack_t *s)
{
    vertex_t *element = s->array[s->top - 1];
    s->top = s->top - 1;
    return element;
}

vertex_t *stack_top(stack_t *s)
{
    return s->array[s->top - 1];
}

void stack_destroy(stack_t *s)
{
    free(s->array);
}

bool stack_empty(stack_t *s)
{
    return s->top == 0;
}