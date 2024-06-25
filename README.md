# Student Information System

This C program implements a simple student information system that allows users to manage student details, course details, and generate student reports. The system uses file operations to store and retrieve data for persistence. Below is an overview of the program's structure and functionality:

## Structures

1. **student**: Stores student information, including index number, name, and department.
2. **grades**: Stores grade information for students, including student ID, course ID, and grade.
3. **course**: Stores course details, including course ID, course name, and credit value.

## Functions

1. **main()**: The entry point of the program, displaying a menu and handling user input to navigate between different functionalities.
2. **addStuDet()**: Prompts the user to enter and save student details and their respective grades.
3. **coursedet()**: Prompts the user to enter and save course details.
4. **report()**: Generates a report for a student, including their courses, grades, and GPA. It also allows editing student or course details.

## Main Menu

The main menu provides the following options:
- **1 | Student Details**: Calls `addStuDet()` to add new student details.
- **2 | Course Details**: Calls `coursedet()` to add new course details.
- **3 | Student Report**: Calls `report()` to generate and display a report for a specific student.
- **0 | Exit**: Exits the program.

## Function Descriptions

### addStuDet()

- Opens or creates `studentdetails.txt` and `gradefile.txt` for appending.
- Prompts the user to enter student details (index number, name, department) and writes them to `studentdetails.txt`.
- Prompts the user to enter grades for multiple courses and writes them to `gradefile.txt`.

### coursedet()

- Opens or creates `coursedetails.txt` for appending.
- Displays existing course details from `coursedetails.txt`.
- Prompts the user to enter new course details (course ID, course name, credit value) and writes them to `coursedetails.txt`.

### report()

- Prompts the user to enter a student index number and searches for the student in `studentdetails.txt`.
- If the student is found, it displays the student's details and their course grades by reading `gradefile.txt` and `coursedetails.txt`.
- Calculates the GPA based on the grades and credit values.
- Provides options to edit student or course details, which involves removing the old records and re-entering the new ones.

## File Operations

- The program uses file operations (`fopen`, `fwrite`, `fread`, `fclose`) to handle data persistence.
- Temporary files are used for editing records to ensure data integrity.

## GPA Calculation

- The GPA is calculated based on the grades and their respective credit values, with different grades (A, B, C, D, E, AB) corresponding to specific grade points.

This system is a basic implementation of a student information management system, demonstrating file handling, structured data storage, and basic user interaction through a console-based menu.
