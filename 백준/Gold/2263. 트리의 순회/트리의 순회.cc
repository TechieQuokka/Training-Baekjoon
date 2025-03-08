#include <iostream>
#include <vector>

using namespace std;

void DepthFirstSearch (vector<int>& in_tree, vector<int>& post_tree, int inStart, int inEnd, int postStart, int postEnd);

/*
12
7 3 8 1 9 4 10 0 11 5 2 6
7 8 3 9 10 4 1 11 5 6 2 0

9
8 4 9 2 5 1 6 3 7
8 9 4 5 2 6 7 3 1
*/

int main (int argc, char* argv[]) {
	
	int length = 0;
	cin >> length;
	
	vector<int> in_tree;
	vector<int> post_tree;
	
	for (int index = 0; index < length; index++) {
		
		int node = 0;
		cin >> node;
		in_tree.push_back(node);
	}
	
	for (int index = 0; index < length; index++) {
		
		int node = 0;
		cin >> node;
		post_tree.push_back(node);
	}
	
	DepthFirstSearch (in_tree, post_tree, 0, length - 1, 0, length - 1);
	return 0;
}

int FindElement (vector<int>& in_tree, int target) {
	
	int length = in_tree.size();
	for (int index = 0; index < length; index++) {
		
		if (in_tree[index] == target) return index;
	}
	return -1;
}

void DepthFirstSearch (vector<int>& in_tree, vector<int>& post_tree, int inStart, int inEnd, int postStart, int postEnd) {

	if (inStart > inEnd || postStart > postEnd) return;
	
	int find = FindElement (in_tree, post_tree[postEnd]);
	int left_length = find - inStart;
	int right_length = inEnd - find;
	
	cout << in_tree[find] << " ";
	
	DepthFirstSearch (in_tree, post_tree, inStart, find - 1, postStart, postStart + left_length - 1);
	DepthFirstSearch (in_tree, post_tree, find + 1, inEnd, postEnd - right_length, postEnd - 1);
	return;
}