#include <stdio.h>

int Solution (int buffer[1024][1024], int number, int select);

int main (int argc, char* argv[]) {
  
  int number = 0, select = 0;
  scanf ("%d%d", &number, &select);
  
  int buffer[1024][1024];
  for (int row = 0; row < 1024; row++) {
    for (int column = 0; column < 1024; column++) {
      
      buffer[row][column] = -2147483648; // -inf
    }
  }
  
  int result = Solution (buffer, number, select);
  printf ("%d\n", result % 1000000003);
  return 0;
}

int Solution (int buffer[1024][1024], int number, int select) {
  
  if (select == 1) return number;
  if (number < 2 * select) return 0;
  if (select <= 0) return 0;
  
  if (buffer[number][select] >= 0) return buffer[number][select];
  
  return buffer[number][select] = (Solution (buffer, number - 1, select) + Solution (buffer, number - 2, select - 1)) % 1000000003;
}