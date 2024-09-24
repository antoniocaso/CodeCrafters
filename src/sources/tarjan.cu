#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "headers/lib.h"
#include "tarjan.h"

#define THREADxBLOCKalongXorY 16

// M Matrice di adiacenza
// N numero righe e colonne matrice di adiacenza
__global__ void tarjanDevice(int *M, int N, int *disc, int *low, int *visited, int *tarjan_stack, int *control_stack, int* stack_member)
{

    // row e col sono gli indici riga e colonna per l'inizio della sottomatrice
    // ogni thread processa una sottomatrice
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    // Facciamo delle prove solo per il primo blocco, dovrebbe trovare una SCC
    if (threadIdx.x == 0 && threadIdx.y == 0 && blockIdx.x == 0 && blockIdx.y == 0)
    {

        int control_stack_depth = 0;
        int tarjan_stack_depth = 0;
        // index di tarjan
        int index = 0;
        int i = row;

        // push nodo iniziale sullo stack
        tarjan_stack[threadIdx.x * N + tarjan_stack_depth] = i; // indice di riga
        stack_member[i] = 1;
        tarjan_stack_depth++;
    
        // push nodo iniziale sullo stack
        control_stack[threadIdx.x * N + control_stack_depth] = i; // indice di riga
        control_stack_depth++;

        disc[i] = index;
        low[i] = index;
        index++;

        
        while (control_stack_depth > 0)
        {
            // while control stack is not empty

            // pop
            int node = control_stack[threadIdx.x * N + control_stack_depth - 1];
            printf("%d\n", node);
            
            for (int k = 0; k < 10; k++)
            {
                if (M[node * N + k] == 1)
                {
                    if (visited[k] == 0)
                    {
                        visited[k] = 1;
                        control_stack[threadIdx.x * N + control_stack_depth] = k; // indice di riga
                        control_stack_depth++;

                        tarjan_stack[threadIdx.x * N + tarjan_stack_depth] = k; // indice di riga
                        stack_member[k] = 1;
                        tarjan_stack_depth++;

                        disc[k] = index;
                        low[k] = index;
                        index++;
                    }else if(stack_member[k] == 1){
                    
                        low[node] = low[node] < low[k] ? low[node] : low[k];
                    }
                }
            }

            int top = control_stack[threadIdx.x * N + control_stack_depth - 1];
            control_stack_depth--;

            if(control_stack_depth != 0){
                top = control_stack[threadIdx.x * N + control_stack_depth - 1];
                low[top] = low[top] < low[node] ? low[top] : low[node];
            }
            if(low[node] == disc[node]){
                
                printf("Found SCC, %d\n", node);
            }
            
        }
        printf("END WHILE\n");
    }
}

void to_adj_matrix(int *M, int width)
{
    FILE *file = fopen("../data/graph103", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    char *buffer = (char *)malloc(sizeof(char) * 10000);

    char delim[] = " ";
    int src = 0, dst = 0;
    char *token;
    while (fgets(buffer, 10000, file) != NULL)
    {
        printf("buffer: %s", buffer);
        token = strtok(buffer, delim);
        printf("LOG: reading row: %s\n", token);

        token = strtok(NULL, delim);
        while (token != NULL)
        {
            sscanf(token, "%d", &dst);
            printf("LOG: read: %s\n", token);
            M[src * width + dst] = 1;
            token = strtok(NULL, delim);
        }
        src++;
    }

    free(buffer);
}

int main()
{

    int width = 103; // number of vertices

    int *M = (int *)malloc(width * width * sizeof(int));
    memset(M, 0, width * width * sizeof(int));

    to_adj_matrix(M, width);

    // stampa matrice

    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < width; x++)
        {
            printf("%d ", M[y * width + x]);
        }
        printf("\n");
    }

    // CUDA grid management
    int gridsize = width / THREADxBLOCKalongXorY;

    if (gridsize * THREADxBLOCKalongXorY < width)
    {
        gridsize = gridsize + 1;
    }

    dim3 dimGrid(gridsize, gridsize);
    dim3 dimBlock(THREADxBLOCKalongXorY, THREADxBLOCKalongXorY);
    printf("Gridsize: %d\n", gridsize);

    int *dev_M;
    int *dev_disc, *dev_low, *dev_visited;
    int *dev_control, *dev_tarjan, *dev_member;
    int size = width * width * sizeof(int);
    cudaMalloc((void **)&dev_M, size);

    cudaMalloc((void **)&dev_disc, width * sizeof(int));
    cudaMalloc((void **)&dev_low, width * sizeof(int));
    cudaMalloc((void **)&dev_visited, width * sizeof(int));
    cudaMalloc((void **)&dev_control, width * sizeof(int));
    cudaMalloc((void **)&dev_tarjan, width * sizeof(int));
    cudaMalloc((void **)&dev_member, width * sizeof(int));

    cudaMemcpy(dev_M, M, size, cudaMemcpyHostToDevice);

    cudaMemset(dev_disc, -1, width * sizeof(int));
    cudaMemset(dev_low, -1, width * sizeof(int));
    cudaMemset(dev_visited, 0, width * sizeof(int));
    cudaMemset(dev_control, 0, width * sizeof(int));
    cudaMemset(dev_tarjan, 0, width * sizeof(int));
    cudaMemset(dev_member, 0, width * sizeof(int));


    cudaError_t mycudaerror;
    mycudaerror = cudaGetLastError();

    // kernel launch
    tarjanDevice<<<dimGrid, dimBlock>>>(dev_M, width, dev_disc, dev_low, dev_visited, dev_tarjan, dev_control, dev_member);
    mycudaerror = cudaGetLastError();
    if (mycudaerror != cudaSuccess)
    {
        fprintf(stderr, "%s\n", cudaGetErrorString(mycudaerror));
        exit(1);
    }
    cudaDeviceSynchronize();
    cudaFree(dev_M);
    cudaFree(dev_disc);
    cudaFree(dev_low);
    free(M);
    printf("Terminated");
    exit(0);
}
