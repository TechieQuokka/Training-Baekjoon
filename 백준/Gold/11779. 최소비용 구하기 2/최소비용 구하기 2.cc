#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct VertexType {
	
	int Number;
	int Weight;
	vector<int> Path;
	
	VertexType (int number, int weight, vector<int> path) : Number (number), Weight (weight), Path (path) { }
	
	bool operator < (const struct VertexType vertex) const {
		
		return this->Weight > vertex.Weight;
	}
};

struct NodeType {
	
	vector<struct VertexType> Elements;
	bool IsVisited;
};

pair<vector<int>, int> DijkstraAlgorithm (vector<struct NodeType>& source, int start, int end);

int main (int argc, char* argv[]) {
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	vector<struct NodeType> source (vertex + 1);
	for (int index = 0; index < edge; index++) {
		
		int from = 0, to = 0, weight = 0;
		cin >> from >> to >> weight;
		
		source[from].Elements.push_back (VertexType (to, weight, vector<int>()));
	}
	
	int start = 0, end = 0;
	cin >> start >> end;
	
	auto result = DijkstraAlgorithm (source, start, end);
	cout << result.second << '\n';
	cout << result.first.size() << '\n';
	for (const auto& element : result.first) {
		
		cout << element << " ";
	}
	return 0;
}

pair<vector<int>, int> DijkstraAlgorithm (vector<struct NodeType>& source, int start, int end) {
	
	priority_queue<struct VertexType> buffer;
	buffer.push({start, 0, vector<int>()});
	
	while (!buffer.empty()) {
		
		auto current = buffer.top(); buffer.pop();
		
		int number = current.Number;
		if (number == end) {
			
			current.Path.push_back (number);
			return { current.Path, current.Weight };
		}
		
		if (source[number].IsVisited == true) continue;
		source[number].IsVisited = true;
		
		current.Path.push_back (number);
		for (auto& element : source[number].Elements) {
			
			buffer.emplace(VertexType(element.Number, current.Weight + element.Weight, current.Path));
		}
	}
	
	return {};
}