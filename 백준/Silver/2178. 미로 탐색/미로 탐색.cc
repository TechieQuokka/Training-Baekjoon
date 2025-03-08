#include <iostream>
#include <queue>

using namespace std;

struct CoordinateType {
	
	int X, Y;
	int Depth;
};

int Solution (int map[128][128], int width, int height);
/*
10 8
1110011111
0011110101
0000011111
0000000001
1111111111
1011000000
1111111111
0001111111
*/

int main (int argc, char* argv[]) {
	
	int width = 4, height = 6;
	scanf ("%d%d", &width, &height);
	
	int map[128][128] = { 0, };
	
	for (int row = 1; row <= width; row++) {
		for (int column = 1; column <= height; column++) {
			
			char character = getchar();
			if (character == '\n') {
				
				column--;
				continue;
			}
			map[row][column] = character - '0';
		}
	}
	
	int result = Solution (map, width, height);
	printf ("%d\n", result);
	
	return 0;
}

int Solution (int map[128][128], int width, int height) {
	
	if (map == NULL) return -1;
	
	queue<struct CoordinateType> buffer;
	buffer.push({1, 1, 1});
	
	int depth = 1;	
	while (!buffer.empty()) {
		
		struct CoordinateType current = buffer.front(); buffer.pop();
		if (map[current.X][current.Y] == 0) continue;
		else if (current.X == width && current.Y == height) {
			
			depth = current.Depth;
			break;
		}
		
		map[current.X][current.Y] = 0;
		depth = current.Depth;
		
		buffer.push({current.X - 1, current.Y, current.Depth + 1});
		buffer.push({current.X, current.Y + 1, current.Depth + 1});
		buffer.push({current.X + 1, current.Y, current.Depth + 1});
		buffer.push({current.X, current.Y - 1, current.Depth + 1});
	}
	
	return depth;
}