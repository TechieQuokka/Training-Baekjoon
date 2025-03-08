#include <stdio.h>

struct CoordinateType {

    double X, Y;
};

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3);

int main (int argc, char* argv[]) {

    struct CoordinateType p1, p2, p3;
    scanf ("%lf%lf", &p1.X, &p1.Y);
    scanf ("%lf%lf", &p2.X, &p2.Y);
    scanf ("%lf%lf", &p3.X, &p3.Y);

    double result = Counterclockwise (p1, p2, p3);
    if (result < 0) printf ("-1");
    else if (result > 0) printf ("1");
    else printf ("0");
    return 0;
}

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3) {

    double result = (p2.X - p1.X) * (p3.Y - p2.Y) - (p2.Y - p1.Y) * (p3.X - p2.X);
    return result;
}