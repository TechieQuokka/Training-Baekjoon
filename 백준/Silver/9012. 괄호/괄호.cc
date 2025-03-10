#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

bool ParenthesisCheck (string source, int length);

int main (int argc, char* argv[]) {
    
    int input = 0;
    cin >> input;
    for (int loop = 0; loop < input; loop++) {
        
        string source;
        cin >> source;
        
        bool result = ParenthesisCheck (source, source.size());
        cout << (result ? "YES" : "NO") << endl;
    }
    return 0;
}

bool ParenthesisCheck (string source, int length) {
    
    stack<char> stack;
    for (int index = 0; index < length; index++) {
        
        char character = source[index];
        if (character == '(') stack.push(character);
        else if (character == ')') {
                
            if (stack.empty()) return false;
            char top = stack.top();
            int result = abs (character - top);
            if (result > 2) return false;
            else stack.pop();
        }
    }
    return stack.empty();
}
