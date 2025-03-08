#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct NodeType {
	
	vector<int> Vertex;
	int Parent;
};

int NearestCommonAnscestor (vector<struct NodeType>& nodes, int child1, int child2);

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int repeat = 0;
	cin >> repeat;
	for (int loop = 0; loop < repeat; loop++) {
		
		int count = 0;
		cin >> count;
		
		vector<struct NodeType> tree(count + 1);
		for (int index = 1; index < count; index++) {
			
			int parent = 0, child = 0;
			cin >> parent >> child;
			
			tree[parent].Vertex.push_back (child);
			tree[child].Parent = parent;
		}
		
		int child1 = 0, child2 = 0;
		cin >> child1 >> child2;
		cout << NearestCommonAnscestor (tree, child1, child2) << "\n";
	}

	return 0;
}



int NearestCommonAnscestor (vector<struct NodeType>& nodes, int child1, int child2) {
	
	stack<int> parent_stack[2];
	
	parent_stack[0].push(child1);
	int parent = child1;
	while (nodes[parent].Parent != 0) {
		
		parent = nodes[parent].Parent;
		parent_stack[0].push(parent);
	}
	
	parent_stack[1].push(child2);
	parent = child2;
	while (nodes[parent].Parent != 0) {
		
		parent = nodes[parent].Parent;
		parent_stack[1].push(parent);
	}
	
	while (!parent_stack[0].empty() && !parent_stack[1].empty()) {
		
		int anscestor1 = parent_stack[0].top(), anscestor2 = parent_stack[1].top();
		parent_stack[0].pop(); parent_stack[1].pop();
		
		if (anscestor1 == anscestor2 &&
			(parent_stack[0].empty() || parent_stack[1].empty()) ||
			parent_stack[0].top() != parent_stack[1].top()) {
			
			return anscestor1;
		}
	}
	return -1;
}