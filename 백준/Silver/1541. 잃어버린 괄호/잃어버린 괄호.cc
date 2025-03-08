#include <stdio.h>
#include <stdbool.h>

int StringToInteger (const char* const source, int* const nextPosition);

int main (int argc, char* argv[]) {
    
    char source[128] = { 0, };
    scanf ("%s", source);
    
    int index = 0, pivot = 0, sum = 0, position = 0, sign = source[0] == '-' ? -1 : 1;
    for (index = 0; source[pivot] != '\0'; pivot += position) {
            
        int element = StringToInteger (source + pivot, &position);
        if (element < 0) element *= (-1);
        
        sum += element * sign;
        if (source[pivot + position] == '-') sign = -1;
    }
    
    printf ("%d\n", sum);
    
    return 0;
}

bool IsDigit (char character) {
    
    return character >= '0' && character <= '9';
}

int StringToInteger (const char* const source, int* const nextPosition) {
    
    if (source == NULL || nextPosition == NULL) return -1;
    
    int sign = 1;
    if (source[0] == '-') sign = -1;
    
    int index = 0, result = 0;
    for (index = (int)(source[0] == '+' || source[0] == '-'); source[index] != '\0' && IsDigit (source[index]); index++) {
        
        int element = source[index] - '0';
        result *= 10;
        result += element;
    }
    result *= sign;
    
    *nextPosition = index;
    return result;
}
