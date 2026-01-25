1. Allocate and free a simple struct
```c
//exercise.c
#include <stdlib.h>
#include "exercise.h"

Point *point_new(int x, int y) {
  Point *new_one = malloc(sizeof(Point)); 
  if (new_one == NULL) {
    return NULL;
  }

  new_one->x = x;
  new_one->y = y;

  return new_one;
}

void point_free(Point *p) {
  if (p == NULL) {
    return;
  }

  free(p); 
}

//exercise.h
#pragma once

typedef struct {
  int x;
  int y;
} Point;

Point *point_new(int x, int y);
void  point_free(Point *p);
```

2. Allocate Int Array on the Heap 
```c
#include <stdlib.h>
#include <stddef.h>

int *int_array_new(size_t length, int initial_value) {
  if (length == 0) {
    return NULL;
  }
  
  int *arr = malloc(length * sizeof(int));
  if (arr == NULL) {
    return NULL;
  }

  int *current = arr;
  int *end = arr + length;
  while (current < end) {
    *current = initial_value;
    current++;
  }
  //alternative:
  //for (size_t i = 0; i < length; i++) {
  //arr[i] = initial_value;

  return arr;
}
```

3. 
