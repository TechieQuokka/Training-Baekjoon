#include <iostream>
#include <cmath>

using namespace std;

int Blackjack (int* array, int length, int number);

int main (int argc, char* argv[]) {
    
    int size = 0, number = 0;
    cin >> size >> number;
    int* array = new int[size];
    if (array == NULL) return 0;
    
    for (int index = 0; index < size; index++) {
        
        cin >> array[index];
    }
    
    cout << Blackjack (array, size, number) << "\n";
    delete[] array;
    return 0;
}

int Blackjack (int* array, int length, int number) {
    
    if (array == NULL) throw array;
    
    int result = 0;
    for (int first = 0; first < length; first++) {
        for (int second = first + 1; second < length; second++) {
            for (int third = second + 1; third < length; third++) {
                
                int sum = array[first] + array[second] + array[third];
                if ((sum - result) > 0 && number >= sum) result = sum;
            }
        }
    }
    return result;
}
