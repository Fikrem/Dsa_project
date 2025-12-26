using namespace std;

#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include "StudentManager.h"
#include "SearchManager.h"
#include "Sorter.h"
#include "Grader.h"
#include "TableFormatter.h"
#include "Utils.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Forward declarations
void adminMenu(StudentManager& manager);
void studentMenu(StudentManager& manager, Student* student);

// Admin menu functions
void addStudentMenu(StudentManager& manager);
void updateStudentMenu(StudentManager& manager);
void deleteStudentMenu(StudentManager& manager);
void searchStudentMenu(StudentManager& manager);
void sortStudentsMenu(StudentManager& manager);
void gradeStudentMenu(StudentManager& manager);
void viewAllStudentsMenu(StudentManager& manager);
void undoMenu(StudentManager& manager);

int main() {
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        STUDENT RECORD MANAGEMENT SYSTEM                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    cout << "\nInitializing system..." << endl;
    
    StudentManager manager("data/students.csv", "data/courses.csv");
    
    cout << "\nSystem ready!\n" << endl;
    
    while (true) {
        clearScreen();
        cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                          LOGIN                                 ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
        cout << "\n1. Admin Login" << endl;
        cout << "2. Student Login" << endl;
        cout << "3. Exit" << endl;
        cout << "\nChoice: ";
        
        int choice = Utils::getInt();
        
        if (choice == 3) {
            cout << "\nSaving data and exiting..." << endl;
            break;
        }
        
        cout << "\nEnter ID: ";
        string id = Utils::getLine();
        
        cout << "Enter Password: ";
        string password = Utils::getLine();
        
        Student* student = nullptr;
        StudentManager::UserType userType = manager.authenticate(id, password, &student);
        
        if (userType == StudentManager::UserType::ADMIN) {
            adminMenu(manager);
        } else if (userType == StudentManager::UserType::STUDENT) {
            studentMenu(manager, student);
        } else {
            cout << "\n Invalid credentials! Please try again." << endl;
            pause();
        }
    }
    
    return 0;
}

void adminMenu(StudentManager& manager) {
    while (true) {
        clearScreen();
        cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                      ADMIN MENU                                ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
        cout << "\n1.  Add Student" << endl;
        cout << "2.  Update Student" << endl;
        cout << "3.  Delete Student" << endl;
        cout << "4.  Search Students" << endl;
        cout << "5.  Sort Students" << endl;
        cout << "6.  Grade Student" << endl;
        cout << "7.  View All Students" << endl;
        cout << "8.  Undo Last Operation" << endl;
        cout << "9.  Logout" << endl;
        cout << "\nChoice: ";
        
        int choice = Utils::getInt();
        
        switch (choice) {
            case 1: addStudentMenu(manager); break;
            case 2: updateStudentMenu(manager); break;
            case 3: deleteStudentMenu(manager); break;
            case 4: searchStudentMenu(manager); break;
            case 5: sortStudentsMenu(manager); break;
            case 6: gradeStudentMenu(manager); break;
            case 7: viewAllStudentsMenu(manager); break;
            case 8: undoMenu(manager); break;
            case 9: return;
            default:
                cout << "\n❌ Invalid choice!" << endl;
                pause();
        }
    }
}

void studentMenu(StudentManager& manager, Student* student) {
    while (true) {
        clearScreen();
        cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    STUDENT PORTAL                              ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
        cout << "\nWelcome, " << student->getFullName() << "!" << endl;
        cout << "\n1. View My Academic Record" << endl;
        cout << "2. Logout" << endl;
        cout << "\nChoice: ";
        
        int choice = Utils::getInt();
        
        if (choice == 1) {
            clearScreen();
            TableFormatter::displayStudentDetailed(*student);
            pause();
        } else if (choice == 2) {
            return;
        } else {
            cout << "\n❌ Invalid choice!" << endl;
            pause();
        }
    }
}

void addStudentMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                      ADD STUDENT                               ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nEnter Student ID: ";
    string id = Utils::getLine();
    
    // Check if student already exists
    if (manager.getStudent(id)) {
        cout << "\n❌ Student with ID " << id << " already exists!" << endl;
        pause();
        return;
    }
    
    cout << "Enter Password: ";
    string password = Utils::getLine();
    
    cout << "Enter First Name: ";
    string firstName = Utils::getLine();
    
    cout << "Enter Last Name: ";
    string lastName = Utils::getLine();
    
    cout << "Enter Department: ";
    string department = Utils::getLine();
    
    int age;
    do {
        cout << "Enter Age (15-100): ";
        age = Utils::getInt();
    } while (!Utils::isValidAge(age));
    
    char sex;
    do {
        cout << "Enter Sex (M/F): ";
        sex = Utils::getChar();
    } while (!Utils::isValidSex(sex));
    
    int year;
    do {
        cout << "Enter Year of Study (1-7): ";
        year = Utils::getInt();
    } while (!Utils::isValidYear(year));
    
    cout << "Enter Section: ";
    string section = Utils::getLine();
    
    Student newStudent(id, password, firstName, lastName, department, age, sex, year, section);
    
    // Enroll in courses
    vector<Course> availableCourses = manager.getCoursesForStudent(department, year);
    
    if (!availableCourses.empty()) {
        cout << "\n Available courses for " << department << " Year " << year << ":" << endl;
        for (size_t i = 0; i < availableCourses.size(); ++i) {
            cout << (i + 1) << ". " << availableCourses[i].getCourseCode() 
                     << " - " << availableCourses[i].getCourseName()
                     << " (" << availableCourses[i].getCreditHours() << " credits)" << endl;
        }
        
        cout << "\nStudent will be enrolled in these courses." << endl;
        
        // Initialize courses with default grades
        for (const Course& course : availableCourses) {
            CourseResult result(0, 0, "F", course.getCreditHours());
            newStudent.addCourse(course.getCourseCode(), result);
        }
    }
    
    if (manager.addStudent(newStudent)) {
        cout << "\n✅ Student added successfully!" << endl;
    } else {
        cout << "\n❌ Failed to add student!" << endl;
    }
    
    pause();
}

void updateStudentMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    UPDATE STUDENT                              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nEnter Student ID: ";
    string id = Utils::getLine();
    
    Student* student = manager.getStudent(id);
    if (!student) {
        cout << "\n❌ Student not found!" << endl;
        pause();
        return;
    }
    
    cout << "\nCurrent Information:" << endl;
    TableFormatter::displayStudent(*student);
    
    Student updatedStudent = *student;
    
    cout << "\nWhat would you like to update?" << endl;
    cout << "1. Personal Information" << endl;
    cout << "2. Academic Information" << endl;
    cout << "3. Cancel" << endl;
    cout << "\nChoice: ";
    
    int choice = Utils::getInt();
    
    if (choice == 1) {
        cout << "\nEnter new First Name (or press Enter to keep current): ";
        string firstName = Utils::getLine();
        if (!firstName.empty()) updatedStudent.setFirstName(firstName);
        
        cout << "Enter new Last Name (or press Enter to keep current): ";
        string lastName = Utils::getLine();
        if (!lastName.empty()) updatedStudent.setLastName(lastName);
        
        cout << "Enter new Age (or 0 to keep current): ";
        int age = Utils::getInt();
        if (age > 0 && Utils::isValidAge(age)) updatedStudent.setAge(age);
        
    } else if (choice == 2) {
        cout << "\nEnter new Department (or press Enter to keep current): ";
        string dept = Utils::getLine();
        if (!dept.empty()) updatedStudent.setDepartment(dept);
        
        cout << "Enter new Year of Study (or 0 to keep current): ";
        int year = Utils::getInt();
        if (year > 0 && Utils::isValidYear(year)) updatedStudent.setYearOfStudy(year);
        
        cout << "Enter new Section (or press Enter to keep current): ";
        string section = Utils::getLine();
        if (!section.empty()) updatedStudent.setSection(section);
        
    } else {
        return;
    }
    
    if (manager.updateStudent(id, updatedStudent)) {
        cout << "\n✅ Student updated successfully!" << endl;
    } else {
        cout << "\n❌ Failed to update student!" << endl;
    }
    
    pause();
}

void deleteStudentMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    DELETE STUDENT                              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nEnter Student ID: ";
    string id = Utils::getLine();
    
    Student* student = manager.getStudent(id);
    if (!student) {
        cout << "\nStudent not found!" << endl;
        pause();
        return;
    }
    
    TableFormatter::displayStudent(*student);
    
    cout << "\n⚠️  Are you sure you want to delete this student? (y/n): ";
    char confirm = Utils::getChar();
    
    if (confirm == 'y' || confirm == 'Y') {
        if (manager.deleteStudent(id)) {
            cout << "\n✅ Student deleted successfully!" << endl;
        } else {
            cout << "\n Failed to delete student!" << endl;
        }
    } else {
        cout << "\n Deletion cancelled." << endl;
    }
    
    pause();
}

void searchStudentMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    SEARCH STUDENTS                             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    SearchCriteria criteria;
    
    cout << "\nEnter search criteria (press Enter to skip):" << endl;
    
    cout << "Student ID: ";
    string id = Utils::getLine();
    if (!id.empty()) criteria.id = id;
    
    cout << "First Name: ";
    string firstName = Utils::getLine();
    if (!firstName.empty()) criteria.firstName = firstName;
    
    cout << "Last Name: ";
    string lastName = Utils::getLine();
    if (!lastName.empty()) criteria.lastName = lastName;
    
    cout << "Department: ";
    string dept = Utils::getLine();
    if (!dept.empty()) criteria.department = dept;
    
    cout << "Age (0 to skip): ";
    int age = Utils::getInt();
    if (age > 0) criteria.age = age;
    
    cout << "Sex (M/F or press Enter to skip): ";
    string sexStr = Utils::getLine();
    if (!sexStr.empty()) criteria.sex = sexStr[0];
    
    cout << "Year of Study (0 to skip): ";
    int year = Utils::getInt();
    if (year > 0) criteria.yearOfStudy = year;
    
    cout << "Minimum GPA (or -1 to skip): ";
    double minGPA = Utils::getDouble();
    if (minGPA >= 0) criteria.minGPA = minGPA;
    
    cout << "Maximum GPA (or -1 to skip): ";
    double maxGPA = Utils::getDouble();
    if (maxGPA >= 0) criteria.maxGPA = maxGPA;
    
    cout << "\nSearch Mode:" << endl;
    cout << "1. Match ALL criteria (AND)" << endl;
    cout << "2. Match ANY criteria (OR)" << endl;
    cout << "Choice: ";
    int modeChoice = Utils::getInt();
    
    SearchMode mode = (modeChoice == 2) ? SearchMode::MATCH_ANY : SearchMode::MATCH_ALL;
    
    vector<Student> allStudents = manager.getAllStudents();
    vector<Student> results = SearchManager::search(allStudents, criteria, mode);
    
    clearScreen();
    cout << "\nSearch Results:" << endl;
    TableFormatter::displayStudents(results);
    
    pause();
}

void sortStudentsMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                     SORT STUDENTS                              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nSelect sort field:" << endl;
    cout << "1. Sex" << endl;
    cout << "2. Age" << endl;
    cout << "3. GPA" << endl;
    cout << "4. Department" << endl;
    cout << "5. Year of Study" << endl;
    cout << "6. ID" << endl;
    cout << "7. Name" << endl;
    
    cout << "\nChoice: ";
    int choice = Utils::getInt();
    
    SortField field;
    bool validChoice = true;
    
    switch (choice) {
        case 1: field = SortField::SEX; break;
        case 2: field = SortField::AGE; break;
        case 3: field = SortField::GPA; break;
        case 4: field = SortField::DEPARTMENT; break;
        case 5: field = SortField::YEAR_OF_STUDY; break;
        case 6: field = SortField::ID; break;
        case 7: field = SortField::NAME; break;
        default:
            cout << "\n Invalid choice!" << endl;
            pause();
            validChoice = false;
    }
    
    if (!validChoice) {
        return;
    }
    
    cout << "\nSort order:" << endl;
    cout << "1. Ascending" << endl;
    cout << "2. Descending" << endl;
    cout << "Choice: ";
    int orderChoice = Utils::getInt();
    bool ascending = (orderChoice == 1);
    
    vector<Student> students = manager.getAllStudents();
    Sorter::sort(students, field, ascending);
    
    clearScreen();
    cout << "\n Sorted Students:" << endl;
    TableFormatter::displayStudents(students);
    
    pause();
}

void gradeStudentMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                     GRADE STUDENT                              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nEnter Student ID: ";
    string id = Utils::getLine();
    
    Student* student = manager.getStudent(id);
    if (!student) {
        cout << "\n Student not found!" << endl;
        pause();
        return;
    }
    
    cout << "\nStudent: " << student->getFullName() << endl;
    
    const auto& courses = student->getCourses();
    if (courses.empty()) {
        cout << "\n Student has no enrolled courses!" << endl;
        pause();
        return;
    }
    
    cout << "\nEnrolled Courses:" << endl;
    int index = 1;
    vector<string> courseCodes;
    for (const auto& pair : courses) {
        cout << index++ << ". " << pair.first 
                 << " (Current Grade: " << pair.second.grade << ")" << endl;
        courseCodes.push_back(pair.first);
    }
    
    cout << "\nSelect course to grade (1-" << courseCodes.size() << "): ";
    int choice = Utils::getInt();
    
    if (choice < 1 || choice > static_cast<int>(courseCodes.size())) {
        cout << "\n Invalid choice!" << endl;
        pause();
        return;
    }
    
    string courseCode = courseCodes[choice - 1];
    CourseResult currentResult = student->getCourseResult(courseCode);
    
    cout << "\nCourse: " << courseCode << endl;
    cout << "Current Assessment: " << currentResult.assessment << "/50" << endl;
    cout << "Current Final Exam: " << currentResult.finalExam << "/50" << endl;
    cout << "Current Grade: " << currentResult.grade << endl;
    
    double assessment, finalExam;
    
    do {
        cout << "\nEnter Assessment Score (0-50): ";
        assessment = Utils::getDouble();
    } while (assessment < 0 || assessment > 50);
    
    do {
        cout << "Enter Final Exam Score (0-50): ";
        finalExam = Utils::getDouble();
    } while (finalExam < 0 || finalExam > 50);
    
    Student updatedStudent = *student;
    Grader::gradeCourse(updatedStudent, courseCode, assessment, finalExam, currentResult.creditHours);
    
    cout << "\nNew Total Score: " << (assessment + finalExam) << "/100" << endl;
    cout << "New Grade: " << updatedStudent.getCourseResult(courseCode).grade << endl;
    cout << "New GPA: " << fixed << setprecision(2) << updatedStudent.getGPA() << endl;
    
    if (manager.updateStudent(id, updatedStudent)) {
        cout << "\n Grade updated successfully!" << endl;
    } else {
        cout << "\nFailed to update grade!" << endl;
    }
    
    pause();
}

void viewAllStudentsMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   ALL STUDENTS                                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    vector<Student> students = manager.getAllStudents();
    TableFormatter::displayStudents(students);
    
    pause();
}

void undoMenu(StudentManager& manager) {
    clearScreen();
    cout << "╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                        UNDO                                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    if (!manager.canUndo()) {
        cout << "\n No operations to undo!" << endl;
        pause();
        return;
    }
    
    cout << "\nLast operation: " << manager.getLastOperation() << endl;
    cout << "\n Undo this operation? (y/n): ";
    char confirm = Utils::getChar();
    
    if (confirm == 'y' || confirm == 'Y') {
        manager.undo();
        cout << "\nOperation undone successfully!" << endl;
    } else {
        cout << "\n Undo cancelled." << endl;
    }
    
    pause();
}
