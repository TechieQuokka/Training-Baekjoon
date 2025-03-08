#include <iostream>
#include <vector>

#define INFINITY 2147483647

using namespace std;

struct VertexType {
	
	long long Number;
	long long Weight;
};

pair<vector<vector<long long>>, vector<vector<long long>>> Initialize (vector<vector<struct VertexType>> nodes);
void Floyd_Warshall_Algorithm (vector<vector<long long>>& distance, vector<vector<long long>>& path, int vertex);
void Display (vector<vector<long long>>& source);
void PrintPath (vector<vector<long long>>& source, int from, int to);
//4 6
//1 2 3
//1 3 6
//1 4 15
//2 3 -2
//3 4 2
//4 1 1

int main (int argc, char* argv[]) {
	
	int vertex = 0, edge = 0;
	cin >> vertex >> edge;
	
	vector<vector<struct VertexType>> nodes (vertex);
	
	for (int index = 0; index < edge; index++) {
		
		int from = 0, to = 0, weight = 0;
		cin >> from >> to >> weight;
		
		nodes[from - 1].push_back({to - 1, weight});
	}
	
	auto tables = Initialize (nodes);
	auto& distance = tables.first;
	auto& path = tables.second;
	
	Floyd_Warshall_Algorithm (distance, path, vertex);
	
	Display (distance);
	
	for (int row = 0; row < vertex; row++) {
		for (int column = 0; column < vertex; column++) {
			
			PrintPath (path, row, column);
		}
	}
	return 0;
}

void PrintPath(vector<vector<long long>>& source, int from, int to) {
    
    if (source[from][to] == INFINITY) {
        cout << "0\n";
        return;
    }
    
    vector<long long> result;
    int current = to;
    
    while (current != from) {
        result.insert(result.begin(), current + 1);
        current = source[from][current];
        if (current == INFINITY) {
            cout << "0\n";
            return;
        }
    }
    
    result.insert(result.begin(), from + 1);
    cout << result.size() << " ";
    
    for (const auto& element : result) {
        cout << element << " ";
    }
    cout << "\n";
    return;
}

void Floyd_Warshall_Algorithm (vector<vector<long long>>& distance, vector<vector<long long>>& path, int vertex) {
		
	for (int pivot = 0; pivot < vertex; pivot++) {
		for (int row = 0; row < vertex; row++) {
			for (int column = 0; column < vertex; column++) {
				
				long long sum = distance[row][pivot] + distance[pivot][column];
				if (distance[row][column] > sum) {
					
					distance[row][column] = sum;
					path[row][column] = path[pivot][column];
				}
			}
		}
	}
	return;
}

pair<vector<vector<long long>>, vector<vector<long long>>> Initialize (vector<vector<struct VertexType>> nodes) {
	
	int length = nodes.size();
	vector<vector<long long>> distance (length, vector<long long> (length, INFINITY));
	vector<vector<long long>> path	 (length, vector<long long> (length, INFINITY));
	
	for (int index = 0; index < length; index++) {
		
		distance[index][index] = 0;
		
		auto vertex = nodes[index];
		for (const auto& element : vertex) {
			
			int number = element.Number, weight = element.Weight;
			if (distance[index][number] <= weight) continue;
			distance[index][number] = weight;
			path[index][number] = index;
		}
	}
	
	return { distance, path };
}

void Display (vector<vector<long long>>& source) {
	
	for (const auto& vertex : source) {
		for (const auto& element : vertex) {
			
			if (element == INFINITY) cout << "0 ";
			else cout << element << " ";
		}
		cout << "\n";
	}
	return;
}