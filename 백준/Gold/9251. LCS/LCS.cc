#include <stdio.h>
#include <string.h>

int Calculate (char* left, char* right);

int main (int argc, char* argv[]) {
    
    char left[1001] = { 0, }, right[1001] = { 0, };
    scanf ("%s%s", left, right);
    
    printf ("%d", Calculate (left, right));
    return 0;
}

int max (int left, int right) {
    
    return left < right ? right : left;
}

int Calculate (char* left, char* right) {
    
    if (left == NULL || right == NULL) return -1;
    
    int leftLength = strlen (left) + 1;
    int rightLength = strlen (right) + 1;
    
    int buffer[1001][1001] = { 0, };
    int row = 0, column = 0;
    for (row = 1; row < leftLength; row++) {
            
        char leftElement = left[row - 1];
        for (column = 1; column < rightLength; column++) {
            
            char rightElement = right[column - 1];
            if (leftElement != rightElement) buffer[row][column] = max (buffer[row - 1][column], buffer[row][column - 1]);
            else buffer[row][column] = buffer[row - 1][column - 1] + 1;
        }
    }
    return buffer[row - 1][column - 1];
}
