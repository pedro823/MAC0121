#ifndef __BUFFER_H__
#define __BUFFER_H__

typedef struct buf_s {
    char* data;
    int max, top;
} Buffer;

Buffer* buffer_create();

void buffer_push_back(Buffer* b, char c);

void buffer_reset(Buffer* b);

void buffer_destroy(Buffer* b);

#endif
