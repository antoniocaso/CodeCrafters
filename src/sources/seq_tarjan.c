#include <string.h>
#include "headers/lib.h"

#define UNVISITED -1
void tarjan(subgraph_t *g, vertex_t *v, stack_t *s, char *scc)
{
    static int index = 0;
    v->index = index;
    v->lowlink = index;
    index++;

    stack_push(s, v);
    v->in_stack = true;

    // printf("lunghezza:%d\n", v->adj_list.n);
    for (int i = 0; i < v->adj_list->cap; i++)
    {
        pair_t *p = v->adj_list->bucket[i];
        if (p != NULL){
            type_t u_label = p->key;
            vertex_t *u = (vertex_t *)dict_get(&g->bucket, u_label);
            if (u != NULL && u->index == -1)
            {
                // printf("figli\n");
                // printf("%d ", u->label);
                tarjan(g, u, s, scc);

                v->lowlink = u->lowlink < v->lowlink ? u->lowlink : v->lowlink;
            }
            else if (u != NULL && u->in_stack == true)
            {
                v->lowlink = v->lowlink < u->index ? v->lowlink : u->index;
            }
        }
    }

    vertex_t *w = NULL;

    if (v->lowlink == v->index)
    {

        // printf("\n");
        while (!stack_empty(s) && stack_top(s) != v)
        {
            w = stack_top(s);
            // printf("%d ", w->label);
            sprintf(scc + strlen(scc), "%d ", w->label);
            w->in_stack = false;
            stack_pop(s);
        }
        if (stack_empty(s) == false)
        {
            w = stack_top(s);
            // printf("%d ", w->label);
            sprintf(scc + strlen(scc), "%d\n", w->label);
            // printf("\n");
            w->in_stack = false;
            stack_pop(s);
        }
    }
}

void find_scc(subgraph_t *g, char *s)
{
    // printf("Find SCC\n");
    memset(s, 0, strlen(s));
    stack_t st;
    stack_create(&st, g->nv);

    pair_t **vertices = g->bucket.bucket;

    for (int i = 0; i < g->bucket.cap; i++)
    {

        if (vertices[i] != NULL)
        {
            vertex_t *v = (vertex_t *)vertices[i]->value;
            if (v != NULL && v->index == -1)
            {
                
                tarjan(g, v, &st, s);
                
            }
        }

        // printf("Result string: %s\n", s);
    }
}
