#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

class MedianHeap {
private:
  priority_queue<int> MaxHeap;
  priority_queue<int, vector<int>, greater<int>> MinHeap;
  int Size = 0;
  
  bool IsEmpty (void) {
    
    return this->Size == 0;
  }
  
public:
  void Insert (int data) {
    
    priority_queue<int>& maxHeap = this->MaxHeap;
    priority_queue<int, vector<int>, greater<int>>& minHeap = this->MinHeap;
    
    if (maxHeap.size() == minHeap.size()) maxHeap.push (data);
    else minHeap.push (data);
    
    int& size = this->Size;
    if (size > 1 && maxHeap.top() > minHeap.top()) {
      
      int temp = maxHeap.top(); maxHeap.pop();
      maxHeap.push (minHeap.top()); minHeap.pop();
      minHeap.push (temp);
    }
    
    size++;
    return;
  }
  
  bool Remove (void) {
    
    if (this->IsEmpty()) return false;
    
    priority_queue<int>& maxHeap = this->MaxHeap;
    priority_queue<int, vector<int>, greater<int>>& minHeap = this->MinHeap;
    
    int& size = this->Size;
    if (size % 2 == 0) minHeap.pop();
    else maxHeap.pop();
    
    if (size > 1 && maxHeap.top() > minHeap.top()) {
      
      int temp = maxHeap.top(); maxHeap.pop();
      maxHeap.push (minHeap.top()); minHeap.pop();
      minHeap.push (temp);
    }
    
    size--;
    return true;
  }
  
  double FindMedian (void) {
    
    if (this->Size % 2 == 0) {
      
      return ((double) this->MaxHeap.top() + (double) this->MinHeap.top()) / 2.0;
    }
    else return this->MaxHeap.top();
  }
};

int main (int argc, char* argv[]) {
  
  int testcase = 0;
  scanf ("%d", &testcase);
  
  for (int repeat = 0; repeat < testcase; repeat++) {
    
    int length = 0;
    scanf ("%d", &length);
    printf ("%d\n", (int)ceil(length / 2.0));
    
    class MedianHeap heap;
    for (int index = 1; index < length + 1; index++) {
      
      int data = 0;
      scanf ("%d", &data);
      heap.Insert (data);
      if (index % 2 == 1) printf ("%d ", (int)heap.FindMedian());
      if (index % 20 == 0) printf ("\n");
    }
    printf ("\n");
  }
  return 0;
}