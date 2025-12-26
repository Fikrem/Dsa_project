using namespace std;

#include "../include/Grader.h"

string Grader::calculateLetterGrade(double totalScore) {
    if (totalScore >= 90) return "A+";
    if (totalScore >= 85 && totalScore < 90) return "A";
    if (totalScore >= 80 && totalScore < 85) return "A-";
    if (totalScore >= 75 && totalScore < 80) return "B+";
    if (totalScore >= 70 && totalScore < 75) return "B";
    if (totalScore >= 65 && totalScore < 70) return "B-";
    if (totalScore >= 60 && totalScore < 65) return "C+";
    if (totalScore >= 55 && totalScore < 60) return "C";
    if (totalScore >= 50 && totalScore < 55) return "C-";
    if (totalScore < 50) return "F";
    
    return "F";
}

double Grader::getGradePoint(const string& grade) {
    if (grade == "A+" || grade == "A") return 4.0;
    if (grade == "A-") return 3.75;
    if (grade == "B+") return 3.5;
    if (grade == "B") return 3.0;
    if (grade == "B-") return 2.75;
    if (grade == "C+") return 2.5;
    if (grade == "C") return 2.0;
    if (grade == "C-") return 1.75;
    if (grade == "F") return 0.0;
    return 0.0;
}

void Grader::gradeCourse(Student& student, const string& courseCode,
                        double assessment, double finalExam, int creditHours) {
    if (assessment < 0 || assessment > 50 || finalExam < 0 || finalExam > 50) {
        return;
    }
    
    double totalScore = assessment + finalExam;
    string grade = calculateLetterGrade(totalScore);
    
    CourseResult result(assessment, finalExam, grade, creditHours);
    student.addCourse(courseCode, result);
}
