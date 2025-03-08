#include <stdio.h>

long long FindValue (long long* source, int length, long long left, long long right, const long long pivot);

int main (int argc, char* argv[]) {
    
    long long count = 0, pivot = 0;
    scanf ("%lld%lld", &count, &pivot);
    
    static long long source[10001] = { 0, };
    
    long long index = 0, sum = 0;
    for (index = 0; index < count; index++) {
        
        scanf ("%lld", source + index);
        sum += source[index];
    }
    
    long long result = FindValue (source, count, 0, sum / pivot, pivot);
    printf ("%lld\n", result == 0 ? 1 : result);
    return 0;
}

long long GetNumberOfSplitItem (long long* source, long long length, double value) {
    
    long long sum = 0;
    int index = 0;
    for (index = 0; index < length; index++) {
        
        sum += source[index] / value;
    }
    return sum;
}

long long FindValue (long long* source, int length, long long left, long long right, const long long pivot) {
    
    long long middle = (left + right) / 2;
    if (left > right) return middle;
    
    if (GetNumberOfSplitItem (source, length, middle) >= pivot) return FindValue (source, length, middle + 1, right, pivot);
    return FindValue (source, length, left, middle - 1, pivot);
}
