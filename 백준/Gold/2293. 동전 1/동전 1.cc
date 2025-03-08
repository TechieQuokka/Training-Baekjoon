#include <iostream>
#include <vector>

using namespace std;

int Solution (vector<int>& source, int value);

int main (int argc, char* argv[]) {
	
	int line = 3, value = 10;
	cin >> line >> value;
	
	vector<int> source;
	for (int index = 0; index < line; index++) {
		
		int coin = 0;
		cin >> coin;
		source.push_back(coin);
	}
	
	int result = Solution (source, value);
	cout << result;
	return 0;
}

int Solution (vector<int>& source, int value) {
	
	vector<int> table (value + 1, 0);
	
	table[0] = 1;
	
	for (const auto& coin : source) {
		for (int index = coin; index <= value; index++) {
			
			table[index] += table[index - coin];
		}
	}
	
	return table[value];
}