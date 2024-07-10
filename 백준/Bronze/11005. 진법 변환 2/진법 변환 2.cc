#include <stdio.h>
#include <math.h>

char* ConvertNumber (const int number, const int notation);

int main (int argc, char* argv[]) {
    
    int number = 0, notation = 0;
    scanf ("%d%d", &number, &notation);
    
    char* result = ConvertNumber (number, notation);
    printf ("%s", result);
    return 0;
}

long double logN(long double base, long double number) {

	return logl(number) / logl(base);
}

char NumberToCharacter (int number) {
    
    return number < 10 ? number + '0' : number + 'A' - 10;
}

char* ConvertNumber (const int number, const int notation) { // 60466175 36
    
    long long int value = number;
    
    static char buffer[128] = { 0, };
    int index = 0; int exponent = (int) logN ((long double)notation, (long double)value); // logN (36, 60466175) -> 4.999999995385
    for (index = 0; value > 0; index++, exponent--) {
        
        long long int decrement = 0;
        for (decrement = notation - 1; decrement >= 0; decrement--) {
            
            long long int calculate = value - (long long int) powl ((long double)notation, (long double)exponent) * decrement;
            if (calculate < 0) continue;
            
            value = calculate;
            buffer[index] = NumberToCharacter (decrement);
            break;
        }
    }
    while ((int)logN (notation, number) != (index - 1)) {
        
        buffer[index++] = '0';
    }
    buffer[index] = '\0';
    
    return buffer;
}
