#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[]) {
  
  int length = 0;
  scanf ("%d", &length);
  
  int previous = 0;
  scanf ("%d", &previous);
  
  int count = 0;
  for (int index = 1; index < length; index++) {
    
    int current = 0;
    scanf ("%d", &current);
    
    int minus = log2(current);
    int exponent = ceil(log2(previous));
    exponent -= minus;
    
    if (exponent < 0) {
      
      previous = current;
      continue;
    }
    
    previous = current * pow(2, exponent);
    count += exponent;
  }
  
  printf ("%d", count);
  
  return 0;
}