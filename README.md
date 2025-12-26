# Student Record Management System

A comprehensive console-based C++ application for managing student records with advanced features including multi-parameter search, sorting, grading, and undo functionality.

## Features

### 🔐 Authentication System
- **Admin Access**: Full CRUD operations, search, sort, grade, and undo
  - Username: `admin`
  - Password: `admin123`
- **Student Access**: View-only access to personal academic records
  - Login with student ID and password (default: `password` for all sample students)

### 📊 Data Structures
- **AVL Tree**: Self-balancing binary search tree for O(log n) operations
- **Hash Map**: Fast course result lookups
- **Stack**: Undo operation management (last 5 operations)

### 🔍 Advanced Search
- Multi-parameter search with:
  - ID, Name (first/last), Department, Age, Sex, Year of Study, GPA range
  - **MATCH_ALL** mode: AND logic (all criteria must match)
  - **MATCH_ANY** mode: OR logic (any criteria can match)

### 📈 Sorting
- Sort by: Sex, Age, GPA, Department, Year of Study, ID, Name
- Single parameter sorting with ascending/descending order
- Stable merge sort implementation

### 🎓 Grading System
- Assessment score (0-50) + Final exam (0-50)
- Automatic letter grade calculation (A/B/C/D/F)
- SGPA calculation based on credit hours
- Grade scale: A=4.0, B=3.0, C=2.0, D=1.0, F=0.0

### ↩️ Undo Functionality
- Command pattern-based undo system
- Stores last 5 operations (Add, Update, Delete)
- One-click undo with confirmation

### 📋 Table Display
- Beautiful ASCII table formatting
- Summary view for multiple students
- Detailed view with course breakdown

## Project Structure

```
Dsa_project/
├── include/              # Header files
│   ├── AVLTree.h        # Template AVL tree
│   ├── Course.h         # Course class
│   ├── Student.h        # Student class with CourseResult
│   ├── Grader.h         # Grading logic
│   ├── SearchManager.h  # Multi-parameter search
│   ├── Sorter.h         # Single-parameter merge sort
│   ├── UndoManager.h    # Command pattern undo
│   ├── StudentManager.h # Main controller
│   ├── TableFormatter.h # Display formatting
│   └── Utils.h          # Utility functions
├── src/                 # Implementation files
│   ├── Course.cpp
│   ├── Student.cpp
│   ├── Grader.cpp
│   ├── SearchManager.cpp
│   ├── Sorter.cpp
│   ├── UndoManager.cpp
│   ├── StudentManager.cpp
│   ├── TableFormatter.cpp
│   ├── Utils.cpp
│   └── main.cpp         # Menu system
├── data/                # CSV databases
│   ├── courses.csv      # Course catalog
│   └── students.csv     # Student records
├── Makefile             # Build configuration
└── README.md            # This file
```

## Building and Running

### Prerequisites
- g++ compiler with C++17 support
- Linux/Unix environment (or WSL on Windows)

### Build
```bash
make
```

### Run
```bash
make run
# or
./student_manager
```

### Clean
```bash
make clean
```

### Rebuild
```bash
make rebuild
```

## Usage

### Admin Login
1. Select "Admin Login"
2. Enter username: `admin`
3. Enter password: `admin123`

Admin can:
- Add new students
- Update student information
- Delete students
- Search students (multi-parameter)
- Sort students (single parameter)
- Grade students
- View all students
- Undo last operation

### Student Login
1. Select "Student Login"
2. Enter student ID (e.g., `001`)
3. Enter password (`password` for sample data)

Students can:
- View their complete academic record
- See all course grades and GPA

## Sample Data

### Sample Students
- **001**: John Doe (CS, Year 1, GPA: 3.75)
- **002**: Jane Smith (CS, Year 1, GPA: 4.00)
- **003**: Michael Johnson (CS, Year 2, GPA: 2.77)
- **004**: Emily Williams (CS, Year 2, GPA: 3.92)
- **005**: David Brown (CS, Year 3, GPA: 3.21)
- **006**: Sarah Davis (EE, Year 1, GPA: 3.69)
- **007**: Robert Miller (EE, Year 2, GPA: 2.70)
- **008**: Lisa Wilson (ME, Year 1, GPA: 3.92)
- **009**: James Moore (ME, Year 2, GPA: 3.30)
- **010**: Amanda Taylor (CS, Year 1, GPA: 3.58)

All sample students have password: `password`

### Departments
- **CS**: Computer Science
- **EE**: Electrical Engineering
- **ME**: Mechanical Engineering

## Technical Details

### CSV File Format

**courses.csv**:
```csv
department,year_of_study,course_code,course_name,credit_hours
CS,1,CS101,Introduction to Programming,3
```

**students.csv**:
```csv
id,password_hash,first_name,last_name,department,age,sex,year_of_study,section,course_results
001,hash,"John","Doe",CS,20,M,1,A,"CS101:45:48:A:3|MATH101:40:45:B:4"
```

Course results format: `course_code:assessment:final:grade:credits|...`

### Password Hashing
Simple hash function for demonstration (DJB2 algorithm). In production, use proper cryptographic hashing (e.g., bcrypt, SHA-256).

### Data Persistence
- Data loaded from CSV on startup
- Data saved to CSV on exit
- Single read/write per program lifecycle

## Design Patterns

- **Command Pattern**: Undo functionality
- **Template Pattern**: Generic AVL tree
- **Singleton-like**: StudentManager as central controller
- **Strategy Pattern**: Search modes (MATCH_ALL vs MATCH_ANY)

## Algorithms

- **AVL Tree**: O(log n) insert, delete, search
- **Merge Sort**: O(n log n) stable sorting
- **Binary Search**: O(log n) for sorted data
- **Hash Map**: O(1) average case for course lookups

## Future Enhancements

- Attendance tracking
- Report generation (PDF/CSV export)
- Backup mechanism
- CGPA calculation (cumulative GPA)
- Course prerequisites
- Semester management
- Email notifications
- Web interface

## License

This project is created for educational purposes.

## Author

Created as a Data Structures and Algorithms project demonstrating:
- AVL Trees
- Merge Sort
- Binary Search
- Stack (for undo)
- Hash Maps
- Object-Oriented Design
- File I/O
- Command Pattern
