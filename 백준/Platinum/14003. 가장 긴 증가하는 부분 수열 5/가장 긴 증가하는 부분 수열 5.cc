
#include <iostream>
#include <vector>

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
    for (int index = result.size() - 1; index >= 0; index--) {
        
        cout << result[index] << " ";
    }
    
    return 0;
}

int FindIndex (vector<int>& buffer, int target) {
    
    int start = 0, end = buffer.size() - 1;
    
    while (start <= end) {
        
        int middle = (start + end) / 2;
        if (buffer[middle] == target) return middle;
        else if (buffer[middle] < target) start = middle + 1;
        else end = middle - 1;
    }
    
    return end + 1;
}

vector<int> Calculate (int* sequence, int length) {
    
    if (sequence == NULL) throw;
    
    vector<int> buffer;
    vector<pair<int, int>> record;
    
    buffer.push_back (sequence[0]);
    record.push_back ({sequence[0], 0});
    for (int index = 1; index < length; index++) {
        
        int element = buffer.back();
        if (element < sequence[index]) {
            
            buffer.push_back (sequence[index]);
            record.push_back ({sequence[index], buffer.size() - 1});
        }
        else {
            
            int position = FindIndex (buffer, sequence[index]);
            buffer[position] = sequence[index];
            record.push_back ({sequence[index], position});
        }
    }
    
    vector<int> result; int pivot = buffer.size() - 1;
    for (int index = length - 1; index >= 0; index--) {
        
        auto element = record[index];
        if (element.second == pivot) {
            
            result.push_back (element.first);
            pivot--;
        }
    }
    
    return result;
}
