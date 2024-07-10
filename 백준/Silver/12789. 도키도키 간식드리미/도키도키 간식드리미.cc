#include <iostream>
#include <stack>
#include <queue>
#include <deque>

using namespace std;

bool Check (queue<int>& space) {
    
    int increase = 0;
    while (!space.empty()) {
        
        int element = space.front();
        space.pop();
        
        if (increase > element) return false;
        //cout << element << " ";
        increase = element;
    }
    return true;
}

int main (int argc, char* argv[]) {
    
    int length = 0; // 1 3 2 4 5 6(Nice) | 5 1 3 4 2(Sad)
    cin >> length;
    
    deque<int> buffer;
    for (int index = 0; index < length; index++) {
        
        int element = 0;
        cin >> element;
        
        buffer.push_front(element);
    }
    
    queue<int> temp;
    stack<int> bucket;
    while (!buffer.empty()) {
        
        int first = buffer.back(); buffer.pop_back();           // 1 3 2 4 
        int second = buffer.empty() ? 0 : buffer.back();   // 3 2 4 5 
        
        if (first > second) {
            if (bucket.empty() || !bucket.empty() && bucket.top() > first) {
                
                bucket.push (first); // 5 4 
                continue;
            }
            else {
                
                buffer.push_back (first);
                bucket.pop();
                continue;
            }
        }
        else {
            if (bucket.empty() || bucket.top() > first) temp.push (first);
            else {
                
                bucket.pop();
                bucket.push(first);
            }
        }
    }
    
    while (!bucket.empty()) {
        
        temp.push (bucket.top());
        bucket.pop();
    }
    
    cout << (Check (temp) ? "Nice" : "Sad");
    return 0;
}
