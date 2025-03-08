#include <stdio.h>
#include <stdbool.h>

int Find (int* parent, int u);
bool Union (int* parent, int u, int v);

int main (int argc, char* argv[]) {
  
  int number = 0, count = 0;
  scanf ("%d%d", &number, &count);
  
  int parent[1000001] = { 0, };
  for (int index = 0; index <= number; index++) {
    
    parent[index] = -1;
  }
  
  for (int repeat = 0; repeat < count; repeat++) {
    
    int command = 0, u = 0, v = 0;
    scanf ("%d%d%d", &command, &u, &v);
    
    if (command == 0) {
      
      Union (parent, u, v);
    }
    else {
      
      u = Find (parent, u);
      v = Find (parent, v);
      printf ("%s\n", u == v ? "YES" : "NO");
    }
  }
  
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