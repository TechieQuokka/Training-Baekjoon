#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <cstring>

using namespace std;

struct VertexType {
	
	int Number;
	int Weight;
	
	VertexType (int number, int weight) : Number (number), Weight (weight) { }
	
	bool operator < (const struct VertexType vertex) const {
		
		return this->Weight > vertex.Weight;
	}
};

struct NodeType {
	
	vector<struct VertexType> Element;
	bool IsVisited;
};

int DijkstraAlgorithm (struct NodeType* nodes, int start, int end);
void ClearVisit (struct NodeType* nodes, int length);
void ChangeTool (struct NodeType* nodes, int road1, int road2);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false); 
	cin.tie(NULL); 
	cout.tie(NULL);
	
	int testcase = 2;
	cin >> testcase;
	for (int loop = 0; loop < testcase; loop++) {
		
		int vertex = 0, edge = 0, destination = 0;
		cin >> vertex >> edge >> destination;
		
		int start = 0, road1 = 0, road2 = 0;
		cin >> start >> road1 >> road2;
		
		struct NodeType* graph = new struct NodeType[vertex];
		if (graph == NULL) throw;
		
		memset ((struct NodeType*) graph, 0, vertex * sizeof (struct NodeType));
		
		for (int repeat = 0; repeat < edge; repeat++) {
			
			int vertex1 = 0, vertex2 = 0, weight = 0;
			cin >> vertex1 >> vertex2 >> weight;
			
			struct NodeType& first = graph[vertex1 - 1];
			first.Element.push_back(VertexType(vertex2 - 1, weight * 2));
			first.IsVisited = false;
			
			struct NodeType& second = graph[vertex2 - 1];
			second.Element.push_back(VertexType(vertex1 - 1, weight * 2));
			second.IsVisited = false;
		}
		
		ChangeTool (graph, road1 - 1, road2 - 1);
		ChangeTool (graph, road2 - 1, road1 - 1);
		
		vector<int> targets;
		for (int index = 0; index < destination; index++) {
			
			int target = 0;
			cin >> target;
			
			targets.push_back(target);
		}
		sort(targets.begin(), targets.end());
		
		for (const auto& target : targets) {
			
			int weight = DijkstraAlgorithm (graph, start - 1, target - 1);
			if (weight != INT_MAX && weight % 2 != 0) cout << target << " ";
			ClearVisit (graph, vertex);
		}
		cout << "\n";
		
		delete[] graph;
	}
	return 0;
}

int DijkstraAlgorithm (struct NodeType* nodes, int start, int end) {
	
	if (nodes == NULL) throw;
	
	priority_queue<struct VertexType> buffer;
	buffer.push(VertexType(start, 0));
	while(!buffer.empty()) {
		
		struct VertexType current = buffer.top(); buffer.pop();
		if (nodes[current.Number].IsVisited == true) continue;
		nodes[current.Number].IsVisited = true;
		
		if (current.Number == end) return current.Weight;
		
		for (const auto& node : nodes[current.Number].Element) {
			
			buffer.push(VertexType(node.Number, node.Weight + current.Weight));
		}
	}
	
	return INT_MAX;
}

void ChangeTool (struct NodeType* nodes, int road1, int road2) {
	
	vector<struct VertexType>& node = nodes[road1].Element;
	for (auto& vertex : node) {
		if (vertex.Number == road2) {
			
			vertex.Weight--;
			break;
		}
	}
	return;
}

void ClearVisit (struct NodeType* nodes, int length) {
	
	if (nodes == NULL) throw;
	
	for (int index = 0; index < length; index++) {
		
		nodes[index].IsVisited = false;
	}
	return;
}