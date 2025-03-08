#include <iostream>
#include <queue>

using namespace std;

struct NodeType {
	
	int Value;
	int Depth;
};

int solution (int start, int end);

int main (int argc, char* argv[]) {
	
	int start = 5, end = 17;
	scanf ("%d%d", &start, &end);
	int result = solution (start, end);
	cout << result;
	return 0;
}

int solution (int start, int end) {
	
	static bool plane[1000001] = { 0, };
	queue<struct NodeType> buffer;
	
	int depth = 0;
	
	buffer.push({start, 0});
	while (!buffer.empty()) {
		
		struct NodeType current = buffer.front(); buffer.pop();
		if (current.Value < 0 || current.Value > 1000000 || plane[current.Value] == true) continue;
		else if (current.Value == end) {
			
			depth = current.Depth;
			break;
		}
		
		plane[current.Value] = true;
		depth = current.Depth;
		
		buffer.push ({current.Value * 2, current.Depth});
		buffer.push ({current.Value - 1, current.Depth + 1});
		buffer.push ({current.Value + 1, current.Depth + 1});
	}
	
	return depth;
}