#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct NodeType {
  
  int from;
  int to;
  int weight;
};

int MST_Kruskal (vector<struct NodeType>& graph, int vertex);

int main (int argc, char* argv[]) {
  
  int testcase = 0;
  scanf ("%d", &testcase);
  for (int repeat = 0; repeat < testcase; repeat++) {
    
    vector<struct NodeType> graph;
    
    int vertex = 0, edge = 0;
    scanf ("%d%d", &vertex, &edge);
    
    for (int index = 0; index < edge; index++) {
      
      int from = 0, to = 0;
      scanf ("%d%d", &from, &to);
      graph.push_back ({from - 1, to - 1, 1});
    }
    
    int result = MST_Kruskal (graph, vertex);
    printf ("%d\n", result);
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

void Initialize (int* source, int length) {
  
  for (int index = 0; index < length; index++) {
    
    source[index] = -1;
  }
  return;
}

bool ascending (const struct NodeType& left, const struct NodeType& right) {
  
  return left.weight < right.weight;
}

int MST_Kruskal (vector<struct NodeType>& graph, int vertex) {
  
  int* parent = new int[vertex];
  Initialize (parent, vertex);
  
  sort (graph.begin(), graph.end(), &ascending);
  
  int result = 0;
  for (const struct NodeType& element : graph) {
    
    int u = element.from;
    int v = element.to;
    if (Find (parent, u) != Find (parent, v)) {
      
      Union (parent, u, v);
      result += element.weight;
    }
  }
  return result;
}