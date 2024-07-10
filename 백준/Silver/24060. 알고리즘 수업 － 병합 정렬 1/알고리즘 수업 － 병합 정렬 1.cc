#include <iostream>

using namespace std;

template<typename T> void MergeSort (T* array, int left, int right, int (*compare) (const T,  const T), void (*update_Callback) (T*, T*, int, int, int, int, int, int));
int Ascending (const int argument1, const int argument2) {
    
    return argument1 - argument2;
}

int result = -1, position = 0; // global variable

void Display_Callback (int* array, int* buffer, int left, int middle, int right, int start, int center, int index) {
    
    static int count = 0;
    if (count++ == position) result = array[start - 1];
    return;
}

int main (int argc, char* argv[]) {
    
    int size = 0;
    cin >> size >> position;
    position--;
    
    int* array = new int[size];
    if (array == NULL) throw array;
    
    for (int index = 0; index < size; index++) {
        
        cin >> array[index];
    }
    
    MergeSort<int> (array, 0, size - 1, &Ascending, &Display_Callback);
    cout << result << "\n";
    return 0;
}

template<typename T> void Merge (T* array, int left, int middle, int right, int (*compare) (const T,  const T), void (*update_Callback) (T*, T*, int, int, int, int, int, int)) {
    
    T* buffer = new T[right + 2];
    if (buffer == NULL) throw buffer;
    
    int start = left, center = middle + 1, index = 1;
    while (start <= middle && center <= right) {
        if (compare (array[start], array[center]) < 0) buffer[index++] = array[start++];
        else buffer[index++] = array[center++];
    }
    
    while (start <= middle) buffer[index++] = array[start++];
    while (center <= right) buffer[index++] = array[center++];
    
    start = left, index = 1;
    while (start <= right) {
        
        array[start++] = buffer[index++];
        if (update_Callback != NULL) update_Callback (array, buffer, left, middle, right, start, center, index);
    }
    delete[] buffer;
    return;
}

template<typename T> void MergeSort (T* array, int left, int right, int (*compare) (const T,  const T), void (*update_Callback) (T*, T*, int, int, int, int, int, int)) {
    
    if (compare == NULL) throw compare;
    if (left >= right) return;
    
    int middle = (left + right) / 2;
    MergeSort<T> (array, left, middle, compare, update_Callback);
    MergeSort<T> (array, middle + 1, right, compare, update_Callback);
    Merge<T> (array, left, middle, right, compare, update_Callback);
    return;
}
