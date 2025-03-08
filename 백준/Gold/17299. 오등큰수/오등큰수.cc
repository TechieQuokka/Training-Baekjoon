#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> Solution (int* source, int length, unordered_map<int, int>& numberOf);

int main (int argc, char* argv[]) {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int length = 0;
	cin >> length;
	
	unordered_map<int, int> numberOf;
	
	int* source = new int[length];
	for (int index = 0; index < length; index++) {
		
		cin >> source[index];
		numberOf[source[index]]++;
	}
	
	vector<int> result = Solution (source, length, numberOf);
	for (int index = 0; index < length; index++) {
		
		cout << result[index] << " ";
	}
	
	delete[] source;
	return 0;
}

vector<int> Solution (int* source, int length, unordered_map<int, int>& numberOf) {
	
	if (source == NULL) throw;
	
	stack<int> buffer;
	vector<int> result(length, 0);
	for (int index = 0; index < length; buffer.push(index++)) {
		
		if (buffer.empty() ||
			numberOf[source[buffer.top()]] >= numberOf[source[index]]) continue;
		
		while (!buffer.empty()) {
			
			int current = buffer.top();
			if (numberOf[source[current]] >= numberOf[source[index]]) break;
			
			result[current] = source[index];
			buffer.pop();
		}
	}
	
	int size = buffer.size();
	for (int index = 0; index < size; index++) {
		
		result[buffer.top()] = -1;
		buffer.pop();
	}
	return result;
}