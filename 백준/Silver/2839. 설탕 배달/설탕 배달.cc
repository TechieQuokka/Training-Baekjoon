#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    
    int number = 6;
    cin >> number;
    
    for (int pivot = number / 5, sum = 0, temporary = number; pivot >= 0; pivot--, sum = 0) {
        
        number = temporary;
        number -= pivot * 5;
        sum += pivot;
        if (number % 3 == 0) {
            
            sum += number / 3;
            cout << sum << endl;
            return 0;
        }
    }
    
    cout << -1 << endl;
    return 0;
}
