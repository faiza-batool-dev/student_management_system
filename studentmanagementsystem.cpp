#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct student {
    string name;
    string rollNo;
    string semester;
    string department;
    char section;
    int marks;
};

void addStudent();
void viewStudents();
void viewOneStudent();
void removeStudent();
void updateStudent();

int main() {
    int choice = 0;

    while (choice != 6) {
        cout << endl << "---------- Student Management ----------" << endl;
        cout << endl << " 1. Add Student " << endl;
        cout << endl << " 2. Remove Student " << endl;
        cout << endl << " 3. Update Student " << endl;
        cout << endl << " 4. View One student " << endl;
        cout << endl << " 5. View Students " << endl;
        cout << endl << " 6. Exit " << endl;
        cout << endl << " Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << endl << "---------- Add Student ----------" << endl;
            addStudent();
            break;
        case 2:
            cout << endl << "---------- Remove Student ----------" << endl;
            removeStudent();
            break;
        case 3:
            cout << endl << "---------- Update Student ----------" << endl;
            updateStudent();
            break;
        case 4:
            cout << endl << " ---------- View one Student ---------- " << endl;
            viewOneStudent();
            break;
        case 5:
            cout << endl << "  ---------- View Students ----------  " << endl;
            viewStudents();
            break;
        case 6:
            cout << endl << "  Exit  " << endl;
            break;
        }
    }
}

void addStudent() {
    ofstream studentData("studentData.txt", ios::app);
    student student;

    cout << "Enter student name:  ";
    cin.ignore();
    getline(cin, student.name);

    cout << "Enter student Roll No:  ";
    getline(cin, student.rollNo);

    cout << "Enter student Semester:  ";
    getline(cin, student.semester);

    cout << "Enter student Department:  ";
    getline(cin, student.department);

    cout << "Enter student Section:  ";
    cin >> student.section;

    cout << "Enter student Marks:  ";
    cin >> student.marks;

    studentData << student.name << "," << student.rollNo << "," << student.semester << ","
        << student.department << "," << student.section << "," << student.marks << endl;

    studentData.close();
    cout << "\nStudent added successfully!\n";
}

void viewStudents() {
    string line;
    ifstream studentData("studentData.txt");

    while (getline(studentData, line)) {
        stringstream commaCutter(line);
        student s1;
        string marksString, tempSection;

        getline(commaCutter, s1.name, ',');
        getline(commaCutter, s1.rollNo, ',');
        getline(commaCutter, s1.semester, ',');
        getline(commaCutter, s1.department, ',');
        getline(commaCutter, tempSection, ',');
        s1.section = tempSection[0];
        getline(commaCutter, marksString, ',');
        s1.marks = stoi(marksString);

        cout << endl << "Name: " << s1.name
            << ", Roll No: " << s1.rollNo
            << ", Semester: " << s1.semester
            << ", Department: " << s1.department
            << ", Section: " << s1.section
            << ", Marks: " << s1.marks << endl;
    }

    cout << endl << "--------------------------------------" << endl;
    studentData.close();
}

void viewOneStudent() {
    ifstream studentData("studentData.txt");
    string line, rollNoToFind;
    bool found = false;

    cout << endl << "Enter roll no to view student detail: ";
    cin >> rollNoToFind;

    while (getline(studentData, line)) {
        stringstream commaCutter(line);
        student s1;
        string marksString, tempSection;

        getline(commaCutter, s1.name, ',');
        getline(commaCutter, s1.rollNo, ',');
        getline(commaCutter, s1.semester, ',');
        getline(commaCutter, s1.department, ',');
        getline(commaCutter, tempSection, ',');
        s1.section = tempSection[0];
        getline(commaCutter, marksString, ',');
        s1.marks = stoi(marksString);

        if (s1.rollNo == rollNoToFind) {
            cout << "\nStudent found!\n";
            cout << "Name: " << s1.name << endl;
            cout << "Roll No: " << s1.rollNo << endl;
            cout << "Semester: " << s1.semester << endl;
            cout << "Department: " << s1.department << endl;
            cout << "Section: " << s1.section << endl;
            cout << "Marks: " << s1.marks << endl;
            found = true;
        }
    }

    if (!found)
        cout << "\n No student exists with this roll no:";
    cout << endl << "--------------------------------------" << endl;
    studentData.close();
}

