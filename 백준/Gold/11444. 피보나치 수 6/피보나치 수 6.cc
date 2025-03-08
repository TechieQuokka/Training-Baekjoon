#include <stdio.h>

long long int (*Power (long long int matrix[8][8], long long int size, long long int exponent, long long int remain))[8];
long long int (*MatrixMultiplication (long long int left[8][8], long long int right[8][8], long long int horizontal, long long int vertical, long long int pivotSize, long long int remain))[8];

int main (int argc, char* argv[]) {
    
    long long int number = 0;
    scanf ("%lld", &number);
    if (number == 0) {
        
        printf ("0");
        return 0;
    }
    
    long long int matrix[8][8] = {{ 1, 1 }, { 1, 0 }};
    long long int (*buffer)[8] = Power (matrix, 2, number, 1000000007);
    
    long long int temp[8][8] = {{ 1 }, { 0 }};
    
    long long int (*result)[8] = MatrixMultiplication (buffer, temp, 2, 1, 2, 1000000007);
    
    printf ("%lld", result[1][0] % 1000000007);
    return 0;
}

long long int (*MatrixMultiplication (long long int left[8][8], long long int right[8][8], long long int horizontal, long long int vertical, long long int pivotSize, long long int remain))[8] {
    
    if (left == NULL || right == NULL) return NULL;
    
    static long long int buffer[8][8] = { 0, };
    
    long long int row = 0, column = 0;
    for (row = 0; row < horizontal; row++) {
        for (column = 0; column < vertical; column++) {
            
            long long int sum = 0, pivot = 0;
            for (pivot = 0; pivot < pivotSize; pivot++) {
                
                sum += left[row][pivot] * right[pivot][column] % remain;
            }
            buffer[row][column] = sum % remain;
        }
    }
    
    return buffer;
}

long long int (*MemoryCopy (long long int matrix[8][8], long long int size))[8] {
    
    static long long int buffer[8][8] = { 0, };
    
    long long int row = 0, column = 0;
    for (row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            buffer[row][column] = matrix[row][column];
        }
    }
    
    return buffer;
}

long long int (*Power (long long int matrix[8][8], long long int size, long long int exponent, long long int remain))[8] {
    
    if (exponent <= 1LL) return matrix;
    
    long long int (*result)[8] = Power (matrix, size, exponent / 2LL, remain);
    if (exponent % 2LL == 0) return MemoryCopy (MatrixMultiplication (result, result, size, size, size, remain), size);
    else return MemoryCopy (MatrixMultiplication (MemoryCopy (MatrixMultiplication (result, result, size, size, size, remain), size), matrix, size, size, size, remain), size);
}
