#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct SoluteType {
	
	int Solute1, Solute2;
};

struct SoluteType Solution (vector<int>& source, int length);

// -99 -2 -1 4 98

int main (int argc, char* argv[]) {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int length = 0;
	cin >> length;
	
	vector<int> source;
	for (int index = 0; index < length; index++) {
		
		int solute = 0;
		cin >> solute;
		source.push_back(solute);
	}
	sort(source.begin(), source.end());
	
	struct SoluteType result = Solution (source, length);
	if (result.Solute1 < result.Solute2)
		 cout << result.Solute1 << " " << result.Solute2;
	else cout << result.Solute2 << " " << result.Solute1;
	return 0;
}

struct SoluteType Solution (vector<int>& source, int length) {
	
	struct SoluteType result = { 0, };
	
	int minimum = 2000000001;
	int left = 0, right = length - 1;
	while (left < right) {
		
		int absolute_sum = abs (source[left] + source[right]);
		if (minimum > absolute_sum) {
			
			minimum = absolute_sum;
			result.Solute1 = source[left];
			result.Solute2 = source[right];
		}
		
		if (abs(source[left]) > abs(source[right])) left++;
		else right--;
	}
	return result;
}