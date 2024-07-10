#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main (int argc, char* argv[]) {

    int number = 0;
    cin >> number;
    
    vector<int> source, original;
    for (int loop = 0; loop < number; loop++) {
        
        int value = 0;
        cin >> value;
        source.push_back(value), original.push_back(value);
    }
    
    sort (source.begin(), source.end());
    source.erase(unique(source.begin(), source.end()), source.end());
    
    for(int index = 0; index < number; index++) {
        
        cout << lower_bound (source.begin(), source.end(), original[index]) - source.begin() << " ";
    }
    cout << "\n";
    return 0;
}
