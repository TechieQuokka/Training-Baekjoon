#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

struct SolutionType {
    
    int X, Y;
};

struct SolutionType SystemOfEquations (int a, int b, int c, int d, int e, int f);

int main (int argc, char* argv[]) {
    
    int a = 1, b = 3, c = -1, d = 4, e = 1, f = 7;
    cin >> a >> b >> c >> d >> e >> f;
    auto result = SystemOfEquations (a, b, c, d, e, f);
    cout << result.X << " " << result.Y << "\n";
    return 0;
}

struct SolutionType SystemOfEquations (int a, int b, int c, int d, int e, int f) {
    
    list<struct SolutionType> solution;
    int maximum = 1000;
    for (int x = -999; x < maximum; x++) {
        for (int y = -999; y < maximum; y++) {
            
            int result = a * x + b * y;
            if (result == c) solution.push_back({x, y});
        }
    }
    
    for (int x = -999; x < maximum; x++) {
        for (int y = -999; y < maximum; y++) {
            
            int result = d * x + e * y;
            if (result != f) continue;
            
            auto it = find_if(solution.begin(), solution.end(), [x, y](const struct SolutionType& element){
                                  return element.X == x && element.Y == y; });
            if (it == solution.end()) continue;
            return {x, y};
        }
    }
    
    return {-999999, -999999};
}
