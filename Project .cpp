#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<chrono>
#include<thread>
#include <limits>
#include<cstdio> // For remove and rename

using namespace std;

// --- USING STRUCTURES ---
struct students{
    string roll_no, f_name, l_name;
};

struct faculty{
    string id, f_name, l_name, dep;
};

struct courses{
    string code, name, credits;
};

// Global instances(global Variables)
students student;
faculty fac;
courses course;

// --- UTILITY FUNCTIONS ---
void wait_and_clear(int seconds = 2) {
    this_thread::sleep_for(chrono::seconds(seconds));
    system("cls");
}

void pause_screen() {
    cout << "\nPress any key to continue...";
    while (!_kbhit()) {}
    _getch();
    system("cls");
}

// --- LOGIN SYSTEM ---
bool checklogin(string id, string pass) {
    ifstream file("users.txt");
    if(!file){
        // Create default user if file doesn't exist
        ofstream newFile("users.txt");
        newFile << "admin admin";
        newFile.close();
        file.open("users.txt");
    }
    
    string file_id, file_pass;
    while(file >> file_id >> file_pass) {
        if(file_id == id && file_pass == pass) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// ==========================================
//           STUDENT MANAGEMENT
// ==========================================

void add_student(){
    char choice;
    do{
        system("cls");
        cout << "ADD STUDENT" << endl;
        cout << "Enter Roll number: "; cin >> student.roll_no;
        cout << "Enter first name: "; cin >> student.f_name;
        cout << "Enter last name: "; cin >> student.l_name;
        
        ofstream file("students.txt", ios::app); 
        file << student.roll_no << " " << student.f_name << " " << student.l_name << endl;    
        file.close();
        
        cout << endl << "Student added successfully!" << endl;
        cout << "Add another? (y/n): ";
        cin >> choice;
    } while(choice == 'y' || choice == 'Y');
}

void view_student(){
    cout << "VIEW STUDENTS" << endl;
    ifstream file("students.txt");
    if (!file) {
        cout << "No data found." << endl;
        pause_screen();
        return;
    }
    
    cout << "\n-----------------------------------" << endl;
    cout << "Roll No\t\tName" << endl;
    cout << "-----------------------------------" << endl;
    
    while (file >> student.roll_no >> student.f_name >> student.l_name){
        cout << student.roll_no << "\t\t" << student.f_name << " " << student.l_name << endl;
    }
    file.close();
    pause_screen();
}

void update_student(){
    string roll;
    cout << "UPDATE STUDENT" << endl;
    cout << "Enter Roll number to update: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");
    bool found = false;

    while (file >> student.roll_no >> student.f_name >> student.l_name){
        if (student.roll_no == roll){
            found = true;
            cout << "Current Name: " << student.f_name << " " << student.l_name << endl;
            cout << "Enter New First Name: "; cin >> student.f_name;
            cout << "Enter New Last Name: "; cin >> student.l_name;
            cout << "Record Updated." << endl;
        }
        temp << student.roll_no << " " << student.f_name << " " << student.l_name << endl;
    }
    file.close();
    temp.close();
    
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(!found) cout << "Student not found!" << endl;
    pause_screen();
}

void delete_student(){
    string roll;
    cout << "DELETE STUDENT" << endl;
    cout << "Enter Roll number to delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");
    bool found = false;

    while (file >> student.roll_no >> student.f_name >> student.l_name){
        if (student.roll_no == roll){
            found = true;
            cout << "Deleting student: " << student.f_name << " " << student.l_name << endl;
            continue; // Skip writing this to temp file
        }
        temp << student.roll_no << " " << student.f_name << " " << student.l_name << endl;
    }
    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found) cout << "Student deleted successfully." << endl;
    else cout << "Student not found." << endl;
    pause_screen();
}

void student_management() {
    int choice;
    do{
        system("cls");
        cout<<"STUDENT MANAGEMENT"<<endl;
        cout<<"1. Add Student"<<endl;
        cout<<"2. View Students"<<endl;
        cout<<"3. Update Student"<<endl;
        cout<<"4. Delete Student"<<endl;
        cout<<"5. Back"<<endl;
        cout<<"Select(1-5): ";
        cin>>choice;

        switch(choice) {
            case 1: add_student(); break;
            case 2: view_student(); break;
            case 3: update_student(); break;
            case 4: delete_student(); break;
            case 5: break; 
            default: cout<<"Invalid Input!"; wait_and_clear(); break;
        }
    } while (choice!=5);
}

// ==========================================
//           FACULTY MANAGEMENT
// ==========================================

