#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Solution (string left, string right, vector<vector<int>>& buffer);

int main (int argc, char* argv[]) {
    string left = "", right = "";
    cin >> left >> right;

    vector<vector<int>> buffer (left.size() + 1, vector<int> (right.size() + 1, 0));
    int result = Solution(left, right, buffer);

    cout << result << "\n";

    vector<char> source;

    int row = left.length(), column = right.length();
    while (row > 0 && column > 0) {
        if (left[row - 1] == right[column - 1]) {
            source.push_back(left[row - 1]);
            row--;
            column--;
        } else if (buffer[row - 1][column] >= buffer[row][column - 1]) {
            row--;
        } else {
            column--;
        }
    }

    reverse(source.begin(), source.end());
    for (const auto& element : source) cout << element;
    return 0;
}

int Solution (string left, string right, vector<vector<int>>& buffer) {
    int leftLength = left.size() + 1;
    int rightLength = right.size() + 1;

    for (int row = 1; row < leftLength; row++) {
        char leftElement = left[row - 1];
        for (int column = 1; column < rightLength; column++) {
            char rightElement = right[column - 1];
            if (leftElement != rightElement) {
                buffer[row][column] = max(buffer[row - 1][column], buffer[row][column - 1]);
            } else {
                buffer[row][column] = buffer[row - 1][column - 1] + 1;
            }
        }
    }

    return buffer[left.size()][right.size()];
}
