#ifndef GRADER_H
#define GRADER_H

#include "Student.h"

class Grader {
public:
    // Calculate letter grade from total score (0-100)
    static std::string calculateLetterGrade(double totalScore);
    
    // Calculate grade point from letter grade
    static double getGradePoint(const std::string& grade);
    
    // Add or update a course grade for a student
    static void gradeCourse(Student& student, const std::string& courseCode,
                           double assessment, double finalExam, int creditHours);
};

#endif // GRADER_H