void add_faculty(){
    char choice;
    do{
        system("cls");
        cout << "ADD FACULTY" << endl;
        cout << "Enter ID: "; cin >> fac.id;
        cout << "Enter First Name: "; cin >> fac.f_name;
        cout << "Enter Last Name: "; cin >> fac.l_name;
        cout << "Enter Department: "; cin >> fac.dep;
        
        ofstream file("faculty.txt", ios::app);
        file << fac.id << " " << fac.f_name << " " << fac.l_name << " " << fac.dep << endl;
        file.close();
        
        cout << "Faculty added successfully!" << endl;
        cout << "Add another? (y/n): "; cin >> choice;
    } while(choice == 'y' || choice == 'Y');
}

void view_faculty(){
    cout << "VIEW FACULTY" << endl;
    ifstream file("faculty.txt");
    if (!file) {
        cout << "No data found." << endl;
        pause_screen();
        return;
    }
    cout << "\n------------------------------------------------" << endl;
    cout << "ID\tName\t\tDepartment" << endl;
    cout << "------------------------------------------------" << endl;
    while (file >> fac.id >> fac.f_name >> fac.l_name >> fac.dep){
        cout << fac.id << "\t" << fac.f_name << " " << fac.l_name << "\t" << fac.dep << endl;
    }
    file.close();
    pause_screen();
}

void update_faculty(){
    string id;
    cout << "UPDATE FACULTY" << endl;
    cout << "Enter ID to update: "; cin >> id;

    ifstream file("faculty.txt");
    ofstream temp("temp_fac.txt");
    bool found = false;

    while (file >> fac.id >> fac.f_name >> fac.l_name >> fac.dep){
        if (fac.id == id){
            found = true;
            cout << "Enter New Department: "; cin >> fac.dep;
            cout << "Record Updated." << endl;
        }
        temp << fac.id << " " << fac.f_name << " " << fac.l_name << " " << fac.dep << endl;
    }
    file.close();
    temp.close();
    remove("faculty.txt");
    rename("temp_fac.txt", "faculty.txt");
    
    if(!found) cout << "Faculty not found." << endl;
    pause_screen();
}

void delete_faculty(){
    string id;
    cout << "DELETE FACULTY" << endl;
    cout << "Enter ID to delete: "; cin >> id;

    ifstream file("faculty.txt");
    ofstream temp("temp_fac.txt");
    bool found = false;

    while (file >> fac.id >> fac.f_name >> fac.l_name >> fac.dep){
        if (fac.id == id){
            found = true;
            continue;
        }
        temp << fac.id << " " << fac.f_name << " " << fac.l_name << " " << fac.dep << endl;
    }
    file.close();
    temp.close();
    remove("faculty.txt");
    rename("temp_fac.txt", "faculty.txt");
    
    if(found) cout << "Faculty deleted." << endl;
    else cout << "Not found." << endl;
    pause_screen();
}

void faculty_management(){
    int choice;
    do{
        system("cls");
        cout<<"FACULTY MANAGEMENT"<<endl;
        cout<<"1. Add Faculty"<<endl;
        cout<<"2. View Faculty"<<endl;
        cout<<"3. Update Faculty"<<endl;
        cout<<"4. Delete Faculty"<<endl;
        cout<<"5. Back"<<endl;
        cout<<"Select(1-5): ";
        cin>>choice;
        
        switch(choice) {
            case 1: add_faculty(); break;
            case 2: view_faculty(); break;
            case 3: update_faculty(); break;
            case 4: delete_faculty(); break;
            case 5: break;
            default: cout<<"Invalid Input!"; wait_and_clear(); break;
        }
    } while (choice!=5);
}

// ==========================================
//           COURSE MANAGEMENT
// ==========================================

void add_course(){
    char choice;
    do{
        system("cls");
        cout << "ADD COURSE" << endl;
        cout << "Enter Course Code: "; cin >> course.code;
        cout << "Enter Course Name: "; cin >> course.name;
        cout << "Enter Credit Hours: "; cin >> course.credits;

        ofstream file("courses.txt", ios::app);
        file << course.code << " " << course.name << " " << course.credits << endl;
        file.close();

        cout << "Course added!" << endl;
        cout << "Add another? (y/n): "; cin >> choice;
    } while(choice == 'y' || choice == 'Y');
}

void view_cources(){
    cout << "VIEW COURSES" << endl;
    ifstream file("courses.txt");
    if(!file) { cout << "No courses found." << endl; pause_screen(); return; }
    
    cout << "\n-----------------------------------" << endl;
    cout << "Code\tName\t\tCredits" << endl;
    cout << "-----------------------------------" << endl;
    while (file >> course.code >> course.name >> course.credits){
        cout << course.code << "\t" << course.name << "\t\t" << course.credits << endl;
    }
    file.close();
    pause_screen();
}

