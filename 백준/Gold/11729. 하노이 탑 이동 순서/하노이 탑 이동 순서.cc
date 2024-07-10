#include <iostream>

using namespace std;

void TowerOfHanoi (int numberOfDisk, char from, char temporary, char to);

int main (int argc, char* argv[]) {
    
    int number = 0;
    cin >> number;
    
    cout << (0x1 << number) - 0x1 << "\n";
    TowerOfHanoi (number, '1', '3', '2');
    return 0;
}

void TowerOfHanoi (int numberOfDisk, char from, char temporary, char to) {
    
    if (numberOfDisk == 1) cout << from << " " << temporary << "\n";
    else {
        
        TowerOfHanoi (numberOfDisk - 1, from, to, temporary);
        cout << from << " " << temporary << "\n";
        TowerOfHanoi (numberOfDisk - 1, to, temporary, from);
    }
    return;
}
