#include <stdio.h>
#include <stdlib.h>

int Solution (int* source, int length, const int target);

int Ascending (const void* argument1, const void* argument2) {
	
	return *(int*) argument1 > *(int*) argument2 ? 1 : -1;
}

int main (int argc, char* argv[]) {
	
	int length = 0;
	scanf ("%d", &length);
	
	int source[100001] = { 0, };
	
	int index = 0;
	for (index = 0; index < length; index++) {
		
		int element = 0;
		scanf ("%d", &element);
		source[index] = element;
	}
	
	qsort ((int*) source, length, sizeof (int), &Ascending);
	
	int target = 0;
	scanf ("%d", &target);
	int result = Solution (source, length, target);
	
	printf ("%d", result);
	return 0;
}

int Solution (int* source, int length, const int target) {
	
	if (source == NULL) return -1;
	
	int count = 0;
	int left = 0, right = 0;
	for (left = 0, right = length - 1; left < right; ) {
		
		//printf ("%d %d\n", source[left], source[right]);
		int compare = target == source[left] + source[right];
		count += compare;
		
		if (compare) {
			if (source[left + 1] + source[right] < source[left] + source[right - 1]) left++;
			else right--;
		}
		else {
			if (source[left] + source[right] < target) left++;
			else right--;
		}
	}
	
	return count;
}