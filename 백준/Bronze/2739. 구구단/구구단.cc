#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {

    int time = 0;
    cin >> time;

    for (int repeat = 1; repeat < 10; repeat++) {

        cout << time << " * " << repeat << " = " << time * repeat << endl;
    }
    return 0;
}
