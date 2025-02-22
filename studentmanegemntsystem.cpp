#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Struct definitions
struct Student {
    string ID;
    string name;
    string classInfo;
    int marks[3][3]; // 3 subjects, 3 marks each
    float cgpa;
};

struct Teacher {
    string ID;
    string name;
    string subject;
};

// Function declarations
void addTeacher();
void deleteTeacher();
void displayTeachers();
void addStudent();
void deleteStudent();
void addGrades();
void calculateCGPA();
void averageCGPA();
void listPassedStudents();
void listFailedStudents();
void displayAllStudents();
void viewGrades();
void viewCgpa();

void adminMenu();
void teacherMenu();
void studentMenu();

// Function definitions

// Add teacher functionality
void addTeacher() {
    ofstream out("Teacher.txt", ios::app);
    if (!out) {
        cout << "This file does not exist" << endl;
        return;
    }

    Teacher teacher;
    cout << "Enter teacher ID: ";
    cin >> teacher.ID;
    cout << "Enter the teacher name: ";
    cin.ignore();
    getline(cin, teacher.name);
    cout << "Enter the teacher subject: ";
    getline(cin, teacher.subject);

    out << teacher.ID << " " << teacher.name << " " << teacher.subject << endl;
    out.close();
    cout << "Teacher added successfully!" << endl;
}

// Delete teacher functionality
void deleteTeacher() {
    ifstream in("Teacher.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }

    ofstream temp("Temp.txt");
    if (!temp) {
        cout << "Temporary file could not be created" << endl;
        return;
    }

    string id, line, targetID;
    cout << "Enter teacher ID to delete: ";
    cin >> targetID;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, id, ' ');
        if (id != targetID) {
            temp << line << endl;
        }
        else {
            found = true;
        }
    }
    in.close();
    temp.close();

    remove("Teacher.txt");
    rename("Temp.txt", "Teacher.txt");

    if (found) {
        cout << "Teacher deleted successfully!" << endl;
    }
    else {
        cout << "Teacher ID not found." << endl;
    }
}

// Display all teachers functionality
void displayTeachers() {
    ifstream in("Teacher.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }

    string line;
    cout << "List of Teachers:" << endl;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

// Add student functionality
void addStudent() {
    ofstream out("Student.txt", ios::app);
    if (!out) {
        cout << "This file does not exist" << endl;
        return;
    }

    Student student;
    cout << "Enter the student ID: ";
    cin >> student.ID;
    cin.ignore();
    cout << "Enter the student name: ";
    getline(cin, student.name);
    cout << "Enter the class: ";
    getline(cin, student.classInfo);

    out << student.ID << " " << student.name << " " << student.classInfo << " 0 0 0 0" << endl; // Initialize marks and cgpa
    out.close();
    cout << "Student added successfully!" << endl;
}

// Delete student functionality
void deleteStudent() {
    ifstream in("Student.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }

    ofstream temp("Temp.txt");
    if (!temp) {
        cout << "Temporary file could not be created" << endl;
        return;
    }

    string id, line, targetID;
    cout << "Enter student ID to delete: ";
    cin >> targetID;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, id, ' ');
        if (id != targetID) {
            temp << line << endl;
        }
        else {
            found = true;
        }
    }
    in.close();
    temp.close();

    remove("Student.txt");
    rename("Temp.txt", "Student.txt");

    if (found) {
        cout << "Student deleted successfully!" << endl;
    }
    else {
        cout << "Student ID not found." << endl;
    }
}
void addGrades() {
    ifstream in("Student.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }

    ofstream temp("Temp.txt");
    if (!temp) {
        cout << "Temporary file could not be created" << endl;
        return;
    }

    string id, line, targetID;
    cout << "Enter student ID to add grades: ";
    cin >> targetID;
    bool found = false;

    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, id, ' ');
        if (id == targetID) {
            found = true;
            string name, classInfo;
            int marks[3][3];
            float cgpa;

            ss >> name >> classInfo;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    ss >> marks[i][j];

            // Get new grades from user
            for (int i = 0; i < 3; ++i) {
                cout << "Enter grades for subject " << (i + 1) << ": ";
                for (int j = 0; j < 3; ++j) {
                    cout << "Mark " << (j + 1) << ": ";
                    cin >> marks[i][j];
                }
            }

            // Calculate CGPA
            float totalMarks = 0;
            int count = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j) {
                    totalMarks += marks[i][j];
                    ++count;
                }
            cgpa = (totalMarks / count) / 25.0;
            if (cgpa > 4.0) {
                cgpa = 4.0; // Cap CGPA at 4.0
            }// Example CGPA calculation

            // Write updated student data to temp file
            temp << id << " " << name << " " << classInfo << " ";
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    temp << marks[i][j] << " ";
            temp << cgpa << endl;

            cout << "Grades added successfully and CGPA updated!" << endl;
        }
        else {
            temp << line << endl;
        }
    }

    if (!found) {
        cout << "Student ID not found." << endl;
    }

    in.close();
    temp.close();
    remove("Student.txt");
    rename("Temp.txt", "Student.txt");
}
// Calculate CGPA functionality
void calculateCGPA() {
    ifstream inFile("Student.txt");
    ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) {
        cout << "Error opening files!" << endl;
        return;
    }

    string line, targetID;
    cout << "Enter Student ID to calculate CGPA: ";
    cin >> targetID;

    bool found = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        if (id == targetID) {
            found = true;
            ss >> name >> classInfo;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    ss >> marks[i][j];

            // Calculate CGPA
            float totalMarks = 0;
            int count = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j) {
                    totalMarks += marks[i][j];
                    ++count;
                }
            cgpa = (totalMarks / count) / 25.0;
            if (cgpa > 4.0) {
                cgpa = 4.0; // Cap CGPA at 4.0
            }

            tempFile << id << " " << name << " " << classInfo << " ";
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    tempFile << marks[i][j] << " ";
            tempFile << cgpa << endl;

            cout << "CGPA calculated and updated: " << cgpa << endl;
        }
        else {
            tempFile << line << endl;
        }
    }

    if (!found) {
        cout << "Student ID not found." << endl;
    }

    inFile.close();
    tempFile.close();
    remove("Student.txt");
    rename("temp.txt", "Student.txt");
}
//calculate average CGPA functionality
void averageCGPA() {
    ifstream inFile("Student.txt");
    if (!inFile) {
        cout << "Error opening student file!" << endl;
        return;
    }

    float totalCGPA = 0;
    int count = 0;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        ss >> name >> classInfo;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                ss >> marks[i][j];
        ss >> cgpa;

        totalCGPA += cgpa;
        count++;
    }

    if (count == 0) {
        cout << "No students found." << endl;
    }
    else {
        cout << "Average CGPA: " << totalCGPA / count << endl;
    }

    inFile.close();
}
void listPassedStudents() {
    ifstream inFile("Student.txt");
    if (!inFile) {
        cout << "Error opening student file!" << endl;
        return;
    }

    cout << "=== Passed Students (CGPA >= 2.0) ===" << endl;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        ss >> name >> classInfo;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                ss >> marks[i][j];
        ss >> cgpa;

        if (cgpa >= 2.0) {
            cout << line << endl;
        }
    }

    inFile.close();
}
void listFailedStudents() {
    ifstream inFile("Student.txt");
    if (!inFile) {
        cout << "Error opening student file!" << endl;
        return;
    }

    cout << "=== Failed Students (CGPA < 2.0) ===" << endl;
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        ss >> name >> classInfo;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                ss >> marks[i][j];
        ss >> cgpa;

        if (cgpa < 2.0) {
            cout << line << endl;
        }
    }

    inFile.close();
}



