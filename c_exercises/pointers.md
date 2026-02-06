1. Basic pointer & dereference
```c
#include <stdio.h>
#include "exercise.h"

int my_number = 0;
int *my_number_ptr = NULL;

void pointer_setup() {
  my_number = 10;
  my_number_ptr = &my_number;
  *my_number_ptr = 42;
  printf("Pointer address: %p\n", (void*)my_number_ptr);
  printf("Value: %d\n", my_number);
}
```

2. Swap two integers using pointers
```c
void swap_ints(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 2a. Use a pointer to update a player's health
void apply_damage(int *health, int damage) {
  *health -= damage;
  if (*health < 0) {
    *health = 0;
  }
}
```

3. Set a value via pointer to pointer
```c
void set_via_pp(int **pp, int value) {
  if (pp == 0 || *pp == 0) {
    return;
  }
  **pp = value;
}
```

4. Walk an array with pointer arithmetic
```c
#include <stddef.h>

void fill_with_pointer(int *out, int length) {
  int arr[5] = {1, 2, 3, 4, 5};
  int *p = arr;
  for (int i = 0; i < length && i < 5; i++) {
    *(out + i) = *(p + i);
  }
}
```

5. String (char *) manipulation - compute the length of a C-string using a pointer that walks through the string
```c
#include <stddef.h>

size_t my_strlen(const char *s) {
  //int count = 0;
  const char *p = s;
  while (*p != '\0') {
  //while (*(s + count) != '\0') {
    //count++;
    p++;
  } 
  return (size_t)(p - s);
}
```

5a. Copy a C string from src to dst using pointer arithmetic
```c
#include <stddef.h>

void copy_message(const char *src, char *dst) {
  const char *p_src = src;
  char *p_dst = dst;
  while (*p_src != '\0') {
    *p_dst = *p_src;
    p_dst++;
    p_src++;
  }
  *p_dst = '\0';
}
```

6. Dynamically allocated array
```c
#include <stdlib.h>

int *make_sequence(size_t n) {
  if (n == 0) {
    return NULL;
  }
  int *numbers = malloc(n * sizeof(int)); 
  if (numbers == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < n; i++) {
    *(numbers + i) = i;
  }
  return numbers;
}
```

7. Sum with a moving pointer
```c
#include <stddef.h>

int sum_with_pointer(const int *arr, size_t length) {
  int sum = 0;
  
  const int *p = arr;
  const int *end = arr + length;
  while (p < end) {
    sum += *p;
    p++;
  }

  return sum;
}
```

8. Count positive numbers using pointer arithmetic
```c
#include <stddef.h>

size_t count_positive(const int *arr, size_t length) {
  if (length == 0) {
    return 0;
  }

  int count = 0;
  
  const int *p = arr;
  const int *end = arr + length;

  while (p < end) {
    if (*p > 0) {
      count++;
    }
    p++;
  }

  return count;
}
```

9. Find the maximum element
```c
#include <stddef.h>

int *find_max(int *arr, size_t length) {
  if (length == 0) {
    return NULL;
  }

  int *max = arr;
  int *current = arr + 1;
  int *end = arr + length;

  while (current < end) {
    if (*max < *current) {
      max = current;
    }
    current++;
  }

  return max;
}
```

10. Reverse an array in-place using pointers
```c
#include <stddef.h>

void reverse_in_place(int *arr, size_t length) {
  int *left = arr;
  int *right = arr + length - 1;

  while (left < right) {
    int reversable = *left;
    *left = *right;
    *right = reversable;
    left++;
    right--;
  }
}
```

11. Compare two arrays for equality
```c
#include <stddef.h>

int arrays_equal(const int *a, const int *b, size_t length) {
  if (length == 0) {
    return 1;
  }

  const int *pa = a;
  const int *pb = b;
  const int *end = a + length;

  while (pa < end) {
    if (*pa != *pb) {
      return 0;
    }
    pa++;
    pb++;
  }

  return 1;
}
```

12. Write two helper functions - set_value should store a value through a pointer to a pointer, swap_pointers should swap two int * pointers using int ** parameters.
```c
#include <stddef.h>

void set_value(int **pp, int value) {
  if (pp == NULL || *pp == NULL) {
    return;
  }
  **pp = value;
}

void swap_pointers(int **a, int **b) {
  if (a == NULL || b == NULL) {
    return;
  }
  int *temp = *a;
  *a = *b;
  *b = temp;
}
```

13. To be added
