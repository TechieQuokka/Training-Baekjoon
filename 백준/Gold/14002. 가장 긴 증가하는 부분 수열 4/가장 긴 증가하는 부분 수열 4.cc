#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> Calculate (int* sequence, int length);

int main (int argc, char* argv[]) {
    
    int length = 0;
    cin >> length;
    
    int* sequence = new int[length];
    if (sequence == NULL) return -1;
    
    for (int index = 0; index < length; index++) {
        
        cin >> sequence[index];
    }
    
    auto result = Calculate (sequence, length);
    cout << result.size() << "\n";
    for (auto iterate = result.end() - 1; iterate != result.begin() - 1; iterate--) {
        
        cout << *iterate << " ";
    }
    
    return 0;
}

vector<int> Calculate (int* sequence, int length) {
    
    if (sequence == NULL) throw;
    
    int maximum = INT_MIN, current = 0;
    vector<int> buffer(length);
    for (int index = 1; index < length; index++) {
        for (int pivot = index - 1; pivot >= 0; pivot--) {
            
            if (sequence[index] > sequence[pivot]) buffer[index] = max (buffer[index], buffer[pivot] + 1);
        }
        if (maximum < buffer[index]) {
            
            maximum = buffer[index];
            current = index;
        }
    }
    
    int previous = buffer[current];
    vector<int> subStack;
    subStack.push_back (sequence[current]);
    for (int index = current - 1; index >= 0; index--) {
        
        if (buffer[index] == previous - 1) {
            
            subStack.push_back(sequence[index]);
            previous = buffer[index];
        }
    }
    
    return subStack;
}
