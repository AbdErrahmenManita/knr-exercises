#include <stdio.h>
int binsearch(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (high > low) {
    mid = (high + low) / 2;
    if (x > v[mid])
      low = mid + 1;
    else
      high = mid;
  }
  if (v[low] == x)
    return low;
  return -1;
}
int main() {
  int v[100000];
  for (int i = 0; i < 100000; i++) {
    v[i] = i;
  }
  printf("V filled successfully\n");
  int pos = binsearch(14, v, 20);
  printf("%d\n", pos);
}
