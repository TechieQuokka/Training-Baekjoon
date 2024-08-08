#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
#include <cstring>

using namespace std;

struct VertexType {
	
	int Number;
	int Weight;
	
	VertexType(int number, int weight) : Number(number), Weight(weight) { }
	
	bool operator<(const struct VertexType vertex) const {
		return this->Weight > vertex.Weight;
	}
};

struct NodeType {
	
	vector<struct VertexType> Element;
	bool IsVisited;
};

vector<int> DijkstraAlgorithm (struct NodeType* nodes, int numberOfVertex, int start);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false); 
	cin.tie(NULL); 
	cout.tie(NULL);
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	int startPoint = 0;
	cin >> startPoint;
	
	struct NodeType* nodes = new struct NodeType[vertex];
	if (nodes == NULL) throw;
	
	memset ((struct NodeType*) nodes, 0, vertex * sizeof (struct NodeType));
	
	for (int index = 0; index < edge; index++) {
		
		int start = 0, end = 0, weight = 0;
		cin >> start >> end >> weight;
		
		nodes[start - 1].Element.push_back (VertexType (end - 1, weight));
	}
	
	vector<int> result = DijkstraAlgorithm (nodes, vertex, startPoint - 1);
	for (const auto& element : result) {
		
		if (element == INT_MAX) cout << "INF" << "\n";
		else cout << element << "\n";
	}
	
	delete[] nodes;
	return 0;
}

vector<int> DijkstraAlgorithm (struct NodeType* nodes, int numberOfVertex, int start) {
	
	if (nodes == NULL) throw;
	
	vector<int> cost(numberOfVertex, INT_MAX);
	
	priority_queue<struct VertexType> buffer;
	buffer.push(VertexType(start, 0));
	while(!buffer.empty()) {
		
		struct VertexType current = buffer.top(); buffer.pop();
		
		int number = current.Number;
		if (nodes[number].IsVisited == true) continue;
		nodes[number].IsVisited = true;
		
		cost[number] = current.Weight;
				
		for (const auto& element : nodes[number].Element) {
			
			buffer.emplace(VertexType(element.Number, current.Weight + element.Weight));
		}
	}
	
	return cost;
}