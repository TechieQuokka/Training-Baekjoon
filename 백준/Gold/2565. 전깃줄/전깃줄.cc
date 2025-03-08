#include <stdio.h>
#include <stdlib.h>

struct CordType {
    
    int left, right;
};

int Calculate (struct CordType cords[128], int size);

int ascending (const void* left, const void* right) {
    
    return (*(struct CordType*)left).left - (*(struct CordType*)right).left;
}

int main (int argc, char* argv[]) {
    
    int numberOf = 0;
    scanf ("%d", &numberOf);
    
    struct CordType cords[128] = { 0, };
    int index = 0;
    for (index = 0; index < numberOf; index++) {
        
        scanf ("%d%d", &cords[index].left, &cords[index].right);
    }
    qsort ((struct CordType*) cords, numberOf, sizeof (struct CordType), &ascending);
    
    int result = Calculate (cords, numberOf);
    printf ("%d", numberOf - result);
    
    return 0;
}

int maximum (int left, int right) {
    
    return left < right ? right : left;
}

int Calculate (struct CordType cords[128], int size) {

    if (cords == NULL) return -1;
    
    int buffer[128] = { 0, };
    int index = 0, pivot = 0, maxValue = -9999999;
    for (index = 1; index < size; index++) {
        for (pivot = index - 1; pivot >= 0; pivot--) {
            if (cords[index].right > cords[pivot].right) 
                buffer[index] = maximum (buffer[index], buffer[pivot] + 1);
        }
        if (maxValue < buffer[index]) maxValue = buffer[index];
    }
    return maxValue + 1;
}
