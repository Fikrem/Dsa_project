using namespace std;

#include "../include/Student.h"
#include "../include/Utils.h"
#include <sstream>

Student::Student() : id(""), passwordHash(""), firstName(""), lastName(""),
                     department(""), age(0), sex('M'), yearOfStudy(1),
                     section(""), gpa(0.0) {}

Student::Student(const string& id, const string& password,
                 const string& firstName, const string& lastName,
                 const string& department, int age, char sex,
                 int yearOfStudy, const string& section)
    : id(id), firstName(firstName), lastName(lastName),
      department(department), age(age), sex(sex),
      yearOfStudy(yearOfStudy), section(section), gpa(0.0) {
    setPassword(password);
}

void Student::setPassword(const string& password) {
    passwordHash = Utils::hashPassword(password);
}

void Student::addCourse(const string& courseCode, const CourseResult& result) {
    courses[courseCode] = result;
    calculateGPA();
}

void Student::updateCourse(const string& courseCode, const CourseResult& result) {
    if (courses.find(courseCode) != courses.end()) {
        courses[courseCode] = result;
        calculateGPA();
    }
}

void Student::removeCourse(const string& courseCode) {
    courses.erase(courseCode);
    calculateGPA();
}

bool Student::hasCourse(const string& courseCode) const {
    return courses.find(courseCode) != courses.end();
}

CourseResult Student::getCourseResult(const string& courseCode) const {
    auto it = courses.find(courseCode);
    if (it != courses.end()) {
        return it->second;
    }
    return CourseResult();
}

bool Student::verifyPassword(const string& password) const {
    return passwordHash == Utils::hashPassword(password);
}

void Student::calculateGPA() {
    if (courses.empty()) {
        gpa = 0.0;
        return;
    }
    
    double totalPoints = 0.0;
    int totalCredits = 0;
    
    for (const auto& pair : courses) {
        const CourseResult& result = pair.second;
        double gradePoint = 0.0;
        
        // Use Grader's getGradePoint for consistency
        if (result.grade == "A+" || result.grade == "A") gradePoint = 4.0;
        else if (result.grade == "A-") gradePoint = 3.75;
        else if (result.grade == "B+") gradePoint = 3.5;
        else if (result.grade == "B") gradePoint = 3.0;
        else if (result.grade == "B-") gradePoint = 2.75;
        else if (result.grade == "C+") gradePoint = 2.5;
        else if (result.grade == "C") gradePoint = 2.0;
        else if (result.grade == "C-") gradePoint = 1.75;
        else if (result.grade == "F") gradePoint = 0.0;
        else gradePoint = 0.0;
        
        totalPoints += gradePoint * result.creditHours;
        totalCredits += result.creditHours;
    }
    
    gpa = totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

string Student::toCSV() const {
    stringstream ss;
    
    // Basic info
    ss << id << "," << passwordHash << "," << firstName << "," << lastName << ","
       << department << "," << age << "," << sex << "," << yearOfStudy << ","
       << section << ",\"";
    
    // Course results
    bool first = true;
    for (const auto& pair : courses) {
        if (!first) ss << "|";
        first = false;
        
        const string& courseCode = pair.first;
        const CourseResult& result = pair.second;
        
        ss << courseCode << ":" << result.assessment << ":" << result.finalExam
           << ":" << result.grade << ":" << result.creditHours;
    }
    
    ss << "\"";
    
    return ss.str();
}

Student Student::fromCSV(const string& csvLine) {
    Student student;
    
    // Parse CSV with quoted fields
    vector<string> fields;
    string current;
    bool inQuotes = false;
    
    for (size_t i = 0; i < csvLine.length(); ++i) {
        char c = csvLine[i];
        
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            fields.push_back(Utils::trim(current));
            current.clear();
        } else {
            current += c;
        }
    }
    fields.push_back(Utils::trim(current));
    
    if (fields.size() < 10) {
        return student;
    }
    
    // Parse basic info
    student.id = fields[0];
    student.passwordHash = fields[1];
    student.firstName = fields[2];
    student.lastName = fields[3];
    student.department = fields[4];
    student.age = stoi(fields[5]);
    student.sex = fields[6][0];
    student.yearOfStudy = stoi(fields[7]);
    student.section = fields[8];
    
    // Parse course results
    string courseData = fields[9];
    if (!courseData.empty()) {
        vector<string> courseEntries = Utils::split(courseData, '|');
        
        for (const string& entry : courseEntries) {
            vector<string> parts = Utils::split(entry, ':');
            if (parts.size() >= 5) {
                string courseCode = Utils::trim(parts[0]);
                double assessment = stod(Utils::trim(parts[1]));
                double finalExam = stod(Utils::trim(parts[2]));
                string grade = Utils::trim(parts[3]);
                int credits = stoi(Utils::trim(parts[4]));
                
                student.courses[courseCode] = CourseResult(assessment, finalExam, grade, credits);
            }
        }
    }
    
    student.calculateGPA();
    
    return student;
}
