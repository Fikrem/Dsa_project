using namespace std;

#include "../include/Sorter.h"

void Sorter::sort(vector<Student>& students, SortField field, bool ascending) {
    if (students.empty()) return;
    quickSort(students, 0, students.size() - 1, field, ascending);
}

void Sorter::quickSort(vector<Student>& students, int low, int high, SortField field, bool ascending) {
    if (low < high) {
        int pi = partition(students, low, high, field, ascending);
        quickSort(students, low, pi - 1, field, ascending);
        quickSort(students, pi + 1, high, field, ascending);
    }
}

int Sorter::partition(vector<Student>& students, int low, int high, SortField field, bool ascending) {
    Student pivot = students[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        int cmp = compare(students[j], pivot, field);
        bool shouldSwap = ascending ? (cmp < 0) : (cmp > 0);
        
        if (shouldSwap) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

int Sorter::compare(const Student& a, const Student& b, SortField field) {
    switch (field) {
        case SortField::SEX:
            if (a.getSex() < b.getSex()) return -1;
            else if (a.getSex() > b.getSex()) return 1;
            break;
            
        case SortField::AGE:
            if (a.getAge() < b.getAge()) return -1;
            else if (a.getAge() > b.getAge()) return 1;
            break;
            
        case SortField::GPA:
            if (a.getGPA() < b.getGPA()) return -1;
            else if (a.getGPA() > b.getGPA()) return 1;
            break;
            
        case SortField::DEPARTMENT:
            return a.getDepartment().compare(b.getDepartment());
            
        case SortField::YEAR_OF_STUDY:
            if (a.getYearOfStudy() < b.getYearOfStudy()) return -1;
            else if (a.getYearOfStudy() > b.getYearOfStudy()) return 1;
            break;
            
        case SortField::ID:
            return a.getId().compare(b.getId());
            
        case SortField::NAME:
            return a.getFullName().compare(b.getFullName());
    }
    
    return 0;
}
