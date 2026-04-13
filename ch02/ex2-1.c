#include <float.h>
#include <limits.h>
#include <stdio.h>
long power_n(int base, int n) {
  long res = 1;
  long i = 0;
  while (i < n) {
    res = res * base;
    ++i;
  }
  return res;
}
long max_val(int size) {
  long i = 0;
  long res = 0;
  while (i < size) {
    res = res + power_n(2, i);
    ++i;
  }
  return res;
}
signed long min_val_signed(int size) { return -power_n(2, size - 1); }
int main() {
  printf("Signed Char :    %20d\tto\t%d\n", SCHAR_MIN, SCHAR_MAX);
  printf("Unsigned Char :  %20d\tto\t%u\n", 0, UCHAR_MAX);
  printf("Signed Int :     %20d\tto\t%d\n", INT_MIN, INT_MAX);
  printf("Unsigned Int :   %20d\tto\t%u\n", 0, UINT_MAX);
  printf("Signed Short :   %20d\tto\t%d\n", SHRT_MIN, SHRT_MAX);
  printf("Unsigned Short : %20d\tto\t%u\n", 0, USHRT_MAX);
  printf("Signed Long :    %20ld\tto\t%ld\n", LONG_MIN, LONG_MAX);
  printf("Unsigned Long :  %20d\tto\t%lu\n", 0, ULONG_MAX);

  /// These are how we are gonna compute them

  printf("\nSigned Char :  %20d\tto\t%d\n", min_val_signed(sizeof(char) * 8),
         max_val((sizeof(char) * 8) - 1));
  printf("Unsigned Char :  %20d\tto\t%u\n", 0, max_val(sizeof(char) * 8));
  printf("Signed Int :     %20d\tto\t%d\n", min_val_signed(sizeof(int) * 8),
         max_val((sizeof(int) * 8) - 1));
  printf("Unsigned Int :   %20d\tto\t%u\n", 0, max_val(sizeof(int) * 8));
  printf("Signed Short :   %20d\tto\t%d\n", min_val_signed(sizeof(short) * 8),
         max_val((sizeof(short) * 8) - 1));
  printf("Unsigned Short : %20d\tto\t%u\n", 0, max_val(sizeof(short) * 8));
  printf("Signed Long :    %20ld\tto\t%ld\n", min_val_signed(sizeof(long) * 8),
         max_val((sizeof(long) * 8) - 1));
  printf("Unsigned Long :  %20d\tto\t%lu\n", 0, max_val(sizeof(long) * 8));

  // MAX Floiting-Point
  printf("\nFloat :  %10g\tto\t%g\n", FLT_MIN, FLT_MAX);
  printf("Double : %10lg\tto\t%lg\n", DBL_MIN, DBL_MAX);
  return 0;
}
