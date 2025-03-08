#include <iostream>
#include <vector>

using namespace std;

vector<int> GetPrimeNumbers (int start, int end, int maximum);
int Solution (vector<int>& primeNumbers, int number);

int main (int argc, char* argv[]) {
	
	int number = 0;
	cin >> number;
	
	auto primeNumbers = GetPrimeNumbers (2, number, 10000001);
	cout << Solution (primeNumbers, number);
	
	return 0;
}

int Solution (vector<int>& primeNumbers, int number) {
	
	int length = primeNumbers.size();
	int count = 0, sum = 2;
	int left = 0, right = 0;
	while (right < length) {
		
		if (number == sum) {
			
			sum += primeNumbers[++right];
			count++;
			continue;
		}
		
		if (number > sum) sum += primeNumbers[++right];
		else sum -= primeNumbers[left++];
	}
	
	return count;
}

vector<int> GetPrimeNumbers (int start, int end, int maximum) {
	
	vector<int> primeNumber; vector<bool> sieve (maximum, false);
	for (int time = 2; time <= end; time++) {
		
		if (sieve[time] != false) continue;
		for (int index = time + time; index <= end; index += time) {
			
			sieve[index] = true;
		}
		
		if (sieve[time] == false && time >= start) primeNumber.push_back(time);
	}
	
	return primeNumber;
}