#include <iostream>
#include <cmath>

using namespace std;

template<typename T> void InsertionSort (T* array, const size_t size, signed int (*compare) (const T, const T));
char* IntegerToString (unsigned int integer);

int Descending (const char argument1, const char argument2) {
    
    return argument2 - argument1;
}

int main (int argc, char* argv[]) {
    
    int number = 0;
    cin >> number;
    char* source = IntegerToString (number);
    InsertionSort<char> (source, (size_t)(log10(number) + 1), &Descending);
    cout << source << endl;
    return 0;
}

char* IntegerToString (unsigned int integer) {
    
    int length = (int)(log10 (integer) + 1.0);
    char* destination = new char[length + 1];
    for (int index = length - 1; index >= 0; index--, integer /= 10U) {
        
        destination[index] = (char)((integer % 10U) + '0');
    }
    destination[length] = '\0';
    return destination;
}

template<typename T> void InsertionSort (T* array, const size_t size, signed int (*compare) (const T, const T)) {
    
    if (array == NULL || compare == NULL) return;
    
    for (size_t pivot = 1U; pivot < size; pivot++) {
        
        T key = array[pivot];
        size_t index = 0U;
        for (index = pivot; index && compare (key, array[index - 1U]) < 0; index--) array[index] = array[index - 1U];
        array[index] = key;
    }
    return;
}
