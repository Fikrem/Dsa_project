#ifndef COURSE_H
#define COURSE_H

#include <string>

using namespace std;

class Course {
private:
    string courseCode;
    string courseName;
    string department;
    int yearOfStudy;
    int creditHours;

public:
    // Constructors
    Course();
    Course(const string& code, const string& name, 
           const string& dept, int year, int credits);
    
    // Getters
    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
    string getDepartment() const { return department; }
    int getYearOfStudy() const { return yearOfStudy; }
    int getCreditHours() const { return creditHours; }
    
    // Setters
    void setCourseCode(const string& code) { courseCode = code; }
    void setCourseName(const string& name) { courseName = name; }
    void setDepartment(const string& dept) { department = dept; }
    void setYearOfStudy(int year) { yearOfStudy = year; }
    void setCreditHours(int credits) { creditHours = credits; }
    
    // CSV serialization
    string toCSV() const;
    static Course fromCSV(const string& csvLine);
};

#endif // COURSE_H
