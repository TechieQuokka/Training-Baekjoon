#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> BreadthFirstSearch (int start, int end);

int main (int argc, char* argv[]) {
	
	int start = 0, end = 0;
	cin >> start >> end;
	if (start == end) {
		
		cout << 0 << "\n" << end;
		return 0;
	}
	
	auto result = BreadthFirstSearch (start, end);
	vector<int> solve;
	
	int current = result.size() - 1;
	solve.push_back(result[current].first);
	
	int parent = result[current].second;
	while (result[parent].second != -1) {
		
		solve.push_back(result[parent].first);
		parent = result[parent].second;
	}
	solve.push_back(result[parent].first);
	
	int length = solve.size();
	printf ("%d\n", length - 1);
	for (int index = length - 1; index >= 0; index--) {
		
		printf ("%d ", solve[index]);
	}
	
	return 0;
}

vector<pair<int, int>> BreadthFirstSearch (int start, int end) {
	
	static bool table[1000001] = { 0, };
	vector<pair<int, int>> result;
	
	int index = -1;
	queue<pair<int, int>> buffer;
	buffer.push({start, index});
	
	while (!buffer.empty()) {
		
		auto element = buffer.front(); buffer.pop();
		int number = element.first;
		if (number < 0 || number > 1000000 || table[number] == true) continue;
		else if (number == end) {
			
			result.push_back({number, element.second});
			break;
		}
		
		table[number] = true;
		result.push_back({number, element.second});
		index++;
		
		buffer.push({number * 2, index});
		buffer.push({number - 1, index});
		buffer.push({number + 1, index});
	}
	
	return result;
}