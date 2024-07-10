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
        
        int height = (int) ceil (log2 (length));
        int size = (1 << (height + 1));
        this->Element.resize (size);
        struct ElementType<T> element = { -1, defaultValue, defaultValue, false };
        fill (this->Element.begin(), this->Element.end(), element);
        
        this->Length = length;
        this->DefaultValue = defaultValue;
        
        // callback
        this->Merge = Merge;
        this->Update = Update;
        return;
    }
    
    T BuildRecursive (T* source, int position, int left, int right) {
        
        if (left == right) return this->Element[position].Value = source[left];
        
        int middle = (left + right) / 2;
        T leftValue = this->BuildRecursive (source, position * 2, left, middle);
        T rightValue = this->BuildRecursive (source, position * 2 + 1, middle + 1, right);
        
        return this->Element[position].Value = this->Merge (leftValue, rightValue);
    }
    
    T Build (T* source) {
        
        return this->BuildRecursive (source, 1, 0, this->Length - 1);
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
        
        cout << "[" << (*iter).Value << "] ";
    }
    cout << endl;
    return;
}

int main (int argc, char* argv[]) {
    
    int length = 0, numberOfUpdate = 2, numberOfSum = 2;
    cin >> length >> numberOfUpdate >> numberOfSum;
    
    bigInt* source = new bigInt[length];
    for (bigInt index = 0; index < length; index++) {
        
        bigInt element = 0;
        cin >> element;
        source[index] = element;
    }
    
    struct SegmentTreeType<bigInt> tree;
    tree.Create(length, 0, &MergeSum, &Update);
    tree.Build (source);
    
    bigInt count = numberOfUpdate + numberOfSum;
    for (bigInt loop = 0; loop < count; loop++) {
        
        bigInt option = 0, from = 0, to = 0, value;
        cin >> option;
        if (option == 1) {
            
            cin >> from >> to >> value;
            tree.UpdateRange (value, from - 1, to - 1);
        }
        else {
            
            cin >> from >> to;
            bigInt value = tree.Query (from - 1, to - 1);
            cout << value << "\n";
        }
        
        // print
        //PrintVector (tree.Element);
    }
    
    delete[] source;
    return 0;
}
