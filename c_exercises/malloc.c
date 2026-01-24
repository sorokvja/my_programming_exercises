// 1. Allocate and free a simple struct
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

// 2. 
