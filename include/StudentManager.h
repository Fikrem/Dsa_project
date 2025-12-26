#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include "Course.h"
#include "AVLTree.h"
#include "UndoManager.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class StudentManager {
private:
    AVLTree<Student> studentTree;
    vector<Course> courses;
    UndoManager undoManager;
    
    // File paths
    string studentsFilePath;
    string coursesFilePath;
    
    // Helper functions for file I/O
    void loadCoursesFromCSV();
    void loadStudentsFromCSV();
    void saveStudentsToCSV();
    
public:
    StudentManager(const string& studentsFile, const string& coursesFile);
    ~StudentManager();
    
    // Authentication
    enum class UserType { ADMIN, STUDENT, INVALID };
    UserType authenticate(const string& id, const string& password, Student** outStudent = nullptr);
    
    // CRUD operations
    bool addStudent(const Student& student, bool useUndo = true);
    bool updateStudent(const string& id, const Student& newData, bool useUndo = true);
    bool deleteStudent(const string& id, bool useUndo = true);
    Student* getStudent(const string& id);
    vector<Student> getAllStudents();
    
    // Course management
    vector<Course> getCoursesForStudent(const string& department, int yearOfStudy);
    const vector<Course>& getAllCourses() const { return courses; }
    
    // Undo operations
    bool canUndo() const { return undoManager.canUndo(); }
    void undo() { undoManager.undo(); }
    string getLastOperation() const { return undoManager.getLastCommandDescription(); }
    
    // Save data
    void save();
    
    // Friend classes for undo commands
    friend class AddStudentCommand;
    friend class UpdateStudentCommand;
    friend class DeleteStudentCommand;
};

#endif // STUDENTMANAGER_H
