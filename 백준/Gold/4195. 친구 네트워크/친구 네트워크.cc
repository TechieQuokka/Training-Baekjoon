#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int Find (int* parent, int u);
bool Union (int* parent, int* counter, int u, int v);

void Initialize (int* parent, int length, int data) {
  
  for (int index = 0; index < length; index++) {
    
    parent[index] = data;
  }
  return;
}

int Max (int left, int right) {
  
  return left < right ? right : left;
}

void Display (int* source, int length) {
  
  cout << "[ ";
  for (int index = 0; index < length; index++) {
    
    cout << source[index] << "  ";
  }
  cout << "]" << endl;
  return;
}

int main (int argc, char* argv[]) {
  
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int testcase = 0;
  cin >> testcase;
  
  int parent[200002] = { 0, };
  int counter[200002] = { 0, };
  
  for (int repeat = 0; repeat < testcase; repeat++) {
    
    map<string, int> friends;
    
    int numberOf = 0, label = 0;
    cin >> numberOf;
    
    Initialize (parent, 200002, -1);
    Initialize (counter, 200002, 1);
    
    for (int index = 0; index < numberOf; index++) {
      
      string identity[2];
      cin >> identity[0] >> identity[1];
      
      if (friends.find(identity[0]) == friends.end()) {
        
        friends[identity[0]] = label++;
      }
      if (friends.find(identity[1]) == friends.end()) {
        
        friends[identity[1]] = label++;
      }
      
      int u = friends[identity[0]];
      int v = friends[identity[1]];
      
      Union (parent, counter, u, v);
      
      int parent_u = Find (parent, u);
      int parent_v = Find (parent, v);
      
      printf ("%d\n", Max (counter[parent_u], counter[parent_v]));
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

bool Union (int* parent, int* counter, int u, int v) {
  
  u = Find (parent, u);
  v = Find (parent, v);
  
  if (u == v) return false;
  if (parent[u] > parent[v]) Swap (&u, &v);
  if (parent[u] == parent[v]) parent[u]--;
  
  counter[u] += counter[v];
  parent[v] = u;
  return true;
}