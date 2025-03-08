#include <iostream>
#include <vector>

using namespace std;

struct ItemType {
    
    int Weight, Value;
};

int Calculate (struct ItemType* items, int maxWeight, int length);

int main (int argc, char* argv[]) {
    
    int length = 0, maxWeight = 0;
    cin >> length >> maxWeight;
    
    struct ItemType* items = new struct ItemType[length + 1];
    if (items == NULL) throw;
    
    items[0] = {0, 0};
    for (int index = 1; index <= length; index++) {
        
        cin >> items[index].Weight >> items[index].Value;
    }
    
    cout << Calculate (items, maxWeight, length);
    
    return 0;
}

int Calculate (struct ItemType* items, int maxWeight, int length) {
    
    if (items == NULL) throw;
    
    static int table[128][100010] = { 0, };
    
    for (int index = 1; index <= length; index++) {
        for (int weight = 1; weight <= maxWeight; weight++) {
            if (weight - items[index].Weight < 0) table[index][weight] = table[index - 1][weight];
            else table[index][weight] = max (table[index - 1][weight], table[index - 1][weight - items[index].Weight] + items[index].Value);
        }
    }
    
    return table[length][maxWeight];
}
