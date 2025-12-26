using namespace std;

#include "../include/Grader.h"

char Grader::calculateLetterGrade(double totalScore) {
    if (totalScore >= 90) return 'A';
    if (totalScore >= 80) return 'B';
    if (totalScore >= 70) return 'C';
    if (totalScore >= 60) return 'D';
    return 'F';
}

double Grader::getGradePoint(char grade) {
    switch (grade) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return 0.0;
    }
}

double Grader::calculateSGPA(const Student& student) {
    const auto& courses = student.getCourses();
    
    if (courses.empty()) {
        return 0.0;
    }
    
    double totalPoints = 0.0;
    int totalCredits = 0;
    
    for (const auto& pair : courses) {
        const CourseResult& result = pair.second;
        double gradePoint = getGradePoint(result.grade);
        totalPoints += gradePoint * result.creditHours;
        totalCredits += result.creditHours;
    }
    
    return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

void Grader::updateStudentGPA(Student& student) {
    student.calculateGPA();
}

void Grader::gradeCourse(Student& student, const string& courseCode,
                        double assessment, double finalExam, int creditHours) {
    // Validate scores
    if (assessment < 0 || assessment > 50 || finalExam < 0 || finalExam > 50) {
        return;
    }
    
    double totalScore = assessment + finalExam;
    char grade = calculateLetterGrade(totalScore);
    
    CourseResult result(assessment, finalExam, grade, creditHours);
    student.addCourse(courseCode, result);
}
