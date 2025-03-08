#include <iostream>
#include <queue>
#include <vector>

#define NONE -1
#define INFINITY 99999999

using namespace std;

struct VertexType {
	
	int Number;
	int Weight;
	
	VertexType (int number, int weight) : Number(number), Weight(weight) { }
};

struct NodeType {
	
	vector<struct VertexType> Element;
	bool IsVisited;
	int Parent;
};

int NumberOfPath (struct NodeType* node, int start, int end, int vertex);
void Display (struct NodeType* node, int start);
void Initialize (struct NodeType* node, int vertex);

//3 3
//0
//0
//3 1 2 3

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int employee = 0, work = 0;
	cin >> employee >> work;
	
	int vertex = employee + work + 2;
	struct NodeType* nodes = new struct NodeType[vertex];
	if (nodes == NULL) throw;
	
	Initialize (nodes, vertex - 1);
	
	for (int employee_vertex = 1; employee_vertex <= employee; employee_vertex++) {
		
		int weight = 2;
		nodes[0].Element.push_back({employee_vertex, weight});
		nodes[employee_vertex].Element.push_back({0, 0});
		
		int count = 0;
		cin >> count;
		for (int loop = 0; loop < count; loop++) {
			
			int work_vertex = 0;
			cin >> work_vertex;
			
			nodes[employee_vertex].Element.push_back({work_vertex + employee, weight});
			nodes[work_vertex + employee].Element.push_back({employee_vertex, 0});
		}
	}
	
	int termination = employee + work + 1;
	for (int index = 0; index < work; index++) {
		
		int employee_vertex = employee + index + 1;
		int weight = 1;
		nodes[employee_vertex].Element.push_back({termination, weight});
		nodes[termination].Element.push_back({employee_vertex, 0});
	}
	
	cout << NumberOfPath (nodes, 0, termination, vertex) - 1;
	delete[] nodes;
	return 0;
}

void Initialize (struct NodeType* node, int vertex) {
	
	if (node == NULL) throw;
	
	for (int index = 0; index <= vertex; index++) {
		
		node[index].IsVisited = false;
		node[index].Parent = NONE;
	}
	return;
}

struct VertexType& FindVertex (vector<struct VertexType>& vertex, int target) {
	
	for (auto& element : vertex) {
		if (element.Number == target) {
			
			return element;
		}
	}
	throw;
}

int FindMinimumWeight (struct NodeType* node, int end) {
	
	int minimum = INFINITY; // inf
	
	int current = end;
	int parent = node[current].Parent;
	while (parent != NONE) {
				
		int weight = FindVertex (node[parent].Element, current/* target */).Weight;
		if (minimum > weight) minimum = weight;
		
		current = parent;
		parent = node[current].Parent;
	}
	
	return minimum;
}

void Update (struct NodeType* node, int end, int minimum) {
	
	int current = end;
	int parent = node[current].Parent;
	while (parent != NONE) {
		
		auto& forward = FindVertex (node[parent].Element, current/* target */);
		auto& backward = FindVertex (node[current].Element, parent/* target */);
		
		forward.Weight -= minimum;
		backward.Weight += minimum;
		
		current = parent;
		parent = node[current].Parent;
	}
	
	return;
}

int NumberOfPath (struct NodeType* node, int start, int end, int vertex) {
	
	if (node == NULL) throw;
	
	bool exit = false;
	
	node[start].Parent = NONE;
	node[start].IsVisited = true;
	
	queue<int> buffer;
	buffer.push(start);
	
	while (!buffer.empty() && exit == false) {
		
		int current = buffer.front(); buffer.pop();
		
		auto& pivot = node[current].Element;
		for (const auto& child : pivot) {
			if (child.Weight == 0 || node[child.Number].IsVisited == true) continue;
			
			const auto& childNumber = child.Number;
			node[childNumber].IsVisited = true;
			node[childNumber].Parent = current;
			buffer.push(childNumber);
			if (childNumber == end) {
				
				exit = true;
				break;
			}
		}
	}
	if (exit == false) return 1;
	
	int minimum = FindMinimumWeight (node, end);
	Update (node, end, minimum);
	
	Initialize (node, vertex - 1);
	
	return NumberOfPath (node, start, end, vertex) + 1;
}

void Display (struct NodeType* node, int start) {
	
	if (node == NULL) throw;
	
	queue<int> buffer;
	buffer.push(start);
	
	while (!buffer.empty()) {
		
		int current = buffer.front(); buffer.pop();
		if (node[current].IsVisited == true) continue;
		else node[current].IsVisited = true;
		
		for (const auto& child : node[current].Element) {
			
			cout << current << " -> " << child.Number << " : " << child.Weight << endl;
			buffer.push(child.Number);
		}
	}
	return;
}