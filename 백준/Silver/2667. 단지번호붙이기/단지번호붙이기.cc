#include <stdio.h>
#include <stdlib.h>

int Solution (int apartment[32][32], int size, int x, int y);

int compare (const void* left, const void* right) {
	
	return *(int*) left > *(int*) right;
}

int main (int argc, char* argv[]) {
	
	int length = 0;
	scanf ("%d", &length);
	
	int apartment[32][32] = { 0, };
	for (int row = 1; row <= length; row++) {
		for (int column = 1; column <= length; column++) {
			
			char character = getchar();
			if (character == '\n') {
				
				column--;
				continue;
			}
			apartment[row][column] = character - '0';
		}
	}
	
	int result[625] = { 0, };
	int current = 0;
	for (int row = 1; row <= length; row++) {
		for (int column = 1; column <= length; column++) {
			
			int count = Solution (apartment, length, row, column);
			if (count == 0) continue;
			
			result[current++] = count;
		}
	}
	
	qsort ((int*) result, current, sizeof (int), &compare);
	
	printf ("%d\n", current);
	for (int index = 0; index < current; index++) {
		
		printf ("%d\n", result[index]);
	}
	return 0;
}

int Solution (int apartment[32][32], int size, int x, int y) {
	
	if (apartment[x][y] == 0) return 0;
	else apartment[x][y] = 0;
	
	int count = 1;
	count += Solution (apartment, size, x - 1, y); // up
	count += Solution (apartment, size, x, y + 1); // right
	count += Solution (apartment, size, x + 1, y); // down
	count += Solution (apartment, size, x, y - 1); // left
	
	return count;
}