void removeStudent() {
    ifstream studentData("studentData.txt");
    ofstream tempFile("temp.txt");
    string line, rollNoToRemove, nameToRemove;
    bool found = false;

    cout << "Enter Name of student to remove: ";
    cin.ignore();
    getline(cin, nameToRemove);
    cout << "\nEnter roll number to remove student: ";
    cin >> rollNoToRemove;

    while (getline(studentData, line)) {
        stringstream commaCutter(line);
        student s1;
        string tempSection, marksString;

        getline(commaCutter, s1.name, ',');
        getline(commaCutter, s1.rollNo, ',');
        getline(commaCutter, s1.semester, ',');
        getline(commaCutter, s1.department, ',');
        getline(commaCutter, tempSection, ',');
        s1.section = tempSection[0];
        getline(commaCutter, marksString, ',');
        s1.marks = stoi(marksString);

        if (s1.name == nameToRemove && s1.rollNo == rollNoToRemove) {
            found = true;
            continue;
        }

        tempFile << s1.name << "," << s1.rollNo << "," << s1.semester << ","
            << s1.department << "," << s1.section << "," << s1.marks << endl;
    }

    studentData.close();
    tempFile.close();

    remove("studentData.txt");
    rename("temp.txt", "studentData.txt");

    if (found)
        cout << "\nStudent removed successfully!\n";
    else
        cout << "\nNo student found with that roll number.\n";

    cout << "--------------------------------------" << endl;
}

void updateStudent() {
    ifstream studentData("studentData.txt");
    ofstream tempFile("temp.txt");
    string line, rollNoToRemove, nameToRemove;
    bool found = false;

    cout << "Enter Name of student to update data: ";
    cin.ignore();
    getline(cin, nameToRemove);
    cout << "Enter roll number of student to update: ";
    getline(cin, rollNoToRemove);

    while (getline(studentData, line)) {
        stringstream commaCutter(line);
        student s1;
        string tempSection, marksString;

        getline(commaCutter, s1.name, ',');
        getline(commaCutter, s1.rollNo, ',');
        getline(commaCutter, s1.semester, ',');
        getline(commaCutter, s1.department, ',');
        getline(commaCutter, tempSection, ',');
        s1.section = tempSection[0];
        getline(commaCutter, marksString, ',');
        s1.marks = stoi(marksString);

        if (s1.rollNo == rollNoToRemove && s1.name == nameToRemove) {
            found = true;
            cout << "\nStudent found!\n";
            cout << "Current Data:\n";
            cout << "1. Name: " << s1.name << endl;
            cout << "2. Roll No: " << s1.rollNo << endl;
            cout << "3. Semester: " << s1.semester << endl;
            cout << "4. Department: " << s1.department << endl;
            cout << "5. Section: " << s1.section << endl;
            cout << "6. Marks: " << s1.marks << endl;

            int choice;
            cout << "\nEnter the number of the field you want to update: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                cout << "Enter new name: ";
                getline(cin, s1.name);
                break;
            case 2:
                cout << "Enter new roll: ";
                getline(cin, s1.rollNo);
                break;
            case 3:
                cout << "Enter new semester: ";
                getline(cin, s1.semester);
                break;
            case 4:
                cout << "Enter new department: ";
                getline(cin, s1.department);
                break;
            case 5:
                cout << "Enter new section: ";
                cin >> s1.section;
                break;
            case 6:
                cout << "Enter new marks: ";
                cin >> s1.marks;
                break;
            default:
                cout << "Invalid choice, keeping data same.\n";
            }

            cout << "\nRecord updated successfully!\n";
        }

        tempFile << s1.name << "," << s1.rollNo << "," << s1.semester << ","
            << s1.department << "," << s1.section << "," << s1.marks << endl;
    }

    studentData.close();
    tempFile.close();

    remove("studentData.txt");
    rename("temp.txt", "studentData.txt");

    if (!found)
        cout << "\nNo student found with that roll number.\n";

    cout << "--------------------------------------" << endl;
}
