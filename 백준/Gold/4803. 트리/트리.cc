#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNodeType {
	
	vector<int> Vertex;
	bool IsVisited;
};

bool IsTree (vector<struct TreeNodeType>& tree, int start);

int main (int argc, char* argv[]) {
	
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
	for (int case_number = 1; true; case_number++) {
		
		int vertex = 0, edge = 0;
		cin >> vertex >> edge;
		if (vertex == 0 && edge == 0) break;
		
		vector<struct TreeNodeType> tree (vertex + 1);
		for (int index = 0; index < edge; index++) {
			
			int from = 0, to = 0;
			cin >> from >> to;
			
			tree[from].Vertex.push_back (to);
			tree[to].Vertex.push_back (from);
		}
		
		int count = 0;
		for (int node = 0; node < vertex; node++) {
			
			bool result = IsTree (tree, node + 1);
			count += (int) result;
		}
		
		cout << "Case " << case_number << ": ";
		if (count == 0) {
			
			cout << "No trees." << "\n";
		}
		else if (count == 1) {
			
			cout << "There is one tree." << "\n";
		}
		else {
			
			cout << "A forest of " << count << " trees." << "\n";
		}
	}
	
	return 0;
}

bool IsTree (vector<struct TreeNodeType>& tree, int start) {
	
	stack<pair<int, int>> buffer;
	buffer.push({start, -1});
	
	while (!buffer.empty()) {
		
		auto& current = buffer.top(); buffer.pop();
		int node = current.first, previous = current.second;
		
		if (tree[node].IsVisited == true) return false;
		tree[node].IsVisited = true;
		
		for (const auto& element : tree[node].Vertex) {
			
			if (previous == element) continue;
			buffer.push({element, node});
		}
	}
	return true;
}