#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[]) {
  
  int length = 0;
  scanf ("%d", &length);
  
  long long* buffer = (long long*) calloc (length, sizeof (long long));
  for (int index = 0; index < length; index++) {
    
    scanf ("%lld", buffer + index);
  }
  
  long long* counter = (long long*) calloc (length, sizeof (long long));
  long long result = 0;
  
  for (int index = 1; index < length; index++) {
    
    long long calculate = ceil(log2((double)buffer[index - 1] / buffer[index])) + counter[index - 1];
    if (calculate > 0) {
      
      counter[index] = calculate;
      result += calculate;
    }
  }
  
  printf ("%lld\n", result);
  
  free ((long long*) counter);
  free ((long long*) buffer);
  return 0;
}