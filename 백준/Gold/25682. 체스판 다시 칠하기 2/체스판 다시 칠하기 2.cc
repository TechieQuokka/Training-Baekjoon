#include <iostream>
#include <vector>

using namespace std;

int CountCell (vector<vector<bool>> board, bool color, int width, int height, int size);

int main (int argc, char* argv[]) {

    int width = 0, height = 0, size = 0;
    cin >> width >> height >> size;
    
    vector<vector<bool>> board(width, vector<bool>());
    for (int pivot = 0; pivot < width; pivot++) {
        
        string source;
        cin >> source;
        int length = source.size();
        for (int index = 0; index < length; index++) {
            
            board[pivot].push_back(source[index] == 'B');
        }
    }
    
    int result = min (CountCell(board, true, width, height, size), CountCell (board, false, width, height, size));
    cout << result;
    return 0;
}

int CountCell (vector<vector<bool>> board, bool color, int width, int height, int size) {
    
    vector<vector<int>> prefixSum(width + 1, vector<int>(height + 1, 0));
    for (int row = 0; row < width; row++) {
        for (int column = 0; column < height; column++) {
            
            bool value = (row + column) % 2 == 0 ? board[row][column] != color : board[row][column] == color;
            prefixSum[row + 1][column + 1] = prefixSum[row][column + 1] + prefixSum[row + 1][column] - prefixSum[row][column] + (int)value;
        }
    }
    
    int count = 99999999;
    int rowSize = width - size + 2, columnSize = height - size + 2;
    for (int row = 1; row < rowSize; row++) {
        for (int column = 1; column < columnSize; column++) {
            
            count = min (count, prefixSum[row + size - 1][column + size - 1] - prefixSum[row + size - 1][column - 1] - prefixSum[row - 1][column + size - 1] + prefixSum[row - 1][column - 1]);
        }
    }
    return count;
}
