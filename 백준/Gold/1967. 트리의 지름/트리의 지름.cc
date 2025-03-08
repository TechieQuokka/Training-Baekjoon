#include <iostream>
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

struct ElementType {
	
	int Number;
	int Weight;
};

struct TreeNodeType {
	
	vector<struct ElementType> Vertex;
	int Accumulate;
	bool IsVisited;
};

void UpdateAccumulate (struct TreeNodeType* tree, int start);
void Clear (struct TreeNodeType* tree, int length);
pair<int, int> Find (struct TreeNodeType* tree, int length);

int main (int argc, char* argv[]) {
	
	int edge;
	cin >> edge;
	
	struct TreeNodeType* tree = new struct TreeNodeType[edge + 1];
	if (tree == NULL) throw;
	
	memset ((struct TreeNodeType*) tree, 0, (edge + 1) * sizeof (struct TreeNodeType));
	
	for (int index = 0; index < edge - 1; index++) {
		
		int parent = 0, child = 0, length = 0;
		cin >> parent >> child >> length;
		
		tree[parent].Vertex.push_back({child, length});
		tree[child].Vertex.push_back({parent, length});
	}
	
	UpdateAccumulate (tree, 1);
	auto result = Find (tree, edge);
	
	Clear (tree, edge);
	UpdateAccumulate (tree, result.first);
	result = Find (tree, edge);
	cout << result.second << "\n";
	
	delete[] tree;
	return 0;
}

void Clear (struct TreeNodeType* tree, int length) {
	
	if (tree == NULL) throw;
	
	for (int index = 0; index < length; index++) {
		
		auto& element = tree[index + 1];
		element.Accumulate = 0;
		element.IsVisited = false;
	}
	return;
}

pair<int, int> Find (struct TreeNodeType* tree, int length) {
	
	if (tree == NULL) throw;
	
	pair<int, int> result = { -999999, -999999 };
	
	for (int index = 0; index < length; index++) {
		
		if (tree[index + 1].Accumulate > result.second) {
			
			result.first = index + 1;
			result.second = tree[index + 1].Accumulate;
		}
	}
	return result;
}

void UpdateAccumulate (struct TreeNodeType* tree, int start) {
	
	if (tree == NULL) throw;
	
	stack<pair<int, int>> buffer; // start, accumulate
	buffer.push({start, 0});
	
	while (!buffer.empty()) {
		
		auto& element = buffer.top(); buffer.pop();
		int current = element.first, accumulate = element.second;
		
		if (tree[current].IsVisited == true) continue;
		tree[current].IsVisited = true;
		
		tree[current].Accumulate = accumulate;
		
		for (const auto& node : tree[current].Vertex) {
			
			int number = node.Number, weight = node.Weight;
			buffer.push({number, accumulate + weight});
		}
	}
	return;
}