//Ty Skinner
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

// Struct to store course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load courses from a file into a data structure
map<string, Course> loadCourses(const string& fileName) {
    map<string, Course> courses;
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error: Cannot open file " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<string> parts = split(line, ',');
        if (parts.size() >= 2) {
            Course course;
            course.courseNumber = parts[0];
            course.courseTitle = parts[1];
            for (size_t i = 2; i < parts.size(); ++i) {
                course.prerequisites.push_back(parts[i]);
            }
            courses[course.courseNumber] = course;
        }
    }

    inputFile.close();
    return courses;
}

// Function to print a sorted list of all courses
void printCourseList(const map<string, Course>& courses) {
    vector<string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    sort(courseNumbers.begin(), courseNumbers.end());

    for (const string& courseNumber : courseNumbers) {
        cout << courseNumber << ": " << courses.at(courseNumber).courseTitle << endl;
    }
}

// Function to print course information
void printCourseInformation(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Title: " << course.courseTitle << endl;
        cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            cout << "None";
        }
        else {
            for (const string& prereq : course.prerequisites) {
                cout << prereq << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "Error: Course not found." << endl;
    }
}

// Main menu function
void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course Information\n";
    cout << "9. Exit\n";
}

int main() {
    map<string, Course> courses;
    string fileName;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter the file name: ";
            cin >> fileName;
            courses = loadCourses(fileName);
            if (!courses.empty()) {
                cout << "Courses loaded successfully." << endl;
            }
            break;
        }
        case 2: {
            if (courses.empty()) {
                cout << "Error: No courses loaded. Please load a file first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        }
        case 3: {
            if (courses.empty()) {
                cout << "Error: No courses loaded. Please load a file first." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter course number: ";
                cin >> courseNumber;
                printCourseInformation(courses, courseNumber);
            }
            break;
        }
        case 9:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Error: Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
