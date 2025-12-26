using namespace std;

#include "../include/Utils.h"
#include <iostream>
#include <limits>

namespace Utils {
    string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        if (start == string::npos) return "";
        
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }
    
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        
        return tokens;
    }
    
    string join(const vector<string>& vec, const string& delimiter) {
        if (vec.empty()) return "";
        
        string result = vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            result += delimiter + vec[i];
        }
        
        return result;
    }
    
    bool isValidAge(int age) {
        return age >= 15 && age <= 100;
    }
    
    bool isValidGPA(double gpa) {
        return gpa >= 0.0 && gpa <= 4.0;
    }
    
    bool isValidSex(char sex) {
        return sex == 'M' || sex == 'F' || sex == 'm' || sex == 'f';
    }
    
    bool isValidYear(int year) {
        return year >= 1 && year <= 7;  // Support up to 7 years (e.g., medicine)
    }
    
    string getLine() {
        string line;
        getline(cin, line);
        return trim(line);
    }
    
    int getInt() {
        int value;
        while (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
    
    double getDouble() {
        double value;
        while (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
    
    char getChar() {
        char value;
        cin >> value;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
    
    // Simple hash function for password (for demonstration purposes)
    string hashPassword(const string& password) {
        unsigned long hash = 5381;
        for (char c : password) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        
        stringstream ss;
        ss << hex << hash;
        return ss.str();
    }
}
