#ifndef QUEUE_H
#define QUEUE_H

#define CAPACITY 10
typedef struct {
    int buffer[CAPACITY];
    int head;
    int tail;
    int size;
} CircularQueue;


void enqueue(CircularQueue *q, int value);
void init_queue(CircularQueue *q);
int getOldestElement(const CircularQueue *q);

#endif // QUEUE_H
