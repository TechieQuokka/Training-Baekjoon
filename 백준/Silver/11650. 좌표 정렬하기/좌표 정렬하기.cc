#include <iostream>
#include <algorithm>

using namespace std;

struct CoordinateType {

    int X, Y;
};

int Ascending (const struct CoordinateType argument1, const struct CoordinateType argument2) {
    
    if (argument1.X != argument2.X) return argument1.X < argument2.X;
    else return argument1.Y < argument2.Y;
}

void PrintCoordinate (struct CoordinateType* coordinates, size_t size) {
    
    if (coordinates == NULL) throw coordinates;
    
    for (int index = 0; index < size; index++) {
        
        cout << coordinates[index].X << " " << coordinates[index].Y << "\n";
    }
    return;
}

int main (int argc, char* argv[]) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int input = 0;
    cin >> input;
    
    struct CoordinateType* coordinates = new struct CoordinateType[input];
    if (coordinates == NULL) return 0;
    
    for (int index = 0; index < input; index++) cin >> coordinates[index].X >> coordinates[index].Y;
    
    sort (coordinates, coordinates + input, &Ascending);
    PrintCoordinate (coordinates, input);
    return 0;
}