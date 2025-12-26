#ifndef SORTER_H
#define SORTER_H

#include "Student.h"
#include <vector>

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
    static void sort(vector<Student>& students, SortField field, bool ascending = true);
    
private:
    static void quickSort(vector<Student>& students, int low, int high, SortField field, bool ascending);
    static int partition(vector<Student>& students, int low, int high, SortField field, bool ascending);
    static int compare(const Student& a, const Student& b, SortField field);
};

#endif // SORTER_H
