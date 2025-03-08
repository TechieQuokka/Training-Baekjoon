#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N_Queen (bool buffer[16], int pivot, int depth, int size);

int main (int argc, char* argv[]) {
    
    bool buffer[16] = { false, };
    
    int number = 0;
    cin >> number;
    
    int count = N_Queen (buffer, 0, 0, number);
    printf ("%d\n", count);
    return 0;
}

bool CheckQueen (vector<pair<int, int>>& nStack, int index, int depth) {

    for (auto iterate = nStack.begin(); iterate != nStack.end(); iterate++) {
        
        int sum = (*iterate).first + (*iterate).second;
        int subtract = (*iterate).first - (*iterate).second;
        if (sum == (index + depth) || subtract == (index - depth)) return false;
    }
    return true;
}

int N_Queen (bool buffer[16], int pivot, int depth, int size) {
    
    if (depth == size) return 1;
    
    static vector<pair<int, int>> nStack;
    bool board[16] = { 0, };
    
    int index = 0, count = 0;
    for (index = 0; index < size; index++) {
        
        if (buffer[index] == true || !CheckQueen (nStack, index, depth)) continue;
        
        memset ((bool*) board, 0, size * sizeof (bool));
        
        if (index - 1 >= 0) board[index - 1] = true;
        if (index + 1 < size) board[index + 1] = true;
        board[index] = true;
        for (auto iterate = nStack.begin(); iterate != nStack.end(); iterate++) board[(*iterate).first] = true;
        
        nStack.push_back ({index, depth});
        count += N_Queen (board, index, depth + 1, size);
        nStack.pop_back ();
    }
    
    return count;
}
