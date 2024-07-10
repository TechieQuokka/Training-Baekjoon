#include <iostream>

using namespace std;

struct CoordinateType {

    int X, Y;
};

template<typename T> void InsertionSort (T* array, const size_t size, signed int (*compare) (const T, const T));
template<typename T> void MergeSort (T* array, const size_t start, const size_t end, signed int (*compare) (const T, const T));

int Ascending (const struct CoordinateType argument1, const struct CoordinateType argument2) {
    
    if (argument1.Y != argument2.Y) return argument1.Y - argument2.Y;
    else return argument1.X - argument2.X;
}

void PrintCoordinate (struct CoordinateType* coordinates, size_t size) {
    
    if (coordinates == NULL) throw coordinates;
    
    for (int index = 0; index < size; index++) {
        
        cout << coordinates[index].X << " " << coordinates[index].Y << "\n";
    }
    return;
}

int main (int argc, char* argv[]) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int input = 0;
    cin >> input;
    
    struct CoordinateType* coordinates = new struct CoordinateType[input];
    if (coordinates == NULL) return 0;
    
    for (int index = 0; index < input; index++) cin >> coordinates[index].X >> coordinates[index].Y;
    
    MergeSort<struct CoordinateType> (coordinates, 0, input - 1, &Ascending);
    PrintCoordinate (coordinates, input);
    return 0;
}

template<typename T> void Partition (T* array, const size_t start, const size_t middle, const size_t end, signed int (*compare) (const T, const T)) {
    
    size_t leftBufferSize = middle - start + 1, rightBufferSize = end - middle;
    
    // create buffer arrays
    T* leftBuffer = new T[leftBufferSize], * rightBuffer = new T[rightBufferSize];
    if (leftBuffer == NULL || rightBuffer == NULL) throw leftBuffer;
    
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

template<typename T> void InsertionSort (T* array, const size_t size, signed int (*compare) (const T, const T)) {
    
    if (array == NULL || compare == NULL) throw array;
    
    for (unsigned int pivot = 1U; pivot < size; pivot++) {
        
        T key = array[pivot];
        unsigned int index = 0U;
        for (index = pivot; index > 0 && compare(key, array[index - 1]) < 0; index--) array[index] = array[index - 1];
        array[index] = key;
    }
    return;
}
