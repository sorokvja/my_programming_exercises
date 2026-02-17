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

3. to be added
