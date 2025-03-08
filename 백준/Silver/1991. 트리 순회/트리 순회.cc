#include <iostream>
#include <vector>

using namespace std;

void PreOrder (vector<vector<int>>& tree, int current);
void InOrder (vector<vector<int>>& tree, int current);
void PostOrder (vector<vector<int>>& tree, int current);

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int length = 0;
	cin >> length;
	vector<vector<int>> tree(26);
	
	for (int index = 0; index < length; index++) {
		
		char parent = 0, leftChild = 0, rightChild = 0;
		cin >> parent >> leftChild >> rightChild;
		
		tree[parent - 'A'].push_back(leftChild - 'A');
		tree[parent - 'A'].push_back(rightChild - 'A');
	}
	
	PreOrder (tree, 0); cout << '\n';
	InOrder (tree, 0); cout << '\n';
	PostOrder (tree, 0); cout << '\n';
	return 0;
}

void PreOrder (vector<vector<int>>& tree, int current) {
	
	if (tree[current].empty()) return;
	
	cout << (char)(current + 'A');
	PreOrder (tree, tree[current][0]);
	PreOrder (tree, tree[current][1]);
	return;
}

void InOrder (vector<vector<int>>& tree, int current) {
	
	if (tree[current].empty()) return;
	
	InOrder (tree, tree[current][0]);
	cout << (char)(current + 'A');
	InOrder (tree, tree[current][1]);
	return;
}

void PostOrder (vector<vector<int>>& tree, int current) {
	
	if (tree[current].empty()) return;
	
	PostOrder (tree, tree[current][0]);
	PostOrder (tree, tree[current][1]);
	cout << (char)(current + 'A');
	return;
}