#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Labeling (vector<vector<int>>& source, int width, int height);
vector<struct CoordinateListType> CollectCoordinate (vector<vector<int>>& source, int width, int height, int numberOfLabel);
int IslandDistanceCalculator (int from, int to, vector<vector<int>>& island, int width, int height, vector<struct CoordinateListType>& data);
int MST_Kruskal (vector<struct NodeType>& graph, int vertex);
bool CheckIsland (vector<struct NodeType>& graph, int vertex);
void Display (vector<vector<int>>& source, int width, int height) {
  
  for (int row = 0; row < width; row++) {
    for (int column = 0; column < height; column++) {
      
      printf ("%d  ", source[row][column]);
    }
    printf ("\n");
  }
  return;
}

struct NodeType {
  
  int from;
  int to;
  int weight;
};

struct CoordinateType {
  
  int x, y;
};

struct CoordinateListType {
  
  vector<struct CoordinateType> Coordinates;
};

int main (int argc, char* argv[]) {
  
  int width = 0, height = 0;
  cin >> width >> height;
  
  vector<vector<int>> island (width, vector<int> (height, 0));
  
  for (int row = 0; row < width; row++) {
    for (int column = 0; column < height; column++) {
      
      int element = 0;
      cin >> element;
      
      island[row][column] = element != 0 ? -1 : 0;
    }
  }
  
  int label = Labeling (island, width, height);
  // Display (island, width, height);
  
  vector<struct NodeType> graph;
  
  vector<struct CoordinateListType> data = CollectCoordinate (island, width, height, label);
  for (int from = 0; from < label; from++) {
    for (int to = from + 1; to < label; to++) {

      int distance = IslandDistanceCalculator (from, to, island, width, height, data);
      if (distance == -1) continue;
      
      // printf ("%d -> %d : %d\n", from + 1, to + 1, distance);
      graph.push_back ({from, to, distance});
    }
  }
  
  int result = MST_Kruskal (graph, label);
  if (result == 0 || !CheckIsland (graph, label)) cout << -1;
  else cout << result;
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

bool CheckIsland (vector<struct NodeType>& graph, int vertex) {
  
  int* parent = new int[vertex];
  Initialize (parent, vertex);
  
  for (const auto& element : graph) {
    
    Union (parent, element.from, element.to);
  }
  
  int count = 0;
  for (int index = 0; index < vertex; index++) {
    
    count += parent[index] < 0;
  }
  return count == 1;
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
  
  delete[] parent;
  return result;
}

int Absolute (int value) {
  
  if (value >= 0) return value;
  return -value;
}

bool CrossPointWidthChecker (vector<vector<int>>& island, int x, int y, int to, int length) {
  
  int number = 0;
  for (int index = y; index < length; index++, number++) {
    
    int element = island[x][index];
    if (element == 0) continue;
    else if (element != to) return false;
    else return number > 1;
  }
  return false;
}

bool CrossPointHeightChecker (vector<vector<int>>& island, int x, int y, int to, int length) {
  
  int number = 0;
  for (int index = x; index < length; index++, number++) {
    
    int element = island[index][y];
    if (element == 0) continue;
    else if (element != to) return false;
    else return number > 1;
  }
  return false;
}

int IslandDistanceCalculator (int from, int to, vector<vector<int>>& island, int width, int height, vector<struct CoordinateListType>& data) {
  
  int minimum = 2147483647;
  for (const auto& leftIsland : data[from].Coordinates) {
    for (const auto& rightIsland : data[to].Coordinates) {
      
      int leftX = leftIsland.x, rightX = rightIsland.x;
      int leftY = leftIsland.y, rightY = rightIsland.y;
      bool result = false;
      
      if (leftX == rightX) { // width check
        if (leftY < rightY) result = CrossPointWidthChecker (island, leftX, leftY + 1, to + 1, height);
        else                result = CrossPointWidthChecker (island, rightX, rightY + 1, from + 1, height);
        
        int distance = Absolute (leftY - rightY);
        if (result && minimum > distance) {
          
          minimum = distance;
        }
      }
      
      if (leftY == rightY) { // height check
        if (leftX < rightX) result = CrossPointHeightChecker (island, leftX + 1, leftY, to + 1, width);
        else                result = CrossPointHeightChecker (island, rightX + 1, rightY, from + 1, width);
        
        int distance = Absolute (leftX - rightX);
        if (result && minimum > distance) {
          
          minimum = distance;
        }
      }
    }
  }
  
  if (minimum == 2147483647) return -1;
  else return minimum - 1;
}

vector<struct CoordinateListType> CollectCoordinate (vector<vector<int>>& source, int width, int height, int numberOfLabel) {
  
  vector<struct CoordinateListType> buffer (numberOfLabel);
  for (int row = 0; row < width; row++) {
    for (int column = 0; column < height; column++) {
      if (source[row][column] == 0) continue;
      
      buffer[source[row][column] - 1].Coordinates.push_back ({row, column});
    }
  }
  
  return buffer;
}

void LabelingRecursive (vector<vector<int>>& source, int x, int y, int width, int height, int label) {
  
  if (x < 0 || y < 0 || x >= width || y >= height) return;
  if (source[x][y] != -1) return;
  
  source[x][y] = label;
  
  LabelingRecursive (source, x + 1, y, width, height, label);
  LabelingRecursive (source, x - 1, y, width, height, label);
  LabelingRecursive (source, x, y + 1, width, height, label);
  LabelingRecursive (source, x, y - 1, width, height, label);
  return;
}

int Labeling (vector<vector<int>>& source, int width, int height) {
  
  int label = 1;
  for (int row = 0; row < width; row++) {
    for (int column = 0; column < height; column++) {
      if (source[row][column] == -1) {
        
        LabelingRecursive (source, row, column, width, height, label++);
      }
    }
  }
  return label - 1;
}