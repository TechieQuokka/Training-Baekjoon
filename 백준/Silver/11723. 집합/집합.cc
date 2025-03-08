#include <iostream>
#include <set>

using namespace std;

int main (int argc, char* argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    set<int> buffer;

    int length = 0;
    cin >> length;

    for (int repeat = 0; repeat < length; repeat++) {

        string command = "";
        int value = 0;
        cin >> command;
        if (command == "add") {

            cin >> value;
            buffer.insert(value);
        }
        else if (command == "remove") {

            cin >> value;
            buffer.erase(value);
        }
        else if (command == "check") {

            cin >> value;
            cout << (buffer.find(value) != buffer.end()) << "\n";
        }
        else if (command == "toggle") {

            cin >> value;
            if (buffer.find(value) == buffer.end()) buffer.insert(value);
            else buffer.erase(value);
        }
        else if (command == "all") {
            for (int number = 1; number < 21; number++) {

                buffer.insert(number);
            }
        }
        else {

            buffer.clear();
        }
    }
    return 0;
}