void delete_cources(){
    string code;
    cout << "DELETE COURSE" << endl;
    cout << "Enter Course Code: "; cin >> code;
    
    ifstream file("courses.txt");
    ofstream temp("temp_crs.txt");
    bool found = false;

    while (file >> course.code >> course.name >> course.credits){
        if(course.code == code) { found = true; continue; }
        temp << course.code << " " << course.name << " " << course.credits << endl;
    }
    file.close();
    temp.close();
    remove("courses.txt");
    rename("temp_crs.txt", "courses.txt");
    
    if(found) cout << "Course deleted." << endl;
    else cout << "Not found." << endl;
    pause_screen();
}

void enroll_student(){
    string roll, code;
    cout << "ENROLL STUDENT" << endl;
    cout << "Enter Student Roll No: "; cin >> roll;
    cout << "Enter Course Code: "; cin >> code;
    
    ofstream file("enrollments.txt", ios::app);
    file << roll << " " << code << endl;
    file.close();
    
    cout << "Student Enrolled Successfully!" << endl;
    pause_screen();
}

void course_enrollment(){
    int choice;
    do{
        system("cls");
        cout<<"COURSE & ENROLLMENT"<<endl;
        cout<<"1. Add Course"<<endl;
        cout<<"2. View Courses"<<endl;
        cout<<"3. Delete Course"<<endl;
        cout<<"4. Enroll Student"<<endl;
        cout<<"5. Back"<<endl;
        cout<<"Select(1-5): ";
        cin>>choice;
        
        switch(choice) {
            case 1: add_course(); 
			break;
            case 2: view_cources(); 
			break;
            case 3: delete_cources(); 
			break;
            case 4: enroll_student(); 
			break;
            case 5: break;
            default: cout<<"Invalid Input!"; 
			wait_and_clear(); 
			break;
        }
    } while (choice!=5);
}

// ==========================================
//      ATTENDANCE & RESULTS (Placeholders)
// ==========================================
// To fully implement these, you would need relational logic 
// matching student IDs to marks. Here are simple file appends.

void mark_attendance(){
    string roll, status, date;
    cout<<"MARK ATTENDANCE"<<endl;
    cout<<"Enter Roll No: "; 
	cin>>roll;
    cout<<"Enter Date (DD/MM/YY): "; 
	cin>>date;
    cout<<"Status (P/A): "; 
	cin>>status;
    
    ofstream file("attendance.txt", ios::app);
    file<<roll<<" "<<date<<" "<<status<<endl;
    file.close();
    cout<<"Attendance Marked."<<endl;
    pause_screen();
}

void enter_marks() {
    string roll, subject;
    int marks;
    cout<<"ENTER MARKS"<<endl;
    cout<<"Enter Roll No: "; 
	cin>>roll;
    cout<<"Enter Subject: "; 
	cin>>subject;

    // input validation for marks
    while (true) {
        cout<<"Enter Marks: ";
        cin>>marks;

        if (cin.fail()) {
            cin.clear();  // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
            cout<<"Invalid input! Please enter a valid number for marks."<<endl;
        } else if (marks<0 || marks>100) {
            cout<<"Invalid marks! Please enter a value between 0 and 100."<<endl;
        } else {
            break;  // valid input, exit the loop
        }
    }

    ofstream file("marks.txt", ios::app);
    file<<roll<<" "<<subject<< " "<<marks<<endl;
    file.close();
    cout<<"Marks Uploaded."<<endl;
    pause_screen();
}
void view_attendance_report() {
    cout << "VIEW ATTENDANCE REPORT" << endl;
    string roll;
    
    cout << "Enter Roll Number to view attendance: ";
    cin >> roll;
    
    ifstream file("attendance.txt");
    if (!file) {
        cout << "No attendance data found." << endl;
        pause_screen();
        return;
    }
    
    bool found = false;
    cout << "\nAttendance Report for Roll No: " << roll << endl;
    cout << "Date\t\tStatus" << endl;
    cout << "------------------------"<<endl;
    
    while (file >> student.roll_no >> student.f_name >> student.l_name >> roll >> student.f_name >> student.l_name) {
        if (student.roll_no == roll) {
            found = true;
            cout << roll << "\t\t" << student.f_name << " " << student.l_name << endl;
        }
    }

    if (!found) {
        cout << "No attendance found for this roll number." << endl;
    }
    
    file.close();
    pause_screen();
}
void view_marks_report() {
    cout << "VIEW MARKS REPORT" << endl;
    string roll;
    
    cout << "Enter Roll Number to view marks: ";
    cin >> roll;
    
    ifstream file("marks.txt");
    if (!file) {
        cout << "No marks data found." << endl;
        pause_screen();
        return;
    }
    
    bool found = false;
    cout<<"\nMarks Report for Roll No: "<<roll<<endl;
    cout<<"Subject\tMarks"<<endl;
    cout<<"-------------------"<<endl;
    
    string subject;
    int marks;
    
    while (file>>student.roll_no>>subject>>marks) {
        if (student.roll_no == roll) {
            found = true;
            cout << subject << "\t"<< marks<<endl;
        }
    }

    if (!found) {
        cout<<"No marks found for this roll number."<<endl;
    }
    
    file.close();
    pause_screen();
}

