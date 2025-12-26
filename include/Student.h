#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <map>

using namespace std;

// Struct to hold course result information
struct CourseResult {
    double assessment;    // Out of 50
    double finalExam;     // Out of 50
    char grade;           // A, B, C, D, F
    int creditHours;
    
    CourseResult() : assessment(0), finalExam(0), grade('F'), creditHours(0) {}
    CourseResult(double assess, double final, char g, int credits)
        : assessment(assess), finalExam(final), grade(g), creditHours(credits) {}
    
    double getTotalScore() const { return assessment + finalExam; }
};

class Student {
private:
    string id;
    string passwordHash;
    string firstName;
    string lastName;
    string department;
    int age;
    char sex;
    int yearOfStudy;
    string section;
    map<string, CourseResult> courses;  // courseCode -> CourseResult
    double gpa;  // SGPA only

public:
    // Constructors
    Student();
    Student(const string& id, const string& password,
            const string& firstName, const string& lastName,
            const string& department, int age, char sex,
            int yearOfStudy, const string& section);
    
    // Getters
    string getId() const { return id; }
    string getPasswordHash() const { return passwordHash; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getFullName() const { return firstName + " " + lastName; }
    string getDepartment() const { return department; }
    int getAge() const { return age; }
    char getSex() const { return sex; }
    int getYearOfStudy() const { return yearOfStudy; }
    string getSection() const { return section; }
    double getGPA() const { return gpa; }
    const map<string, CourseResult>& getCourses() const { return courses; }
    
    // Setters
    void setId(const string& newId) { id = newId; }
    void setPassword(const string& password);
    void setFirstName(const string& name) { firstName = name; }
    void setLastName(const string& name) { lastName = name; }
    void setDepartment(const string& dept) { department = dept; }
    void setAge(int newAge) { age = newAge; }
    void setSex(char newSex) { sex = newSex; }
    void setYearOfStudy(int year) { yearOfStudy = year; }
    void setSection(const string& sec) { section = sec; }
    void setGPA(double newGpa) { gpa = newGpa; }
    
    // Course management
    void addCourse(const string& courseCode, const CourseResult& result);
    void updateCourse(const string& courseCode, const CourseResult& result);
    void removeCourse(const string& courseCode);
    bool hasCourse(const string& courseCode) const;
    CourseResult getCourseResult(const string& courseCode) const;
    
    // Authentication
    bool verifyPassword(const string& password) const;
    
    // GPA calculation
    void calculateGPA();
    
    // CSV serialization
    string toCSV() const;
    static Student fromCSV(const string& csvLine);
    
    // Comparison operators for sorting
    bool operator<(const Student& other) const { return id < other.id; }
    bool operator>(const Student& other) const { return id > other.id; }
    bool operator==(const Student& other) const { return id == other.id; }
};

#endif // STUDENT_H
