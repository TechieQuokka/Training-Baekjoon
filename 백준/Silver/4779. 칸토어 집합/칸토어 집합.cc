#include <iostream>
#include <cmath>

using namespace std;

void Cantor (int number);

int main (int argc, char* argv[]) {
    
    int number = 0;
    while (cin >> number){
        
        Cantor (number);
        cout << "\n";
    }
    return 0;
}

void Cantor (int number) {
    
    int size = pow(3, number - 1);
    if (number == 0) {
        
        cout << '-';
        return;
    }
    
    Cantor (number - 1);
    for (int repeat = 0; repeat < size; repeat++) {
        
        cout << " ";
    }
    Cantor (number - 1);
    return;
}
