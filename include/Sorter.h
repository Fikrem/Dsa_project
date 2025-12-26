#ifndef SORTER_H
#define SORTER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;

enum class SortField {
    SEX,
    AGE,
    GPA,
    DEPARTMENT,
    YEAR_OF_STUDY,
    ID,
    NAME
};

class Sorter {
public:
    // Multi-parameter sort (sequential sorting)
    static void sort(vector<Student>& students,
                    const vector<SortField>& fields,
                    bool ascending = true);
    
    // Single parameter sorts
    static void sortBySex(vector<Student>& students, bool ascending = true);
    static void sortByAge(vector<Student>& students, bool ascending = true);
    static void sortByGPA(vector<Student>& students, bool ascending = true);
    static void sortByDepartment(vector<Student>& students, bool ascending = true);
    static void sortByYear(vector<Student>& students, bool ascending = true);
    
private:
    // Merge sort implementation
    static void mergeSort(vector<Student>& students, int left, int right,
                         const vector<SortField>& fields, bool ascending);
    static void merge(vector<Student>& students, int left, int mid, int right,
                     const vector<SortField>& fields, bool ascending);
    
    // Comparison function for multi-field sorting
    static int compare(const Student& a, const Student& b,
                      const vector<SortField>& fields);
};

#endif // SORTER_H
