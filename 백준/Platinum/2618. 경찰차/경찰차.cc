#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct PositionType {
	
	int X, Y;
};

int Minimum (int table[1024][1024], vector<struct PositionType>& targets, int p1, int p2, int current, int count);
int Calculate_Distance (struct PositionType position1, struct PositionType position2);

int main (int argc, char* argv[]) {
	
	static int table[1024][1024] = { 0, };
	vector<struct PositionType> buffer;
	
	int size = 0, count = 0;
	cin >> size >> count;
	
	buffer.push_back ({1, 1});
	for (int index = 0; index < count; index++) {
		
		int x = 0, y = 0;
		cin >> x >> y;
		
		buffer.push_back ({x, y});
	}
	buffer.push_back ({size, size});
	
	int result = Minimum (table, buffer, 0, count + 1, 1, count);
	cout << result << "\n";
	
	int p1 = 0, p2 = count + 1;
	
	for (int index = 1; index <= count; index++) {
		
		int left = Calculate_Distance (buffer[p1], buffer[index]) + table[index][p2];
		int right = Calculate_Distance (buffer[p2], buffer[index]) + table[p1][index];
		
		if (left < right) {
			
			cout << 1 << "\n";
			p1 = index;
		}
		else {
			
			cout << 2 << "\n";
			p2 = index;
		}
	}
	
	return 0;
}

int Calculate_Distance (struct PositionType position1, struct PositionType position2) {
	
	return abs (position1.X - position2.X) + abs (position1.Y - position2.Y); 
}

int Minimum (int table[1024][1024], vector<struct PositionType>& targets, int p1, int p2, int current, int count) {
	
	if (current > count) return 0;
	else if (table[p1][p2] != 0) return table[p1][p2];
	
	int left = Calculate_Distance (targets[p1], targets[current]) + Minimum (table, targets, current, p2, current + 1, count);
	int right = Calculate_Distance (targets[p2], targets[current]) + Minimum (table, targets, p1, current, current + 1, count);
	
	return table[p1][p2] = min (left, right);
}