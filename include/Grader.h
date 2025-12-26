#ifndef GRADER_H
#define GRADER_H

#include "Student.h"
#include <vector>

class Grader {
public:
    // Calculate letter grade from total score (0-100)
    static char calculateLetterGrade(double totalScore);
    
    // Calculate grade point from letter grade
    static double getGradePoint(char grade);
    
    // Calculate SGPA for a student based on their courses
    static double calculateSGPA(const Student& student);
    
    // Update student's GPA
    static void updateStudentGPA(Student& student);
    
    // Add or update a course grade for a student
    static void gradeCourse(Student& student, const std::string& courseCode,
                           double assessment, double finalExam, int creditHours);
};

#endif // GRADER_H
