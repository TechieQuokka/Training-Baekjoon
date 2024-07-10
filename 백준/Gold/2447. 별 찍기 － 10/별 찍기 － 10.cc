#include <iostream>

using namespace std;

void DisplayDoorPattern (int row, int column, int size);

int main (int argc, char* argv[]) {
    
    int size = 9;
    cin >> size;
    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            
            DisplayDoorPattern (row, column, size);
        }
        cout << "\n";
    }
    return 0;
}

void DisplayDoorPattern (int row, int column, int size) {

    int pattern = 3;
    if ((row / size) % pattern == 1 && (column / size) % pattern == 1) cout << ' ';
    else if (size / pattern == 0) cout << '*';
    else DisplayDoorPattern (row, column, size / pattern);
    return;
}
