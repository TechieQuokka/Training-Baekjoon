#include <stdio.h>
#include <stdbool.h>

struct CoordinateType {
    double X, Y;
};

struct LineType {
    struct CoordinateType point1;
    struct CoordinateType point2;
};

double Counterclockwise(struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3);
bool Solution(struct LineType line1, struct LineType line2);
void Swap(struct CoordinateType* a, struct CoordinateType* b);

int main(int argc, char* argv[]) {
    struct LineType line1 = {0, }, line2 = {0, };

    scanf("%lf%lf%lf%lf", &line1.point1.X, &line1.point1.Y, &line1.point2.X, &line1.point2.Y);
    scanf("%lf%lf%lf%lf", &line2.point1.X, &line2.point1.Y, &line2.point2.X, &line2.point2.Y);

    printf("%d\n", Solution(line1, line2));
    return 0;
}

void Swap(struct CoordinateType* a, struct CoordinateType* b) {
    struct CoordinateType temp = *a;
    *a = *b;
    *b = temp;
    return;
}

bool Compare (struct CoordinateType point1, struct CoordinateType point2) {
  
  if (point1.X != point2.X) return point1.X > point2.X;
  return point1.Y > point2.Y;
}

bool Compare2 (struct CoordinateType point1, struct CoordinateType point2) {
  
  if (point1.X != point2.X) return point1.X >= point2.X;
  return point1.Y >= point2.Y;
}

bool Solution(struct LineType line1, struct LineType line2) {
    double a = Counterclockwise(line1.point1, line1.point2, line2.point1);
    double b = Counterclockwise(line1.point1, line1.point2, line2.point2);
    double c = Counterclockwise(line2.point1, line2.point2, line1.point1);
    double d = Counterclockwise(line2.point1, line2.point2, line1.point2);

    double c1 = a * b;
    double c2 = c * d;
    
    if (c1 == 0 && c2 == 0) {
      if (Compare (line1.point1, line1.point2)) Swap (&line1.point1, &line1.point2);
      if (Compare (line2.point1, line2.point2)) Swap (&line2.point1, &line2.point2);
      if (Compare2 (line1.point2, line2.point1) && Compare2 (line2.point2, line1.point1)) return true;
      else return false;
    }
    else if (c1 <= 0 && c2 <= 0) return true;
    else return false;
}

double Counterclockwise(struct CoordinateType p1, struct CoordinateType p2, struct CoordinateType p3) {
    double result = (p2.X - p1.X) * (p3.Y - p2.Y) - (p2.Y - p1.Y) * (p3.X - p2.X);

    if (result > 0) return 1;
    else if (result == 0) return 0;
    else return -1;
}
