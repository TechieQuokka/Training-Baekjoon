#include <stdio.h>

unsigned Power (unsigned base, unsigned exponent, unsigned remain);

int main (int argc, char* argv[]) {
    
    unsigned base = 2U, exponent = 10U, remain = 0U;
    
    scanf ("%u%u%u", &base, &exponent, &remain);
    
    printf ("%u", Power (base, exponent, remain));
    return 0;
}

unsigned Power (unsigned base, unsigned exponent, unsigned remain) {
    
    if (exponent == 0U) return 1U;
    if (exponent <= 1U) return base % remain;
    
    long long int result = (long long int) Power (base, exponent / 2U, remain) % remain;
    
    if (exponent % 2U == 0U) return (result * result) % remain;
    else return result * result % remain * base % remain;
}
