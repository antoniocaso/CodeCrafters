#include "headers/lib.h"

void list_create(list_t *l)
{
    l->array = (type_t *)malloc(SIZE * sizeof(type_t));
    if (l->array == NULL)
    {
        fprintf(stderr, "Error in memory allocation %s:%d\n", __FILE__, __LINE__);
        exit(1);
    }
    l->size = SIZE;
    l->n = 0; // numero di elementi
}

void list_add_element(list_t *l, type_t element)
{

    int i = 0;
    for (i = 0; i < l->n; i++)
    {
        if (l->array[i] >= element)
        {
            break;
        }
    }
    if (i == l->n || l->array[i] != element)
    {
        if (l->n + 1 >= l->size)
        {
            resize(l, GROWTH_FACTOR * l->size);
        }

        l->array[l->n] = element;

        l->n = l->n + 1;
    }
}

void resize(list_t *l, int new_size)
{
    type_t *new_array;
    new_array = (type_t *)realloc(l->array, new_size * sizeof(type_t));
    l->array = new_array;
    l->size = new_size;
}

void list_destroy(list_t *l)
{
    free(l->array);
}

/* Creates a new libraries */
void graph_create(graph_t *g, int size)
{
    g->nv = 0;
    g->bucket = (vertex_t *)malloc(size * sizeof(vertex_t));
    if (g->bucket == NULL)
    {
        fprintf(stderr, "Error in memory allocation %s:%d\n", __FILE__, __LINE__);
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        g->bucket[i] = (vertex_t){label : 0, owner : -1, adj_list : NULL, lowlink : -1, index : -1, in_stack : false, local_scc : -1};
    }
}

/* Inserts vertex inside libraries data structure */
vertex_t *graph_insert_vertex(graph_t *g, type_t label)
{
    // scelgo il vertice da inserire
    // da modifcare se si vuole fare l'inserimento in order
    vertex_t *v = &g->bucket[g->nv];

    v->label = label;
    v->owner = -1;
    v->adj_list = (dict_t*) malloc(sizeof(dict_t));
    g->nv = g->nv + 1;
    return v;
}


void create_adj_list(vertex_t* v, int cap){
    dict_create(v->adj_list, cap);
}

/* Add an edge to the libraries between vertices u and v */
void graph_insert_edge(graph_t *g, vertex_t *u, type_t label)
{
    dict_put(u->adj_list, label, NULL);
}

/* Returns the vertices of the libraries */
vertex_t *graph_vertices(graph_t *g)
{
    return g->bucket;
}

vertex_t *graph_get_vertex_by_index(graph_t *g, int i)
{
    return &g->bucket[i];
}

int graph_find_vertex(graph_t *g, int label)
{
    for (int i = 0; i < g->nv; i++)
    {
        if (g->bucket[i].label == label)
        {
            return i;
        }
    }
    return -1;
}

void graph_print_adjacency_list(graph_t g)
{
    for (int i = 0; i < g.nv; i++)
    {

        vertex_t v = g.bucket[i];

        printf("[%d][%d]-> ", v.label, v.local_scc);

        dict_t* adj_list = v.adj_list;

        
        for (int j = 0; j < adj_list->cap; j++)
        {
            pair_t *element = adj_list->bucket[j];
            if(element != NULL){
                printf("%d ", element->key);
            }

        }
        printf("\n");
    }
}

void graph_destroy(graph_t *g)
{
    for (int i = 0; i < g->nv; i++)
    {
        vertex_t v = g->bucket[i];
        dict_destroy(v.adj_list);
    }
    free(g->bucket);
}
