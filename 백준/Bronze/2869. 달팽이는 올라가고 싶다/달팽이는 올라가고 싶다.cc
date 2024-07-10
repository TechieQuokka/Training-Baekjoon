#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    int climb = 0, fall = 0, height = 0;
    cin >> climb >> fall >> height;
    
    int result = (height - fall - 1) / (climb - fall) + 1;
    cout << result << endl;
    return 0;
}
