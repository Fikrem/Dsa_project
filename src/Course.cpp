using namespace std;

#include "../include/Course.h"
#include "../include/Utils.h"

Course::Course() : courseCode(""), courseName(""), department(""),
                   yearOfStudy(0), creditHours(0) {}

Course::Course(const string& code, const string& name,
               const string& dept, int year, int credits)
    : courseCode(code), courseName(name), department(dept),
      yearOfStudy(year), creditHours(credits) {}

string Course::toCSV() const {
    return department + "," + to_string(yearOfStudy) + "," +
           courseCode + "," + courseName + "," + to_string(creditHours);
}

Course Course::fromCSV(const string& csvLine) {
    vector<string> fields = Utils::split(csvLine, ',');
    
    if (fields.size() < 5) {
        return Course();
    }
    
    string dept = Utils::trim(fields[0]);
    int year = stoi(Utils::trim(fields[1]));
    string code = Utils::trim(fields[2]);
    string name = Utils::trim(fields[3]);
    int credits = stoi(Utils::trim(fields[4]));
    
    return Course(code, name, dept, year, credits);
}
