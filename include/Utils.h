#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

namespace Utils {
    // String manipulation
    string trim(const string& str);
    vector<string> split(const string& str, char delimiter);
    string join(const vector<string>& vec, const string& delimiter);
    
    // Input validation
    bool isValidAge(int age);
    bool isValidGPA(double gpa);
    bool isValidSex(char sex);
    bool isValidYear(int year);
    
    // Safe input
    string getLine();
    int getInt();
    double getDouble();
    char getChar();
    
    // Password hashing (simple hash for demonstration)
    string hashPassword(const string& password);
}

#endif // UTILS_H
