#include "vector.h"
#include "string.h"

Vector *vector_new(size_t elem_size) {
  Vector *vector = malloc(sizeof(Vector));
  if (vector == NULL) {
    LOG_ERROR("Failed to allocate memory for vector");
    exit(137);
  }
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
    if (vector->data == NULL) {
      LOG_ERROR("Failed to allocate memory for vector");
      exit(137);
    }
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
  } else {
    LOG_ERROR("Vector is empty");
    exit(-1);
  }

  if (vector->size < vector->capacity / 2) {
    vector->data =
        realloc(vector->data, vector->capacity * vector->_elem_malloc_size / 2);
  }
}

void *vector_get(Vector *vector, size_t index) {
  return (void *)((char *)vector->data + (index * vector->_elem_malloc_size));
}

void vector_set(Vector *vector, size_t index, void *value) {
  size_t offset = index * vector->_elem_malloc_size;
  memcpy((void *)((char *)vector->data + offset), value,
         vector->_elem_malloc_size);
}

void vector_foreach(Vector *vector, void (*callback)(void *value)) {
  for (int i = 0; i < vector->size; i++) {
    callback(vector_get(vector, i));
  }
}

size_t vector_size(Vector *vector) { return vector->size; }

bool vector_is_empty(Vector *vector) { return (vector->size == 0) ? 1 : 0; }

