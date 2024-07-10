#include <stdio.h>

void QuickSort (int* source, int start, int end);
int Partitioning (int* source, int start, int end);

void Display (int* source, int length) {
    
    int index = 0;
    for (index = 0; index < length; index++) {
        
        printf ("%d\n", source[index]);
    }
    return;
}

int main (int argc, char* argv[]) {
    
    int source[1024] = { 0, };
    int length = 0;
    scanf ("%d", &length);
    
    int index = 0;
    for (index = 0; index < length; index++) {
        
        scanf ("%d", source + index);
    }
    QuickSort (source, 0, length - 1);
    Display (source, length);
    
    return 0;
}

void Swap (int* argument1, int* argument2) {
    
    int temp = *argument1;
    *argument1 = *argument2;
    *argument2 = temp;
    return;
}

int Partitioning (int* source, int start, int end) {
    
    int left = start, right = end, pivot = start;
    while (left < right) {
        
        while (left < right && source[left] < source[pivot]) left++;
        while (left < right && source[right] > source[pivot]) right--;
        Swap (source + left, source + right);
    }
    Swap (source + left, source + pivot);
    return left;
}

void QuickSort (int* source, int start, int end) {

    if (start >= end) return;
    
    int pivot = Partitioning (source, start, end);
    QuickSort (source, start, pivot);
    QuickSort (source, pivot + 1, end);
    return;
}
