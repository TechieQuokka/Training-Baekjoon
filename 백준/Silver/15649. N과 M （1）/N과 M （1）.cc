#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void Permutation (int size, int limit, int pivot, bool isDuplicate, void (*display) (int*, int));
int ASCIIStringToInteger (char* source, int length);

void Display (int* buffer, int size) {
    
    static char bucket[16] = { '1', '2', '3', '4', '5', '6', '7', '8' };
    static int position = 1;
    
    char storage[16] = { 0, };
    
    //printf ("%3d : ", position++);
    int index = 0;
    for (index = 0; index < size; index++) {
        
        char character = bucket[buffer[index]];
        printf ("%c ", character);
        storage[index] = character;
    }
    printf ("\n");
    
    int compare = ASCIIStringToInteger (storage, 2) % 3 == 0;
    //printf ("-> %c\n", compare ? 'O' : 'X');
    return;
}

int main (int argc, char* argv[]) {
    
    int n = 0, m = 0;
    scanf ("%d%d", &n, &m);
    Permutation (n, m, 0, false, &Display);
    return 0;
}

void Permutation (int size, int limit, int pivot, bool isDuplicate, void (*display) (int*, int)) {
    
    static int buffer[16] = { 0, };
    static bool check[16] = { 0, };
    
    if (limit == pivot) {
        
        if (display != NULL) display (buffer, limit);
        return;
    }
    
    int index = 0;
    for (index = 0; index < size; index++) {
        
        if (check[index] && !isDuplicate) continue;
        
        buffer[pivot] = index;
        check[index] = true;
        Permutation (size, limit, pivot + 1, isDuplicate, display);
        check[index] = false;
    }
    return;
}

int ASCIIStringToInteger (char* source, int length) {
    
    if (source == NULL) return 0;
    
    int digit = 0;
    int result = 0, index = 0;
    for (index = 0; index < length; index++) {
        
        char character = source[length - index - 1];
        result += (character - '0') * pow (10, digit);
        if (result > 0) digit++;
    }
    
    return result;
}
