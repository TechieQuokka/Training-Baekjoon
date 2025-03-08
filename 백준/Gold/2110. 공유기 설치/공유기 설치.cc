#include <stdio.h>
#include <stdlib.h>

int FindValue (int* source, int length, int left, int right, int pivot);

int ascending (const void* left, const void* right) {
    
    return *(int*)left > *(int*)right;
}

int main (int argc, char* argv[]) {
    
    int length = 0, pivot = 0;
    scanf ("%d%d", &length, &pivot);
    
    static int source[200001] = { 0, };
    
    int index = 0, maximum = -9999999;
    for (index = 0; index < length; index++) {
        
        scanf ("%d", source + index);
    }
    qsort (source, length, sizeof (int), &ascending);
    
    int result = FindValue (source, length, 0, source[length - 1], pivot);
    printf ("%d\n", result);
    return 0;
}

int Calculate (int* source, int length, int middle) {

    int index = 0, previous = source[0], count = 1;
    for (index = 0; index < length; index++) {
        
        int interval = source[index] - previous;
        if (interval < middle) continue;
        
        count++;
        previous = source[index];
    }
    
    return count;
}

int FindValue (int* source, int length, int left, int right, int pivot) {
    
    int middle = (left + right) / 2;
    if (left > right) return middle;
    
    if (Calculate (source, length, middle) >= pivot) return FindValue (source, length, middle + 1, right, pivot);
    else return FindValue (source, length, left, middle - 1, pivot);
}
