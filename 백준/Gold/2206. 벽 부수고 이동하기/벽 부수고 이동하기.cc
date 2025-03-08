#include <iostream>
#include <queue>

#define ROW 1024
#define COLUMN 1024

using namespace std;

struct CoordinateType {
	
	int X, Y;
	int Depth;
	bool IsBroken;
};

struct StatusType {
	
	bool IsNotVisit, IsRoad;
	bool IsNotVirtualVisit;
};

int Solution (struct StatusType road[ROW][COLUMN], struct CoordinateType goal);

int main (int argc, char* argv[]) {
	
	int height = 0, width = 0;
	cin >> width >> height;
	
	static struct StatusType road[ROW][COLUMN] = { 0 };
	for (int row = 1; row <= width; row++) {
		for (int column = 1; column <= height; column++) {
			
			char character = getchar();
			if (character == '\n') {
				
				column--;
				continue;
			}
			road[row][column].IsRoad = character - '0' == 0;
			road[row][column].IsNotVisit = true;
			road[row][column].IsNotVirtualVisit = true;
		}
	}

	int result = Solution (road, {width, height, 0, false});
	cout << result;
	return 0;
}

int Solution (struct StatusType road[ROW][COLUMN], struct CoordinateType goal) {
	
	if (road == NULL) throw;
	
	int depth = 0;
	
	queue<struct CoordinateType> buffer;
	buffer.push({1, 1, 1, false}); // 4, 5
	
	while (!buffer.empty()) {
		
		struct CoordinateType current = buffer.front(); buffer.pop();
		if (current.X == goal.X && current.Y == goal.Y) {
			
			depth = current.Depth;
			return depth;
		}
		else if (current.IsBroken == true && road[current.X][current.Y].IsNotVirtualVisit == false) continue;
		else if (road[current.X][current.Y].IsRoad == false && current.IsBroken == true ||
				road[current.X][current.Y].IsNotVisit == false) continue;
		
		road[current.X][current.Y].IsNotVisit = current.IsBroken;
		road[current.X][current.Y].IsNotVirtualVisit = !current.IsBroken;
		depth = current.Depth;
		
		//cout << current.X << " : " << current.Y << " > " << current.IsBroken << endl;
		
		bool broken = road[current.X][current.Y].IsRoad == false || current.IsBroken;
		buffer.push({current.X - 1, current.Y, current.Depth + 1, broken});
		buffer.push({current.X, current.Y + 1, current.Depth + 1, broken});
		buffer.push({current.X + 1, current.Y, current.Depth + 1, broken});
		buffer.push({current.X, current.Y - 1, current.Depth + 1, broken});
	}
	
	return -1;
}