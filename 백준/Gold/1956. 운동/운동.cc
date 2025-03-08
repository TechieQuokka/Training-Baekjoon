#include <iostream>
#include <vector>
#include <limits.h>

#define INFINITY 2147483647

using namespace std;

struct EdgeType {
	
	long long From, To;
	long long Weight;
};

vector<vector<long long>> FloydWarshallAlgorithm (vector<struct EdgeType>& list, int vertex);
long long Calculate (vector<vector<long long>>& table, int vertex);

int main (int argc, char* argv[]) {
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	vector<struct EdgeType> list;
	for (int index = 0; index < edge; index++) {
		
		int from = 0, to = 0, weight = 0;
		cin >> from >> to >> weight;
		list.push_back({from - 1, to - 1, weight});
	}
	
	vector<vector<long long>> table = FloydWarshallAlgorithm (list, vertex);
	long long result = Calculate (table, vertex);
	if (result != INFINITY) cout << result;
	else cout << -1;
	return 0;
}

vector<vector<long long>> Initialize (vector<struct EdgeType>& list, int vertex) {
	
	vector<vector<long long>> table(vertex, vector<long long>(vertex, INFINITY));
	for (int index = 0; index < vertex; index++) {
		
		table[index][index] = 0;
	}
	
	for (const auto& element : list) {
		
		auto& cell = table[element.From][element.To];
		if (cell > element.Weight) cell = element.Weight;
	}
	return table;
}

vector<vector<long long>> FloydWarshallAlgorithm (vector<struct EdgeType>& list, int vertex) {
	
	vector<vector<long long>> table = Initialize (list, vertex);
	for (int pivot = 0; pivot < vertex; pivot++) {
		for (int row = 0; row < vertex; row++) {
			for (int column = 0; column < vertex; column++) {
				if (row == column || row == pivot || column == pivot) continue;
				
				table[row][column] = min (table[row][column], table[row][pivot] + table[pivot][column]);
			}
		}
	}
	return table;
}

long long Calculate (vector<vector<long long>>& table, int vertex) {
	
	long long result = INFINITY;
	for (int row = 0; row < vertex; row++) {
		for (int column = 0; column < vertex; column++) {
			
			if (row == column) continue;
			result = min (result, table[row][column] + table[column][row]);
		}
	}
	return result;
}