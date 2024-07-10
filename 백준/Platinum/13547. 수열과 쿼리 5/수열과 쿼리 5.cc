#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct ElementType {
	
	int start;
	int end;
	int index;
};

int square_root = 0;

bool Compare (struct ElementType left, struct ElementType right) {
	
	if (left.start/square_root != right.start/square_root) return left.start / square_root < right.start / square_root;
	return left.end < right.end;
}

void Increment (vector<int>& sequence, vector<int>& counter, int& current, int start, int end);
void Decrement (vector<int>& sequence, vector<int>& counter, int& current, int start, int end);

int main (int argc, char* argv[]) {
	
	int sequence_size;
	cin >> sequence_size;
	
	square_root = (int) sqrt (sequence_size);
	
	vector<int> sequence;
	for (int index = 0; index < sequence_size; index++) {
		
		int element = 0;
		cin >> element;
		sequence.push_back(element);
	}
	
//	for (const auto& element : sequence) {
//		
//		cout << element << " ";
//	}
//	cout << endl;
	
	vector<struct ElementType> query_list;
	
	int query = 0;
	cin>> query;
	for (int index = 0; index < query; index++) {
		
		int start = 0, end = 0;
		cin >> start >> end;
		
		query_list.push_back({start - 1, end - 1, index});
	}
	
	sort (query_list.begin(), query_list.end(), &Compare);
	
//	for (const auto& element : query_list) {
//		
//		cout <<  element.start << ", " << element.end << ", " << element.index << endl;
//	}
	
	vector<int> counter (1001000, 0);
	int current = 0;
	
	int left = query_list[0].start, right = query_list[0].end;
	Increment (sequence, counter, current, query_list[0].start, query_list[0].end);
//	
//	for (const auto& element : counter) {
//		
//		cout << element + 1000 << endl;
//	}
	
	vector<int> result (query, 0);
	result[query_list[0].index] = current;
	
	//cout << left << " , " << right << endl;
	
//	for (const auto& element : counter) {
//		
//		cout << element << " ";
//	}
//	cout << endl;
	
	for (int index = 1; index < query; index++) {
		
		int pivot_left = query_list[index].start, pivot_right = query_list[index].end;
		
		while (pivot_left < left) {
			if (counter[sequence[--left]]++ == 0) current++;
		}
		
		while (pivot_left > left) {
			if (--counter[sequence[left++]] == 0) current--;
		}
		
		while (pivot_right > right) {
			if (counter[sequence[++right]]++ == 0) current++;
		}
		
		while (pivot_right < right) {
			if (--counter[sequence[right--]] == 0) current--;
		}
		
		result[query_list[index].index] = current;
	}
	
	for (const auto& element : result) {
		
		cout << element << "\n";
	}
	return 0;
}

void Increment (vector<int>& sequence, vector<int>& counter, int& current, int start, int end) {
		
	for (int index = start; index <= end; index++) {
		
		if (counter[sequence[index]]++ == 0) current++;
	}
	return;
}

void Decrement (vector<int>& sequence, vector<int>& counter, int& current, int start, int end) {
		
	for (int index = start; index <= end; index++) {
		
		if (--counter[sequence[index]] == 0) current--;
	}
	return;
}