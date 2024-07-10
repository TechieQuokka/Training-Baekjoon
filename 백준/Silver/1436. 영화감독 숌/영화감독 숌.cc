#include <iostream>

using namespace std;

unsigned int GetTitleNumber (unsigned int number);

int main (int argc, char* argv[]) {
    
    unsigned int input = 0U;
    cin >> input;
    
    cout << GetTitleNumber (input) << endl;
    return 0;
}

unsigned int GetTitleNumber (unsigned int number) {
    
    unsigned int endNumber = 665U;
    for (unsigned int increase = 0U; increase != number; endNumber++) {
        for (unsigned int buffer = endNumber; buffer != 0; buffer /= 10U) {
            if (buffer % 1000U == 666U) {
                
                increase++;
                break;
            }
                    
        }
    }
    return endNumber - 1;
}