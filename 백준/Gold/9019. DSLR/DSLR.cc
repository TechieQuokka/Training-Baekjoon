#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

string BreadthFirstSearch (int before, int after);

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int count = 0;
	cin >> count;
	
	for (int repeat = 0; repeat < count; repeat++) {
		
		int before = 0, after = 0;
		cin >> before >> after;
		
		string result = BreadthFirstSearch (before, after);
		cout << result << "\n";
	}
	return 0;
}

int Double (int number) {
	
	int result = number * 2;
	return result % 10000;
}

int Subtract (int number) {
	
	if (number - 1 < 0) return 9999;
	return number - 1;
}

int Left (int number) {
	
	int left = number % 1000;
	int right = number / 1000;
	return left * 10 + right;
}

int Right (int number) {
	
	int left = number % 10;
	int right = number / 10;
	return left * 1000 + right;
}

string BreadthFirstSearch (int before, int after) {
	
	bool visited[10001] = { false, };
	
	queue<pair<int, string>> buffer;
	buffer.push({before, ""});
	
	while (!buffer.empty()) {
		
		auto current = buffer.front(); buffer.pop();
		int pivot = current.first;
		string log = current.second;
		
		if (pivot == after) return log;
		
		int calculate = 0;
		calculate = Double (pivot);
		if (visited[calculate] == false) {
			
			buffer.push({calculate, log + 'D'});
			visited[calculate] = true;
		}
		
		calculate = Subtract (pivot);
		if (visited[calculate] == false) {
			
			buffer.push({calculate, log + 'S'});
			visited[calculate] = true;
		}
		
		calculate = Left (pivot);
		if (visited[calculate] == false) {
			
			buffer.push({calculate, log + 'L'});
			visited[calculate] = true;
		}
		
		calculate = Right (pivot);
		if (visited[calculate] == false) {
			
			buffer.push({calculate, log + 'R'});
			visited[calculate] = true;
		}
	}
	
	return "";
}