#include <iostream>
#include <queue>
#include <stack>
#include <cstring>
#include <limits.h>

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

long long DijkstraAlgorithm (struct NodeType* nodes, int start, int end);
void ClearNodes (struct NodeType* nodes, int numberOfVertex);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false); 
	cin.tie(NULL); 
	cout.tie(NULL);
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	struct NodeType* nodes = new struct NodeType[vertex];
	if (nodes == NULL) throw;
	
	memset ((struct NodeType*) nodes, 0, vertex * sizeof (struct NodeType));
	
	for (int index = 0; index < edge; index++) {
		
		int start = 0, end = 0, weight = 0;
		cin >> start >> end >> weight;
		
		nodes[start - 1].Element.push_back (VertexType (end - 1, weight));
		nodes[end - 1].Element.push_back (VertexType (start - 1, weight));
	}
	
	int middle1 = 0, middle2 = 0;
	cin >> middle1 >> middle2;
	
	long long sum[2] = { 0 };
	sum[0] += DijkstraAlgorithm (nodes, 1 - 1, middle1 - 1); ClearNodes (nodes, vertex);
	sum[0] += DijkstraAlgorithm (nodes, middle1 - 1, middle2 - 1); ClearNodes (nodes, vertex);
	sum[0] += DijkstraAlgorithm (nodes, middle2 - 1, vertex - 1); ClearNodes (nodes, vertex);
	
	sum[1] += DijkstraAlgorithm (nodes, 1 - 1, middle2 - 1); ClearNodes (nodes, vertex);
	sum[1] += DijkstraAlgorithm (nodes, middle2 - 1, middle1 - 1); ClearNodes (nodes, vertex);
	sum[1] += DijkstraAlgorithm (nodes, middle1 - 1, vertex - 1); ClearNodes (nodes, vertex);
	
	long long total = sum[0] + sum[1];
	if (total >= INT_MAX) cout << -1;
	else if (sum[0] < sum[1]) cout << sum[0];
	else cout << sum[1];
	
	delete[] nodes;
	return 0;
}

void ClearNodes (struct NodeType* nodes, int numberOfVertex) {
	
	if (nodes == NULL) throw;
	
	for (int index = 0; index < numberOfVertex; index++) {
		
		nodes[index].IsVisited = false;
	}
	return;
}

long long DijkstraAlgorithm (struct NodeType* nodes, int start, int end) {
	
	if (nodes == NULL) throw;
	
	long long weight = INT_MAX;
	
	priority_queue<struct VertexType> buffer;
	buffer.push(VertexType(start, 0));
	while(!buffer.empty()) {
		
		struct VertexType current = buffer.top(); buffer.pop();
		
		int number = current.Number;
		if (nodes[number].IsVisited == true) continue;
		nodes[number].IsVisited = true;
		
		if (number == end) {
			
			weight = current.Weight;
			break;
		}
				
		for (const auto& element : nodes[number].Element) {
			
			buffer.push(VertexType(element.Number, current.Weight + element.Weight));
		}
	}
	
	return weight;
}