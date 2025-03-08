#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct CoordinateType {

    double X, Y;
};

struct LineType {

    struct CoordinateType point1;
    struct CoordinateType point2;
};

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3);
bool Solution (struct LineType line1, struct LineType line2);

int main (int argc, char* argv[]) {

    struct LineType line1 = { 0, }, line2 = { 0, };

    scanf ("%lf%lf%lf%lf", &line1.point1.X, &line1.point1.Y, &line1.point2.X, &line1.point2.Y);
    scanf ("%lf%lf%lf%lf", &line2.point1.X, &line2.point1.Y, &line2.point2.X, &line2.point2.Y);

    printf ("%d\n", Solution (line1, line2));
    return 0;
}

void Swap (double* left, double* right) {

    double temp = *left;
    *left = *right;
    *right = temp;
    return;
}


bool Solution (struct LineType line1, struct LineType line2) {

    double a = Counterclockwise (line1.point1, line1.point2, line2.point1);
    double b = Counterclockwise (line1.point1, line1.point2, line2.point2);
    double c = Counterclockwise (line2.point1, line2.point2, line1.point1);
    double d = Counterclockwise (line2.point1, line2.point2, line1.point2);

    double c1 = a * b;
    double c2 = c * d;

    
    return c1 <= 0 && c2 <= 0;
}

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3) {

    double result = (p2.X - p1.X) * (p3.Y - p2.Y) - (p2.Y - p1.Y) * (p3.X - p2.X);
    return result;
}