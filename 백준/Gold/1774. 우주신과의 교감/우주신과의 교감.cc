#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct NodeType {
  
  int from;
  int to;
  double weight;
};

struct CoordinateType {
  
  double x, y;
};

double MST_Kruskal (vector<struct NodeType>& graph, int* parent);
bool Union (int* parent, int u, int v);
void Initialize (int* source, int length);

int main (int argc, char* argv[]) {
  
  int vertex = 0, numberOf = 0;
  cin >> vertex >> numberOf;
  
  vector<struct CoordinateType> buffer;
  for (int index = 0; index < vertex; index++) {
    
    double v = 0, u = 0;
    cin >> v >> u;
    
    buffer.push_back ({v, u});
  }
  
  vector<struct NodeType> graph;
  
  for (int row = 0; row < vertex; row++) {
    for (int column = 0; column < vertex; column++) {
      
      double x1 = buffer[row].x, y1 = buffer[row].y;
      double x2 = buffer[column].x, y2 = buffer[column].y;
      double distance = sqrt(pow (x2 - x1, 2.0) + pow (y2 - y1, 2.0));
      
      graph.push_back ({row, column, distance});
    }
  }
  
  int* parent = new int[vertex];
  Initialize (parent, vertex);
  
  for (int index = 0; index < numberOf; index++) {
    
    int u = 0, v = 0;
    cin >> u >> v;
    Union (parent, u - 1, v - 1);
  }
  
  double result = MST_Kruskal (graph, parent);
  printf ("%.2lf", result);
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

double MST_Kruskal (vector<struct NodeType>& graph, int* parent) {
  
  sort (graph.begin(), graph.end(), &ascending);
  
  double result = 0;
  for (const struct NodeType& element : graph) {
    
    int u = element.from;
    int v = element.to;
    if (Find (parent, u) != Find (parent, v)) {
      
      Union (parent, u, v);
      result += element.weight;
    }
  }
  delete[] parent;
  return result;
}