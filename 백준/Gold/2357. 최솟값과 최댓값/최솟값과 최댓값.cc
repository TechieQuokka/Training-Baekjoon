#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

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
        struct ElementType<T> element = { -1, defaultValue };
        fill (this->Element.begin(), this->Element.end(), element);
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

struct MinMaxType {
    
    long long int minimum;
    long long int maximum;
};

struct MinMaxType Compare (const struct MinMaxType left, const struct MinMaxType right) {
    
    static struct MinMaxType minMax = { 0, };
    minMax.maximum = left.maximum > right.maximum ? left.maximum : right.maximum;
    minMax.minimum = left.minimum > right.minimum ? right.minimum : left.minimum;
    return minMax;
}

void PrintVector (vector<struct ElementType<struct MinMaxType>>& source) {
    
    for (auto iterate = source.begin(); iterate != source.end(); iterate++) {
        
        cout << (*iterate).Value.minimum << " ";
    }
    cout << endl;
    return;
}

int main (int argc, char* argv[]) {
    
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    struct MinMaxType defaultValue = { LLONG_MAX, LLONG_MIN };
    
    int length = 10, numberOfCompare = 4;
    cin >> length >> numberOfCompare;
    
    struct MinMaxType* source = new struct MinMaxType[length];
    for (int index = 0; index < length; index++) {
        
        long long int value = 0LL;
        cin >> value;
        source[index].maximum = source[index].minimum = value;
    }
    
    struct SegmentTreeType<struct MinMaxType> tree;
    tree.Create (length, defaultValue, &Compare);
    tree.Build (source);
    
    for (int loop = 0; loop < numberOfCompare; loop++) {
        
        int from = 0, to = 0;
        cin >> from >> to;
        
        struct MinMaxType result = tree.Query (from - 1, to - 1);
        cout << result.minimum << " " << result.maximum << "\n";
        //cout << result.minimum << "\n";
    }
    
    //PrintVector (tree.Element);
    delete[] source;
    return 0;
}
