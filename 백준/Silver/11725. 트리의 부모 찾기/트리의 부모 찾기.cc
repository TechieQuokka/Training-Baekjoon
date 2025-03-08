#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct NodeType {
	
	vector<int> Vertex;
	bool IsVisited;
	int Parent;
};

void DepthFirstSearch (vector<struct NodeType>& nodes, int root);

int main (int argc, char* argv[]) {
	
	int edge = 0;
	scanf ("%d", &edge);
	
	vector<struct NodeType> nodes(edge + 1);
	
	for (int repeat = 0; repeat < edge - 1; repeat++) {
		
		int vertex1 = 0, vertex2 = 0;
		scanf ("%d%d", &vertex1, &vertex2);
		
		nodes[vertex1].Vertex.push_back (vertex2);
		nodes[vertex2].Vertex.push_back (vertex1);
	}
	
	DepthFirstSearch (nodes, 1);
	
	for (int index = 2; index < edge + 1; index++) {
		
		printf ("%d\n", nodes[index].Parent);
	}
	
	return 0;
}

void DepthFirstSearch (vector<struct NodeType>& nodes, int root) {
	
	queue<pair<int, int>> buffer;
	buffer.push({root, -1}); // root, -inf
	
	while (!buffer.empty()) {
		
		const auto& current = buffer.front(); buffer.pop();
		int index = current.first;
		int parent = current.second;
		
		if (nodes[index].IsVisited == true) continue;
		
		nodes[index].IsVisited = true;
		nodes[index].Parent = parent;
		
		for (const auto& element : nodes[index].Vertex) {
			
			buffer.push({element, index});
		}
	}
	
	return;
}