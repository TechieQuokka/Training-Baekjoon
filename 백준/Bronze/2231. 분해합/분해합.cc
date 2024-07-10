#include <iostream>
#include <cmath>

using namespace std;

unsigned int FindConstructor (unsigned int number);

int main (int argc, char* argv[]) {
    
    unsigned int number = 0U;
    cin >> number;
    cout << FindConstructor (number) << endl;
    return 0;
}

unsigned int FindConstructor (unsigned int number) {
    
    unsigned int digit = (unsigned int) log10 ((double) number) + 1U;
    unsigned int pivot = number < 18U ? 0 : number - digit * 9U;

    for (unsigned int constructor = pivot; constructor < number; constructor++) {
        
        unsigned int sum = constructor;
        for (unsigned int loop = 0U, element = constructor; loop < digit; loop++, element /= 10U) {
            
            sum += element % 10U;
        }
        
        if (number == sum) return constructor;
    }
    return 0;
}
