using namespace std;

#include "../include/Sorter.h"
#include <algorithm>

void Sorter::sort(vector<Student>& students,
                 const vector<SortField>& fields,
                 bool ascending) {
    if (students.empty() || fields.empty()) {
        return;
    }
    
    mergeSort(students, 0, students.size() - 1, fields, ascending);
}

void Sorter::sortBySex(vector<Student>& students, bool ascending) {
    sort(students, {SortField::SEX}, ascending);
}

void Sorter::sortByAge(vector<Student>& students, bool ascending) {
    sort(students, {SortField::AGE}, ascending);
}

void Sorter::sortByGPA(vector<Student>& students, bool ascending) {
    sort(students, {SortField::GPA}, ascending);
}

void Sorter::sortByDepartment(vector<Student>& students, bool ascending) {
    sort(students, {SortField::DEPARTMENT}, ascending);
}

void Sorter::sortByYear(vector<Student>& students, bool ascending) {
    sort(students, {SortField::YEAR_OF_STUDY}, ascending);
}

void Sorter::mergeSort(vector<Student>& students, int left, int right,
                      const vector<SortField>& fields, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(students, left, mid, fields, ascending);
        mergeSort(students, mid + 1, right, fields, ascending);
        merge(students, left, mid, right, fields, ascending);
    }
}

void Sorter::merge(vector<Student>& students, int left, int mid, int right,
                  const vector<SortField>& fields, bool ascending) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<Student> leftArray(n1);
    vector<Student> rightArray(n2);
    
    for (int i = 0; i < n1; i++) {
        leftArray[i] = students[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = students[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        int cmp = compare(leftArray[i], rightArray[j], fields);
        
        bool shouldTakeLeft = ascending ? (cmp <= 0) : (cmp >= 0);
        
        if (shouldTakeLeft) {
            students[k] = leftArray[i];
            i++;
        } else {
            students[k] = rightArray[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        students[k] = leftArray[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        students[k] = rightArray[j];
        j++;
        k++;
    }
}

int Sorter::compare(const Student& a, const Student& b,
                   const vector<SortField>& fields) {
    for (const SortField& field : fields) {
        int result = 0;
        
        switch (field) {
            case SortField::SEX:
                if (a.getSex() < b.getSex()) result = -1;
                else if (a.getSex() > b.getSex()) result = 1;
                break;
                
            case SortField::AGE:
                if (a.getAge() < b.getAge()) result = -1;
                else if (a.getAge() > b.getAge()) result = 1;
                break;
                
            case SortField::GPA:
                if (a.getGPA() < b.getGPA()) result = -1;
                else if (a.getGPA() > b.getGPA()) result = 1;
                break;
                
            case SortField::DEPARTMENT:
                result = a.getDepartment().compare(b.getDepartment());
                break;
                
            case SortField::YEAR_OF_STUDY:
                if (a.getYearOfStudy() < b.getYearOfStudy()) result = -1;
                else if (a.getYearOfStudy() > b.getYearOfStudy()) result = 1;
                break;
                
            case SortField::ID:
                result = a.getId().compare(b.getId());
                break;
                
            case SortField::NAME:
                result = a.getFullName().compare(b.getFullName());
                break;
        }
        
        // If not equal, return the result
        if (result != 0) {
            return result;
        }
        // If equal, continue to next field
    }
    
    return 0;  // All fields are equal
}
