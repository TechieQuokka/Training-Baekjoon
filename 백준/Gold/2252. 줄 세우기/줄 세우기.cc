#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <stdlib.h>

using namespace std;

struct NodeType {
	
	vector<int> Vertex;
	int In_degree;
};

struct GraphType {
	
	vector<struct NodeType> Nodes;
	int Count;
};

list<int> Topological_Sort (struct GraphType& graph, stack<int>& buffer);
stack<int> Collect_In_degree (struct GraphType& graph);

int main (int argc, char* argv[]) {
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	struct GraphType graph;
	graph.Nodes.resize(vertex + 1);
	graph.Count = vertex;
	
	for (int repeat = 0; repeat < edge; repeat++) {
		
		int from = 0, to = 0;
		cin >> from >> to;
		graph.Nodes[from].Vertex.push_back(to);
		graph.Nodes[to].In_degree++;
	}
	
	stack<int> buffer = Collect_In_degree (graph);
	list<int> result = Topological_Sort (graph, buffer);
	for (const auto& element : result) {
		
		cout << element << " ";
	}
	
	return 0;
}

stack<int> Collect_In_degree (struct GraphType& graph) {
	
	stack<int> result;
	int length = graph.Nodes.size();
	for (int index = 1; index < length; index++) {
		
		auto& element = graph.Nodes[index];
		if (element.In_degree == 0) {
			
			result.push(index);
		}
	}
	return result;
}

void Discount_In_degree (struct GraphType& graph, stack<int>& buffer, int nodeNumber) {
	
	auto& node = graph.Nodes[nodeNumber];
	for (const auto& child : node.Vertex) {
		
		auto& current = graph.Nodes[child];
		current.In_degree--;
		if (current.In_degree == 0) {
			
			buffer.push(child);
		}
	}
	return;
}

list<int> Topological_Sort (struct GraphType& graph, stack<int>& buffer) {
	
	list<int> result;
	while (!buffer.empty()) {
		
		int element = buffer.top(); buffer.pop();
		result.push_back(element);
		Discount_In_degree (graph, buffer, element);
		graph.Count--;
	}
	
	if (graph.Count != 0) throw;
	return result;
}