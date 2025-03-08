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

double MST_Kruskal (vector<struct NodeType>& graph, int vertex);

int main (int argc, char* argv[]) {
  
  int count = 0;
  scanf ("%d", &count);
  
  vector<struct CoordinateType> buffer;
  for (int index = 0; index < count; index++) {
    
    double x = 0, y = 0;
    scanf ("%lf%lf", &x, &y);
    
    buffer.push_back ({x, y});
  }
  
  vector<struct NodeType> graph;
  
  for (int row = 0; row < count; row++) {
    for (int column = row + 1; column < count; column++) {
      
      double x1 = buffer[row].x, y1 = buffer[row].y;
      double x2 = buffer[column].x, y2 = buffer[column].y;
      double distance = sqrt(pow (x2 - x1, 2.0) + pow (y2 - y1, 2.0));
      
      graph.push_back ({row, column, distance});
    }
  }
  
  double result = MST_Kruskal (graph, count);
  printf ("%.2lf\n", result);
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

double MST_Kruskal (vector<struct NodeType>& graph, int vertex) {
  
  int* parent = new int[vertex];
  Initialize (parent, vertex);
  
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