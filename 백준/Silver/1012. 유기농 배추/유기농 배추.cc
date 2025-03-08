#include <stdio.h>

int Solution (int field[64][64], int x, int y);

int main (int argc, char* argv[]) {
	
	int testcase = 0;
	scanf ("%d", &testcase);
	for (int repeat = 0; repeat < testcase; repeat++) {
		
		int width = 10, height = 8, length = 17;
		scanf ("%d%d%d", &width, &height, &length);
		
		int field[64][64] =  { 0, };
		
		for (int repeat = 0; repeat < length; repeat++) {
			
			int x = 0, y = 0;
			scanf ("%d%d", &x, &y);
			field[x + 1][y + 1] = 1;
		}
		
		int count = 0;
		for (int row = 1; row <= width; row++) {
			for (int column = 1; column <= height; column++) {
				
				count += Solution (field, row, column) != 0;
			}
		}
		
		printf ("%d\n", count);
	}
	
	return 0;
}

int Solution (int field[64][64], int x, int y) {
	
	if (field[x][y] == 0) return 0;
	else field[x][y] = 0;
	
	int count = 1;
	count += Solution (field, x - 1, y); // up
	count += Solution (field, x, y + 1); // right
	count += Solution (field, x + 1, y); // down
	count += Solution (field, x, y - 1); // left
	
	return count;
}