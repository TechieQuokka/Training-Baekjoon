#include <iostream>
#include <stack>

using namespace std;

void Solution (int* source, int length);

int main (int argc, char* argv[]) {
	
	int size = 0;
	scanf ("%d", &size);
	int* buffer = new int[size];
	
	for (int index = 0; index < size; index++) {
		
		scanf ("%d", buffer + index);
	}
	
	Solution (buffer, size);
	
	for (int index = 0; index < size; index++) {
		
		printf ("%d ", buffer[index]);
	}
	delete[] buffer;
	return 0;
}

void Display (int* source, int length) {
	
	if (source == NULL) return;
	
	for (int index = 0; index < length; index++) {
		
		printf ("%d ", source[index]);
	}
	printf ("\n");
	return;
}

void Solution (int* source, int length) {
	
	if (source == NULL) return;
	
	stack<int> buffer;
	
	for (int index = 0; index < length; buffer.push(index++)) {
		
		if (buffer.empty() || source[buffer.top()] > source[index]) continue;
		
		while (!buffer.empty()) {
			
			int current = buffer.top();
			if (source[current] >= source[index]) break;
			
			source[current] = source[index];
			buffer.pop();
		}
	}
	
	int size = buffer.size();
	for (int index = 0; index < size; index++) {
		
		source[buffer.top()] = -1;
		buffer.pop();
	}
	return;
}