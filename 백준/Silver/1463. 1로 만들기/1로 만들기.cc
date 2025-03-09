#include <stdio.h>

int minimum (int left, int right) {
    
    return left < right ? left : right;
}

int main (int argc, char* argv[]) {
    
    int number = 0;
    scanf ("%d", &number);
    
    int buffer[1000000] = {0};
    int index = 0;
    for (index = 2; index <= number; index++) {
        
        buffer[index] = buffer[index - 1] + 1;
        if (index % 2 == 0) buffer[index] = minimum (buffer[index], buffer[index / 2] + 1);
        if (index % 3 == 0) buffer[index] = minimum (buffer[index], buffer[index / 3] + 1);
    }
    printf ("%d\n", buffer[number]);
    return 0;
}
