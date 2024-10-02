#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

long long Query (vector<long long>& tree, int node, int start, int end, int left, int right);
void Update (vector<long long>& tree, int node, int start, int end, int target, long long value);

/*
6
6 4 3 5 2 1
*/

int main (int argc, char* argv[]) {
	
	int length = 0;
	cin >> length;
	
	vector<long long> buffer(length);
	
	for (int index = 0; index < length; index++) {
		
		long long value = 0;
		cin >> value;
		
		buffer[index] = value;
	}
	
	vector<long long> compressed = buffer;
	sort(compressed.begin(), compressed.end());
	compressed.erase(unique(compressed.begin(), compressed.end()), compressed.end());
	
	unordered_map<long long, int> index_map;
	int size = compressed.size();
	for (int index = 0; index < size; index++) {
		
		index_map[compressed[index]] = index;
	}
	
	for (int index = 0; index < length; index++) {
		
		buffer[index] = index_map[buffer[index]];
	}
    
    long long height = (long long) ceil (log2 (length));
    long long tree_size = (1LL << (height + 1LL));
    vector<long long> tree (tree_size);
    vector<long long> source (length);
    
    long long count = 0;
    for (int index = 0; index < length; index++) {
    	
    	int position = buffer[index];
    	long long result = Query (tree, 1, 0, length - 1, position + 1, length - 1);
    	count += result;
    	
    	Update (tree, 1, 0, length - 1, buffer[index], 1LL);
	}
	
	cout << count;
	
	return 0;
}

long long Query (vector<long long>& tree, int node, int start, int end, int left, int right) {
	
	if (left > end || right < start) return 0;
	if (start >= left && end <= right) return tree[node];
	
	int middle = (start + end) / 2;
	long long left_sum = Query (tree, node * 2, start, middle, left, right);
	long long right_sum = Query (tree, node * 2 + 1, middle + 1, end, left, right);
	
	return left_sum + right_sum;
}

void Update (vector<long long>& tree, int node, int start, int end, int target, long long value) {
	
	if (target > end || target < start) return;
	
	tree[node] += value;
	if (start == end) return;
	
	int middle = (start + end) / 2;
	Update (tree, node * 2, start, middle, target, value);
	Update (tree, node * 2 + 1, middle + 1, end, target, value);
	return;
}