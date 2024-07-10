#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    int input = 0;
    cin >> input;
    
    for (int repeat = 0; repeat < input; repeat++) {
        for (int space = input - repeat - 1; space; space--) {
            
            cout << " ";
        }
        for (int star = repeat * 2 + 1; star; star--) {
            
            cout << "*";
        }
        cout << "\n";
    }
    
    for (int repeat = input; repeat > 1; repeat--) {
        for (int space = input - repeat + 1; space; space--) {
            
            cout << " ";
        }
        for (int star = (repeat - 1) * 2 - 1; star; star--) {
            
            cout << "*";
        }
        cout << "\n";
    }
    return 0;
}
