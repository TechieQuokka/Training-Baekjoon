#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

int Combination (int status[32][32], int depth, int size);

int main (int argc, char* argv[]) {
    
    int size = 0;
    cin >> size;
    
    int status[32][32] = { 0, };
    
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            
            cin >> status[row][column];
        }
    }
    
    cout << Combination (status, 0, size);
    
    return 0;
}

int calculate (int status[32][32], int size, vector<int>& startTeam, vector<int>& linkTeam) {
    
    int leftSum = 0, rightSum = 0;
    
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            
            leftSum += status[startTeam[row]][startTeam[column]];
            rightSum += status[linkTeam[row]][linkTeam[column]];
        }
    }
    return abs (leftSum - rightSum);
}

int Combination (int status[32][32], int depth, int size) {
    
    static vector<int> startTeam; static vector<int> linkTeam;
    static int result = INT_MAX;
    
    if (depth == size) {
        if (startTeam.size() == linkTeam.size()) {
            
            return result = min (result, calculate (status, size / 2, startTeam, linkTeam));
        }
        return result;
    }
    
    startTeam.push_back (depth);
    int left = Combination (status, depth + 1, size);
    startTeam.pop_back();
    
    linkTeam.push_back (depth);
    int right = Combination (status, depth + 1, size);
    linkTeam.pop_back();
    
    return min (left, right);
}
