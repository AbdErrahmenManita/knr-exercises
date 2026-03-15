#include <stdio.h>
/* print Celcius-Fahrenheit table
    for celcius =0,10,20,30,...,100; floiting-point*/
int main() {
  float fahr, celcius;
  float lower, upper, step;
  lower = 0;
  upper = 100;
  step = 10;
  celcius = lower;
  printf("Celcius\tFahrenheit\n");
  printf("=======\t==========\n");
  while (celcius <= upper) {
    fahr = (9.0 / 5) * celcius + 32;
    printf("%7.0f\t%10.1f\n", celcius, fahr);
    celcius = celcius + step;
  }
  return 0;
}
