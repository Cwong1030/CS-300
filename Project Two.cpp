//===========================================================================================
// Name        : Project Two.cpp
// Author      : Chris Wong
// Date        : 10/16/2022
//===========================================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Course {
    string courseNum;
    string courseName;
    string Prereqs[3] = { "", "", "" };
};

// Read data from txt file, then load into course vector
void loadCourseData(vector<Course>& course) {
    // open file
    ifstream courseFile("CourseList.txt", ios::in);

    // if file opened successfully
    if (!courseFile.is_open()) {
        cout << "Filed did not open!";
        exit(1);
    }

    // string object to read data into
    string courseInfo;

    // read data from file
    while (getline(courseFile, courseInfo)) {
        // read data from file into Course object
        Course temp;

        // create istringstream object
        istringstream ss(courseInfo);
        // read course number/name from istringstream ss
        getline(ss, temp.courseNum, ',');
        getline(ss, temp.courseName, ',');

        // create temp string to use as tokens for istringstream ss
        string Prereqs;
        // read data into Prereqs and keep assigning to Course object temp Prereqs;
        int i = 0;
        while (getline(ss, Prereqs, ',')) {
            temp.Prereqs[i] = Prereqs;
            i++;
        }

        // once all course data read for 'temp', push into vector courses
        course.push_back(temp);
    }

    // close input file
    courseFile.close();
}

// Print information of course, including its Prereqs
void printCourse(Course course) {
    cout << "Course Number: " << course.courseNum << endl;
    cout << "Course Name: " << course.courseName << endl;
    cout << "Prerequisites: ";
    for (int i = 0; i < 3; i++) {
        if (course.Prereqs[i] != "")
            cout << course.Prereqs[i] << "  ";
    }
    cout << endl << endl;
}

// Prints the courses in sorted-order
void printSortedList(vector<Course>& course) {
    int min, count = course.size();

    // selection sort vector of courses
    for (int i = 0; i < count - 1; i++) {
        min = i;
        for (int j = i + 1; j < count; j++) {
            if (course[j].courseNum < course[min].courseNum)
                min = j;
        }
        // Swap current course with course with min course number
        swap(course[min], course[i]);
    }

    // print list of course
    for (int i = 0; i < count; i++)
        printCourse(course[i]);
}

/**
* Traverse the vector and return 
* specific course information from input
*/
void printCourseInfo(vector<Course>& course) {
    string courseNum;
    cout << "Enter course number: " << endl;
    cin >> courseNum;

    bool found = false;
    for (int i = 0; i < course.size(); i++) {
        if (course[i].courseNum == courseNum) {
            found = true;
            printCourse(course[i]);
            break;
        }
    }

    if (!found)
        cout << endl << "Invalid course number!" << endl;
}

// Menu for user 
void courseMenu() {
    cout << "Menu:" << endl;
    cout << "1. Load Course Data" << endl;
    cout << "2. Display Courses List" << endl;
    cout << "3. Display Course Info" << endl;
    cout << "9. Exit" << endl << endl;
    cout << "Enter choice: ";
    cout << endl;
}

// The int main method
int main() {
    vector<Course> course;
    int choice = 0;
    // Menu loop
    while (choice != 9) {
        courseMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            // calls loadCourseData() to read data from file into course vector
            loadCourseData(course);
            break;
        case 2:
            // call printSortedList() to sort courses, then print them
            printSortedList(course);
            break;
        case 3:
            // call printCourseInfo() to print information for a specific course number
            printCourseInfo(course);
            break;
        }
    }
    cout << "Thank you for using the course planner!";
}