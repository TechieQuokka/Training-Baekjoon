#include <iostream>
#include <vector>

using namespace std;

void Display (vector<int>& source) {
  
  cout << source.size() << endl;
  for (const auto& element : source) {
    
    cout << element << ' ';
  }
  cout << endl;
  return;
}

int main (int argc, char* argv[]) {
  
  int number = 0;
  cin >> number;
  
  vector<int> 세림, 성주;
  while (number - 2 > 0) {
    
    세림.push_back(number);
    성주.push_back(number - 1);
    성주.push_back(number - 2);
    number -= 3;
  }
  if (number == 2) {
    
    세림.push_back (2);
    성주.push_back (1);
  }
  
  Display (세림);
  Display (성주);
  
  return 0;
}