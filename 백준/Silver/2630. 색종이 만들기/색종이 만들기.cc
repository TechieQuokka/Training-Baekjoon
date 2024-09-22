#include <stdio.h>
#include <stdbool.h>

int CountPaper (int paper[][128], int x1, int y1, int x2, int y2, int size, bool (*compare) (int[][128], int, int));

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
    
    int result = CountPaper (buffer, 0, 0, size, size, size, &white);
    printf ("%d\n", result);

    result = CountPaper (buffer, 0, 0, size, size, size, &black);
    printf ("%d\n", result);
    return 0;
}

bool Check (int paper[128][128], int x1, int y1, int x2, int y2, bool (*compare) (int[128][128], int, int)) {

    int row = 0, column = 0;
    for (row = x1; row < x2; row++) {
        for (column = y1; column < y2; column++) {
            if (!compare (paper, row, column)) return false;
        }
    }
    return true;
}

int CountPaper (int paper[][128], int x1, int y1, int x2, int y2, int size, bool (*compare) (int[][128], int, int)) {

    if (size == 0) return 0;
    else if (Check (paper, x1, y1, x2, y2, compare)) return 1;
    
    int count = 0;
    count += CountPaper (paper, x1, y1, x1 + (size / 2), y1 + (size / 2), size / 2, compare);
    count += CountPaper (paper, x1, y1 + (size / 2), x2 - (size / 2), y2, size / 2, compare);
    count += CountPaper (paper, x1 + (size / 2), y1, x2, y2 - (size / 2), size / 2, compare);
    count += CountPaper (paper, x1 + (size / 2), y1 + (size / 2), x2, y2, size / 2, compare);
    return count;
}