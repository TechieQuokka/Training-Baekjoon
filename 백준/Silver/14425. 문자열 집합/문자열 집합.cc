#include <iostream>
#include <map>

using namespace std;

int main (int argc, char* argv[]) {
    
    map<string, bool> map;
    
    int sourceLength = 0, targetLength = 0;
    cin >> sourceLength >> targetLength;
    
    for (int repeat = 0; repeat < sourceLength; repeat++) {
        
        string source;
        cin >> source;
        
        map[source] = true;
    }
    
    int count = 0;
    for (int repeat = 0; repeat < targetLength; repeat++) {
        
        string target;
        cin >> target;
        
        count += map[target];
    }
    
    cout << count << '\n';
    map.clear();
    return 0;
}
