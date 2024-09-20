#include <iostream>
#include <vector>

using namespace std;

int Find (vector<int>& table, int number);
void Union (vector<int>& table, int a, int b);

int main(int argc, char* argv[]) 
{
    int number = 0, count = 0;
    
    cin >> number >> count;
    
    vector<int> table (number + 1);
    for (int index = 0; index <= number; index++) {
      
        table[index] = index;
    }
    
    for (int repeat = 0; repeat < count; repeat++) {
      
        int command = 0, a = 0, b = 0;
        scanf ("%d%d%d", &command, &a, &b);
        
        if (command == 0) Union (table, a, b);
        else {
          
            a = Find (table, a);
            b = Find (table, b);
            printf ("%s\n", a == b ? "YES" : "NO");
        }
    }
    return 0;
}

int Find (vector<int>& table, int number) {
  
    if (number == table[number]) {
      
        return table[number];
    }
    return table[number] = Find (table, table[number]);
}

void Union (vector<int>& table, int a, int b) {
    
    a = Find (table, a);
    b = Find (table, b);
    if (a > b) table[a] = b;
    else table[b] = a;
    return;
}