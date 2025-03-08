#include <stdio.h>
#include <stdlib.h>

struct CoordinateType {

    double X, Y;
};

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3);
double Solution (struct CoordinateType* coordinates, int size);

int main (int argc, char* argv[]) {

    int count = 0;
    scanf ("%d", &count);

    struct CoordinateType data[10001];
    for (int index = 0; index < count; index++) {

        double x = 0, y = 0;
        scanf ("%lf%lf", &x, &y);

        data[index].X = x;
        data[index].Y = y;
    }

    double result = Solution (data, count);
    printf ("%.1lf\n", result);
    return 0;
}

double Solution (struct CoordinateType* coordinates, int size) {

    double result = 0;
    for (int index = 1; index < size - 1; index++) {

        result += Counterclockwise (coordinates[0], coordinates[index], coordinates[index + 1]) / 2.0;
    }

    return abs(result);
}

double Counterclockwise (struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3) {

    double result = (p2.X - p1.X) * (p3.Y - p2.Y) - (p2.Y - p1.Y) * (p3.X - p2.X);
    return result;
}