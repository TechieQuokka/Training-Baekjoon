#include <iostream>
#include <vector>
#include <algorithm>

#define SIZE 30

using namespace std;

vector<long long> CollectSumOfElements (vector<long long>& source);
long long Solution (vector<long long>& left, vector<long long>& right, long long weight);

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	//vector<long long> source = { 1, 2, 3, 4, 5, 6, 7, 8 };
	vector<long long> source;
	
	long long length = 0, weight = 0;
	cin >> length >> weight;
	
	for (long long index = 0; index < length; index++) {
		
		long long data = 0;
		cin >> data;
		
		source.push_back(data);
	}
	
	long long half = source.size() / 2;
	vector<long long> leftSource (source.begin(), source.begin() + half);
	vector<long long> rightSource (source.begin() + half, source.end());
	
	auto left = CollectSumOfElements (leftSource);
	sort(left.begin(), left.end());
//	for (const auto& element : left) {
//		
//		cout << element << " ";
//	}
//	cout << endl;
	
	auto right = CollectSumOfElements (rightSource);
	sort(right.begin(), right.end());
//	for (const auto& element : right) {
//		
//		cout << element << " ";
//	}
//	cout << endl;
	
	cout << Solution (left, right, weight);
	return 0;
}

//8 10
//1 2 3 4 5 6 7 8

long long Solution (vector<long long>& left, vector<long long>& right, long long weight) {
	
	long long count = 0;
	
	long long leftLength = left.size();
	for (const auto& pivot : right) {
		
		if (pivot > weight) break;
		
		long long start = 0, end = leftLength;
		long long middle = 0;
		while (start < end) {
			
			middle = (start + end) / 2;
			if (left[middle] + pivot > weight) {
				
				end = middle;
			}
			else start = middle + 1;
		}
		
		count += end;
		//cout << middle + 1 << " : " << left[middle] << endl;
	}
	return count;
}

void Display (vector<long long>& source, long long length) {
	
	for (long long index = 0; index < length; index++) {
		
		cout << source[index] << " ";
	}
	cout << '\n';
	return;
}

long long Sum (vector<long long>& source, vector<long long>& buffer, long long size) {
	
	long long result = 0;
	for (long long index = 0; index < size; index++) {
		
		result += source[buffer[index]];
	}
	return result;
}

void Combination (vector<long long>& source, vector<long long>& outResult, long long current, long long width, long long depth, long long size) {
	
	static vector<long long> buffer (SIZE);
	
	if (current == width) {
		
		outResult.push_back (Sum (source, buffer, width));
		return;
	}
	if (depth == size) return;
	
	buffer[current] = depth;
	Combination (source, outResult, current + 1, width, depth + 1, size);
	Combination (source, outResult, current, width, depth + 1, size);
	return;
}

vector<long long> CollectSumOfElements (vector<long long>& source) {
	
	vector<long long> result;
	result.push_back(0);
	long long length = source.size();
	
	for (long long width = 1; width <= length; width++) {
		
		Combination (source, result, 0, width, 0, length);
	}
	
	return result;
}