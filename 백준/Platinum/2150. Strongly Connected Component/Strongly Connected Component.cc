#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

struct NodeType {
	
	vector<int> Vertex;
	bool IsVisit;
};

struct GraphType {
	
	vector<struct NodeType> Nodes;
	int Size;
	int Visited_Count;
};

vector<vector<int>> Strongly_Connected_Components (struct GraphType& graph);
struct GraphType Create_Graph (int size);

int Compare (const vector<int>& first, const vector<int>& second) {
	
	return first[0] < second[0];
}

int main (int argc, char* argv[]) {
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	struct GraphType graph = Create_Graph (vertex);
	for (int repeat = 0; repeat < edge; repeat++) {
		
		int from = 0, to = 0;
		cin >> from >> to;
		
		graph.Nodes[from].Vertex.push_back(to);
		graph.Nodes[from].IsVisit = false;
	}
	
	auto result = Strongly_Connected_Components (graph);
	
	int size = result.size();
	for (int index = 0; index < size; index++) {
		
		sort (result[index].begin(), result[index].end());
	}
	
	sort (result.begin(), result.end(), &Compare);
	
	cout << size << "\n";
	for (const auto& group : result) {
		for (const auto& element : group) {
			
			cout << element << " ";
		}
		cout << -1 << "\n";
	}
	
	return 0;
}

bool Have_All_Visited (struct GraphType& graph) {
	
	return graph.Size == graph.Visited_Count;
}

int Find_Unvisited_Vertex (struct GraphType& graph) {
	
	int length = graph.Size;
	for (int index = 1; index <= length; index++) {
		
		if (graph.Nodes[index].IsVisit == false) return index;
	}
	throw;
}

struct GraphType Create_Graph (int size) {
	
	struct GraphType graph;
	graph.Size = size;
	graph.Visited_Count = 0;
	
	graph.Nodes.resize(size + 1);
	return graph;
}

struct GraphType Transpose_Graph (struct GraphType& graph) {
	
	int length = graph.Size;
	struct GraphType new_graph = Create_Graph(length);
	
	for (int from = 1; from <= length; from++) {
		for (const auto& to : graph.Nodes[from].Vertex) {
			
			new_graph.Nodes[to].Vertex.push_back(from);
		}
	}
	return new_graph;
}

// post-order
void Depth_First_Search (struct GraphType& graph, int current, stack<int>& finish_time) {
	
	if (graph.Nodes[current].IsVisit == true) return;
	else graph.Nodes[current].IsVisit = true;
	
	vector<int>& vertex = graph.Nodes[current].Vertex;
	
	int length = vertex.size();
	for (int index = 0; index < length; index++) {
		
		Depth_First_Search (graph, vertex[index], finish_time);
	}
	
	finish_time.push(current);
	graph.Visited_Count++;
	return;
}

// pre-order
vector<int> Record_DFS (struct GraphType& graph, int current) {
	
	stack<int> buffer;
	buffer.push(current);
	
	vector<int> result;
	while (!buffer.empty()) {
		
		int element = buffer.top(); buffer.pop();
		if (graph.Nodes[element].IsVisit == true) continue;
		else graph.Nodes[element].IsVisit = true;
		
		result.push_back(element);
		for (const auto& child : graph.Nodes[element].Vertex) {
			
			buffer.push(child);
		}
	}
	
	return result;
}

vector<vector<int>> Strongly_Connected_Components (struct GraphType& graph) {
	
	stack<int> finish_time;
	while (!Have_All_Visited (graph)) {
		
		int start = Find_Unvisited_Vertex (graph);
		Depth_First_Search (graph, start, finish_time);
	}
	
	struct GraphType reverse_graph = Transpose_Graph (graph);
	vector<vector<int>> result;
	while (!finish_time.empty()) {
		
		int element = finish_time.top(); finish_time.pop();
		if (reverse_graph.Nodes[element].IsVisit == true) continue;
		
		vector<int> group = Record_DFS (reverse_graph, element);
		result.push_back(group);
	}
	
	return result;
}