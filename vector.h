#ifndef vector_h
#define vector_h

#include <stdlib.h>
#include <stdio.h>

#define VECTOR_INIT_CAPACITY 32
#define PUSH_BACK(vec, src, offset)                                            \
  char *ptr = (char *)vec->data + vec->size * offset;                          \
  memcpy((void *)ptr, src, offset);                                            \
  vec->size += 1;
#define LOG_ERROR(message, ...) printf("[ERROR] " message "\n", ##__VA_ARGS__)

typedef struct {
  void *data;
  size_t capacity;
  size_t size;
  size_t _elem_malloc_size;
} Vector;

Vector *vector_new(size_t elem_size);
void vector_free(Vector *vector);
void vector_push_back(Vector *vector, void *value);
void vector_pop_back(Vector *vector);
void vector_foreach(Vector *vector, void (*callback)(void *value));
void *vector_get(Vector *vector, size_t index);
void vector_set(Vector *vector, size_t index, void *value);

#endif
