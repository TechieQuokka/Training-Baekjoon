#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

int Find (int* parent, int u);
bool Union (int* parent, int u, int v);

void Initialize (int* parent, int length) {
  
  for (int index = 0; index < length; index++) {
    
    parent[index] = -1;
  }
  return;
}

int main (int argc, char* argv[]) {
  
  int city = 0;
  scanf ("%d", &city);
  
  int count = 0;
  scanf ("%d", &count);
  
  int parent[2000001] = { 0, };
  Initialize (parent, city);
  
  for (int row = 0; row < city; row++) {
    for (int column = 0; column < city; column++) {
      
      int data = 0;
      scanf ("%d", &data);
      if (data == 1) {
        
        Union (parent, row, column);
      }
    }
  }
  
  int* result = (int*) calloc (count, sizeof (int));
  for (int index = 0; index < count; index++) {
    
    int data = 0;
    scanf ("%d", &data);
    result[index] = Find(parent, data - 1);
  }
  
  int pivot = result[0];
  for (int index = 1; index < count; index++) {
    if (result[index] != pivot) {
      
      printf ("NO");
      return 0;
    }
  }
  printf ("YES");
  return 0;
}


int Find (int* parent, int u) {
  
  if (parent[u] < 0) return u;
  return parent[u] = Find (parent, parent[u]);
}

void Swap (int* left, int* right) {
  
  int temp = *left;
  *left = *right;
  *right = temp;
  return;
}

bool Union (int* parent, int u, int v) {
  
  u = Find (parent, u);
  v = Find (parent, v);
  
  if (u == v) return false;
  if (parent[u] > parent[v]) Swap (&u, &v);
  if (parent[u] == parent[v]) parent[u]--;
  
  parent[v] = u;
  return true;
}