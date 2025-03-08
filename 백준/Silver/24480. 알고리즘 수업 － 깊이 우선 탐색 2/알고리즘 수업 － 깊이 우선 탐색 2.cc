#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

struct NodeType {
	
	vector<int> vertex;
	bool isVisited;
};

vector<int>& DepthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex);

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
		sort (element.begin(), element.end(), greater<int>()); // ascending
	}
	
	vector<int>& result = DepthFirstSearch (nodes, start - 1, numberOfVertex);
	for (const auto& element : result) {
		
		cout << element << "\n";
	}
	
	delete[] nodes;
	return 0;
}

vector<int>& DepthFirstSearch (struct NodeType* nodes, int current, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	static vector<int> buffer(numberOfVertex, 0);
	static int count = 1;
	
	vector<int>& result = buffer;
	
	struct NodeType& node = nodes[current];
	if (node.isVisited == true) return result;
	
	result[current] = count++;
	
	node.isVisited = true;
	
	vector<int>& vertex = node.vertex;
	for (const auto& element : vertex) {
		
		result = DepthFirstSearch (nodes, element, numberOfVertex);
	}
	return result;
}