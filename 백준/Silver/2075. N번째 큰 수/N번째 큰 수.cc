#include <iostream>
#include <queue>

using namespace std;

int main (int argc, char* argv[]) {
  
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  priority_queue<int, vector<int>, greater<int>> heap;
  
  int number = 0;
  cin >> number;
  
  for (int index = 0; index < number; index++) {
    
    int data = 0;
    cin >> data;
    
    heap.push (data);
  }
  
  int size = number * number - number;
  for (int index = 0; index < size; index++) {
    
    int data = 0;
    cin >> data;
    
    heap.push (data);
    heap.pop();
  }
  
  cout << heap.top();
  return 0;
}