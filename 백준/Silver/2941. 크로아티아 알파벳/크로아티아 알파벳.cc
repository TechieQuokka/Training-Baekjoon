#include <iostream>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {
    
    string croatiaAlphabet[] = { "c=", "c-", "dz=", "d-", "lj", "nj", "s=", "z=" };
    int length = sizeof (croatiaAlphabet) / sizeof (string);
    
    string sentence = "ljes=njak";
    cin >> sentence;
    int size = sentence.length();
    
    for (int index = 0; index < length; index++) {
        for (int loop = 0; loop < size; loop++) {
            
            int position = sentence.find(croatiaAlphabet[index]);
            if (position >= 0) sentence.replace (position, croatiaAlphabet[index].length(), "a");
        }
    }
    
    cout << sentence.length() << endl;
    return 0;
}
