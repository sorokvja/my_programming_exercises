0. Allocate memory on the heap for one int using malloc
```c
#include <stdlib.h>

int *allocate_int_42(void) {
  int *p = malloc(sizeof(int));
  if (!p) {
    return NULL;
  }
  *p = 42;
  return p;
}
```

1. Allocate and free a simple struct  

exercise.h
```c
#pragma once

typedef struct {
  int x;
  int y;
} Point;

Point *point_new(int x, int y);
void  point_free(Point *p);
```
exercise.c
```c
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
```

2. Allocate a dynamic array of int values on the heap, set all elements to the same initial value, and return a pointer to the array  
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

3. Build a simple system that tracks a stack of int values - implement a fixed-capacity stack of int values stored on the heap
```c
#include <stdlib.h>
#include <stddef.h>

typedef struct {
  size_t count;
  size_t capacity;
  int *data;
} IntStack;

IntStack *int_stack_new(size_t capacity) {
  IntStack *s = malloc(sizeof(IntStack));
  if (s == NULL) {
    return NULL;
  }

  s->data = NULL;
  s->count = 0;
  s->capacity = capacity;

  if (capacity > 0) {
    s->data = malloc(sizeof(int) * capacity);
    if (s->data == NULL) {
      free(s);
      return NULL;
    }
  } else {
    s->data = NULL;
  }

  return s;
}

void int_stack_free(IntStack *s) {
  if (s == NULL) {
    return;
  }
  free(s->data);
  free(s);
}

int int_stack_push(IntStack *s, int value) {
  if (s == NULL) {
    return -1;
  }
  if (s->count == s->capacity) {
    return -1;
  }
  s->data[s->count] = value;
  s->count++;
  return 0;
}

int int_stack_pop(IntStack *s, int *out_value) {
  if (s == NULL || out_value == NULL) {
    return -1;
  }
  if (s->count == 0) {
    return -1;
  }
  s->count--;
  *out_value = s->data[s->count];
  return 0;
}
```

4. Add stack_push and stack_pop for stack_t  

exercise.h
```c
#pragma once

#include <stddef.h>

typedef struct {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void stack_free(stack_t *s);

int stack_push(stack_t *s, void *value);
int stack_pop(stack_t *s, void **out_value);
```
exercise.c
```c
#include <stdlib.h>
#include "exercise.h"

stack_t *stack_new(size_t capacity) {
  stack_t *s = malloc(sizeof(stack_t));
  if (s == NULL) {
    return NULL;
  }

  s->count = 0;
  s->capacity = capacity;
  s->data = NULL;

  if (capacity > 0) {
    s->data = malloc(sizeof(void *) * capacity);
    if (s->data == NULL) {
      free(s);
      return NULL;
    }
  }

  return s;
}

void stack_free(stack_t *s) {
  if (s == NULL) {
    return;
  }
  free(s->data);
  free(s);
}

int stack_push(stack_t *s, void *value) {
  if (s->count  == s->capacity) {
    return -1;
  }
  s->data[s->count] = value;
  s->count++;
  return 0;
}

int stack_pop(stack_t *s, void **out_value) {
  if (s->count == 0) {
    return -1;
  }
  s->count--;
  *out_value = s->data[s->count];
  return 0;
}
```

5. Upgrade a stack to automatically grow when it’s full. 

stack.h
```c
#pragma once

#include <stddef.h>

typedef struct {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t initial_capacity);
void stack_free(stack_t *s);
int stack_push(stack_t *s, void *value);
int stack_pop(stack_t *s, void **out_value);
```
exercise.c
```c
#include <stdlib.h>
#include "stack.h"

stack_t *stack_new(size_t initial_capacity) {
  stack_t *s = malloc(sizeof(stack_t));
  if (!s) {
    return NULL;
  }

  s->count = 0;
  s->capacity = initial_capacity;
  s->data = NULL;

  if (initial_capacity > 0) {
    s->data = malloc(initial_capacity * sizeof(void *));
    if (!s->data) {
      free(s);
      return NULL;
    }
  }

  return s;
}

void stack_free(stack_t *s) {
  if (!s) {
    return;
  }
  free(s->data);
  free(s);
}

int stack_push(stack_t *s, void *value) {
  if (s == NULL) {
    return -1;
  }
  if (s->count < s->capacity) {
    s->data[s->count] = value;
    s->count++;
    return 0;
  }
  if (s->count == s->capacity) {
    size_t new_capacity;
    if (s->capacity == 0) {
      new_capacity = 1;
    } else {
      new_capacity = s->capacity * 2;
    }
    void **new_data = realloc(s->data, new_capacity * sizeof(void *));
    if (new_data == NULL) {
      return -1;
    }
    s->data = new_data;
    s->capacity = new_capacity;
  }
  s->data[s->count] = value;
  s->count++;
  return 0;
}

int stack_pop(stack_t *s, void **out_value) {
  if (!s || !out_value) {
    return -1;
  }
  if (s->count == 0) {
    return -1;
  }

  s->count--;
  *out_value = s->data[s->count];
  return 0;
}
```

