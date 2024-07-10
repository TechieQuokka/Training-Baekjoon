#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

void AlphabetCounter (int* counter, string source);
vector<string> GetGroupPattern (int* counter, int length);
string MakeString (char character, int count);

int main (int argc, char* argv[]) {
    
    int counter[128] = { 0, };
    int input = 3;
    cin >> input;
    
    int count = 0;
    for (int loop = 0; loop < input; loop++) {
        
        string source = "abababab";
        cin >> source;
    
        AlphabetCounter (counter, source);
        vector<string> pattern = GetGroupPattern (counter, 128);
        memset (counter, 0, 128 * sizeof (int));
        
        bool result = true;
        int size = pattern.size();
        for (int index = 0; index < size; index++) {
            
            int indexer = source.find(pattern[index]);
            if (indexer < 0) {
                
                result = false;
                break;
            }
        }
        
        count += (int) result;
    }
    
    cout << count << endl;
    return 0;
}

string MakeString (char character, int count) {
    
    char* source = new char[count + 1];
    for (int index = 0; index < count; index++)
        source[index] = character;
    source[count] = '\0';
    
    string destination(source);
    delete source;
    return destination;
}

vector<string> GetGroupPattern (int* counter, int length) {
    
    if (counter == NULL) return vector<string>();
    
    vector<string> list;
    for (int index = 0; index < length; index++) {
        
        if (counter[index] > 1) list.push_back (MakeString ((char)index, counter[index]));
    }
    return list;
}

void AlphabetCounter (int* counter, string source) {

    if (counter == NULL) return;
    
    int length = source.length();
    for (int index = 0; index < length; index++) {
        
        counter[source[index]]++;
    }
    return;
}
