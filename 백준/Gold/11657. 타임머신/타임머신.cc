#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

#define INFINITY 2147483647

using namespace std;

struct EdgeType {
	
	long long From, To;
	long long Weight;
};

pair<vector<long long>, bool> BellmanFordAlgorithm (vector<struct EdgeType>&, long long, long long);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	
	long long vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	bool check = false;
	vector<struct EdgeType> list (edge);
	for (int index = 0; index < edge; index++) {
		
		long long from = 0, to = 0, weight = 0;
		cin >> from >> to >> weight;
		list.push_back({from - 1, to - 1, weight});
		if (from == 1) check = true;
	}
	
	if (check == false) {
		for (int repeat = 1; repeat < vertex; repeat++) {
			
			cout << -1 << "\n";
		}
		return 0;
	}
	
	const auto result = BellmanFordAlgorithm (list, vertex, 0);
	if (result.second == false) {
		
		cout << -1;
		return 0;
	}
	for (int index = 1; index < vertex; index++) {
		
		int element = result.first[index];
		if (element == INFINITY) cout << -1 << "\n";
		else cout << element << "\n";
	}
	
	return 0;
}

vector<long long> InitializeSingleSource (long long vertex, long long start) {
	
	vector<long long> table (vertex);
	for (auto& element : table) {
		
		element = INFINITY;
	}
	table[start] = 0;
	return table;
}

bool Relax (vector<long long>& table, struct EdgeType edge) {
	
	long long weight = table[edge.From] + edge.Weight;
	if (table[edge.To] > weight) {
		
		table[edge.To] = weight;
		return true;
	}
	return false;
}

pair<vector<long long>, bool> BellmanFordAlgorithm (vector<struct EdgeType>& list, long long vertex, long long start) {
	
	vector<long long> table = InitializeSingleSource (vertex, start);
	for (int repeat = 1; repeat < vertex; repeat++) {
		
		int renewal = false;
		for (const auto& edge : list) {
			
			renewal |= Relax (table, edge);
		}
		if (renewal == false) return {table, true};
	}
	
	for (const auto& edge : list) {
		
		if (Relax (table, edge)) return {table, false};
	}
	return {table, true};
}