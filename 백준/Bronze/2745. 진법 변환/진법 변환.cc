#include <iostream>
#include <cstring>

using namespace std;

int ToDecimal (string source, int base);
int ToNumber (char character);

int main (int argc, char* argv[]) {
    
    string source; int base = 0;
    cin >> source >> base;
    cout << ToDecimal (source, base) << endl;
    return 0;
}

int ToNumber (char character) {
    
    if (character >= 'A') return character - 'A' + 10;
    return character - '0';
}

int ToDecimal (string source, int base) {
    
    int result = 0, increase = 1;
    for (int index = source.size() - 1; index >= 0; index--, increase *= base) {
        
        result += ToNumber (source[index]) * increase;
    }
    return result;
}
