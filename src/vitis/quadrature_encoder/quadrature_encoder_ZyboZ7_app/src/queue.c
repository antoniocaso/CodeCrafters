#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

// Inserisce un elemento nella coda circolare
void enqueue(CircularQueue *q, int value) {
    q->buffer[q->tail] = value;
    q->tail = (q->tail + 1) % CAPACITY;
    if (q->size == CAPACITY) {
        q->head = (q->head + 1) % CAPACITY;  // Se la coda è piena, sposta la testa
    } else {
        q->size++;
    }
}

// Inizializza la coda circolare
void init_queue(CircularQueue *q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    enqueue(q, 0);
}

// Restituisce l'elemento più vecchio nella coda
int getOldestElement(const CircularQueue *q) {
    if (q->size == 0) {
        printf("Errore: la coda è vuota.\n");
    }
    return q->buffer[q->head];
}
