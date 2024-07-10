#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {

    int input = 0;
    cin >> input;

    for (int repeat = 0; repeat < input; repeat++) {

        int lvalue = 0, rvalue = 0;
        cin >> lvalue >> rvalue;
        cout << "Case #" << repeat + 1 << ": " << lvalue + rvalue << endl;
    }
    return 0;
}
