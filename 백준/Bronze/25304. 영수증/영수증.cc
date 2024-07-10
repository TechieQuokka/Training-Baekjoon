#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {

    int total = 0, count = 0;
    cin >> total >> count;

    int sum = 0;
    for (int loop = 0; loop < count; loop++) {

        int price = 0, numberOf = 0;
        cin >> price >> numberOf;
        sum += price * numberOf;
    }

    cout << (total == sum ? "Yes" : "No") << endl;
    return 0;
}