// Display all students functionality
void displayAllStudents() {
    ifstream inFile("Student.txt");
    if (!inFile) {
        cout << "Error opening student file!" << endl;
        return;
    }

    cout << "=== Students List ===" << endl;
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}


// View grades functionality
void viewGrades() {
    ifstream in("Student.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }
    string line, T;
    cout << "Enter student ID: ";
    cin >> T;
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        if (id == T) {
            found = true;
            ss >> name >> classInfo;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    ss >> marks[i][j];
            ss >> cgpa;

            cout << "Grades for student " << name << " (" << id << ") in class " << classInfo << ":" << endl;
            for (int i = 0; i < 3; ++i) {
                cout << "Subject " << (i + 1) << " grades: ";
                for (int j = 0; j < 3; ++j) {
                    cout << marks[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "Student ID not found." << endl;
    }
    in.close();
}
// View CGPA functionality
void viewCgpa() {
    ifstream in("Student.txt");
    if (!in) {
        cout << "This file does not exist" << endl;
        return;
    }
    string line, T;
    cout << "Enter student ID: ";
    cin >> T;
    bool found = false;
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, classInfo;
        int marks[3][3];
        float cgpa;

        getline(ss, id, ' ');
        if (id == T) {
            found = true;
            ss >> name >> classInfo;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    ss >> marks[i][j];
            ss >> cgpa;

            cout << "CGPA for student " << name << " (" << id << ") in class " << classInfo << " is: " << cgpa << endl;
            break;
        }
    }
    if (!found) {
        cout << "Student ID not found." << endl;
    }
    in.close();
}

// Admin menu
void adminMenu() {
    int choice;
    do {
        cout << "Admin Menu:" << endl;
        cout << "1. Add Teacher" << endl;
        cout << "2. Delete Teacher" << endl;
        cout << "3. Display All Teachers" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTeacher();
            break;
        case 2:
            deleteTeacher();
            break;
        case 3:
            displayTeachers();
            break;
        case 4:
            cout << "Exiting Admin Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

// Teacher menu
void teacherMenu() {
    int choice;
    do {
        cout << "Teacher Menu:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Calculate CGPA" << endl;
        cout << "4. Average CGPA" << endl;
        cout << "5. List Passed Students" << endl;
        cout << "6. List Failed Students" << endl;
        cout << "7. Display All Students" << endl;
        cout << "8. Add Grades" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            calculateCGPA();
            break;
        case 4:
            averageCGPA();
            break;
        case 5:
            listPassedStudents();
            break;
        case 6:
            listFailedStudents();
            break;
        case 7:
            displayAllStudents();
            break;
        case 8:
            addGrades();
            break;
        case 9:
            cout << "Exiting Teacher Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);
}

// Student menu
void studentMenu() {
    int choice;
    do {
        cout << "Student Menu:" << endl;
        cout << "1. View Grades" << endl;
        cout << "2. View CGPA" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewGrades();
            break;
        case 2:
            viewCgpa();
            break;
        case 3:
            cout << "Exiting Student Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

// Main menu
int main() {
    int choice;
    do {
        cout << "Main Menu:" << endl;
        cout << "1. Student Management System for Admin" << endl;
        cout << "2. Student Management System for Teacher" << endl;
        cout << "3. Student Management System for Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            adminMenu();
            break;
        case 2:
            teacherMenu();
            break;
        case 3:
            studentMenu();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}