#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "positionHandler.h"

typedef struct {
    pos* v;
    int size, ini, fim;
} queue;

queue* queue_create();
void queue_insert(queue* q, pos x);
void queue_insertList(queue* q, posList list);
pos queue_pop(queue* q);
pos queue_next(queue* q);
int queue_empty(queue q);
void queue_destroy(queue* q);


#endif
