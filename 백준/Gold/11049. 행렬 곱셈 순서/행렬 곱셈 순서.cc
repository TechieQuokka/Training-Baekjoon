#include <iostream>
#include <limits.h>

using namespace std;

int MemoizedMatrixChain (int* dimension, int size);

int main (int argc, char* argv[]) {
	
	int size = 0;
	cin >> size;
	
	int* dimension = new int[size + 1];
	if (dimension == NULL) return -1;
	
	for (int index = 0; index < size; index++) {
		
		int row = 0, column = 0;
		cin >> row >> column;
		dimension[index] = row;
		dimension[index + 1] = column;
	}
	
	int minimum = MemoizedMatrixChain (dimension, size + 1);
	cout << minimum;
	
	delete[] dimension;
	return 0;
}

int LookUp_Chain (int cost[512][512], int* dimension, int left, int right) {
	
	if (cost[left][right] < INT_MAX) return cost[left][right];
	if (left == right) cost[left][right] = 0;
	else {
		for (int index = left; index < right; index++) {
		
			int calculate = LookUp_Chain (cost, dimension, left, index)
				+ LookUp_Chain (cost, dimension, index + 1, right)
				+ (dimension[left - 1] * dimension[index] * dimension[right]);
				
			if (calculate < cost[left][right]) cost[left][right] = calculate;
		}
	}
	
	return cost[left][right];
}

int MemoizedMatrixChain (int* dimension, int size) {
	
	int cost[512][512] = { 0, };
	int length = size;
	for (int row = 1; row < length; row++) {
		for (int column = row; column < length; column++) {
			
			cost[row][column] = INT_MAX;
		}
	}
	
	return LookUp_Chain (cost, dimension, 1, length - 1);
}