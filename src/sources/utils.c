#include <time.h>
#include "headers/lib.h"
/* IMPLEMENTATIONS */

void read_graph_from_file(graph_t *g, FILE *buffer)
{
    int nv;
    char *line;
    FILE *offset = buffer;

    /**
     * LETTURA NUMERO VERTICI
     */
    int err = fscanf(offset, "%d", &nv);
    CHECK_ERROR(err, 1)

    graph_create(g, nv);

    /**
     * LETTURA VERTICI
     */
    for (int i = 0; i < nv; i++)
    {
        int label;
        err = fscanf(offset, "%d ", &label);

        CHECK_ERROR(err, 1);
        vertex_t *v = graph_insert_vertex(g, label);
#ifdef DEBUG
        printf("Vertice inserito: %d\n", v->label);
#endif
    }

    for (int i = 0; i < g->nv; i++)
    {
        int n_list;
        int label;

        err = fscanf(offset, "%d %d", &label, &n_list);
        CHECK_ERROR(err, 2)

        vertex_t *v = graph_get_vertex_by_index(g, label);
        create_adj_list(v, n_list);
        for (int i = 0; i < n_list; i++)
        {
            err = fscanf(offset, "%d {}", &label);
            CHECK_ERROR(err, 1)
            graph_insert_edge(g, v, label);
#ifdef DEBUG
            printf("Arco inserito: %d\n", label);
#endif
        }
    }
}

