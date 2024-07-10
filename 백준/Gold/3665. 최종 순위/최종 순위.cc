#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>
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
void Initialize (struct GraphType& graph, vector<int>& bucket);
void Switching (struct GraphType& graph, int team1, int team2);

int main (int argc, char* argv[]) {
	
	int loop = 0;
	cin >> loop;
	for (int cycle = 0; cycle < loop; cycle++) {
		
		int vertex = 0;
		cin >> vertex;
		
		vector<int> bucket;
		for (int index = 0; index < vertex; index++) {
			
			int element = 0;
			cin >> element;
			bucket.push_back(element);
		}
		
		struct GraphType graph;
		graph.Nodes.resize(vertex + 1);
		graph.Count = vertex;
		
		Initialize (graph, bucket);
		
		int count = 0;
		cin >> count;
		for (int repeat = 0; repeat < count; repeat++) {
			
			int team1 = 0, team2 = 0;
			cin >> team1 >> team2;
			Switching (graph, team1, team2);
		}
		
		auto buffer = Collect_In_degree (graph);
		if (buffer.empty()) {
			
			cout << "IMPOSSIBLE" << endl;
			continue;
		}
		auto result = Topological_Sort (graph, buffer);
		if (result.empty()) {
			
			cout << "IMPOSSIBLE" << endl;
			continue;
		}
		for (const auto& element : result) {
			
			cout << element << " ";
		}
		cout << "\n";
		}
	
	return 0;
}

void Switching (struct GraphType& graph, int team1, int team2) {
	
	auto& vertex1 = graph.Nodes[team1].Vertex;
	auto& vertex2 = graph.Nodes[team2].Vertex;
	if (find(vertex1.begin(), vertex1.end(), team2) != vertex1.end()) {
		
		vertex1.erase(remove(vertex1.begin(), vertex1.end(), team2));
		vertex2.push_back(team1);
		graph.Nodes[team1].In_degree++;
		graph.Nodes[team2].In_degree--;
	}
	else {
		
		vertex2.erase(remove(vertex2.begin(), vertex2.end(), team1));
		vertex1.push_back(team2);
		graph.Nodes[team2].In_degree++;
		graph.Nodes[team1].In_degree--;
	}
	return;
}

void Initialize (struct GraphType& graph, vector<int>& bucket) {
	
	int length = bucket.size();
	for (int from = 0; from < length; from++) {
		for (int to = from + 1; to < length; to++) {
			
			graph.Nodes[bucket[from]].Vertex.push_back(bucket[to]);
			graph.Nodes[bucket[to]].In_degree++;
		}
	}
	return;
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
	
	if (graph.Count != 0) return list<int>(0);
	return result;
}