#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution (vector<int>& card, int length);

int main (int argc, char* argv[]) {
  
  int testcase = 0;
  cin >> testcase;
  
  for (int repeat = 0; repeat < testcase; repeat++) {
    
    int length = 0;
    scanf ("%d", &length);
    
    vector <int> card (length);
    for (int index = 0; index < length; index++) {
      
      scanf ("%d", &card[index]);
    }
    
    printf ("%d\n", solution (card, length));
  }
  return 0;
}

int solution (vector<int>& card, int length) {
  
  int total = 0;
  for (int index = 0; index < length; index++) {
    
    total += card[index];
  }
  
  vector<vector<int>> table (length, vector<int> (length, 0));
  
  for (int size = 1; size <= length; size++) {
    for (int row = 0; row <= length - size; row++) {
      
      int column = row + size - 1;
      if (size == 1) {
        
        table[row][column] = card[row];
        continue;
      }
      
      table[row][column] = max (card[row] - table[row + 1][column], card[column] - table[row][column - 1]);
    }
  }
  
  return (total + table[0][length - 1]) / 2;
}