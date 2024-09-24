#include "headers/lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define type_t int
#define MPI
#define DEBUG
// #define DEBUG 0
#include <unistd.h>
// #define GDB

// m: numero di nodi MPI
// rank: il rank del processo corrente
void cut(graph_t *g, int m, int rank, char *root_cut)
{
    /*TODO*/
    // trovare il numero di nodi da inviare ad ogni MPI
    int k = g->nv / m;

    // shuffle
    type_t *shuffled = shuffle(g->nv);
    char* s = (char *) malloc( INT32_MAX * sizeof(char));
    if(s == NULL){
        fprintf(stderr, "Errore allocazione");
        exit(1);
    }
    for (int i = 0; i < m; i++)
    {
        
        char *serialized_subgraph;
        if (i == m - 1 && g->nv % m != 0)
        {
            serialized_subgraph = get_serialized_subgraph(g, s, k + (g->nv % m), (m - 1) * k, shuffled, i);
        }
        else
        {
            serialized_subgraph = get_serialized_subgraph(g, s, k, i * k, shuffled, i);
        }
        // MPI SEND
        // TODO: aggiungere controllo degli errori
        if (i != 0)
        {
            int err = MPI_Send(serialized_subgraph, BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            CHECK_ERROR(err, MPI_SUCCESS)
        }
        else
        {
            strcpy(root_cut, serialized_subgraph);
        }
    }
    free(s);
    free(shuffled);
}

// risultati scc
int mapping(graph_t *g, char *s, int id, dict_t *map)
{
    char *line = malloc(LINE_SIZE * sizeof(char));

    char *vertex;
    char delim[] = "\n";
    int v = 0;

    line = strtok(s, delim);
    do
    {
        list_t *l = malloc(sizeof(list_t));
        list_create(l);

        dict_put(map, id, l);
        char *end = line;

        while (*end)
        {

            int v = strtol(line, &end, 10);
            // printf("GET: %d\n", v);
            g->bucket[v].local_scc = id;
            list_add_element(l, v);

            while (*end == ' ')
            {
                end++;
            }
            line = end;
        }

        line = strtok(NULL, delim);
        id++;
    } while (line != NULL);

    free(line);

    return id;
}

void reverse_mapping(graph_t *g, char *s, dict_t *map)
{
    FILE *f = fopen("sol", "w");
    char *line = malloc(100 * sizeof(char));

    char delim[] = "\n";
    int v = 0;

    line = strtok(s, delim);
    do
    {

        char *end = line;
        while (*end)
        {
            int v = strtol(line, &end, 10);

            list_t *l = dict_get(map, v);
            for (int i = 0; i < l->n; i++)
            {
                fprintf(f, "%d ", l->array[i]);
            }

            while (*end == ' ')
            {
                end++;
            }
            line = end;
        }
        fprintf(f, "\n");
        line = strtok(NULL, delim);

    } while (line != NULL);

    free(line);
    printf("TERMINATO");
}

vertex_t *create_vertex(int label)
{
    vertex_t *v = malloc(sizeof(vertex_t));
    v->in_stack = false;
    v->label = label;
    v->index = -1;
    v->lowlink = -1;
    v->adj_list = (dict_t *)malloc(sizeof(dict_t));
    return v;
}

void insert_vertex(subgraph_t *g, vertex_t *v)
{

    dict_put(&g->bucket, v->label, v);
}

void create_metagraph(graph_t *g, dict_t *map, subgraph_t *meta)
{ // nodeid sono gli id scc (chiavi del dict) e // values sono i vertex con liste di
    // adiacenza aggiornate
    for (int i = 0; i < map->cap; i++)              //itero su map
    {
        if (map->bucket[i] != NULL)                 //se c'è una posizione valida di map
        {
            int key = map->bucket[i]->key;          //prendo da map i di scc
            vertex_t *v = create_vertex(key);       //creo un vertice a partire da scc
            create_adj_list(v, 10000);            
            insert_vertex(meta, v);

            // printf("Inserisco %d\n", key); // nome del macronodo

            list_t * or = map->bucket[i]->value; // lista dei nodi che compongono il macronodo

            for (int i = 0; i < or->n; i++)
            {
                
                int or_label = or->array[i];
                vertex_t *ov = &g->bucket[or_label];
                for (int j = 0; j < ov->adj_list->cap; j++)
                {
                    
                    pair_t *p = ov->adj_list->bucket[j];
                    if (p != NULL)
                    {
                        int adj = g->bucket[p->key].local_scc;
                        if (adj != key)
                        {
                            dict_put(v->adj_list, adj, NULL);
                        }
                    }
                }
            }
        }
    }
}
/*
void fwbw(subgraph_t *meta){
    dict_t b = meta->bucket;

    for(int i = 0; i < b.cap; i++){

        pair_t *p = b.bucket[i];

        if(p!=NULL){
            // 1, [   ]

            vertex_t *v = p->value;
            list_t *l = &v->adj_list;
            for(int j = 0; j < l->n; j++){

                int adj = l->array[j]; // aggiungere flag visited
                vertex_t * u = dict_get(&b, adj);

                for(int k = 0; k < u->adj_list.n; k++){
                    int e = u->adj_list.array[k];
                    if(e == v->label){
                        // merge

                        break;
                    }
                }
            }


        }

    }
}
*/

int main(int argc, char *argv[])
{
#ifdef MPI
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

#ifdef GDB
    {
        volatile int i = 0;
        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        printf("PID %d on %s ready for attach (node %d)\n", getpid(), hostname, rank);
        fflush(stdout);
        while ((0 == i))
            sleep(5);
    }
#endif

    graph_t g;

    char s[BUFFER_SIZE];

    if (rank == 0)
    {

        FILE *file = fopen("../data/graph1000", "r");
        if (file == NULL)
        {
            printf("errore apertura file");
            exit(1);
        }
        read_graph_from_file(&g, file);
        fclose(file);
#ifdef DEBUG
        //graph_print_adjacency_list(g);
#endif
        cut(&g, size, rank, s);
    }
    else
    {

        MPI_Request request;
        MPI_Status status;
        MPI_Irecv(&s, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }

    // TODO:

#ifdef DEBUG
    //printf("[PROCESSO: %d]\n%s", rank, s);
#endif

    subgraph_t sg;

    read_graph_from_string(&sg, s, rank);

#ifdef DEBUG
    printf("[PROCESSO: %d]: Running Tarjan\n", rank);
    //dict_vertex_print(&sg.bucket);
#endif

    find_scc(&sg, s);
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank != 0)
    {
        int err = MPI_Ssend(s, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        CHECK_ERROR(err, MPI_SUCCESS)
    }

    if (rank == 0)
    {
        char buffer[BUFFER_SIZE]; // TODO:
        MPI_Request request;
        MPI_Status status;
        int last_id = 0;
        dict_t map;
        dict_create(&map, g.nv);

        for (int i = 1; i < size; i++)
        {
            MPI_Irecv(&buffer, BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
            // printf("[PROCESSO %d]: Ricevuto da %d\n%s\n", rank, status.MPI_SOURCE, buffer);
            last_id = mapping(&g, buffer, last_id, &map);
        }

        
        last_id = mapping(&g, s, last_id, &map);
        // last_id è il numero di nodi del nuovo grafo
        //  dividere di nuovo
        //  mandare gli archi del taglio
        //  fare tarjan sul totale

        // graph_print_adjacency_list(g);

        for (int i = 0; i < map.cap; i++)
        {
            pair_t *p = map.bucket[i];
            /*
            if (p != NULL)
            {
                printf("%d->", p->key);

                list_t *l = p->value;
                for (int j = 0; j < l->n; j++)
                {
                    int v = l->array[j];
                    printf("%d ", v);
                }
                printf("\n");
            }*/
        }
        subgraph_t meta;
        dict_create(&meta.bucket, last_id);
        meta.nv = last_id;

        
        create_metagraph(&g, &map, &meta);
        
        /*
        dict_t b = meta.bucket;
        for (int i = 0; i < b.cap; i++)
        {

            pair_t *p = b.bucket[i];

            if (p != NULL)
            {
                int key = p->key;
                vertex_t *value = (vertex_t *)p->value;
                if (value != NULL)
                {
                    printf("%d-> ", value->label);
                    list_t *l = &value->adj_list;
                    for (int j = 0; j < l->n; j++)
                    {
                        printf("%d ", *(l->array + j));
                    }
                    printf("\n");
                }

        }
        */
        find_scc(&meta, s);
        reverse_mapping(&g, s, &map);

        // torniamo
        /*if(){ // grafo sufficientemente piccolo
            new = create_metagraph(&g);
            find_scc(new)
        } else {
            cut_sugli_archi()
        }*/

        // QUANDO FINITO TARJAN
        // finito ultimo tarjan dovremmo controllare
        // scc corrispondente alle nuove label che hanno scc uguale

        graph_destroy(&g);
    }

    MPI_Finalize();
#endif

    /* graph_t g;

     FILE *file = fopen("/home/miriam/CLionProjects/hpc_project/data/graph103", "r");
     if (file == NULL)
     {
         printf("errore apertura file");
         exit(1);
     }
     read_graph_from_file(&g, file);
     fclose(file);

     graph_print_adjacency_list(g);

     cuda_tarjan_host(&subgraph);
     */

    return 0;
}
