#include <iostream>
#include <stack>

using namespace std;

struct CoordinateType {
	
	int X, Y;
};

struct NodeType {
	
	int Value;
	int NumberOfCase;
	struct CoordinateType Parent;
};

int Calculate_NumberOfCase (struct NodeType space[512][512], const struct CoordinateType goal);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    
    int width = 0, height = 0;
    cin >> width >> height;
    
    static struct NodeType space[512][512];
    for (int row = 1; row <= width; row++) {
    	for (int column = 1; column <= height; column++) {
    		
    		cin >> space[row][column].Value;
    		space[row][column].NumberOfCase = -1;
    		space[row][column].Parent = { 0, 0 };
		}
	}
	
	space[0][0].Value = 999999;
	space[width][height].NumberOfCase = 1;
	
	int result = Calculate_NumberOfCase (space, {width, height});
	cout << result;
	
	return 0;
}

void Update (struct NodeType space[512][512], struct CoordinateType current) {
	
	int increase = space[current.X][current.Y].NumberOfCase;
	
	for (current = space[current.X][current.Y].Parent; current.X != 0 && current.Y != 0;
			current = space[current.X][current.Y].Parent) {
		
		space[current.X][current.Y].NumberOfCase += increase;
	}
	
	return;
}

int Calculate_NumberOfCase (struct NodeType space[512][512], const struct CoordinateType goal) {
	
	if (space == NULL) throw;
	
	stack<pair<struct CoordinateType, struct CoordinateType>> buffer; // current, parent
	buffer.push({{1, 1}, {0, 0}});
	
	while (!buffer.empty()) {
		
		auto& current = buffer.top(); buffer.pop();
		auto parent = current.second;
		int x = current.first.X, y = current.first.Y;
		int parent_x = current.second.X, parent_y = current.second.Y;
		
		if (x < 1 || y < 1 || x > goal.X || y > goal.Y) continue;
		else if (space[x][y].Value >= space[parent_x][parent_y].Value) continue;
		else if (space[x][y].NumberOfCase != -1) {
			
			space[x][y].Parent = parent;
			Update (space, {x, y});
			continue;
		}
		
		space[x][y].Parent = parent;
		space[x][y].NumberOfCase = 0;
		
		buffer.push({{x + 1, y}, {x, y}});
		buffer.push({{x, y + 1}, {x, y}});
		buffer.push({{x - 1, y}, {x, y}});
		buffer.push({{x, y - 1}, {x, y}});
	}
	
	return space[1][1].NumberOfCase;
}