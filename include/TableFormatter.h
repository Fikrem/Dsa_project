#ifndef TABLEFORMATTER_H
#define TABLEFORMATTER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;

class TableFormatter {
public:
    // Display single student in table format
    static void displayStudent(const Student& student);
    
    // Display multiple students in table format
    static void displayStudents(const vector<Student>& students);
    
    // Display student with detailed course information
    static void displayStudentDetailed(const Student& student);
    
private:
    // Helper functions for table drawing
    static void printHorizontalLine(const vector<int>& columnWidths);
    static void printRow(const vector<string>& values,
                        const vector<int>& columnWidths);
    static string centerText(const string& text, int width);
    static string padRight(const string& text, int width);
};

#endif // TABLEFORMATTER_H
