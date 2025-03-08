#include <iostream>
#include <vector>

using namespace std;

struct NodeType {
  
  vector<int> vertex;
  bool isVisited;
  int numberOfChild;
};

int DepthFirstSearch (vector<struct NodeType>& graph, int current);

int main (int argc, char* argv[]) {
  
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  
  int vertex = 0, root = 0, count = 0;
  cin >> vertex >> root >> count;
  
  vector<struct NodeType> graph (vertex);
  for (int index = 0; index < vertex - 1; index++) {
    
    int from = 0, to = 0;
    cin >> from >> to;
    
    graph[from - 1].vertex.push_back (to - 1);
    graph[to - 1].vertex.push_back (from - 1);
    
    graph[from - 1].isVisited = graph[to - 1].isVisited = false;
    graph[from - 1].numberOfChild = graph[to - 1].numberOfChild = 0;
  }
  
  graph[root - 1].numberOfChild = DepthFirstSearch (graph, root - 1);
  
  for (int index = 0; index < count; index++) {
    
    int query = 0;
    cin >> query;
    cout << graph[query - 1].numberOfChild << "\n";
  }
  return 0;
}

int DepthFirstSearch (vector<struct NodeType>& graph, int current) {
  
  if (graph[current].isVisited) return 0;
  
  graph[current].isVisited = true;
  
  int numberOfChild = 1;
  for (const int& element : graph[current].vertex) {
    
    numberOfChild += DepthFirstSearch (graph, element);
  }
  
  return graph[current].numberOfChild = numberOfChild;
}