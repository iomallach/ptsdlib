#include "vector.h"
#include "string.h"

Vector *vector_new(size_t elem_size) {
  Vector *vector = malloc(sizeof(Vector));
  vector->data = NULL;
  vector->capacity = 0;
  vector->size = 0;
  vector->_elem_malloc_size = elem_size;
  return vector;
}

void vector_free(Vector *vector) {
  if (vector->data != NULL) {
    free(vector->data);
  }
  free(vector);
}

void vector_push_back(Vector *vector, void *value) {
  if (vector->data == NULL) {
    vector->data = malloc(vector->_elem_malloc_size * VECTOR_INIT_CAPACITY);
    vector->capacity = VECTOR_INIT_CAPACITY;
    PUSH_BACK(vector, value, vector->_elem_malloc_size);
  } else if (vector->size + 1 > vector->capacity) {
    vector->data =
        realloc(vector->data, vector->capacity * vector->_elem_malloc_size * 2);
    vector->capacity *= 2;
    PUSH_BACK(vector, value, vector->_elem_malloc_size);
  } else {
    PUSH_BACK(vector, value, vector->_elem_malloc_size);
  }
}

void vector_pop_back(Vector *vector) {
  if (vector->size > 0) {
    vector->size -= 1;
  }
  // TODO: Realloc at some size/capacity threshold
}

void *_vector_at(Vector *vector, size_t index) {
  return (void *)((char *)vector->data + (index * vector->_elem_malloc_size));
}

void vector_foreach(Vector *vector, void (*callback)(void *value)) {
  for (int i = 0; i < vector->size; i++) {
    callback(_vector_at(vector, i));
  }
}
