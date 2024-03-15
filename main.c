#include "vector.h"
#include <stdio.h>

void print_int(void *value) { printf("%d ", *(char *)value); }

int main(void) {
  Vector *vector = vector_new(sizeof(int));
  if (vector == NULL) {
    printf("Failed to allocate memory for vector\n");
  }

  for (int i = 65; i < 69; i++) {
    vector_push_back(vector, (void *)&i);
    vector_foreach(vector, print_int);
    printf("\n");
  }
  print_int(vector_get(vector, 0));
  print_int(vector_get(vector, 2));
  int t = 4;
  vector_set(vector, 2, (void *)&t);
  print_int(vector_get(vector, 2));
  printf("\n-------------------------\n");
  vector_pop_back(vector);
  vector_pop_back(vector);
  vector_foreach(vector, print_int);
  printf("\n-------------------------\n");
  vector_pop_back(vector);
  vector_pop_back(vector);
  vector_pop_back(vector);
  vector_pop_back(vector);
  vector_free(vector);

  return 0;
}
