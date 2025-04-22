#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    long long prev, curr;
    scanf("%lld", &prev);
    
    long long count = 0;
    for (int i = 1; i < N; i++) {
        scanf("%lld", &curr);
        
        if (prev <= curr) {
            prev = curr;
        } else {
            long long ratio = (prev + curr - 1) / curr;
            int exponent = 0;
            long long power = 1;
            
            while (power < ratio) {
                power <<= 1;
                exponent++;
            }
            
            count += exponent;
            prev = curr * power;
        }
    }
    
    printf("%lld\n", count);
    return 0;
}