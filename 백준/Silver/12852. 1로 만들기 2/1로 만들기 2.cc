#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> BreadthFirstSearch (int number);

int main (int argc, char* argv[]) {
	
	int input = 0;
	cin >> input;
	if (input == 1) {
		
		cout << 0 << "\n" << 1;
		return 0;
	}
	
	auto result = BreadthFirstSearch (input);
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

vector<pair<int, int>> BreadthFirstSearch (int number) {
	
	vector<pair<int, int>> result;
	
	int index = -1;
	queue<pair<int, int>> buffer;
	buffer.push({number, index});
	
	while (!buffer.empty()) {
		
		auto element = buffer.front(); buffer.pop();
		int number = element.first;
		if (number == 1) {
			
			result.push_back({number, element.second});
			break;
		}
		else if (number < 1) continue;
		
		result.push_back({number, element.second});
		index++;
		
		if (number % 3 == 0) buffer.push({number / 3, index});
		if (number % 2 == 0) buffer.push({number / 2, index});
		buffer.push({number - 1, index});
	}
	
	return result;
}