#include <stdio.h>
#include <limits.h>

long long int Power (long long int base, long long int exponent, long long int modular);
long long int Factorial (long long int number, long long int modular);

int main (int argc, char* argv[]) {
    
    long long int n = 0LL, k = 0LL;
    scanf ("%lld%lld", &n, &k);
    
    long long int numerator = Factorial (n, 1000000007LL);
    long long int denominator = Factorial (k, 1000000007LL) * Factorial (n - k, 1000000007LL) % 1000000007LL;
    
    printf ("%lld", numerator * Power (denominator, 1000000007LL - 2LL, 1000000007LL) % 1000000007LL);
    return 0;
}

long long int Power (long long int base, long long int exponent, long long int modular) {
    
    if (exponent == 0LL) return 1LL;
    if (exponent <= 1LL) return base % modular;
    
    long long int result = Power (base, exponent / 2LL, modular) % modular;
    
    if (exponent % 2LL == 0LL) return (result * result) % modular;
    else return result * result % modular * base % modular;
}

long long int Factorial (long long int number, long long int modular) {
    
    if (number <= 1LL) return 1;
    return number * Factorial (number - 1LL, modular) % modular;
}
