#include <iostream>
#include <stack>

using namespace std;

struct DataType {
	
	int Value;
	long long int NumberOf;
};

long long int Solution (int* source, int length);

int main (int argc, char* argv[]) {
	
	int length = 0;
	cin >> length;
	int* source = new int[length];
	if (source == NULL) throw;
	
	for (int index = 0; index < length; index++) {
		
		scanf("%d", source + index);
	}
	
	long long int count = Solution (source, length);
	cout << count;
	
	delete[] source;
	return 0;
}

long long int Solution (int* source, int length) {
	
	if (source == NULL) return -1;
	
	long long int count = 0LL;
	stack<struct DataType> buffer;
	for (int index = 0; index < length; index++) {
		
		long long int duplicate = 1LL;
		int element = source[index];
		if (buffer.empty()) {
			
			buffer.push({element, duplicate});
			continue;
		}
		
		struct DataType top = buffer.top();
		while (top.Value <= element) {
			
			buffer.pop();
			count += top.NumberOf;
			if (top.Value == element) duplicate += top.NumberOf;
			
			if (buffer.empty()) break;
			top = buffer.top();
		}
		buffer.push({element, duplicate});
		count += (long long int)(top.Value > element);
	}
	
	return count;
}