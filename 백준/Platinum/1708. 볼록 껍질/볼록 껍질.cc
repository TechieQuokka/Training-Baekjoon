#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <unordered_map>

using namespace std;

#define PI 3.14159265358979323846

pair<double, double> pivot = { 2000000000.0, 2000000000.0 };

bool ascending (pair<double, double> element1, pair<double, double> element2) {
	
	double x1 = pivot.first, y1 = pivot.second;
	double x2 = element1.first, y2 = element1.second;
	
	double deltaX1 = x2 - x1;
	double deltaY1 = y2 - y1;
	if (deltaX1 == 0 && deltaY1 == 0) return true;
	
	double theta = atan(deltaY1 / deltaX1);
	double angle1 = theta * 180.0 / PI;
	
	x2 = element2.first, y2 = element2.second;
	
	double deltaX2 = x2 - x1;
	double deltaY2 = y2 - y1;
	if (deltaX2 == 0 && deltaY2 == 0) return false;
	
	theta = atan(deltaY2 / deltaX2);
	double angle2 = theta * 180.0 / PI;
	
	if (angle1 != angle2) return angle1 < angle2;
	return pow(deltaX1, 2.0) + pow(deltaY1, 2.0) < pow(deltaX2, 2.0) + pow(deltaY2, 2.0);
}

pair<double, double> FindTopLeftPoint(const vector<pair<double, double>>& points);
int ConvexHull (vector<pair<double, double>>& buffer, int length);

int main (int argc, char* argv[]) {
	
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int count = 0;
    cin >> count;
	
	vector<pair<double, double>> buffer;
	for (int index = 0; index < count; index++) {
		
		pair<double, double> coordinate;
		cin >> coordinate.first >> coordinate.second;
		buffer.push_back(coordinate);
	}
	
	pivot = FindTopLeftPoint (buffer);
	sort(buffer.begin(), buffer.end(), &ascending);
	
	int result = ConvexHull (buffer, count);
	cout << result << "\n";
	
	return 0;
}

double GetDistance(pair<double, double> p1, pair<double, double> p2) {
	
    return sqrt(pow(p2.first - p1.first, 2.0) + pow(p2.second - p1.second, 2.0));
}

pair<double, double> FindTopLeftPoint(const vector<pair<double, double>>& points) {
    pair<double, double> topLeft = {numeric_limits<double>::max(), numeric_limits<double>::min()};

    for (const auto& point : points) {
        if (point.first < topLeft.first || 
           (point.first == topLeft.first && point.second > topLeft.second)) {
            topLeft = point;
        }
    }

    return topLeft;
}

pair<double, double> FindClosestPoint(const vector<pair<double, double>>& points, pair<double, double> target) {
    
	pair<double, double> closestPoint;
    double minDistance = numeric_limits<double>::max();

    for (const auto& point : points) {
        double distance = GetDistance(target, point);
        if (distance < minDistance) {
            minDistance = distance;
            closestPoint = point;
        }
    }

    return closestPoint;
}

// vector cross product (백터 크로스 곱) 
double crossProduct(const pair<double, double>& p1, const pair<double, double>& p2, const pair<double, double>& p3) {
    
    return (p3.first - p1.first) * (p2.second - p1.second) - (p3.second - p1.second) * (p2.first - p1.first);
}

bool checkTail (pair<double, double> p1, pair<double, double> p2, pair<double, double> p3) {
	
	return crossProduct (p1, p2, p3) == 0.0;
}

int ConvexHull (vector<pair<double, double>>& source, int length) {
	
	deque<pair<double, double>> buffer;
	for (int index = 1; index < 3; index++) {
		
		buffer.push_back (source[index]);
	}
	
	for (int index = 3; index < length; index++) {
		
		bool flag = false;
		while (buffer.size() > 1) {
			
			pair<double, double> p3 = source[index];
			pair<double, double> p2 = buffer.back(); buffer.pop_back();
			pair<double, double> p1 = buffer.back();
			
			double result = crossProduct (p1, p2, p3);
			if (result < 0) { // right
				
				buffer.push_back(p2);
				buffer.push_back(p3);
				flag = true;
				break;
			}
		}
		if (flag == false) buffer.push_back(source[index]);
	}
	buffer.push_front(source[0]);
	int minus = (int) checkTail (buffer.at(0), buffer.at(1), buffer.at(2));
	
	return buffer.size() - minus;
}