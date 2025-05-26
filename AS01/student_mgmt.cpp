#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

//Student structure
typedef struct Student
{
    int id;
    string name;
    int age;
    float grade;
} Student;

//Function prototypes
void addStudent(unordered_map<int, Student> &registry, int id, string name, int age, float grade);
void displayAllStudents(unordered_map<int, Student> &registry);
void findStudentByID(int id, unordered_map<int, Student> &registry);
void deleteStudentByID(int id, unordered_map<int, Student> &registry);
float getAverageGrade(unordered_map<int, Student> &registry);
int factorial(int n);

//This was really fun, a program that implements a student registry using a hashmap
int main() {
    unordered_map<int, Student> registry;
    bool buffer = true;

    //Do a running buffer
    while (buffer) {
        //Display all options
        cout << "---Student Management System---\n";
        cout << "  1: to add student: needs name, id, age, grade\n";
        cout << "  2: to display all students.\n";
        cout << "  3: to find student by ID\n";
        cout << "  4: to delete student by ID\n";
        cout << "  5: calculate average grade of students\n";
        cout << "  6: to calculate factorial of a number\n";
        cout << "  7: to exit\n";
        cout << "  Enter an option from above.\n";
        cout << "-------------------------------\n";

        int option;
        cin >> option;

        //Check selected option
        switch (option) {
            case 1: {
                int id;
                string name;
                int age;
                float grade;

                cout << "----------\n";
                cout << "Enter student name(string): "; //Enter name
                cin.ignore(); //Use ignore to input string
                getline(cin, name);

                cout << "Enter student ID(int): "; //Enter int id
                cin >> id;

                cout << "Enter student age(int): "; //Enter int age
                cin >> age;

                cout << "Enter student grade(float): "; //Enter float grade
                cin >> grade;

                //Checker for if ID exists
                if (registry.find(id) != registry.end()) {
                    cout << "----------\n";
                    cout << "Student ID already exists.\n";
                    cout << "----------\n";
                    break;
                }
                addStudent(registry, id, name, age, grade);
                cout << "----------\n";
                break;
            }
            case 2: {
                displayAllStudents(registry);
                break;
            }
            case 3: {
                int id;

                cout << "Enter ID to find: ";
                cin >> id;

                findStudentByID(id, registry);
                break;
            }
            case 4: {
                int id;

                cout << "Enter ID to delete: ";
                cin >> id;

                deleteStudentByID(id, registry);
                break;
            }
            case 5: {
                float average = getAverageGrade(registry);
                cout << "Average grade of all students: " << average << endl;
                break;
            }
            case 6: {
                int nbr;

                cout << "Enter number to find factorial: ";
                cin >> nbr;

                //Have result to be equal to output
                int result = factorial(nbr);
                cout << "Factorial of " << nbr << " is " << result << endl;
                break;
            }
            case 7: {
                cout << "Exiting...\n";
                buffer = false;
                break;
            }
            default: {
                cout << "Invalid option. Please enter from 1 to 7 only.\n";
                break;
            }
        }
    }
    return 0;
}

//Add students to hashmap
void addStudent(unordered_map<int, Student> &registry, int id, string name, int age, float grade) {
    Student new_Student = {id, name, age, grade};
    registry[id] = new_Student;
    cout << "Student successfully added.\n";
}

//Display all students of hashmap
void displayAllStudents(unordered_map<int, Student> &registry) {
    if (registry.empty()) {
        cout << "Registry is empty. Please input students.\n";
        return;
    }

    //Do some very nice structural binding and auto looping
    for (const auto& [id, student] : registry) {
        cout << "------------\n";
        cout << "ID: " << student.id << endl;
        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Grade: " << student.grade << endl;
        cout << "------------\n";
    }
}

//Find a student by ID
void findStudentByID(int id, unordered_map<int, Student> &registry) {
    //There is an iterator called auto that iterates through a hashmap
    auto finder = registry.find(id);
    if (finder != registry.end()) {
        Student student = finder->second;
        cout << "------------\n";
        cout << "ID: " << student.id << endl;
        cout << "Name: " << student.name << endl;
        cout << "Age: " << student.age << endl;
        cout << "Grade: " << student.grade << endl;
        cout << "------------\n";
    } else {
        cout << "------------\n";
        cout << "Student not found.\n";
        cout << "------------\n";
    }
}

//Delete a student by ID
void deleteStudentByID(int id, unordered_map<int, Student> &registry) {
    //There is an iterator called auto that iterates through a hashmap
    auto finder = registry.find(id);
    if (finder != registry.end()) {
        registry.erase(id);
        cout << "------------\n";
        cout << "Student deleted.\n";
        cout << "------------\n";
    } else {
        cout << "------------\n";
        cout << "Student not found.\n";
        cout << "------------\n";
    }
}

//Loop through hashmap to find average of all students
float getAverageGrade(unordered_map<int, Student> &registry) {
    //Check for empty registry
    if (registry.empty()) {
        cout << "Registry is empty. Please input students.\n" << endl;
        return 0.0f;
    }

    //Loop through using auto and add to sum
    float sum = 0.0f;
    for (const auto& [id, student] : registry) {
        sum += student.grade;
    }

    //Return average
    return (sum / registry.size());
}

//Recursive call to factorial
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
