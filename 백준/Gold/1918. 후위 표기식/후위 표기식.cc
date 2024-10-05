#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;

string ToPostfix (string& infix);

int main (int argc, char* argv[]) {
	
	string infix = "";
	cin >> infix;
	
	cout << ToPostfix (infix);
	
	return 0;
}

bool IsAlphabet (char character) {
	
	return character >= 'A' && character <= 'Z' || character >= 'a' && character <= 'z';
}

string ToPostfix (string& infix) {
	
	vector<char> result;
	stack<char> buffer;
	unordered_map<char, int> table = { {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1} };
	
	for (const auto& element : infix) {
		
		if (IsAlphabet (element)) {
			
			result.push_back(element);
		}
		else if (table.find(element) == table.end()) {
			while (buffer.top() != '(') {
				
				result.push_back (buffer.top());
				buffer.pop();
			}
			buffer.pop();
		}
		else {
			if (buffer.empty() || element == '(') {
				
				buffer.push (element);
				continue;
			}
			
			while (!buffer.empty() && table[element] <= table[buffer.top()]) {
				
				result.push_back (buffer.top());
				buffer.pop();
			}
			buffer.push (element);
		}
	}
	
	while (!buffer.empty()) {
		
		result.push_back (buffer.top());
		buffer.pop();
	}
	
	return string(result.begin(), result.end());
}