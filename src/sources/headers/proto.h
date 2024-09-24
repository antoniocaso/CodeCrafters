#define SIZE 5
#define GROWTH_FACTOR 2
#define type_t int
#define PARTITION 10

#define CHECK_ERROR(actual, expected) { \
 if(actual!=expected) { \
   fprintf(stderr, "Error expected: %d, actual: %d in file %s at line %d\n",expected, actual, __FILE__,__LINE__); \
   exit(1); \
 } \
}


/* graph.c */
void list_create(list_t *l);
void list_add_element(list_t *l, type_t element);
void resize(list_t *l, int new_size);
void list_destroy(list_t *l);

void graph_create(graph_t *g, int size);
void graph_destroy(graph_t *g);
vertex_t *graph_get_vertex_by_index(graph_t *g, int i);
int graph_find_vertex(graph_t *g, int label);
vertex_t *graph_insert_vertex(graph_t *g, type_t label);
void graph_insert_edge(graph_t *g, vertex_t *u, type_t label);
vertex_t *graph_vertices(graph_t *g);
void graph_print_adjacency_list(graph_t g);
void create_adj_list(vertex_t* v, int cap);

/* stack.c */
void stack_create(stack_t *s, int size);
void stack_push(stack_t *s, vertex_t * element);
vertex_t * stack_pop(stack_t *s);
vertex_t * stack_top(stack_t *s);
void stack_destroy(stack_t *s);
bool stack_empty(stack_t *s);




/*utils.c*/
void cut(graph_t *g, int m, int rank, char *root_cut);
char *get_serialized_subgraph(graph_t *g, char *s, int k, int last_inserted, int *shuffled, int rank);
void insert_adjlist(vertex_t *v, char *s);
void swap(int *a, int *b);
type_t *shuffle(int n);
void read_graph_from_buffer(graph_t *g, void *buffer, char type);
void read_graph_from_file(graph_t *g, FILE *buffer);
void read_graph_from_string(subgraph_t *g, char *buffer, int rank);
void dict_vertex_print(dict_t *b);

/* seq_tarjan.c */
void find_scc(subgraph_t *g, char *s);


/* hash.c */
void dict_put(dict_t *d, type_t key, void *value);
void *dict_get(dict_t *d, type_t key);
void dict_create(dict_t *d, int cap);
void dict_destroy(dict_t *d);