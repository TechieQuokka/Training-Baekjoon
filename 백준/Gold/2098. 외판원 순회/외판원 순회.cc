#include <iostream>
#include <vector>

#define INF 987654321

using namespace std;

int TravelingSalesmanProblem (vector<vector<int>>& graph, int pivot, int visit, int vertex);

int main (int argc, char* argv[]) {
  
  ios_base :: sync_with_stdio(false); 
  cin.tie(NULL); 
  cout.tie(NULL);
    
  int vertex = 0;
  cin >> vertex;
  
  vector<vector<int>> graph (vertex, vector<int> (vertex, 0));
  
  for (int row = 0; row < vertex; row++) {
    for (int column = 0; column < vertex; column++) {
      
      int weight = 0;
      cin >> weight;
      
      graph[row][column] = weight;
    }
  }
  
  cout << TravelingSalesmanProblem (graph, 0, 1, vertex);
  return 0;
}

int TravelingSalesmanProblem (vector<vector<int>>& graph, int pivot, int visit, int vertex) {
  
  static vector<vector<int>> table (16, vector<int> (1 << 16, -1));
  
  if (visit == (1 << vertex) - 1) {
    
    if (graph[pivot][0] == 0) return INF;
    return graph[pivot][0];
  }
  
  if (table[pivot][visit] != -1) return table[pivot][visit];
  
  table[pivot][visit] = INF;
  
  for (int node = 0; node < vertex; node++) {
    if (graph[pivot][node] == 0) continue;
    
    int isVisit = 1 << node;
    if ((visit & isVisit) == isVisit) continue;
    
    table[pivot][visit] = min (table[pivot][visit], graph[pivot][node] + TravelingSalesmanProblem (graph, node, visit | isVisit, vertex));
  }
  
  return table[pivot][visit];
}