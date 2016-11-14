#include "buffer.h"
#include <stdlib.h>

Buffer* buffer_create() {
    Buffer* new;
    new = (Buffer*) malloc(sizeof(struct buf_s));
    new->data = (char*) malloc(1024 * sizeof(char));
    new->max = 1024;
    new->top = 0;
    return new;
}

void buffer_reallocate(Buffer* b) {
    Buffer* new;
    int i;
    new = (Buffer*) malloc(sizeof(struct buf_s));
    new->data = (char*) malloc(2 * b->max * sizeof(char));
    for(i = 0; i < buffer->top; i++)
        new->data[i] = b->data[i];
    new->max = 2 * b->max;
    new->top = b->top;
    free(b->data);
    free(b);
    b = new;
}

void buffer_push_back(Buffer* b, char c) {
    if(b->max == b->top)
        buffer_reallocate(b);
    b->data[b->top++] = c;
}

void buffer_reset(Buffer* b) {
    int i;
    for(i = 0; i < Buffer->top; i++)
        Buffer->data[i] = 0;
    b->top = 0;
}

void buffer_destroy(Buffer* b) {
    free(b->data);
    free(b);
}
