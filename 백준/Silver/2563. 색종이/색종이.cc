#include <iostream>
#define MAXIMUM 100

using namespace std;

void DrawPaper (int paper[MAXIMUM][MAXIMUM], int x, int y, int size);
int GetArea (int paper[MAXIMUM][MAXIMUM], int row, int column);

int main (int argc, char* argv[]) {
    
    int input = 3;
    cin >> input;
    
    int paper[MAXIMUM][MAXIMUM] = { 0, };
    for (int loop = 0; loop < input; loop++) {
        
        int x = 0, y = 0, size = 10;
        cin >> x >> y;
        DrawPaper (paper, x, y, size);
    }
    
    int area = GetArea (paper, MAXIMUM, MAXIMUM);
    cout << area << endl;
    return 0;
}

void DrawPaper (int paper[MAXIMUM][MAXIMUM], int x, int y, int size) {

    int horizontal = size + x, vertical = size + y;
    for (int row = x; row < horizontal; row++) {
        for (int column = y; column < vertical; column++) {
            
            paper[row][column]++;
        }
    }
    return;
}

int GetArea (int paper[MAXIMUM][MAXIMUM], int row, int column) {
    
    int area = 0;
    for (int horizontal = 0; horizontal < row; horizontal++) {
        for (int vertical = 0; vertical < column; vertical++) {
            
            area += (bool)(paper[horizontal][vertical] > 0);
        }
    }
    return area;
}
