#include <iostream>
#include <queue>

using namespace std;

struct CoordinateType {
	
	int X, Y, Z;
	int Depth;
};

int Solution (int box[128][128][128], queue<struct CoordinateType>& buffer);
bool Check (int box[128][128][128], int horizontal, int vertical, int height);

int main (int argc, char* argv[]) {
	
	int horizontal = 0, vertical = 0, height = 0;
	cin >> height >> vertical >> horizontal;
	
	queue <struct CoordinateType> buffer;
	
	static int box[128][128][128] = { 0, };
	
	for (int row = 1; row <= horizontal; row++) {
		for (int column = 1; column <= vertical; column++) {
			for (int pivot = 1; pivot <= height; pivot++) {
				
				int element = 0;
				cin >> element;
				
				box[row][column][pivot] = element != -1 ? 1 : -1;
				if (element == 1) buffer.push({row, column, pivot, 0}); 
			}
		}
	}
	
	int result = Solution (box, buffer);
	if (Check (box, horizontal, vertical, height) == false) cout << -1;
	else cout << result;
	
	return 0;
}

int Solution (int box[128][128][128], queue<struct CoordinateType>& buffer) {
	
	if (box == NULL) throw;
	
	int depth = 1;
	while (!buffer.empty()) {
		
		struct CoordinateType current = buffer.front(); buffer.pop();
		if (box[current.X][current.Y][current.Z] == 0 || box[current.X][current.Y][current.Z] == -1) continue;
		
		box[current.X][current.Y][current.Z] = 0;
		depth = current.Depth;
		
		buffer.push({current.X - 1, current.Y, current.Z, current.Depth + 1});
		buffer.push({current.X, current.Y + 1, current.Z, current.Depth + 1});
		buffer.push({current.X + 1, current.Y, current.Z, current.Depth + 1});
		buffer.push({current.X, current.Y - 1, current.Z, current.Depth + 1});
		buffer.push({current.X, current.Y, current.Z - 1, current.Depth + 1});
		buffer.push({current.X, current.Y, current.Z + 1, current.Depth + 1});
	}
	return depth;
}

bool Check (int box[128][128][128], int horizontal, int vertical, int height) {
	
	if (box == NULL) throw;
	
	for (int row = 1; row <= horizontal; row++) {
		for (int column = 1; column <= vertical; column++) {
			for (int pivot = 1; pivot <= height; pivot++) {
				
				if (box[row][column][pivot] == 1) return false;
			}
		}
	}
	
	return true;
}