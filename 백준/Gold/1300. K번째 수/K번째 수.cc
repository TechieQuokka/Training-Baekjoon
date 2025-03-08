#include <stdio.h>

int FindValue (const int pivot, const int size, int left, int right);

int main (int argc, char* argv[]) {
    
    int size = 3, indexer = 7;
    scanf ("%d%d", &size, &indexer);
    
    int result = FindValue (indexer, size, 0, indexer);
    printf ("%d\n", result);
    return 0;
}

int minimum (int left, int right) {
    
    return left < right ? left : right;
}

int Calculate (int middle, const int size) {
    
    int sum = 0;
    int time = 0;
    for (time = 1; time <= size; time++) {
        
        sum += minimum (middle / time, size);
    }
    return sum;
}

int FindValue (const int pivot, const int size, int left, int right) {
    
    int middle = (left + right) / 2;
    if (left > right) return left;
    
    int result = Calculate (middle, size);    
    if (result < pivot) return FindValue (pivot, size, middle + 1, right);
    else return FindValue (pivot, size, left, middle - 1);
}
