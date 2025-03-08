#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

vector<bool> Solution (vector<int>& pendulums);

int main (int argc, char* argv[]) {
	
	vector<int> pendulums;
	
	int length = 0;
	cin >> length;
	for (int index = 0; index < length; index++) {
		
		int weight = 0;
		cin >> weight;
		pendulums.push_back(weight);
	}
	
	auto result = Solution (pendulums);
	
	cin >> length;
	for (int repeat = 0; repeat < length; repeat++) {
		
		int target = 0;
		cin >> target;
		cout << (result[target] ? 'Y' : 'N') << " ";
	}
	return 0;
}

int Subtract (int argument1, int argument2) {
	
	if (argument1 < argument2) return argument2 - argument1;
	return argument1 - argument2;
}

vector<bool> Solution (vector<int>& pendulums) {
	
	int sum = accumulate (pendulums.begin(), pendulums.end(), 0);
	int length = pendulums.size();
	
	vector<vector<bool>> result (length, vector<bool> (sum + *max_element (pendulums.begin(), pendulums.end()) + 1, false));
	
	for (int index = 0; index < length; index++) {
		
		int current = pendulums[index];
		for (int pivot = 0; pivot <= sum; pivot++) {
			
			bool state = current == pivot;
			result[index][pivot] = state;
			
			if (index - 1 < 0) continue;
			
			state |= result[index - 1][pivot];
			state |= result[index - 1][Subtract (current, pivot)];
			state |= result[index - 1][current + pivot];
			
			result[index][pivot] = state;
		}
	}
	
	return result[length - 1];
}