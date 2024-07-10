#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {

    int time = 0;
    cin >> time;
    for (int repeat = 0; repeat < time; repeat++) {

        int argument1 = 0, argument2 = 0;
        cin >> argument1 >> argument2;
        cout << argument1 + argument2 << endl;
    }
    return 0;
}
