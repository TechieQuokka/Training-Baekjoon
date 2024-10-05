#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

double Solution (string& source, unordered_map<char, double>& table);

int main (int argc, char* argv[]) {

    int length = 0;
    cin >> length;

    string source = "";
    cin >> source;

    char pivot = 'A';
    unordered_map<char, double> table;
    for (int index = 0; index < length; index++) {

        double element = 0;
        cin >> element;
        table[pivot++] = element;
    }

    double result = Solution (source, table);
    cout << fixed << setprecision(2) << result << "\n";
    return 0;
}

bool IsAlphabet (char character) {

    return character >= 'A' && character <= 'Z' || character >= 'a' && character <= 'z';
}

double Operator (double lvalue, double rvalue, char command) {

    switch (command) {
        case '*': return lvalue * rvalue;
        case '/': return lvalue / rvalue;
        case '+': return lvalue + rvalue;
        default: return lvalue - rvalue;
    }
}

double Solution (string& source, unordered_map<char, double>& table) {

    stack<double> buffer;
    for (const char& element : source) {
        if (IsAlphabet (element)) {

            buffer.push (table[element]);
            continue;
        }

        double rvalue = buffer.top(); buffer.pop();
        double lvalue = buffer.top(); buffer.pop();

        double result = Operator (lvalue, rvalue, element);
        buffer.push (result);
    }

    return buffer.top();
}