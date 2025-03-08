#include <stdio.h>
#include <stdbool.h>

#define MAXIMUM 8

void Permutation (void* array, int size, size_t type, int left, int height, void* argument, void (*access) (void* array, int size, void* argument));

int main (int argc, char* argv[]) {
    
    int array[MAXIMUM] = { 0, };
    int index = 0;
    for (index = 0; index < MAXIMUM; index++) {
        
        scanf("%d", array + index);
    }
        
    int counter = 0;
    void Access (void* array, int size, void* argument);
    Permutation (array, MAXIMUM, sizeof (int), 0, MAXIMUM - 1, &counter, &Access);
    
    printf ("%d\n", counter);
    return 0;
}

bool IsConvexPolygon (int* array, int length) {
    
    int index = 0;
    for (index = 0; index < length; index++) {
        
        int a1 = index, a2 = (index + 1) % length, a3 = (index + 2) % length;
        if ((array[a1] * array[a3] * 1.4142135623730950) > (array[a2] * (array[a1] + array[a3]))) return false;
    }
    return true;
}

void Access (void* array, int size, void* argument) {
    
    int* counter = (int*) argument;
    int result = (int) IsConvexPolygon ((int*) array, size);
    (*counter) = (*counter) + result;
    return;
}

void Swap (void* argument1, void* argument2, size_t type) {
    
    unsigned char* memory1 = (unsigned char*) argument1, * memory2 = (unsigned char*) argument2;
    size_t byte = 0LLU;
    for (byte = 0LLU; byte < type; byte++) {
        
        unsigned char temporary = memory1[byte];
        memory1[byte] = memory2[byte];
        memory2[byte] = temporary;
    }
    return;
}

void Permutation (void* array, int size, size_t type, int left, int height, void* argument, void (*access) (void* array, int size, void* argument)) {
    
    if (left == height) access (array, size, argument);
    else {
        int index = 0;
        for (index = left; index <= height; index++) {
            
            Swap ((unsigned char*)array + left * type, (unsigned char*)array + index * type, type);
            Permutation ((char*)array, size, type, left + 1, height, argument, access);
            Swap ((unsigned char*)array + left * type, (unsigned char*)array + index * type, type);
        }
    }
    return;
}
