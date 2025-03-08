#include <iostream>
#include <queue>

using namespace std;

struct CoordinateType {
	
	int X, Y;
	int Depth;
};

int Solution (int box[1024][1024], int width, int height, queue<struct CoordinateType>& buffer);
bool Check (int box[1024][1024], int width, int height);

int main (int argc, char* argv[]) {
	
	int width = 0, height = 0;
	cin >> height >> width;
	
	queue<struct CoordinateType> buffer;
	
	static int box[1024][1024] = { 0, };
	for (int row = 1; row <= width; row++) {
		for (int column = 1; column <= height; column++) {
			
			int element = 0;
			cin >> element;
			
			box[row][column] = element != -1 ? 1 : -1;
			if (element == 1) buffer.push({row, column, 0});
		}
	}
	
	int result = Solution (box, width, height, buffer);
	if (Check (box, width, height) == false) cout << -1;
	else cout << result;
	
	return 0;
}

int Solution (int box[1024][1024], int width, int height, queue<struct CoordinateType>& buffer) {
	
	if (box == NULL) throw;
	
	int depth = 1;
	while (!buffer.empty()) {
		
		struct CoordinateType current = buffer.front(); buffer.pop();
		if (box[current.X][current.Y] == 0 || box[current.X][current.Y] == -1) continue;
		
		box[current.X][current.Y] = 0;
		depth = current.Depth;
		
		buffer.push({current.X - 1, current.Y, current.Depth + 1});
		buffer.push({current.X, current.Y + 1, current.Depth + 1});
		buffer.push({current.X + 1, current.Y, current.Depth + 1});
		buffer.push({current.X, current.Y - 1, current.Depth + 1});
	}
	return depth;
}

bool Check (int box[1024][1024], int width, int height) {
	
	if (box == NULL) throw;
	
	for (int row = 1; row <= width; row++) {
		for (int column = 1; column <= height; column++) {
			
			if (box[row][column] == 1) return false;
		}
	}
	
	return true;
}