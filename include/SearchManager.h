#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;

enum class SearchMode {
    MATCH_ALL,  // AND logic - all criteria must match
    MATCH_ANY   // OR logic - any criteria can match
};

struct SearchCriteria {
    string id;
    string firstName;
    string lastName;
    string department;
    int age;
    char sex;
    int yearOfStudy;
    double minGPA;
    double maxGPA;
    
    SearchCriteria() : id(""), firstName(""), lastName(""), department(""),
                      age(-1), sex('\0'), yearOfStudy(-1), minGPA(-1.0), maxGPA(-1.0) {}
};

class SearchManager {
public:
    // Multi-parameter search
    static vector<Student> search(const vector<Student>& students,
                                      const SearchCriteria& criteria,
                                      SearchMode mode = SearchMode::MATCH_ALL);
    
private:
    static bool matchesCriteria(const Student& student, const SearchCriteria& criteria,
                               SearchMode mode);
};

#endif // SEARCHMANAGER_H
