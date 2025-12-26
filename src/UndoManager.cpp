using namespace std;

#include "../include/UndoManager.h"
#include "../include/StudentManager.h"

// AddStudentCommand implementation
AddStudentCommand::AddStudentCommand(StudentManager* mgr, const Student& s)
    : manager(mgr), student(s), executed(false) {}

void AddStudentCommand::execute() {
    if (!executed) {
        manager->addStudent(student, false);  // Don't use undo for undo commands
        executed = true;
    }
}

void AddStudentCommand::undo() {
    if (executed) {
        manager->deleteStudent(student.getId(), false);
        executed = false;
    }
}

string AddStudentCommand::getDescription() const {
    return "Add student: " + student.getId() + " (" + student.getFullName() + ")";
}

// UpdateStudentCommand implementation
UpdateStudentCommand::UpdateStudentCommand(StudentManager* mgr, const Student& oldS, const Student& newS)
    : manager(mgr), oldStudent(oldS), newStudent(newS), executed(false) {}

void UpdateStudentCommand::execute() {
    if (!executed) {
        manager->updateStudent(newStudent.getId(), newStudent, false);
        executed = true;
    }
}

void UpdateStudentCommand::undo() {
    if (executed) {
        manager->updateStudent(oldStudent.getId(), oldStudent, false);
        executed = false;
    }
}

string UpdateStudentCommand::getDescription() const {
    return "Update student: " + newStudent.getId() + " (" + newStudent.getFullName() + ")";
}

// DeleteStudentCommand implementation
DeleteStudentCommand::DeleteStudentCommand(StudentManager* mgr, const Student& s)
    : manager(mgr), student(s), executed(false) {}

void DeleteStudentCommand::execute() {
    if (!executed) {
        manager->deleteStudent(student.getId(), false);
        executed = true;
    }
}

void DeleteStudentCommand::undo() {
    if (executed) {
        manager->addStudent(student, false);
        executed = false;
    }
}

string DeleteStudentCommand::getDescription() const {
    return "Delete student: " + student.getId() + " (" + student.getFullName() + ")";
}

// UndoManager implementation
void UndoManager::executeCommand(unique_ptr<Command> command) {
    command->execute();
    
    undoStack.push(move(command));
    
    // Maintain max size
    if (undoStack.size() > MAX_UNDO_SIZE) {
        // Remove oldest command (at bottom of stack)
        stack<unique_ptr<Command>> tempStack;
        
        while (undoStack.size() > 1) {
            tempStack.push(move(undoStack.top()));
            undoStack.pop();
        }
        
        undoStack.pop();  // Remove the oldest
        
        while (!tempStack.empty()) {
            undoStack.push(move(tempStack.top()));
            tempStack.pop();
        }
    }
}

bool UndoManager::canUndo() const {
    return !undoStack.empty();
}

void UndoManager::undo() {
    if (canUndo()) {
        undoStack.top()->undo();
        undoStack.pop();
    }
}

void UndoManager::clear() {
    while (!undoStack.empty()) {
        undoStack.pop();
    }
}

int UndoManager::getUndoCount() const {
    return undoStack.size();
}

string UndoManager::getLastCommandDescription() const {
    if (canUndo()) {
        return undoStack.top()->getDescription();
    }
    return "No operations to undo";
}
