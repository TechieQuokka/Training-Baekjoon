#include <stdio.h>
#include <malloc.h>

void Swap (int* left, int* right) {
  
  int temp = *left;
  *left = *right;
  *right = temp;
  return;
}

int main (int argc, char* argv[]) {
  
  int number = 0, pivot = 0;
  scanf ("%d%d", &number, &pivot);
  
  if (number == 1) {
    if (pivot == 0) printf ("1");
    else printf ("Impossible");
    return 0;
  }
  
  if (number == pivot) {
    
    printf ("Impossible");
    return 0;
  }
  
  int* array = (int*) malloc (number * sizeof (int));
  if (array == NULL) return -1;
  
  for (int index = 0; index < number; index++) {
    
    array[index] = index + 1;
  }
  
  int count = number - 1 - pivot;
  for (int index = 1; index < count + 1; index++) {
    
    Swap (array + 0, array + index);
  }
  
  for (int index = 0; index < number; index++) {
    
    printf ("%d ", array[index]);
  }
  
  free (array);
  return 0;
}