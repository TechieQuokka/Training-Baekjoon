#include <stdio.h>
#include <stdbool.h>

int CountPaper (int paper[128][128], int length, int x, int y, bool (*compare) (int[128][128], int, int));

bool black (int paper[128][128], int row, int column) {
    
    return paper[row][column] == 1;
}

bool white (int paper[128][128], int row, int column) {
    
    return paper[row][column] == 0;
}

int main (int argc, char* argv[]) {
    
    int size = 0;
    scanf ("%d", &size);
    
    int buffer[128][128] = { 0, };
    
    int row = 0, column = 0;
    for (row = 0; row < size; row++) {
        for (column = 0; column < size; column++) {
            
            scanf ("%d", &buffer[row][column]);
        }
    }
    
    int result = CountPaper (buffer, size, 0, 0, &white);
    printf ("%d\n", result);
    
    result = CountPaper (buffer, size, 0, 0, &black);
    printf ("%d\n", result);
    return 0;
}

bool Check (int paper[128][128], int length, int x, int y, bool (*compare) (int[128][128], int, int)) {

    int rowLength = length + x;
    int columnLength = length + y;
    
    int row = 0, column = 0;
    for (row = x; row < rowLength; row++) {
        for (column = y; column < columnLength; column++) {
            
            if (!compare (paper, row, column)) return false;
        }
    }
    return true;
}

int CountPaper (int paper[128][128], int length, int x, int y, bool (*compare) (int[128][128], int, int)) {
    
    if (Check (paper, length, x, y, compare)) return 1;
    if (length == 1) return (int) (compare (paper, x, y));
    
    int topLeft = CountPaper (paper, length / 2, x, y, compare);
    int topRight = CountPaper (paper, length / 2, x, y + length / 2, compare);
    int bottomLeft = CountPaper (paper, length / 2, x + length / 2, y, compare);
    int bottomRight = CountPaper (paper, length / 2, x + length / 2, y + length / 2, compare);
    
    return topLeft + topRight + bottomLeft + bottomRight;
}
