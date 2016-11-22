#include "queue.h"
#include "positionHandler.h"
#include <stdlib.h>

queue* queue_create() {
    queue* q;
    q = malloc(sizeof(queue));
    q->v = malloc(400 * sizeof(pos));
    q->ini = q->fim = 0;
    q->size = 400;
    return q;
}

void queue_reallocate(queue* q) {

}

int queue_empty(queue q) {
    return q.fim == q.ini;
}

void queue_insert(queue* q, pos x) {
    if((q->fim + 1) % q->size == q->ini)
        queue_reallocate(q);
    q->v[q->fim] = x;
    q->fim = (q->fim + 1) % q->size;
}

void queue_insertList(queue* q, posList list) {
    int i;
    for(i = 0; i < list.size; i++)
        queue_insert(q, list.v[i]);
}

pos queue_pop(queue *q) {
    pos x;
    if(!queue_empty(*q)) {
        x = q->v[q->ini];
        q->ini = (q->ini + 1) % q->size;
        return x;
    }
    x.i = 0;
    x.j = 0;
    return x;
}

pos queue_next(queue *q) {
    return q->v[q->ini];
}

void queue_destroy(queue* q) {
    free(q->v);
    free(q);
}
