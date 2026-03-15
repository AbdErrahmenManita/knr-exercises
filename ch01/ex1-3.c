#include <stdio.h>
/* print Fahrenheit-Celcius table
    for fahr =0 , 20 ,40 , ... ,300; floiting-point */

int main() {
  float fahr, celcius;
  float lower, upper, step;
  lower = 0;
  upper = 300;
  step = 20;
  fahr = lower;
  printf("Fahrenheit\tCelcius\n");
  printf("==========\t=======\n");
  while (fahr <= upper) {
    celcius = (5.0 / 9) * (fahr - 32);
    printf("%10.0f\t%7.1f\n", fahr, celcius);
    fahr = fahr + step;
  }
  return 0;
}
