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
  
  int number = 0, count = 0;
  scanf ("%d%d", &number, &count);
  
  int parent[1000001] = { 0, };
  Initialize (parent, number);
  
  for (int repeat = 1; repeat <= count; repeat++) {
    
    int u = 0, v = 0;
    scanf ("%d%d", &u, &v);
    
    int root_u = Find (parent, u);
    int root_v = Find (parent, v);
    if (root_u < 0) root_u = u;
    if (root_v < 0) root_v = v;
    
    if (root_v == root_u) {
      
      printf ("%d", repeat);
      return 0;
    }
    
    Union (parent, u, v);
  }
  
  printf ("0");
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