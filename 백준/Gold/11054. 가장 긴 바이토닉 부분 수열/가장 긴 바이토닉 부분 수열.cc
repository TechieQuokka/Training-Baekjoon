#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> Calculate (vector<int>& sequence, int count, bool (&compare) (const int, const int));
bool Increase (const int argument1, const int argument2) {
    
    return argument1 <= argument2;
}

bool Decrease (const int argument1, const int argument2) {
    
    return argument1 >= argument2;
}

int main (int argc, char* argv[]) {
    
    int count = 0;
    cin >> count;
    
    vector<int> sequence(count);
    for (int index = 0; index < count; index++) {
        
        cin >> sequence[index];
    }
    
    vector<int> ascending = Calculate (sequence, count, Increase);
    reverse(sequence.begin(), sequence.end());
    
    vector<int> decending = Calculate (sequence, count, Increase);
    reverse(decending.begin(), decending.end());
    
    int maximum = -9999999;
    for (int index = 0; index < count; index++) {
        
        int sum = ascending[index] + decending[index];
        if (maximum < sum) {
            
            maximum = sum;
        }
    }
    cout << maximum - 1;
    
    return 0;
}

vector<int> Calculate (vector<int>& sequence, int count, bool (&compare) (const int, const int)) {
    
    vector<int> result(count, 1);
    for (int index = 1; index < count; index++) {
        for (int pivot = index - 1; pivot >= 0; pivot--) {
            
            if (compare(sequence[index], sequence[pivot])) continue;
            result[index] = max(result[index], result[pivot] + 1);
        }
    }
    return result;
}
