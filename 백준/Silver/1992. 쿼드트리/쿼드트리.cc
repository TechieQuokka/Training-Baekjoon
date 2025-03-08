#include <stdio.h>
#include <stdbool.h>

void Compression (int buffer[64][64], int length, int x, int y);

int main (int argc, char* argv[]) {
    
    int size = 0;
    scanf ("%d", &size);
    
    int buffer[64][64] = { 0, };
    
    int row = 0, column = 0;
    for (row = 0; row < size; row++) {
            
        char input[128] = { 0, };
        scanf ("%s", input);
        for (column = 0; column < size; column++) {
            
            buffer[row][column] = input[column] - '0';
        }
    }
    
    Compression (buffer, size, 0, 0);
    
    return 0;
}

bool Check (int buffer[64][64], int length, int x, int y) {

    int rowLength = length + x;
    int columnLength = length + y;
    
    int color = buffer[x][y];
    
    int row = 0, column = 0;
    for (row = x; row < rowLength; row++) {
        for (column = y; column < columnLength; column++) {
            
            if (buffer[row][column] != color) return false;
        }
    }
    return true;
}

void Compression (int buffer[64][64], int length, int x, int y) {
    
    if (Check (buffer, length, x, y)) {
        
        printf ("%d", buffer[x][y]);
        return;
    }
    if (length == 1) return;
    
    printf ("(");
    Compression (buffer, length / 2, x, y);
    Compression (buffer, length / 2, x, y + length / 2);
    Compression (buffer, length / 2, x + length / 2, y);
    Compression (buffer, length / 2, x + length / 2, y + length / 2);
    printf (")");
    return;
}
