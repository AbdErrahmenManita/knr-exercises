#include <stdio.h>
float conversion(int f);
int main() {
  int celcius, fahrenheit;
  printf("Fahrenheit\tCelcius\n");
  printf("==========\t=======\n");
  for (fahrenheit = 0; fahrenheit <= 300; fahrenheit = fahrenheit + 20) {
    printf("%10d\t%7.1f\n", fahrenheit, conversion(fahrenheit));
  }
  return 0;
}
float conversion(int f) { return ((5.0 / 9) * (f - 32)); }
