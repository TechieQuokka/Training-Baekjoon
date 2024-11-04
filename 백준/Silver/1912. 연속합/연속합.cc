#include <stdio.h>
#include <malloc.h>

int ContinuousSum (int* sequence, int size);

int main (int argc, char* argv[]) {
    
    int size = 0;
    scanf ("%d", &size);
    
    int* sequence = (int*) calloc (size, sizeof (int));
    if (sequence == NULL) return 0;
    
    int index = 0;
    for (index = 0; index < size; index++) {
        
        scanf ("%d", sequence + index);
    }
    
    printf ("%d", ContinuousSum (sequence, size));
    
    free ((int*) sequence);
    return 0;
}

int ContinuousSum (int* sequence, int size) {
    
    int* buffer = (int*) calloc (size, sizeof (int));
    if (buffer == NULL) return -1;
    
    int index = 0, maximum = buffer[0] = sequence[0];
    if (buffer[0] < 0) buffer[0] = 0;
    for (index = 1; index < size; index++) {
        
        buffer[index] = buffer[index - 1] + sequence[index];
        if (buffer[index] < 0) buffer[index] = 0;
        if (maximum < sequence[index]) maximum = sequence[index];
    }
    if (maximum < 0) return maximum;
    
    int maxValue = -9999999;
    for (index = 0; index < size; index++) {
        
        if (maxValue < buffer[index]) maxValue = buffer[index];
    }
    
    free ((int*) buffer);
    return maxValue;
}
