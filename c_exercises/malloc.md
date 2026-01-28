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
