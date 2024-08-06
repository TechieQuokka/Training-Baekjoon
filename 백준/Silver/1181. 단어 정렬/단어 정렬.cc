#include <iostream>
#include <algorithm>

using namespace std;

void PrintArray (string* array, const int size) {
    
    string previous = "";
    int index = 0;
    for (index = 0; index < size; index++) {
        
        if (previous == array[index]) continue;
        previous = array[index];
        cout << array[index] << "\n";
    }
    return;
}

int Ascending (string argument1, string argument2) {
	
	int length1 = argument1.length(), length2 = argument2.length();
	if (length1 == length2) return argument1 < argument2;
	return length1 < length2;
}

int main (int argc, char* argv[]) {
    
    int size = 0;
    cin >> size;
    
    string* list = new string[size];
    if (list == NULL) return 0;
    
    int index = 0;
    for (index = 0; index < size; index++) {
        
        cin >> list[index];
    }
    
    sort (list, list + size, &Ascending);
    PrintArray (list, size);
    return 0;
}
