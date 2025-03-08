#include <iostream>
#include <vector>

using namespace std;

int Calculate (int* sequence, int length);
int FindIndex (vector<int>& subStack, int value);

int main (int argc, char* argv[]) {
    
    int length = 0;
    cin >> length;
    
    int* sequence = new int[length];
    if (sequence == NULL) return -1;
    
    for (int index = 0; index < length; index++) {
        
        cin >> sequence[index];
    }
    
    int count = Calculate (sequence, length);
    cout << count;
    
    return 0;
}

int FindIndex (vector<int>& subStack, int value) {
    
    int start = 0, end = subStack.size() - 1;
    while (start <= end) {
        
        int middle = (start + end) / 2;
        int element = subStack[middle];
        
        if (element == value) return middle;
        else if (element < value) start = middle + 1;
        else end = middle - 1;
    }
    
    return end + 1;
}

int Calculate (int* sequence, int length) {
    
    if (sequence == NULL) return -1;
    
    vector<int> subStack;
    subStack.push_back (sequence[0]);
    
    for (int index = 1; index < length; index++) {
        
        int element = subStack.back();
        if (element < sequence[index]) subStack.push_back (sequence[index]);
        else {
            int result = FindIndex (subStack, sequence[index]);
            subStack[result] = sequence[index];
        }
    }
    return subStack.size();
}
