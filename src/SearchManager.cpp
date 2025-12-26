using namespace std;

#include "../include/SearchManager.h"
#include <algorithm>

vector<Student> SearchManager::search(const vector<Student>& students,
                                          const SearchCriteria& criteria,
                                          SearchMode mode) {
    vector<Student> results;
    
    for (const Student& student : students) {
        if (matchesCriteria(student, criteria, mode)) {
            results.push_back(student);
        }
    }
    
    return results;
}

Student* SearchManager::searchById(vector<Student>& students, const string& id) {
    // Binary search would work if sorted by ID
    for (Student& student : students) {
        if (student.getId() == id) {
            return &student;
        }
    }
    return nullptr;
}

vector<Student> SearchManager::searchByName(const vector<Student>& students,
                                                 const string& name) {
    vector<Student> results;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    for (const Student& student : students) {
        string fullName = student.getFullName();
        transform(fullName.begin(), fullName.end(), fullName.begin(), ::tolower);
        
        if (fullName.find(lowerName) != string::npos) {
            results.push_back(student);
        }
    }
    
    return results;
}

vector<Student> SearchManager::searchByGPA(const vector<Student>& students,
                                               double minGPA, double maxGPA) {
    vector<Student> results;
    
    for (const Student& student : students) {
        double gpa = student.getGPA();
        if (gpa >= minGPA && gpa <= maxGPA) {
            results.push_back(student);
        }
    }
    
    return results;
}

bool SearchManager::matchesCriteria(const Student& student, const SearchCriteria& criteria,
                                   SearchMode mode) {
    int matchCount = 0;
    int criteriaCount = 0;
    
    // Check ID
    if (criteria.id.has_value()) {
        criteriaCount++;
        if (student.getId() == criteria.id.value()) {
            matchCount++;
        }
    }
    
    // Check first name
    if (criteria.firstName.has_value()) {
        criteriaCount++;
        string firstName = student.getFirstName();
        string searchName = criteria.firstName.value();
        transform(firstName.begin(), firstName.end(), firstName.begin(), ::tolower);
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        
        if (firstName.find(searchName) != string::npos) {
            matchCount++;
        }
    }
    
    // Check last name
    if (criteria.lastName.has_value()) {
        criteriaCount++;
        string lastName = student.getLastName();
        string searchName = criteria.lastName.value();
        transform(lastName.begin(), lastName.end(), lastName.begin(), ::tolower);
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        
        if (lastName.find(searchName) != string::npos) {
            matchCount++;
        }
    }
    
    // Check department
    if (criteria.department.has_value()) {
        criteriaCount++;
        if (student.getDepartment() == criteria.department.value()) {
            matchCount++;
        }
    }
    
    // Check age
    if (criteria.age.has_value()) {
        criteriaCount++;
        if (student.getAge() == criteria.age.value()) {
            matchCount++;
        }
    }
    
    // Check sex
    if (criteria.sex.has_value()) {
        criteriaCount++;
        if (student.getSex() == criteria.sex.value()) {
            matchCount++;
        }
    }
    
    // Check year of study
    if (criteria.yearOfStudy.has_value()) {
        criteriaCount++;
        if (student.getYearOfStudy() == criteria.yearOfStudy.value()) {
            matchCount++;
        }
    }
    
    // Check GPA range
    if (criteria.minGPA.has_value() || criteria.maxGPA.has_value()) {
        criteriaCount++;
        double gpa = student.getGPA();
        bool gpaMatch = true;
        
        if (criteria.minGPA.has_value() && gpa < criteria.minGPA.value()) {
            gpaMatch = false;
        }
        if (criteria.maxGPA.has_value() && gpa > criteria.maxGPA.value()) {
            gpaMatch = false;
        }
        
        if (gpaMatch) {
            matchCount++;
        }
    }
    
    // Return based on mode
    if (mode == SearchMode::MATCH_ALL) {
        return matchCount == criteriaCount;
    } else {  // MATCH_ANY
        return matchCount > 0;
    }
}
