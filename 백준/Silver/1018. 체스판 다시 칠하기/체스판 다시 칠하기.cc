#include <iostream>

using namespace std;

int CalculateNumberOfRepainting (bool board[51][51], int width, int height, int horizontal, int vertical);

int main (int argc, char* argv[]) {
	
	int horizontal = 0, vertical = 0;
	cin >> horizontal >> vertical;
	
	bool board[51][51] = { false };
	for (int row = 0; row < horizontal; row++) {
		for (int column = 0; column < vertical; column++) {
			
			char character = 0;
			cin >> character;
			board[row][column] = character == 'W';
		}
	}
	
	cout << CalculateNumberOfRepainting (board, horizontal, vertical, 8, 8);
	return 0;
}

int CountOfRepaint (bool board[51][51], int x, int y, int width, int height, bool pivot) {
	
	int count = 0;
	
	for (int row = x; row < width; row++) {
		for (int column = y; column < height; column++) {
			
			count += board[row][column] == pivot;
			pivot = !pivot;
		}
		pivot = !pivot;
	}
	
	return count;
}

int CalculateNumberOfRepainting (bool board[51][51], int width, int height, int horizontal, int vertical) {
	
	if (board == NULL) return 0;
	
	int minimum = 987654321;
	
	for (int row = 0; row < width - horizontal + 1; row++) {
		for (int column = 0; column < height - vertical + 1; column++) {
			
			int left = CountOfRepaint (board, row, column, row + horizontal, column + vertical, true);
			int right = CountOfRepaint (board, row, column, row + horizontal, column + vertical, false);
			
			minimum = min (minimum, min (left, right));
		}
	}
	
	return minimum;
}