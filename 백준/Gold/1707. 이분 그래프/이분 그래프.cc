#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

struct NodeType {
	
	vector<int> vertex;
	bool isVisited;
	int depth;
};

bool BreadthFirstSearch (struct NodeType* nodes, int current);
void Initialize (struct NodeType* nodes, int numberOfVertex);

int main (int argc, char* argv[]) {
	
	int numberOfVertex = 0, numberOfEdge = 0;
	struct NodeType* nodes = new struct NodeType[20001];
	if (nodes == NULL) throw;
	
	int count = 0;
	cin >> count;
	for (int repeat = 0; repeat < count; repeat++) {
		
		cin >> numberOfVertex >> numberOfEdge;
		Initialize(nodes, numberOfVertex);
		for (int index = 0; index < numberOfEdge; index++) {
		
			int vertex_u = 0, vertex_v = 0;
			cin >> vertex_u >> vertex_v;
			nodes[vertex_u - 1].vertex.push_back(vertex_v - 1);
			nodes[vertex_v - 1].vertex.push_back(vertex_u - 1);
		}
		
		bool result = false;
		for (int vertex = 0; vertex < numberOfVertex; vertex++) {
			
			result = BreadthFirstSearch (nodes, vertex);
			if (result == false) break;
		}
		cout << (result ? "YES" : "NO") << "\n";
	}
	
	delete[] nodes;
	return 0;
}

void Initialize (struct NodeType* nodes, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	for (int index = 0; index < numberOfVertex; index++) {
		
		nodes[index].isVisited = false;
		nodes[index].depth = 0;
		nodes[index].vertex.clear();
	}
	return;
}

bool BreadthFirstSearch (struct NodeType* nodes, int current) {
	
	if (nodes == NULL) throw;
	
	queue<pair<int, int>> buffer;
	buffer.push({current, 0});
	
	while(!buffer.empty()) {
		
		pair<int, int> current = buffer.front(); buffer.pop();
		if (nodes[current.first].isVisited == true) continue;
		
		nodes[current.first].isVisited = true;
		nodes[current.first].depth = current.second;
		
		for (const auto& element : nodes[current.first].vertex) {
			
			if (nodes[element].isVisited && nodes[element].depth == current.second) return false;
			buffer.push({element, current.second + 1});
		}
	}
	return true;
}