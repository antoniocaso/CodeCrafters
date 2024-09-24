#define type_t int

typedef struct
{
    type_t *array; // underlying structure
    int n;         // number of elements
    int size;      // size of the structure
} list_t;

typedef struct
{
    type_t key;
    void *value;
} pair_t;

typedef struct
{
    pair_t **bucket;
    int cap;
} dict_t;

typedef struct
{
    type_t label;     // name of the vertex
    int owner;        // true if taken by another MPI node while cutting
    dict_t *adj_list; // vertex adj list.
    int lowlink;
    int index;
    bool in_stack;
    int local_scc;
} vertex_t;

typedef struct
{
    int nv;           // number of vertices
    vertex_t *bucket; // bucket of adiacency lists
} graph_t;

typedef struct
{
    vertex_t **array;
    int top;
} stack_t;

typedef struct
{
    int nv;
    dict_t bucket;
} subgraph_t;
