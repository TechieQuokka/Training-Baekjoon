#include <iostream>
#include <vector>

using namespace std;

int KnapsackProblem (vector<int>& weights, vector<int>& values, int size);

int main (int argc, char* argv[]) {
	
	vector<int> weights;
	vector<int> values;
	int size = 7;
	
	int length = 0;
	cin >> length >> size;
	for (int index = 0; index < length; index++) {
		
		int element = 0;
		cin >> element;
		weights.push_back(element);
	}
	
	for (int index = 0; index < length; index++) {
		
		int element = 0;
		cin >> element;
		values.push_back(element);
	}
	
	int result = KnapsackProblem (weights, values, size);
	cout << result;
	return 0;
}

int KnapsackProblem2 (vector<int>& weights, vector<int>& values, int size) {
	
	int length = weights.size();
	vector<vector<int>> buffer (length + 1, vector<int> (size + 1, 0));
	
	for (int index = 1; index <= length; index++) {
		for (int pivot = 0; pivot <= size; pivot++) {
			
			int weight = weights[index - 1], value = values[index - 1];
			if (pivot < value) buffer[index][pivot] = buffer[index - 1][pivot];
			else buffer[index][pivot] = max (buffer[index - 1][pivot], weight + buffer[index - 1][pivot - value]);
		}
	}
	
	int result = 0;
	for (int index = 0; index <= size; index++) {
		if (buffer[length][index] >= size) {
			
			result = index;
			break;
		}
	}
	return result;
}

int KnapsackProblem (vector<int>& weights, vector<int>& values, int size) {
	
	int length = weights.size();
	vector<int> buffer (10000 + 1);
	
	for (int index = 1; index <= length; index++) {
		for (int pivot = 10000; pivot >= 0; pivot--) {
			
			int weight = weights[index - 1], value = values[index - 1];
			if (pivot >= value) buffer[pivot] = max (buffer[pivot], weight + buffer[pivot - value]);
		}
	}
	
	int result = 0;
	for (int index = 0; index <= 10000; index++) {
		if (buffer[index] >= size) {
			
			result = index;
			break;
		}
	}
	return result;
}