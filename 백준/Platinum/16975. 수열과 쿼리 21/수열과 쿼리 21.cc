#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long int bigInt;

template <typename T>
struct ElementType {
    
    int Level;
    T Value;
    T LazyValue;
    bool Exist;
};

template <typename T>
struct SegmentTreeType {
    
    vector<struct ElementType<T>> Element;
    int Length;
    T DefaultValue;
    
    T (*Merge) (const T&, const T&);
    void (*Update) (vector<struct ElementType<T>>&, const int position, const int left, const int right, const T&);
    
    void Create (const int length, const T& defaultValue, T (*Merge) (const T&, const T&),
        void (*Update) (vector<struct ElementType<T>>&, const int, const int, const int, const T&)) {
        
        if (Merge == NULL) throw Merge;
        if (Update == NULL) throw Update;
        
        this->Element.resize (length * 4);
        struct ElementType<T> element = { -1, defaultValue, defaultValue, false };
        fill (this->Element.begin(), this->Element.end(), element);
        
        this->Length = length;
        this->DefaultValue = defaultValue;
        
        // callback
        this->Merge = Merge;
        this->Update = Update;
        return;
    }
    
    T BuildRecursive (T* source, int position, int left, int right, int level) {
        
        this->Element[position].Level = level;
        if (left == right) return this->Element[position].Value = source[left];
        
        int middle = (left + right) / 2;
        T leftValue = this->BuildRecursive (source, position * 2, left, middle, level + 1);
        T rightValue = this->BuildRecursive (source, position * 2 + 1, middle + 1, right, level + 1);
        
        return this->Element[position].Value = this->Merge (leftValue, rightValue);
    }
    
    T Build (T* source) {
        
        if (source == NULL) throw source;
        return this->BuildRecursive (source, 1, 0, this->Length - 1, 0);
    }
    
    void LazyUpdate (const int position, const int left, const int right, const T& value) {
        
        if (this->Element[position].Exist == false) return;
        
        this->Update (this->Element, position, left, right, value);
        if (left != right) this->Element[position * 2].Exist = this->Element[position * 2 + 1].Exist = true;
        
        this->Element[position].LazyValue = this->DefaultValue;
        this->Element[position].Exist = false;
        return;
    }
    
    void UpdateRangeRecursive (int position, int left, int right, int leftRange, int rightRange, T& value) {
    
        this->LazyUpdate (position, left, right, this->Element[position].LazyValue);
        if (leftRange > right || rightRange < left) return;
        if (leftRange <= left && rightRange >= right) {
            
            this->Update (this->Element, position, left, right, value);
            if (left != right) this->Element[position * 2].Exist = this->Element[position * 2 + 1].Exist = true;
            return;
        }
        
        int middle = (left + right) / 2;
        this->UpdateRangeRecursive (position * 2, left, middle, leftRange, rightRange, value);
        this->UpdateRangeRecursive (position * 2 + 1, middle + 1, right, leftRange, rightRange, value);
        
        this->Element[position].Value = this->Merge (this->Element[position * 2].Value, this->Element[position * 2 + 1].Value);
        return;
    }
    
    void UpdateRange (T& value, int leftRange, int rightRange) {
        
        this->UpdateRangeRecursive (1, 0, this->Length - 1, leftRange, rightRange, value);
        return;
    }
    
    T QueryRecursive (int position, int left, int right, int leftRange, int rightRange) {
        
        this->LazyUpdate (position, left, right, this->Element[position].LazyValue);
        if (leftRange > right || rightRange < left) return this->DefaultValue;
        if (leftRange <= left && rightRange >= right) return this->Element[position].Value;
        
        int middle = (left + right) / 2;
        T leftValue = this->QueryRecursive (position * 2, left, middle, leftRange, rightRange);
        T rightValue = this->QueryRecursive (position * 2 + 1, middle + 1, right, leftRange, rightRange);
        return this->Merge (leftValue, rightValue);
    }
    
    T Query (int leftRange, int rightRange) {
        
        return this->QueryRecursive (1, 0, this->Length - 1, leftRange, rightRange);
    }
};

void Update (vector<struct ElementType<bigInt>>& element, const int position, const int left, const int right, const bigInt& value) {
    
    element[position].Value += ((bigInt)(right - left + 1)) * value;
    if (left != right) {
        
        element[position * 2].LazyValue += value; // left
        element[position * 2 + 1].LazyValue += value; // right
    }
    return;
}

bigInt MergeSum (const bigInt& left, const bigInt& right) {
    
    return left + right;
}

void PrintVector (vector<struct ElementType<bigInt>> source) {
    
    for (auto iter = source.begin(); iter != source.end(); iter++) {
        
        cout << "[" << (*iter).Value << "(" << (*iter).Level << ")] ";
    }
    cout << endl;
    return;
}

int main (int argc, char* argv[]) {

    int size = 0;
    cin >> size;

    bigInt* source = new bigInt[size];
    if (source == NULL) throw;

    for (int index = 0; index < size; index++) {

        int value;
        cin >> value;
        source[index] = value;
    }

    struct SegmentTreeType<bigInt> tree;
    tree.Create (size, 0, &MergeSum, &Update);
    tree.Build (source);

    int count = 0;
    cin >> count;
    for (int repeat = 0; repeat < count; repeat++) {

        int command = 0;
        cin >> command;

        if (command == 1) {

            int left = 0, right = 0;
            cin >> left >> right;

            bigInt value = 0;
            cin >> value;

            tree.UpdateRange (value, left - 1, right - 1);
        }
        else {

            int index = 0;
            cin >> index;
            cout << tree.Query (index - 1, index - 1) << "\n";
        }
    }
    delete[] source;
    return 0;
}
