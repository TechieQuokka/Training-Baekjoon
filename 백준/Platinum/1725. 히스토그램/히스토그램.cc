#include <iostream>
#include <stack>

using namespace std;

long long CalculateMaxArea (int* histogram, int length);

int main (int argc, char* argv[]) {
    
    int histogram[100010] = { 0, };  
    
    int length = 0;
    cin >> length;

    for (int index = 0; index < length; index++) {

        cin >> histogram[index];
    }
    
    long long result = CalculateMaxArea (histogram, length);
    cout << result << "\n";
    
    return 0;
}

long long MaxArea (int* histogram, stack<int>& position, int pivot, bool (&compare) (int*, stack<int>&, int)) {
    
    long long largestArea = 0;
    while (compare (histogram, position, pivot)) {
        
        int height = histogram[position.top()]; position.pop();
        int width = position.empty() ? pivot : pivot - 1 - position.top();
        largestArea = max (largestArea, (long long)width * height);
    }
    return largestArea;
}

bool full (int* histogram, stack<int>& position, int pivot) {
    
    return !position.empty() && histogram[position.top()] >= histogram[pivot];
}

bool remain (int* histogram, stack<int>& position, int pivot) {
    
    return !position.empty();
}

long long CalculateMaxArea (int* histogram, int length) {
    
    if (histogram == NULL) throw histogram;
    
    stack<int> position;
    
    long long largestArea = 0;
    int index = 0;
    for (index = 0; index < length; index++) {
        
        largestArea = max (largestArea, MaxArea (histogram, position, index, full));
        position.push (index);
    }
    return max (largestArea, MaxArea (histogram, position, index, remain));
}
