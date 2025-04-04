#include <iostream>
#include <vector>

using namespace std;

#define SIZE 20
#define INF 1e9

int Solution (int works[SIZE][SIZE], int size, int worker, unsigned mask);

int main (int argc, char* argv[]) {
  
  int number = 0;
  cin >> number;
  
  int works[SIZE][SIZE] = { 0, };
  
  for (int row = 0; row < number; row++) {
    for (int column = 0; column < number; column++) {
      
      cin >> works[row][column];
    }
  }
  
  cout << Solution (works, number, 0, 0);
  
  return 0;
}

int min (int left, int right) {
  
  return left < right ? left : right;
}

int Solution (int works[SIZE][SIZE], int size, int worker, unsigned mask) {
  
  static vector<vector<int>> table (SIZE, vector<int> (1 << SIZE, INF));
  if (worker == size) return 0;
  if (table[worker][mask] != INF) return table[worker][mask];
  
  int minimum = INF;
  for (unsigned task = 0; task < size; task++) {
    if (mask & (1 << task)) continue;
    
    minimum = min (minimum, works[worker][task] + Solution (works, size, worker + 1, mask | (1 << task)));
  }
  
  return table[worker][mask] = minimum;
}