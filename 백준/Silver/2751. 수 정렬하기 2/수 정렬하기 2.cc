#include <iostream>
#define NUMBER_OF_DIGITS 10

using namespace std;

template<typename T> void MergeSort (T* array, const size_t start, const size_t end, signed int (*compare) (const T, const T));

int Ascending (const int argument1, const int argument2) {
    
    return argument1 - argument2;
}

int main (int argc, char* argv[]) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin.tie(NULL);
    
    int length = 0;
    cin >> length;
    int* array = new int[length];
    if (array == NULL) return 0;
    
    for (int index = 0; index < length; index++) {
        
        cin >> array[index];
    }
    
    MergeSort (array, 0, length - 1, &Ascending);
    for (int index = 0; index < length; index++) {
        
        cout << array[index] << '\n';
    }
    return 0;
}

template<typename T> void Partition (T* array, const size_t start, const size_t middle, const size_t end, signed int (*compare) (const T, const T)) {
    
    size_t leftBufferSize = middle - start + 1, rightBufferSize = end - middle;
    
    // create buffer arrays
    T* leftBuffer = new T[leftBufferSize], * rightBuffer = new T[rightBufferSize];
    if (leftBuffer == NULL || rightBuffer == NULL) exit(1);
    
    // copy data to buffer arrays leftBuffer[] and rightBuffer[]
    for (size_t index = 0U; index < leftBufferSize; index++) leftBuffer[index] = array[start + index];
    for (size_t index = 0U; index < rightBufferSize; index++) rightBuffer[index] = array[middle + 1U + index];
    
    // merge the buffer arrays back into array[start...end]
    size_t left = 0U, right = 0U, index = 0U;
    for (left = 0U, right = 0U, index = start; left < leftBufferSize && right < rightBufferSize; index++) {
        if (compare (leftBuffer[left], rightBuffer[right]) < 0) array[index] = leftBuffer[left++];
        else array[index] = rightBuffer[right++];
    }
    
    // copy the remaining elements of leftBuffer[], if there are any
    while (left < leftBufferSize) array[index++] = leftBuffer[left++];
    while (right < rightBufferSize) array[index++] = rightBuffer[right++];
    
    // free memory
    delete[] leftBuffer, rightBuffer;
    return;
}

template<typename T> void MergeSort (T* array, const size_t start, const size_t end, signed int (*compare) (const T, const T)) {
    
    if (start >= end) return;
    
    int pivot = start + (end - start) / 2;
    
    // sort first and second halves
    MergeSort (array, start, pivot, compare);
    MergeSort (array, pivot + 1, end, compare);
    Partition (array, start, pivot, end, compare);
    return;
}