void attendance_results(){
    int choice;
    do{
        system("cls");
        cout<<"ATTENDANCE & RESULTS"<<endl;
        cout<<"1. Mark Attendance"<<endl;
        cout<<"2. Enter Marks"<<endl;
        cout<<"3. View Attendace Report"<<endl;
        cout<<"4. View Marks Report"<<endl;
        cout<<"5. BACK"<<endl;
        cout<<"Select(1-5): ";
        cin>>choice;
        switch(choice){
            case 1: mark_attendance(); 
			break;
            case 2: enter_marks(); 
			break;
            case 3: view_attendance_report();
            break;
            case 4: view_marks_report(); 
			break;  
            case 5: break;
            default: cout<<"Invalid Input"; 
			wait_and_clear();
        }
    } while(choice!=3);
}



// ==========================================
//           FEE MANAGEMENT
// ==========================================

void fee_management() {
    int choice;
    string roll;
    int amount;
    do {
        system("cls");
        cout<<"FEE MANAGEMENT"<<endl;
        cout<<"1. Add Fee Record"<<endl;
        cout<<"2. Back"<<endl;
        cin>>choice;

        if (choice==1) {
            cout<<"Enter Roll No: "; 
			cin>>roll;

            // input validation for fee amount
            while (true) {
                cout<<"Enter Fee Amount: ";
                cin>>amount;

                if (cin.fail()) {
                    cin.clear();  // clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
                    cout<<"Invalid input! Please enter a valid number for fee amount."<<endl;
                } else if (amount<0) {
                    cout<<"Invalid amount! Fee cannot be negative." << endl;
                } else {
                    break;  // valid input and exit the loop
                }
            }

            ofstream file("fees.txt", ios::app);
            file<<roll<<" "<<amount<<" Unpaid"<<endl;
            file.close();
            cout<<"Fee Record Added."<<endl;
            pause_screen();
        }

    } while (choice!=2);
}

// ==========================================
//           MAIN SYSTEM
// ==========================================

void admin_portal() {
    int choice;
    do{
        system("cls");
        cout<<"ADMIN PORTAL"<<endl;
        cout<<"1. Student Management"<<endl;
        cout<<"2. Faculty Management"<<endl;
        cout<<"3. Course & Enrollment"<<endl;
        cout<<"4. Attendance & Results"<<endl;
        cout<<"5. Fees Management"<<endl;
        cout<<"6. Exit "<<endl;
        cout<<"Select(1-6): ";
        cin>>choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.";
            wait_and_clear();
            continue;
        }

        switch(choice) {
            case 1: student_management(); 
			break;
            case 2: faculty_management(); 
			break;
            case 3: course_enrollment(); 
			break;
            case 4: attendance_results(); 
			break;
            case 5: fee_management(); 
			break;
            case 6: cout<<"\nGOOD BYE!"<<endl; 
			break;
            default: cout<<"\nInvalid Input!"; wait_and_clear(); 
			break;
        }
    } while(choice!=6);
}

void typewriterEffect(const string &text, int delay) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

int main(){
    string title="WELCOME TO UNIVERSITY MANAGEMENT SYSTEM";
    string w = "WELCOME !\n";
    
    // Intro Effect
    typewriterEffect(title, 50);
    cout << endl << "Loading";
    for (int i = 0; i < 4; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    
    system("cls");
    typewriterEffect(w, 50);
    
    string id, pass;
    bool loggedin = false;
    
    do{
        cout << "\n=== LOGIN ===";
        cout << "\nEnter ID: "; 
		cin >> id;
        cout << "Enter Password: "; 
		cin >> pass;
        
        if(checklogin(id, pass)) {
            cout << "\nLogin successful...";
            this_thread::sleep_for(chrono::seconds(1));
            loggedin = true;
            admin_portal();
        } else {
            cout << "\nInvalid ID or password. Try again." << endl;
            wait_and_clear(2);
        }
    } while(!loggedin);
    
    return 0;
}