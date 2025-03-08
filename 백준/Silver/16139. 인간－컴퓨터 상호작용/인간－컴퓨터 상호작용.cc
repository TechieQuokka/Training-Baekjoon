#include <stdio.h>
#include <stdbool.h>

int main (int argc, char* argv[]) {
    
    static int table[26][200001] = { 0, };
    
    static char buffer[200001] = { 0, };
    scanf ("%s", buffer);
    
    int index = 0, alphabet = 0;
    for (index = 1; true; index++) {
        
        char character = buffer[index - 1];
        if (character == '\0') break;
        
        for (alphabet = 0; alphabet < 26; alphabet++) {
            
            table[alphabet][index] = table[alphabet][index - 1];
        }
        table[character - 'a'][index]++;
    }
    
    int length = 4, repeat = 0;
    scanf (" %d ", &length);
    for (repeat = 0; repeat < length; repeat++) {
        
        char character = 0;
        int start = 0, end = 0;
        scanf (" %c%d%d", &character, &start, &end);
        
        int result = table[character - 'a'][end + 1] - table[character - 'a'][start];
        printf ("%d\n", result);
    }
    return 0;
}
