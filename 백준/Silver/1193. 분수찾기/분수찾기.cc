#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    int number = 0;
    cin >> number;
    
    int pivot = 0;
    for (pivot = 1; pivot < number; pivot++) {
        
        number -= pivot;
    }
    
    if (pivot % 2 == 1) cout << pivot + 1 - number << '/' << number << endl;
    else cout << number << '/' << pivot + 1 - number << endl;
    return 0;
}
