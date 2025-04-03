#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

long long int solution (vector<pair<long long int, long long int>>& jewel, vector<long long int>& bag);

int main (int argc, char* argv[]) {
  
  vector<pair<long long int, long long int>> jewel;
  vector<long long int> bag;
  
  long long int jewelSize = 0, bagSize = 0;
  scanf ("%lld%lld", &jewelSize, &bagSize);
  
  for (long long int index = 0; index < jewelSize; index++) {
    
    long long int weight = 0;
    long long int value = 0;
    scanf ("%lld%lld", &weight, &value);
    
    jewel.push_back ({weight, value});
  }
  
  for (long long int index = 0; index < bagSize; index++) {
    
    long long int capacity = 0;
    scanf ("%lld", &capacity);
    
    bag.push_back(capacity);
  }
  
  sort (jewel.begin(), jewel.end());
  sort(bag.begin(), bag.end());
  
  printf ("%lld", solution (jewel, bag));
  return 0;
}

long long int solution (vector<pair<long long int, long long int>>& jewel, vector<long long int>& bag) {
  
  long long int total = 0, position = 0;
  
  priority_queue<long long> buffer;
  for (int index = 0; index < bag.size(); index++) {
    
    long long int capacity = bag[index];
    while (position < jewel.size() && jewel[position].first <= capacity) {
      
      buffer.push (jewel[position].second);
      position++;
    }
    
    if (!buffer.empty()) {
      
      total += buffer.top();
      buffer.pop();
    }
  }
  return total;
}