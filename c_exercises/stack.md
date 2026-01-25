1. Implement a simple stack of int values using a fixed-size array.
```c
#include <stddef.h>

typedef struct {
  int data[10];
  size_t count;
} IntStack;

void int_stack_init(IntStack *s) {
  s->count = 0;
}

int int_stack_push(IntStack *s, int value) {
  if (s->count == 10) {
    return -1;
  }

  s->data[s->count] = value;
  s->count++;
  return 0;
}

int int_stack_pop(IntStack *s, int *out_value) {
  if (s->count == 0) {
    return -1;
  }

  s->count--;
  *out_value = s->data[s->count];
  return 0;
}
```

2. 
