#include <iostream>
#include <queue>

using namespace std;

struct SpaceType {
	
	int Next;
	int Depth;
	bool IsVisited;
};

int Solution (struct SpaceType board[], int end);

int main (int argc, char* argv[]) {
	
	int numberOfLadders = 0, numberOfSnakes = 0;
	cin >> numberOfLadders >> numberOfSnakes;
	
	struct SpaceType board[128] = { 0 };
	for (int index = 1; index <= 100; index++) {
		
		board[index].Next = index;
	}
	
	int length = numberOfLadders + numberOfSnakes;
	
	for (int index = 0; index < length; index++) {
		
		int start = 0, end = 0;
		cin >> start >> end;
		
		board[start].Next = end;
	}
	
	int result = Solution (board, 100);
	
	cout << result;
	
	return 0;
}

int Solution (struct SpaceType board[], int end) {
	
	if (board == NULL) throw;
	
	int depth = 0;
	
	queue<struct SpaceType> buffer;
	buffer.push({1, 0, false});
	
	while (!buffer.empty()) {
		
		struct SpaceType current = buffer.front(); buffer.pop();
		if (board[current.Next].IsVisited == true) continue;
		else if (current.Next >= end) {
			
			depth = current.Depth;
			break;
		}
		
		board[current.Next].IsVisited = true;
		depth = current.Depth;
		
		for (int dice = 1; dice <= 6; dice++) {
			
			buffer.push({board[current.Next].Next + dice, current.Depth + 1, false});
		}
	}
	
	return depth;
}