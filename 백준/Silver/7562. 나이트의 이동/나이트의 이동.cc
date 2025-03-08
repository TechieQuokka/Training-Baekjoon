#include <iostream>
#include <queue>

using namespace std;

struct CoordinateType {
	
	int X, Y;
	int Depth;
};

int Solution (int size, struct CoordinateType start, struct CoordinateType end);

int main (int argc, char* argv[]) {
	
	int length = 0;
	cin >> length;
	
	for (int repeat = 0; repeat < length; repeat++) {
		
		int size = 0;
		cin >> size;
		
		struct CoordinateType start = { 0, }, end = { 0, };
		cin >> start.X >> start.Y;
		cin >> end.X >> end.Y;
		
		start.X += 2, start.Y += 2;
		end.X += 2, end.Y += 2;
		
		int result = Solution (size, start, end);
		cout << result << "\n";
	}
	
	return 0;
}

int Solution (int size, struct CoordinateType start, struct CoordinateType end) {
	
	bool board[512][512] = { 0, };
	
	int depth = 0;
	
	queue<struct CoordinateType> buffer;
	buffer.push(start);
	
	while (!buffer.empty()) {
		
		struct CoordinateType current = buffer.front(); buffer.pop();
		if (board[current.X][current.Y] == true || 
			current.X < 2 || current.Y < 2 ||
			current.X >= size + 2 || current.Y >= size + 2) continue;
		else if (current.X == end.X && current.Y == end.Y) {
			
			depth = current.Depth;
			break;
		}
		
		board[current.X][current.Y] = true;
		depth = current.Depth;
		
		buffer.push({current.X - 1, current.Y + 2, current.Depth + 1});
		buffer.push({current.X + 1, current.Y + 2, current.Depth + 1});
		buffer.push({current.X + 2, current.Y + 1, current.Depth + 1});
		buffer.push({current.X + 2, current.Y - 1, current.Depth + 1});
		buffer.push({current.X + 1, current.Y - 2, current.Depth + 1});
		buffer.push({current.X - 1, current.Y - 2, current.Depth + 1});
		buffer.push({current.X - 2, current.Y - 1, current.Depth + 1});
		buffer.push({current.X - 2, current.Y + 1, current.Depth + 1});
	}
	
	return depth;
}