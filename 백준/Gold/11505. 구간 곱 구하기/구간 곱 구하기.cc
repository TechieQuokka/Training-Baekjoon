#include <iostream>
#include <vector>

using namespace std;

enum Option { UPDATE = 1, SUM = 2 };

template <typename T>
struct ElementType {
    
    int Level;
    T Value;
};

template <typename T>
struct SegmentTreeType {
    
    vector<struct ElementType<T>> Element;
    int Length;
    T DefaultValue;
    T (*Merge) (const T, const T);
    
    void Create (const int length, const T defaultValue, T (*Merge) (const T, const T)) {
        
        if (length < 1) throw length;
        if (Merge == NULL) throw Merge;
        
        this->Element.resize(length * 4);
        this->Length = length;
        this->Merge = Merge;
        this->DefaultValue = defaultValue;
        return;
    }
    
    T BuildRecursive (const T* source, int position, int leftIndex, int rightIndex, int level) {
        
        if (leftIndex == rightIndex) {
            
            this->Element[position].Level = level;
            return this->Element[position].Value = source[leftIndex];
        }
        
        int middle = leftIndex + (rightIndex - leftIndex) / 2;
        T left = this->BuildRecursive (source, position * 2, leftIndex, middle, level + 1);
        T right = this->BuildRecursive (source, position * 2 + 1, middle + 1, rightIndex, level + 1);
        
        this->Element[position].Level = level;
        return this->Element[position].Value = this->Merge (left, right);
    }
    
    void Build (T* source) {
        
        this->BuildRecursive (source, 1, 0, this->Length - 1, 0);
        return;
    }
    
    T QueryRecursive (int left, int right, int position, int leftIndex, int rightIndex) {
        
        if (left > rightIndex || right < leftIndex) return this->DefaultValue;
        if (left <= leftIndex && right >= rightIndex) return this->Element[position].Value;
        
        int middle = leftIndex + (rightIndex - leftIndex) / 2;
        T leftValue = this->QueryRecursive (left, right, position * 2, leftIndex, middle);
        T rightValue = this->QueryRecursive (left, right, position * 2 + 1, middle + 1, rightIndex);
        
        return this->Merge (leftValue, rightValue);
    }
    
    T Query (int left, int right) {
        
        return this->QueryRecursive (left, right, 1, 0, this->Length - 1);
    }
    
    T UpdateRecursive (T& value, int index, int position, int leftIndex, int rightIndex) {
        
        if (index < leftIndex || index > rightIndex) return this->Element[position].Value;
        if (leftIndex == rightIndex) return this->Element[position].Value = value;
        
        int middle = leftIndex + (rightIndex - leftIndex) / 2;
        T left = this->UpdateRecursive (value, index, position * 2, leftIndex, middle);
        T right = this->UpdateRecursive (value, index, position * 2 + 1, middle + 1, rightIndex);
        return this->Element[position].Value = this->Merge (left, right);
    }
    
    T Update (int index, T value) {
        
        return this->UpdateRecursive (value, index, 1, 0, this->Length - 1);
    }
};

long long int Multiple (const long long int left, const long long int right) {
    
    return (left * right) % 1000000007;
}

int main (int argc, char* argv[]) {
    
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    int length = 0, numberOfUpdate = 2, numberOfSum = 2;
    cin >> length >> numberOfUpdate >> numberOfSum;
    
    long long int* source = new long long int[length];
    for (long long int index = 0; index < length; index++) {
        
        long long int element = 0;
        cin >> element;
        source[index] = element;
    }
    
    struct SegmentTreeType<long long int> tree;
    tree.Create(length, 1, &Multiple);
    tree.Build (source);
    
    int count = numberOfUpdate + numberOfSum;
    for (long long int loop = 0; loop < count; loop++) {
        
        long long int option = 0, from = 0, to = 0;
        cin >> option >> from >> to;
        if (option == UPDATE) {
            
            tree.Update (from - 1, to);
        }
        else {
            
            long long int value = tree.Query (from - 1, to - 1);
            cout << value << "\n";
        }
    }
    
    delete[] source;
    return 0;
}
