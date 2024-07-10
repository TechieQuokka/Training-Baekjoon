#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
        
    int time = 0;
    cin >> time;
    for (int loop = 0; loop < time; loop++) {

        int operand1 = 0, operand2 = 0;
        cin >> operand1 >> operand2;
        cout << operand1 + operand2 << "\n";
    }
    return 0;
}
