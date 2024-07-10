#include <iostream>
#include <deque>

using namespace std;

void PrintArray (int board[9][9], int row, int column) {
    
    if (board == NULL) throw board;
    
    for (int horizontal = 0; horizontal < row; horizontal++) {
        for (int vertical = 0; vertical < column; vertical++) {
            
            cout << board[horizontal][vertical] << " ";
        }
        cout << "\n";
    }
    return;
}
bool Sudoku (int board[9][9], deque<struct LocationType>& location, struct LocationType current);

struct LocationType {
    
    int row, column;
};

int main (int argc, char* argv[]) {
    
    deque<struct LocationType> location;
    
    int board[9][9] = { 0, };
    for (int horizontal = 0; horizontal < 9; horizontal++) {
        for (int vertical = 0; vertical < 9; vertical++) {
            
            int element = 0;
            cin >> element;
            board[horizontal][vertical] = element;
            if (element == 0) location.push_back({horizontal, vertical});
        }
    }
    
    location.push_back ({-1, -1});
    struct LocationType current = location.front(); location.pop_front();
    Sudoku (board, location, current);
    
    PrintArray (board, 9, 9);
    return 0;
}

bool CheckNumber (int board[9][9], int row, int column, int number) {
    
    // check row
    for (int index = 0; index < 9; index++) {
        
        if (board[row][index] == number) return false;
    }
    
    // check column
    for (int index = 0; index < 9; index++) {
        
        if (board[index][column] == number) return false;
    }
    
    // check 3 * 3 range
    int rowStart = (int) (row / 3) * 3, columnStart = (int) (column / 3) * 3;
    int rowEnd = rowStart + 3, columnEnd = columnStart + 3;
    for (int horizontal = rowStart; horizontal < rowEnd; horizontal++) {
        for (int vertial = columnStart; vertial < columnEnd; vertial++) {
            
            if (board[horizontal][vertial] == number) return false;
        }
    }
    
    return true;
}

bool Sudoku (int board[9][9], deque<struct LocationType>& location, struct LocationType current) {
    
    if (location.size() == 0) return false;
    
    for (int number = 1; number < 10; number++) {
        
        if (!CheckNumber(board, current.row, current.column, number)) continue;
        
        board[current.row][current.column] = number;
        struct LocationType pivot = location.front();
        location.pop_front();
        bool result = Sudoku (board, location, pivot);
        if (result == false) return false;
        
        board[current.row][current.column] = 0;
        location.push_front(pivot);
    }
    return true;
}
