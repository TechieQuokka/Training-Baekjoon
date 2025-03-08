#include <iostream>
#include <vector>

using namespace std;

long long Solution (vector<long long>& source, long long length, long long target);

int main (int argc, char* argv[]) {
	
	vector<long long> buffer;
	
	long long length = 0, target = 0;
	cin >> length >> target;
	
	for (long long index = 0; index < length; index++) {
		
		long long element = 0;
		cin >> element;
		buffer.push_back(element);
	}
	buffer.push_back(0);
	
	cout << Solution (buffer, length, target);
	return 0;
}

long long Solution (vector<long long>& source, long long length, long long target) {
	
	long long sum = 0, left = 0, right = 0;
	long long minimum_size = 100000001;
	while (right <= length) {
		if (sum < target) {
			
			sum += source[right++];
			continue;
		}
		if ((right - left) < minimum_size) {
			
			minimum_size = right - left;
		}
		sum -= source[left++];
	}
	return minimum_size == 100000001 ? 0 : minimum_size;
}