1. Create a tiny "alchemist's calculator" that performs basic math using an enum and a switch statement.
```c
typedef enum Operation {
  ADD,
  SUBTRACT,
  MULTIPLY,
  DIVIDE
} Operation;

int calculate(int a, int b, Operation op) {
  switch (op) {
    case ADD:
      return a + b;
    case SUBTRACT:
      return a - b;
    case MULTIPLY:
      return a * b;
    case DIVIDE:
      return (b != 0) ? (a / b) : 0;
    default:
      return 0;
  }
}
```

2. Use an enum and a switch statement to model how bad weather drains a traveler's stamina.
```c
typedef enum {
  WEATHER_SUNNY,
  WEATHER_CLOUDY,
  WEATHER_WINDY,
  WEATHER_RAINY,
  WEATHER_STORM
} WeatherCondition;

int get_stamina_drain(WeatherCondition weather) {
  switch (weather) {
    case WEATHER_SUNNY:
      return 1;
    case WEATHER_CLOUDY:
      return 1;
    case WEATHER_WINDY:
      return 2;
    case WEATHER_RAINY:
      return 3;
    case WEATHER_STORM:
      return 10;
    default:
      return -1;
  }
}
```

3. Use an enum inside a struct to control how a shopkeeper in a game would calculates prices.
```c
#include <stddef.h>

typedef enum {
  FRIENDLY,
  NEUTRAL,
  GREEDY,
  DISCOUNT
} Disposition;

typedef struct {
  Disposition disposition;
  float markup_rate;
} Shopkeeper;

float calculate_price(Shopkeeper s, float base_price) {
  if (base_price < 0.0f) {
    return 0.0f;
  }
  switch (s.disposition) {
    case FRIENDLY:
      return base_price;
    case NEUTRAL:
      return base_price * 1.2f;
    case GREEDY:
      return base_price * s.markup_rate;
    case DISCOUNT:
      return base_price * 0.8f;
    default:
      return base_price;
  }
}
```

4. Use an enum and a switch statement to move a player around a 2D grid.  

exercise.h
```c
#pragma once

typedef struct {
  int x;
  int y;
} Point;

typedef enum {
  DIR_NORTH,
  DIR_SOUTH,
  DIR_EAST,
  DIR_WEST
} Direction;

void move_player(Point *p, Direction dir, int steps);
```
exercise.c
```c
#include <stdio.h>
#include "exercise.h"

void move_player(Point *p, Direction dir, int steps) {
  if (p == NULL || steps < 0) {
    return;
  }
  switch (dir) {
    case DIR_NORTH:
      (*p).y += steps;
      break;
    case DIR_SOUTH:
      (*p).y -= steps;
      break;
    case DIR_EAST:
      p->x += steps;
      break;
    case DIR_WEST:
      p->x -= steps;
      break;
    default:
      printf("Unknown direction: %d\n", dir);
      break;
  }
}
```