void read_graph_from_string(subgraph_t *g, char *buffer, int rank)
{
    /*
     * TODO: bisogna cambiare la serializzazione in modo che possiamo mantenere
     * informazione su nodo esterno/interno */
    int nv;
    char *line;
    int pos;

    /**
     * LETTURA NUMERO DI VERTICI
     */
    line = strtok((char *)buffer, "\n");
    int err = sscanf(line, "%d", &nv);
    CHECK_ERROR(err, 1)

    g->nv = 0;
    dict_create(&g->bucket, nv);

#ifdef DEBUG
    printf("Numero di vertici: %d\n", nv);
#endif
    line = strtok(NULL, "\n");

    for (int i = 0; i < nv; i++)
    {
        int label = (int)strtol(line, &line, 10);

        vertex_t *v = (vertex_t *)malloc(sizeof(vertex_t));
        if (v == NULL)
        {
            fprintf(stderr, "Error in memory allocation %s:%d\n", __FILE__, __LINE__);
            exit(1);
        }
        v->label = label;
        v->owner = false;
        v->adj_list = (dict_t *)malloc(sizeof(dict_t));
        v->lowlink = -1;
        v->index = -1;
        v->in_stack = false;

        dict_put(&g->bucket, label, v);

        g->nv = g->nv + 1;
    }

    for (int i = 0; i < g->nv; i++)
    {
        int n_list;
        int label;

        line = strtok(NULL, "\n");
        int err = sscanf(line, "%d %d", &label, &n_list);
        CHECK_ERROR(err, 2)

        vertex_t *v = (vertex_t *)dict_get(&g->bucket, label);

        create_adj_list(v, n_list);

        for (int i = 0; i < n_list; i++)
        {
            line = strtok(NULL, "\n");
            int err = sscanf(line, "%d {}", &label);
            CHECK_ERROR(err, 1)
            dict_put(v->adj_list, label, NULL);
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

type_t *shuffle(int n)
{
    // srandom(time(NULL));
    type_t *arrayToReturn = malloc(sizeof(type_t) * n); // allocazione dinamica dell'array di ritorno

    for (int i = 0; i < n; i++)
        arrayToReturn[i] = i; // inserisco i valori da o a n in un array

    for (int i = n - 1; i > 0; i--)
    {
        int j = (int)random() %
                (i + 1); // scelgo un valore random col quale scambiare l'iesimo numero
        swap(&arrayToReturn[i], &arrayToReturn[j]);
    }

    return arrayToReturn;
}

void insert_adjlist(vertex_t *v, char *s)
{
    dict_t *dict = v->adj_list;
    for (int j = 0; j < dict->cap; j++)
    {
        pair_t *p = v->adj_list->bucket[j];
        if (p != NULL)
        {
            sprintf(s + strlen(s), "%d {}\n", p->key);
        }
    }
}

char *get_serialized_subgraph(graph_t *g, char *s, int k, int last_inserted, int *shuffled, int rank)
{
    // scrivo il numero di nodi che deve andare nel grafo
    graph_t subgraph;
    graph_create(&subgraph, k);
    subgraph.nv = k;
#ifdef DEBUG
    printf("Calling get_serialized_subgraph...\n");
#endif
    int inserted = 0;
    int i = last_inserted;
    while (inserted < k / PARTITION)
    {
        vertex_t *v = graph_get_vertex_by_index(g, shuffled[i]);
        if (v->owner == -1)
        {
            subgraph.bucket[inserted] = *v;
            v->owner = rank;
#ifdef DEBUG
            printf("Inserting vertex: %d\n", v->label);
#endif
            // graph_insert_vertex(&subgraph, v->label);
            // insert_adjlist(v, s);

            inserted++;
        }
        i = (i + 1) % g->nv;
    }

    while (inserted < k)
    {

        // vertex_t *v = graph_get_vertex_by_index(g, shuffled[i]);
        vertex_t *v = &g->bucket[shuffled[i]];
        dict_t *dict = v->adj_list;
        if (v->owner == -1)
        {
            subgraph.bucket[inserted] = *v;
            v->owner = rank;
#ifdef DEBUG
            printf("Inserting vertex: %d\n", v->label);
#endif
            // graph_insert_vertex(&subgraph, v->label);
            // insert_adjlist(v, s);

            inserted++;
        }

        for (int j = 0; j < dict->cap; j++)
        {
            if (inserted >= k)
            {
                break;
            }
            // va cambiato se facciamo più di una cut

            pair_t *p = dict->bucket[j];

            if (p != NULL)
            {
                vertex_t *neighbour = graph_get_vertex_by_index(g, p->key);

                if (neighbour->owner == -1)
                {
#ifdef DEBUG
                    printf("Inserting vertex: %d\n", neighbour->label);
#endif
                    subgraph.bucket[inserted] = *neighbour;
                    neighbour->owner = rank;

                    inserted++;
                }
            }
        }

        i = (i + 1) % g->nv;
    }



    int num_chars = sprintf(s, "%d\n", k);

    for (int i = 0; i < subgraph.nv; i++)
    {
        num_chars += sprintf(s + num_chars, "%d ", subgraph.bucket[i].label);
    }
    num_chars += sprintf(s + num_chars, "\n");
    for (int i = 0; i < subgraph.nv; i++)
    {
        
        vertex_t *v = &subgraph.bucket[i];
        
        printf("NUMCHARS: %d\n", num_chars);
        num_chars += sprintf(s + num_chars, "%d %d\n", v->label, v->adj_list->cap - 1);
        for (int j = 0; j < v->adj_list->cap; j++)
        {
            
            pair_t *p = v->adj_list->bucket[j];
            if (p != NULL)
            {
                num_chars += sprintf(s + num_chars, "%d {}\n", p->key);
            }
        }
    }
    
    return s;
}

void dict_vertex_print(dict_t *b)
{

    for (int i = 0; i < b->cap; i++)
    {

        pair_t *p = b->bucket[i];

        if (p != NULL)
        {
            vertex_t *v = p->value;

            printf("%d-> ", v->label);

            dict_t *dict = v->adj_list;

            for (int j = 0; j < v->adj_list->cap; j++)
            {
                pair_t *p = v->adj_list->bucket[j];
                if (p != NULL)
                {
                    printf("%d ", p->key);
                }
            }

            printf("\n");
        }
    }
}