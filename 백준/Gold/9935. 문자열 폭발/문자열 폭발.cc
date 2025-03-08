#include <iostream>
#include <deque>

using namespace std;

bool CheckTarget (deque<char>& pocket, string& target);

int main (int argc, char* argv[]) {
    
    string source, target;
    cin >> source >> target;
    
    deque<char> pocket;
    
    int length = source.length(), size = target.length();
    for (int index = 0; index < length; index++) {
    
        char element = source[index];
        pocket.push_back(element);
        if (!(element == target[size - 1] && CheckTarget (pocket, target))) continue;
        
        for (int loop = 0; loop < size; loop++) pocket.pop_back();
    }
    
    if (pocket.empty()) {
        
        cout << "FRULA";
        return 0;
    }
    
    for (auto itorator = pocket.begin(); itorator != pocket.end(); itorator++) {
        
        cout << *itorator;
    }
    
    return 0;
}

bool CheckTarget (deque<char>& pocket, string& target) {
    
    if (pocket.size() < target.length()) return false;
    
    int index = target.length() - 1;
    bool check = false;
    for (auto itorator = pocket.rbegin(); itorator != pocket.rend() && index >= 0; itorator++, index--, check = true) {
        
        char element = *itorator;
        if (element != target[index]) return false;
    }
    return true && check;
}