6. Allocate an array of Player on the heap, then free the array safely.  

player.h  
```c
#pragma once

typedef struct {
    int id;
    int score;
} Player;

Player *create_players(int num_players);
void free_players(Player *players);
```

exercise.c
```c
#include <stdlib.h>
#include "player.h"

Player *create_players(int num_players) {
  if (num_players <= 0) {
    return NULL;
  }
  Player *arr_players = malloc(num_players * sizeof(Player));
  if (!arr_players) {
    return NULL;
  }
  for (int i = 0; i < num_players; i++) {
    (arr_players + i)->id = i;
    (arr_players + i)->score = i * 10;
    //alternative sintax would be:
    //arr_players[i].id = i;
    //arr_players[i].score = i * 10;
  }
  return arr_players;
}

void free_players(Player *players) {
  if (!players) {
    return;
  } 
  free(players);
}
```

7. Duplicate a string on the heap
```c
#include <stdlib.h>

char *duplicate_string(const char *input) {
  if (input == NULL) {
    return NULL;
  }
  const char *p = input;
  while (*p != '\0') {
    p++;
  }
  int len = p - input;
  
  char *copy = malloc((len + 1) * sizeof(char));
  if (copy == NULL) {
    return NULL;
  }
  char *dst = copy;
  const char *src = input;
  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
  return copy;
}
```

8. Allocate a countdown array
```c
#include <stdlib.h>

int *countdown_new(int start, int *out_length) {
  if (out_length == NULL) {
    return NULL;
  }
  if (start <= 0) {
    *out_length = 0;
    return NULL;
  }
  int *countdown = malloc(start * sizeof(int));
  if (countdown == NULL) {
    *out_length = 0;
    return NULL;
  }
  *out_length = start;

  int *dst = countdown;
  int i = start;
  while (i > 0) {
    *dst = i;
    i--;
    dst++;
  }
  return countdown;
}
```

9. Build a dynamic 2D grid (e.g., for a game map), each row can have a different length (a jagged array). The task is to allocate and free the grid using dynamic memory. 

```c
#include <stdlib.h>
#include <stddef.h>

int **make_grid(const int *row_sizes, size_t num_rows) {
  if (row_sizes == NULL) {
    return NULL;
  }

  int **grid = malloc(num_rows * sizeof(int*));
  if (grid == NULL ) {
    return NULL;
  }

  for (int i = 0; i < num_rows; i++) {
    *(grid + i) = malloc(*(row_sizes + i) * sizeof(int));
    if (*(grid + i) == NULL) {
      for (int j = 0; j < i; j++) {
        free(*(grid + j));
      }
      free(grid);
      return NULL;
    }
    for (int k = 0; k < *(row_sizes + i); k++) {
      *(*(grid + i) + k) = i * 10 + k;
    }
  }
  return grid;
}

void free_grid(int **grid, const int *row_sizes, size_t num_rows) {
  if (grid == NULL ) {
    return;
  }
  for (int i = 0; i < num_rows; i++) {
    free(*(grid + i));
  }
  free(grid);
}
```

10. Create and manage a Rectangle struct on the heap using malloc and free
rectangle.h
```c
#pragma once

typedef struct {
  int width;
  int height;
} Rectangle;

Rectangle *rectangle_new(int width, int height);
void rectangle_free(Rectangle *r);
int rectangle_area(Rectangle *r);
```

exercise.c
```c
#include <stdlib.h>
#include <stdio.h>
#include "rectangle.h"

Rectangle *rectangle_new(int width, int height) {
  printf("Allocating rectangle...\n");
  Rectangle *r = malloc(sizeof(Rectangle));
  if (!r) {
    return NULL;
  }
  r->width = width;
  r->height = height;
  return r;
}

void rectangle_free(Rectangle *r) {
  printf("Freeing rectangle...\n");
  if (!r) {
    return;
  }
  free(r);
}

int rectangle_area(Rectangle *r) {
  if (!r) {
    return 0;
  }
  int area = r->width * r->height;
  return area;
}
```

11. Implement dynamic memory management for a small set of 2D points stored on the heap.
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} Point;

Point *point_new(int x, int y) {
  Point *p = malloc(sizeof(Point));
  if (p == NULL) {
    return NULL;
  }
  (*p).x = x;    //p->x = x;
  p->y = y;
  return p;
}

void point_free(Point *p) {
  if (p == NULL) {
    return;
  }
  free(p);
}

void point_print(Point *p) {
  if (p == NULL) {
    printf("NULL");
  } else {
    printf("(%d, %d)", p->x, p->y);
  }
}
```
