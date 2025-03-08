#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define SIZE 1024

void Permutation (int position[SIZE], int depth, int size, void (*access) (int[SIZE], int));

enum Operator { ADD = 0, SUBTRACT = 1, MULTIPLY = 2, DIVIDE = 3, MOD = 4 };
enum Operator operators[SIZE] = { ADD, };
int source[128] = { 0, };
int maximum = INT_MIN, minimum = INT_MAX;

void Access (int position[SIZE], int size) {
    
    int calculate = source[0];
    int index = 0;
    for (index = 0; index < size; index++) {
        
        switch (operators[position[index]]) {
        case ADD:
            calculate += source[index + 1];
            break;
        case SUBTRACT:
            calculate -= source[index + 1];
            break;
        case MULTIPLY:
            calculate *= source[index + 1];
            break;
        case DIVIDE:
            calculate /= source[index + 1];
            break;
        default: break;
        }
    }
    
    if (maximum < calculate) maximum = calculate;
    if (minimum > calculate) minimum = calculate;
    return;
}

int main (int argc, char* argv[]) {
    
    int position[SIZE] = { 0, };
    int count = 0;
    scanf ("%d", &count);
    
    int index = 0;
    for (index = 0; index < count; index++) {
        
        int value = 0;
        scanf ("%d", &value);
        source[index] = value;
    }
    
    int pivot = 0, column = 0;
    for (index = 0, pivot = 0; pivot < 4; pivot++) {
        
        int length = 0;
        scanf ("%d", &length);
        for (column = 0; column < length; column++) {
            
            operators[index++] = (enum Operator) pivot;
        }
    }
    Permutation (position, 0, index, &Access);
    printf ("%d\n%d\n", maximum, minimum);
    return 0;
}

void PrintArray (int* source, int length) {
    
    if (source == NULL) return;
    
    int index = 0;
    for (index = 0; index < length; index++) {
        
        printf ("%d ", source[index]);
    }
    printf ("\n");
    return;
}

void Permutation (int position[SIZE], int depth, int size, void (*access) (int[SIZE], int)) {
    
    static bool used[SIZE] = { 0, };
    
    if (depth == size) {
        
        if (access != NULL) access (position, size);
        return;
    }
    
    int index = 0;
    for (index = 0; index < size; index++) {
        
        if (used[index]) continue;
        
        used[index] = true;
        position[depth] = index;
        Permutation (position, depth + 1, size, access);
        used[index] = false;
    }
    return;
}
