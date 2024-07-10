#include <iostream>

using namespace std;

struct CourseType {

    string SubjectName;
    double Score;
    string Grade;
};

double CalculateRating (struct CourseType courses[32], int count);

int main (int argc, char* argv[]) {
    
    struct CourseType courses[32];
    
    int count = 20;
    for (int index = 0; index < count; index++) {
        
        cin >> courses[index].SubjectName >> courses[index].Score >> courses[index].Grade;
    }
    
    cout << CalculateRating (courses, count) << endl;
    return 0;
}

double ConvertGradeToScore (string grade) {
    
    if (grade == "A+")      return 4.5;
    else if (grade == "A0") return 4.0;
    else if (grade == "B+") return 3.5;
    else if (grade == "B0") return 3.0;
    else if (grade == "C+") return 2.5;
    else if (grade == "C0") return 2.0;
    else if (grade == "D+") return 1.5;
    else if (grade == "D0") return 1.0;
    else if (grade == "F")  return 0.0;
    return -1.0;
}

double CalculateRating (struct CourseType courses[32], int count) {
    
    if (courses == NULL) throw;
    
    double sum = 0.0, total = 0.0;
    for (int index = 0; index < count; index++) {
        
        double score = courses[index].Score, grade = ConvertGradeToScore (courses[index].Grade);
        if (grade == -1.0) continue;
        sum += score * grade;
        total += score;
    }
    return sum / total;
}
