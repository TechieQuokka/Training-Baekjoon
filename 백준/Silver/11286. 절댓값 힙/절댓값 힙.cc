#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct compare {
    
    bool operator() (int element1, int element2) {
        
        if (abs (element1) == abs (element2)) {
            
            return element1 > element2;
        }
        else return abs (element1) > abs (element2);
    }
};

int main (int argc, char* argv[]) {
    
    priority_queue<int, vector<int>, compare> heap;
    
    int count = 0;
    cin >> count;
    
    for (int loop = 0; loop < count; loop++) {
        
        int data = 0;
        cin >> data;
        
        if (data == 0) {
            if (heap.empty()) {
                
                cout << "0\n";
                continue;
            }
            int element = heap.top();
            heap.pop();
            cout << "" << element << "\n";
        }
        else heap.push (data);
    }
    
    return 0;
}
