CC = /usr/bin/mpicc
NVCC = /usr/local/cuda/bin/nvcc
OBJECTS = graph.o stack.o utils.o hash.o seq_tarjan.o
CUDA_PATH?=/usr/local/cuda-12.0/lib64
FLAGS = -g

# METTERE RISULTATI IN BUILD

all: clean graph.o stack.o utils.o hash.o seq_tarjan.o main

test:
	echo "Todo"

clean:
	rm -rf *.o *.out

main: main.o $(OBJECTS)
#   $(CC) main.o $(OBJECTS) -o main.out -L $(CUDA_PATH) -lcudart
	$(CC) main.o $(OBJECTS) -o main.out
main.o: main.c
	$(CC) -g main.c -c -o main.o -I libraries 

graph.o: graph.c
	$(CC) $(FLAGS) graph.c -c -o graph.o

stack.o: stack.c
	$(CC) $(FLAGS) stack.c -c -o stack.o

utils.o: utils.c
	$(CC) $(FLAGS) utils.c -c -o utils.o

hash.o: hash.c
	$(CC) $(FLAGS) hash.c -c -o hash.o

seq_tarjan.o: seq_tarjan.c
	$(CC) $(FLAGS) seq_tarjan.c -c -o seq_tarjan.o
	
#tarjan.o: tarjan.cu
#	$(NVCC) -g -c tarjan.cu -o tarjan.o

tarjan.o: tarjan.cu
	$(NVCC) -g tarjan.cu -o tarjan.o
