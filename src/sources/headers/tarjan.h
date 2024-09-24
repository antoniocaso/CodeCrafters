//
// Created by miriam on 19/12/22.
//

#ifndef HPC_PROJECT_TARJAN_H
#define HPC_PROJECT_TARJAN_H

#include <stdio.h>
#include <stdlib.h>
#include "proto.h"

#define NIL (-1)

// u rappresenta la posizione nel bucket di u
//void tarjan(graph_t *g, int u, int disc[], int low[], stack_t *st, bool stackMember[]);
//void find_scc(graph_t *g);
//void fake_find_scc(graph_t *g);
#ifdef __cplusplus
extern "C" void cuda_tarjan_host(graph_t *g);
#else
void cuda_tarjan_host(graph_t *g);
#endif

#endif //HPC_PROJECT_TARJAN_H
