using namespace std;

#include "../include/TableFormatter.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void TableFormatter::displayStudent(const Student& student) {
    displayStudents({student});
}

void TableFormatter::displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo students to display.\n" << endl;
        return;
    }
    
    // Define column headers and widths
    vector<string> headers = {
        "ID", "Name", "Dept", "Age", "Sex", "Year", "Section", "GPA"
    };
    
    vector<int> widths = {8, 25, 8, 5, 5, 6, 8, 6};
    
    // Print table header
    printHorizontalLine(widths);
    printRow(headers, widths);
    printHorizontalLine(widths);
    
    // Print student data
    for (const Student& student : students) {
        vector<string> row;
        
        row.push_back(student.getId());
        row.push_back(student.getFullName());
        row.push_back(student.getDepartment());
        row.push_back(to_string(student.getAge()));
        row.push_back(string(1, student.getSex()));
        row.push_back(to_string(student.getYearOfStudy()));
        row.push_back(student.getSection());
        
        stringstream gpaStream;
        gpaStream << fixed << setprecision(2) << student.getGPA();
        row.push_back(gpaStream.str());
        
        printRow(row, widths);
    }
    
    printHorizontalLine(widths);
    cout << "Total: " << students.size() << " student(s)\n" << endl;
}

void TableFormatter::displayStudentDetailed(const Student& student) {
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              STUDENT ACADEMIC RECORD                           ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    
    cout << "║ ID:           " << padRight(student.getId(), 47) << "║" << endl;
    cout << "║ Name:         " << padRight(student.getFullName(), 47) << "║" << endl;
    cout << "║ Department:   " << padRight(student.getDepartment(), 47) << "║" << endl;
    cout << "║ Age:          " << padRight(to_string(student.getAge()), 47) << "║" << endl;
    cout << "║ Sex:          " << padRight(string(1, student.getSex()), 47) << "║" << endl;
    cout << "║ Year:         " << padRight(to_string(student.getYearOfStudy()), 47) << "║" << endl;
    cout << "║ Section:      " << padRight(student.getSection(), 47) << "║" << endl;
    
    stringstream gpaStream;
    gpaStream << fixed << setprecision(2) << student.getGPA();
    cout << "║ GPA:          " << padRight(gpaStream.str(), 47) << "║" << endl;
    
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    cout << "║                      COURSE RESULTS                            ║" << endl;
    cout << "╠════════════════════════════════════════════════════════════════╣" << endl;
    
    const auto& courses = student.getCourses();
    
    if (courses.empty()) {
        cout << "║ No courses enrolled                                            ║" << endl;
    } else {
        cout << "║ Course    Assessment  Final  Total  Grade  Credits            ║" << endl;
        cout << "╟────────────────────────────────────────────────────────────────╢" << endl;
        
        for (const auto& pair : courses) {
            const string& courseCode = pair.first;
            const CourseResult& result = pair.second;
            
            stringstream line;
            line << "║ " << left << setw(9) << courseCode
                 << right << setw(6) << fixed << setprecision(1) << result.assessment
                 << setw(8) << fixed << setprecision(1) << result.finalExam
                 << setw(7) << fixed << setprecision(1) << result.getTotalScore()
                 << setw(7) << result.grade
                 << setw(8) << result.creditHours
                 << "            ║";
            
            cout << line.str() << endl;
        }
    }
    
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
}

void TableFormatter::printHorizontalLine(const vector<int>& columnWidths) {
    cout << "+";
    for (int width : columnWidths) {
        cout << string(width + 2, '-') << "+";
    }
    cout << endl;
}

void TableFormatter::printRow(const vector<string>& values,
                             const vector<int>& columnWidths) {
    cout << "|";
    for (size_t i = 0; i < values.size() && i < columnWidths.size(); ++i) {
        cout << " " << left << setw(columnWidths[i]) << values[i] << " |";
    }
    cout << endl;
}

string TableFormatter::centerText(const string& text, int width) {
    int padding = width - text.length();
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    
    return string(leftPad, ' ') + text + string(rightPad, ' ');
}

string TableFormatter::padRight(const string& text, int width) {
    if (text.length() >= static_cast<size_t>(width)) {
        return text.substr(0, width);
    }
    return text + string(width - text.length(), ' ');
}
