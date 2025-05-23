#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct NodeType {
	
	vector<int> vertex;
	bool isVisited;
};

vector<int>& DepthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex);
vector<int>& BreadthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex);
void ClearVisit (struct NodeType* nodes, int numberOfVertex);

int main (int argc, char* argv[]) {
	
	int numberOfVertex = 0, numberOfEdge = 0, start = 0;
	cin >> numberOfVertex >> numberOfEdge >> start;
	
	struct NodeType* nodes = new struct NodeType[numberOfVertex];
	if (nodes == NULL) throw;
	
	memset ((struct NodeType*) nodes, 0, numberOfVertex * sizeof (struct NodeType));
	
	for (int index = 0; index < numberOfEdge; index++) {
		
		int vertex_u = 0, vertex_v = 0;
		cin >> vertex_u >> vertex_v;
		nodes[vertex_u - 1].vertex.push_back(vertex_v - 1);
		nodes[vertex_v - 1].vertex.push_back(vertex_u - 1);
	}
	
	for (int index = 0; index < numberOfVertex; index++) {
		
		vector<int>& element = nodes[index].vertex;
		sort (element.begin(), element.end()); // ascending
	}
	
	vector<int>& result = DepthFirstSearch (nodes, start - 1, numberOfVertex);
	cout << endl;
	
	ClearVisit (nodes, numberOfVertex);
	
	result = BreadthFirstSearch (nodes, start - 1, numberOfVertex);
	cout << endl;
	
	delete[] nodes;
	return 0;
}

void ClearVisit (struct NodeType* nodes, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	for (int index = 0; index < numberOfVertex; index++) {
		
		nodes[index].isVisited = false;
	}
	return;
}

vector<int>& BreadthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	static vector<int> buffer(numberOfVertex, 0);
	int count = 1;
	
	queue<int> vertexQueue;
	vertexQueue.push(current);
	
	while (!vertexQueue.empty()) {
		
		int index = vertexQueue.front(); vertexQueue.pop();
		struct NodeType& node = nodes[index];
		
		if (node.isVisited == true) continue;
		node.isVisited = true;
		
		cout << index + 1 << " ";
		
		buffer[index] = count++;
		
		for (const auto& element : node.vertex) {
			
			vertexQueue.push(element);
		}
	}
	
	return buffer;
}

vector<int>& DepthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	static vector<int> buffer(numberOfVertex, 0);
	static int count = 1;
	
	vector<int>& result = buffer;
	
	struct NodeType& node = nodes[current];
	if (node.isVisited == true) return result;
	node.isVisited = true;
	
	cout << current + 1 << " ";
	result[current] = count++;
	
	vector<int>& vertex = node.vertex;
	for (const auto& element : vertex) {
		
		result = DepthFirstSearch (nodes, element, numberOfVertex);
	}
	return result;
}