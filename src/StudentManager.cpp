using namespace std;

#include "../include/StudentManager.h"
#include "../include/Utils.h"
#include "../include/Grader.h"
#include <fstream>
#include <iostream>

StudentManager::StudentManager(const string& studentsFile, const string& coursesFile)
    : studentsFilePath(studentsFile), coursesFilePath(coursesFile) {
    loadCoursesFromCSV();
    loadStudentsFromCSV();
}

StudentManager::~StudentManager() {
    save();
}

void StudentManager::loadCoursesFromCSV() {
    ifstream file(coursesFilePath);
    
    if (!file.is_open()) {
        cerr << "Warning: Could not open courses file: " << coursesFilePath << endl;
        return;
    }
    
    string line;
    // Skip header
    getline(file, line);
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Course course = Course::fromCSV(line);
        if (!course.getCourseCode().empty()) {
            courses.push_back(course);
        }
    }
    
    file.close();
    cout << "Loaded " << courses.size() << " courses from database." << endl;
}

void StudentManager::loadStudentsFromCSV() {
    ifstream file(studentsFilePath);
    
    if (!file.is_open()) {
        cerr << "Warning: Could not open students file: " << studentsFilePath << endl;
        return;
    }
    
    string line;
    // Skip header
    getline(file, line);
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Student student = Student::fromCSV(line);
        if (!student.getId().empty()) {
            studentTree.insert(student);
        }
    }
    
    cout << "Loaded " << studentTree.size() << " students from database." << endl;
}

void StudentManager::saveStudentsToCSV() {
    ofstream file(studentsFilePath);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open students file for writing: " << studentsFilePath << endl;
        return;
    }
    
    // Write header
    file << "id,password_hash,first_name,last_name,department,age,sex,year_of_study,section,course_results" << endl;
    
    // Write student data
    vector<Student> allStudents = studentTree.getAll();
    for (const Student& student : allStudents) {
        file << student.toCSV() << endl;
    }
    
    file.close();
    cout << "Saved " << allStudents.size() << " students to database." << endl;
}

StudentManager::UserType StudentManager::authenticate(const string& id, const string& password,
                                                      Student** outStudent) {
    // Check for admin login (hardcoded admin credentials)
    if (id == "admin" && password == "admin123") {
        return UserType::ADMIN;
    }
    
    // Check for student login
    Student* student = getStudent(id);
    if (student && student->verifyPassword(password)) {
        if (outStudent) {
            *outStudent = student;
        }
        return UserType::STUDENT;
    }
    
    return UserType::INVALID;
}

bool StudentManager::addStudent(const Student& student, bool useUndo) {
    // Check if student already exists
    if (studentTree.search(student)) {
        return false;
    }
    
    if (useUndo) {
        auto command = make_unique<AddStudentCommand>(this, student);
        undoManager.executeCommand(move(command));
    } else {
        studentTree.insert(student);
    }
    
    return true;
}

bool StudentManager::updateStudent(const string& id, const Student& newData, bool useUndo) {
    Student searchStudent;
    searchStudent.setId(id);
    
    Student* existing = studentTree.find(searchStudent);
    if (!existing) {
        return false;
    }
    
    if (useUndo) {
        Student oldData = *existing;
        auto command = make_unique<UpdateStudentCommand>(this, oldData, newData);
        undoManager.executeCommand(move(command));
    } else {
        studentTree.remove(*existing);
        studentTree.insert(newData);
    }
    
    return true;
}

bool StudentManager::deleteStudent(const string& id, bool useUndo) {
    Student searchStudent;
    searchStudent.setId(id);
    
    Student* existing = studentTree.find(searchStudent);
    if (!existing) {
        return false;
    }
    
    if (useUndo) {
        Student studentCopy = *existing;
        auto command = make_unique<DeleteStudentCommand>(this, studentCopy);
        undoManager.executeCommand(move(command));
    } else {
        studentTree.remove(*existing);
    }
    
    return true;
}

Student* StudentManager::getStudent(const string& id) {
    Student searchStudent;
    searchStudent.setId(id);
    return studentTree.find(searchStudent);
}

vector<Student> StudentManager::getAllStudents() {
    return studentTree.getAll();
}

vector<Course> StudentManager::getCoursesForStudent(const string& department, int yearOfStudy) {
    vector<Course> result;
    
    for (const Course& course : courses) {
        if (course.getDepartment() == department && course.getYearOfStudy() == yearOfStudy) {
            result.push_back(course);
        }
    }
    
    return result;
}

void StudentManager::save() {
    saveStudentsToCSV();
}
