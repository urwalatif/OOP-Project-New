#pragma once
#include <iostream>
#include<string>

using namespace std;
class Admin {
	string userNameAdmin, passwordAdmin;
	string choice; //members

public:
	Admin(); //nulling mmebers
	static bool flagForAdmin;
	virtual void signInPage(); //sign in
	//admin module functions
	virtual void addTeacher();  //polymorphism(virtual function) plus inheritance
	virtual void addStudentByAdmin(); //polymorphism(virtual function) plusinheritance
	virtual void editTeacherDetails();
	virtual void editStudentDetails();
	virtual void viewTeacherDetails();
	virtual void viewStudentDetails();
	//teacher module functions
	virtual void timeTableTeacher();
	virtual void coursesToTeach();
	virtual void markAttendance();
	virtual void assignMarks();
	virtual void assignGrade();
	//student module functions
	virtual void studentRegisterCourses();
	virtual void viewRegisteredCourses();
	virtual void viewFeeStatus();
	virtual void viewAttendance();
	virtual void viewMarks();
	virtual void viewGrades();

};
