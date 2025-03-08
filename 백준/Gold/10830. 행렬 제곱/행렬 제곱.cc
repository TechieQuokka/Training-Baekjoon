#include <stdio.h>

int (*Power (int matrix[8][8], int size, long long int exponent, int remain))[8];
void Print (int matrix[8][8], int horizontal, int vertical);

int main (int argc, char* argv[]) {
    
    int matrix[8][8] = { {1, 2}, {3, 4} };
    
    int width = 0;
    long long int count = 0LL;
    scanf ("%d%lld", &width, &count);
    
    int row = 0, column = 0;
    for (row = 0; row < width; row++) {
        for (column = 0; column < width; column++) {
            
            scanf ("%d", &matrix[row][column]);
        }
    }
    
    int (*result)[8] = Power (matrix, width, count, 1000);
    Print (result, width, width);
    return 0;
}

int (*Multiply (int left[8][8], int right[8][8], int size, int remain))[8] {
    
    static int buffer[8][8] = { 0, };
    
    int row = 0, column = 0, sum = 0, pivot = 0;
    for (row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            for (pivot = 0, sum = 0; pivot < size; pivot++) {
                
                sum += left[row][pivot] * right[pivot][column] % remain;
            }
            buffer[row][column] = sum % remain;
        }
    }
    return buffer;
}

int (*MemoryCopy (int matrix[8][8], int size))[8] {
    
    static int buffer[8][8] = { 0, };
    
    int row = 0, column = 0;
    for (row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            buffer[row][column] = matrix[row][column];
        }
    }
    
    return buffer;
}

int (*Power (int matrix[8][8], int size, long long int exponent, int remain))[8] {
    
    if (exponent <= 1LL) return matrix;
    
    int (*result)[8] = Power (matrix, size, exponent / 2LL, remain);
    if (exponent % 2LL == 0) return MemoryCopy (Multiply (result, result, size, remain), size);
    else return MemoryCopy (Multiply (MemoryCopy (Multiply (result, result, size, remain), size), matrix, size, remain), size);
}

void Print (int matrix[8][8], int horizontal, int vertical) {
    
    if (matrix == NULL) return;
    
    int row = 0, column = 0;
    for (row = 0; row < horizontal; row++) {
        for (column = 0; column < vertical; column++) {
            
            printf ("%d ", matrix[row][column] % 1000);
        }
        printf ("\n");
    }
    return;
}
