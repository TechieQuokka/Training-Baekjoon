#include <iostream>

using namespace std;

unsigned int GetNumberOfRepainting (bool** board, unsigned int width, unsigned int height);
template <typename T> T** CreateTwoDimensions (unsigned int row, unsigned int column);

int main (int argc, char* argv[]) {
    
    unsigned int row = 0U, column = 0U;
    cin >> row >> column;
    
    // create memory
    bool** board = CreateTwoDimensions<bool> (row, column);
    
    // input
    for (unsigned int horizontal = 0U; horizontal < row; horizontal++) {
        for (unsigned int vertical = 0U; vertical < column; vertical++) {
            
            char element = 0;
            cin >> element;
            board[horizontal][vertical] = element == 'W';
        }
    }
    
    unsigned int result = GetNumberOfRepainting (board, row, column);
    cout << result << endl;
    
    // free memory
    for (int index = 0; index < row; index++) {
        
        delete[] board[index];
    }
    delete[] board;
    return 0;
}

template <typename T> T** CreateTwoDimensions (unsigned int row, unsigned int column) {
    
    T** array = new T*[row];
    if (array == NULL) throw array;
    
    for (unsigned int index = 0U; index < row; index++) {
        
        array[index] = new T[column];
        if (array[index] != NULL) continue;
        
        for (unsigned int remove = 0U; remove < index; remove++) {
            
            delete[] array[index];
        }
        delete[] array;
        throw array;
    }
    return array;
}

unsigned int GetNumberOfRepainting (bool** board, unsigned int width, unsigned int height) {
    
    if (board == NULL) throw board;
    if (width < 8U || height < 8U) throw width, height;
    
    bool evert = false;
    unsigned int numberOfRows = 8U, numberOfColumn = 8U, size = 64U, least = 4294967295U;
    for (unsigned int row = numberOfRows - 1U; row < width; row++) {
        for (unsigned int column = numberOfColumn - 1U; column < height; column++) {
                
            unsigned int count = 0U;
            for (unsigned int horizontal = 0U; horizontal < numberOfRows; horizontal++) {
                for (unsigned int vertical = 0U; vertical < numberOfColumn; vertical++) {
                    
                    bool pivot = board[(row + 1U - numberOfRows) + horizontal][(column + 1U - numberOfColumn) + vertical];
                    count += (unsigned int) (pivot == evert);
                    evert = (vertical == numberOfColumn - 1) ? evert : !evert;
                }
            }
            
            unsigned int temporary = (size - count);
            count = temporary < count ? temporary : count;
            if (count < least) least = count;
        }
    }
    return least;
}
