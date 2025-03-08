#include <iostream>
#include <vector>

using namespace std;

struct NodeType {
  
  vector<int> vertex;
  bool isVisited;
  bool check;
};

int CalculateMaxValue (vector<struct NodeType>& graph, const vector<int>& weights, int current, vector<pair<int, int>>& outTable);
void FindPath (vector<struct NodeType>& graph, vector<pair<int, int>>& table, int current, bool flag);
void ClearVisit (vector<struct NodeType>& graph);

int main (int argc, char* argv[]) {
  
  ios_base :: sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int vertex = 0;
  cin >> vertex;
  
  vector<int> weights (vertex, 1);
  
  vector<struct NodeType> graph (vertex);
  for (int index = 0; index < vertex - 1; index++) {
    
    int from = 0, to = 0;
    cin >> from >> to;
    
    graph[from - 1].vertex.push_back (to - 1);
    graph[to - 1].vertex.push_back (from - 1);
  }
  
  vector<pair<int, int>> table (vertex, {0, 0});
  int result = CalculateMaxValue (graph, weights, 0, table);
  cout << vertex - result << endl;
  return 0;
}

int CalculateMaxValue (vector<struct NodeType>& graph, const vector<int>& weights, int current, vector<pair<int, int>>& outTable) {

  if (graph[current].isVisited)
    return max (outTable[current].first, outTable[current].second);
    
  graph[current].isVisited = true;
  outTable[current].second = weights[current];
  
  for (const auto& child : graph[current].vertex) {
    if (graph[child].isVisited) continue;
    
    outTable[current].first += CalculateMaxValue (graph, weights, child, outTable);
    outTable[current].second += outTable[child].first;
  }
  
  return max (outTable[current].first, outTable[current].second);
}

void FindPath (vector<struct NodeType>& graph, vector<pair<int, int>>& table, int current, bool flag) {
  
  if (graph[current].isVisited) return;
  graph[current].isVisited = true;
  
  bool check = flag == false && table[current].first < table[current].second;
  
  graph[current].check = check;
  for (const auto& child : graph[current].vertex) {
    if (graph[child].isVisited) continue;
    
    FindPath (graph, table, child, check);
  }
  return;
}

void ClearVisit (vector<struct NodeType>& graph) {
  
  for (auto& element : graph) {
    
    element.isVisited = false;
  }
  return;
}