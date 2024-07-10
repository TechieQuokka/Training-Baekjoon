#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    int integer = 0;
    cin >> integer;
    
    integer /= 4;
    for (int loop = 0; loop < integer; loop++) {
        
        cout << "long ";
    }
    cout << "int\n";
    return 0;
}
