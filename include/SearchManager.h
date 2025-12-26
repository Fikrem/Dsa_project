#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include "Student.h"
#include <vector>
#include <string>
#include <optional>

using namespace std;

enum class SearchMode {
    MATCH_ALL,  // AND logic - all criteria must match
    MATCH_ANY   // OR logic - any criteria can match
};

struct SearchCriteria {
    optional<string> id;
    optional<string> firstName;
    optional<string> lastName;
    optional<string> department;
    optional<int> age;
    optional<char> sex;
    optional<int> yearOfStudy;
    optional<double> minGPA;
    optional<double> maxGPA;
    
    SearchCriteria() = default;
};

class SearchManager {
public:
    // Multi-parameter search
    static vector<Student> search(const vector<Student>& students,
                                      const SearchCriteria& criteria,
                                      SearchMode mode = SearchMode::MATCH_ALL);
    
    // Single parameter searches (optimized)
    static Student* searchById(vector<Student>& students, const string& id);
    static vector<Student> searchByName(const vector<Student>& students,
                                             const string& name);
    static vector<Student> searchByGPA(const vector<Student>& students,
                                           double minGPA, double maxGPA);
    
private:
    // Helper function to check if a student matches criteria
    static bool matchesCriteria(const Student& student, const SearchCriteria& criteria,
                               SearchMode mode);
};

#endif // SEARCHMANAGER_H
