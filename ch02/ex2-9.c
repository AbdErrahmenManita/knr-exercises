#include <stdio.h>

// x-1 gives us a new binary that have the rightmost 1 in x replaced by zero and
// if that one is preceeded by zeros those zeros turn to one for exemple x=
// 100101100 x-1 = 100101011 so basically it takes x and move replace any zero
// in x by 1 until it reaches the rightmost (first) 1 and change it into 0 then
// leave the rest after the rightmost 1 bit as it is
//
// now when we use & the x-1 act as a mask to x the first ones in x-1 let the
// first 0-bits of x stay as they are (a&1 == a) then when it arrives to the
// first zero in x-1 a.k.a the first 1 in x that 0 serve to change that
// rightmost 1-bit in x into 0 and the rest stay as it
//
//
//
//
//
//
int bitcount(unsigned x) {
  int counter = 0;
  while (x != 0) {
    x &= x - 1;
    counter++;
  }
  return counter;
}
int main() { return 0; }
