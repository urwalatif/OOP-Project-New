#include"adminn.h"
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
void sound();
bool sigInFlag = 0;
void images(string address) //parameter having address or name of image 
{
	RenderWindow window(VideoMode(1380, 768), "FLEX MANAGEMENT SYSTEM");
	Text text;
	Image image;
	if (!(image.loadFromFile(address)))
		cout << "Cannot load image";   //Load Image
	Texture texture;
	texture.loadFromImage(image);  //Load Texture from image
	Sprite sprite;
	sprite.setTexture(texture);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}//Event handling done
		for (int i = 0; i < 300; i++)
			for (int j = 0; j < 300; j++)
				image.setPixel(i, j, Color::Black);
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
void CoursesRegistration(string tempReadDept, ofstream& file, string id);
//handlers of teachers
//for data of teacher
ofstream addTeacherRecord; //simple is for writing
ifstream addTeacherRecordRead;//name having read is for reading os same file
//view teacher details
ifstream viewTeacherRecords;
// for different ids of teacher
ifstream teacherIDRead;
ofstream teacherIDWrite;
//counter of teachers or number of teachers
ofstream teachersRegisteredwrite;
ifstream teachersRegisteredRead;
// for assigning grades
ofstream gradesAssigning;
//variables for counter teacher and id of teacher
int teacherCount = 0;
int teacherID = 1000;
//registartion of teachers courses
ofstream teacherCourses;
ifstream teacherCoursesRead;
//usernames and passwords of teachers
ofstream teacherUserNameAndPassword;
ifstream teacherUserNameAndPasswordRead;
string copyIdTeacher; //storing username of teacher at time of login
//signIn check variables

bool sigInFlagTeacher = 0;
void subjectDuplication(string arr[6], int countSub[6], string subject, int& i); //to check if student or teacher will register same subject twice 
ofstream markAssigning; //for assigning marks(by teacher)
//handlers of students
ifstream marksAssigningRead;
ifstream gradesAssigningRead;
string copyIdStudent;
ofstream attendanceOfStudent;
ifstream attendanceOfStudentRead;
ofstream registerCourses;
ifstream registerCoursesRead;
int studentID = 1000;
ifstream studentIDRead;
ofstream studentIDwrite;
ofstream addStudentRecord;
ifstream addStudentRecordRead;
ifstream viewStudentRecord;
ifstream studentRegisteredRead;
ofstream studentRegisteredWrite;
int studentCount = 0;

//for students credentials
ofstream studentUserNameAndPassword;
ifstream studentUserNameAndPasswordRead;
bool marksDuplicationCheck(string selectCourse, string idOfStudent) //for not letting a teacher to mark same subject twice
{
	string marksId, marksSubject, marksNumbers; //reading pattern as file contains three entites of student marks
	bool flagMarks = 0;
	marksAssigningRead.open("studentMarks.txt");
	while (!marksAssigningRead.eof())
	{
		getline(marksAssigningRead, marksId);
		getline(marksAssigningRead, marksSubject);
		getline(marksAssigningRead, marksNumbers);
		if (selectCourse == marksSubject && idOfStudent == marksId) //for preventing the double marking
		{
			cout << "already marked now" << endl;
			sound();
			flagMarks = 1;
			break;
		}
	}
	marksAssigningRead.close();
	return flagMarks;
}
void sound() //error sound playing
{
	SoundBuffer buffer;
	if (buffer.loadFromFile("beep-01a.wav")) {
	}
	sf::Sound start;				//error sound
	start.setBuffer(buffer);
	start.play();
	system("pause");

}
void DepartmentCheck() //to match depts of teacher and student
{
	string idOfStudent, toGetDept, toGetID;
	addStudentRecordRead.open("studentRecords.txt");
	addTeacherRecordRead.open("teacherRecords.txt");
	bool flagStudent = 0;
	while (1) //for valid id for marks
	{
		system("cls");
		cout << "enter the id of student yu want to assign marks" << endl;
		getline(cin, idOfStudent);
		while (!addStudentRecordRead.eof())//read data till end
		{
			getline(addStudentRecordRead, toGetDept);
			getline(addStudentRecordRead, toGetID);
			if (idOfStudent == toGetID)
			{
				addStudentRecordRead.close();
				flagStudent = 1;
				break;
			}
			else
				if (addStudentRecordRead.eof())
				{
					cout << "id of student does not match our records" << endl;
					sound();
					addStudentRecordRead.close();
					addTeacherRecordRead.close();
					return;
				}

		}
		if (flagStudent)
			break;

	}
	string teacherRead1, teacherReadDept;
	while (!addTeacherRecordRead.eof()) //read data till end from teacher
	{
		for (int i = 0; i < 6; i++)
		{
			if (i < 5)
			{
				getline(addTeacherRecordRead, teacherRead1);
				getline(addTeacherRecordRead, teacherReadDept);
			}
			else
				getline(addTeacherRecordRead, teacherRead1);
		}
		if (teacherRead1 == copyIdTeacher)
		{
			addTeacherRecordRead.close();
			break;
		}
	}

	if (teacherReadDept != toGetDept)
	{
		addTeacherRecordRead.close();
		addStudentRecordRead.close();
		cout << "your department is not same,enter another id for student" << endl;
		sound();

		return;
	}
	if (teacherReadDept == toGetDept)
	{
		markAssigning.open("studentMarks.txt", ios::app);
	}
}
void closeFiles()//closing files
{
	addStudentRecordRead.close();
	teacherCoursesRead.close();
	registerCoursesRead.close();
	attendanceOfStudent.close();
	addTeacherRecordRead.close();
	markAssigning.close();
}
void mainMenu() //main menu
{
	system("cls");
	cout << "press 1 for admin module" << endl;
	cout << "press 2 for teacher module" << endl;
	cout << "press 3 for student module" << endl;
	cout << "press 4 for quit" << endl;
	cout << "enter your choice" << endl;

}
void menuAdmin() //admin menu
{
	system("cls");
	cout << "press 1 for adding new teacher" << endl;
	cout << "press 2 for adding new student" << endl;
	cout << "press 3 for edit teacher details" << endl;
	cout << "press 4 for edit students details" << endl;
	cout << "press 5 for viewing teahcers" << endl;
	cout << "press 6 for viewing students" << endl;
	cout << "press 7 for quiting from this module" << endl;
}
void menuTeacher() //menu teacher
{
	system("cls");
	cout << "press 1 for your courses to teach" << endl;
	cout << "press 2 for marking attendance" << endl;
	cout << "press 3 for timeTable" << endl;
	cout << "press 4 for assigning marks" << endl;
	cout << "press 5 for assigning grades" << endl;
	cout << "press 6 for quiting" << endl;
	cout << "enter your choice" << endl;
}
void menuStudent() //menu student
{
	system("cls");
	cout << "press 1 for registration of courses" << endl;
	cout << "press 2 for view registartion of courses" << endl;
	cout << "press 3 for view your fee status" << endl;
	cout << "press 4 for viiew attendance" << endl;
	cout << "press 5 for view marks" << endl;
	cout << "press 6 for view grades" << endl;
	cout << "press 7 for quitting from this module" << endl;
}
void subjectDuplication(string arr[6], int countSub[6], string subject, int& x) //to check a student should not register a course twice
{
	for (int i = 0; i < 6; i++) //checking through courses array
	{
		for (int j = 0; j < 6; j++)
		{
			if (arr[j] == subject && countSub[j] == 0)
			{
				registerCourses << arr[j] << endl;
				countSub[j]++;
				x++;
				return;
			}
			if (arr[i] == subject)
			{
				cout << "you have already registered this course" << endl;
				sound();
				return;
			}
		}
		{
			cout << "enter course from above or already done" << endl;
			sound();
			return;
		}

	}
}
void CoursesRegistration(string tempReadDept, ofstream& file, string id) //registration of courses
{
	string courseToBeRegister;
	int numberOfCourses = 4;

	if (tempReadDept == "business" || tempReadDept == "Business") ///for business courses
	{
		int countSubjects[6] = { 0 };
		string subjects[6] = { "marketing","business","islamiat","critical business skills","accounting","pak studies" };
		system("cls");
		cout << "chose your courses 4 from below" << endl;
		for (int j = 0; j < 6; j++)
		{
			cout << "-> " << subjects[j] << endl;
		}
		file << id << endl;
		for (int i = 0; i < numberOfCourses;)
		{
			cout << "enter your " << i + 1 << " subject" << endl;
			getline(cin, courseToBeRegister);
			subjectDuplication(subjects, countSubjects, courseToBeRegister, i);
			if (id[0] != '2')
				file << courseToBeRegister << endl;
		}
		cout << "registration of courses done" << endl;
		system("pause");
	}
	else

		if (tempReadDept == "computer science" || tempReadDept == "Computer science" || tempReadDept == "software engineering" || tempReadDept == "Software engineering") //for cs and se deots
		{
			int countSubjects[6] = { 0 };
			string subjects[6] = { "physics","pf","LA","islamiat","op","calculus" };
			system("cls");
			cout << "chose your 4 courses from below" << endl;
			for (int j = 0; j < 6; j++)
			{
				cout << "-> " << subjects[j] << endl;
			}
			file << id << endl;
			for (int i = 0; i < numberOfCourses;)
			{
				cout << "enter your " << i + 1 << " subject" << endl;
				getline(cin, courseToBeRegister);
				subjectDuplication(subjects, countSubjects, courseToBeRegister, i);
				if (id[0] != '2')
					file << courseToBeRegister << endl;
			}
			cout << "registration of courses done" << endl;
			system("pause");
		}
		else
			if (tempReadDept == "electrical engineering" || tempReadDept == "Electrical engineering")//for ee det
			{
				system("cls");
				int countSubjects[6] = { 0 };
				string subjects[6] = { "physics","DLD","circuits","magnetism","controls","transmission" };
				cout << "chose your 4 courses from below" << endl;
				for (int j = 0; j < 6; j++)
					cout << "-> " << subjects[j] << endl;
				file << id << endl;
				for (int i = 0; i < numberOfCourses;)
				{
					cout << "enter your " << i + 1 << " subject" << endl;
					getline(cin, courseToBeRegister);
					subjectDuplication(subjects, countSubjects, courseToBeRegister, i);
					if (id[0] != '2')
						file << courseToBeRegister << endl;
				}
				cout << "registration of courses done" << endl;
				system("pause");
			}
			else
				if (tempReadDept == "social science" || tempReadDept == "Social science")
				{
					int countSubjects[6] = { 0 };
					string subjects[6] = { "english","economics","humanities","agriculture","maths","social study" };
					system("cls");
					cout << "chose your 4 courses from below" << endl;
					for (int j = 0; j < 6; j++)
						cout << "-> " << subjects[j] << endl;
					file << id << endl;
					for (int i = 0; i < numberOfCourses;)
					{
						cout << "enter your " << i + 1 << " subject" << endl;
						getline(cin, courseToBeRegister);
						subjectDuplication(subjects, countSubjects, courseToBeRegister, i);
						if (id[0] != '2')
							file << courseToBeRegister << endl;
					}
					cout << "registration of courses done" << endl;
					system("pause");
				}
}
struct teacherDetails //for teacher detials
{
	string firstNameOfTeahcer, secondNameOfTeacher, deptOfTeahcer, idOfTeacher, userNameTeacher, passwordTeacher, registrationTeacher, genderTeacher, qualificationTeacher, addressTeacher;
	string contactTeacher;
};
struct studentDetails { //for student detials
	string studentFirstName, studentSecondName, studentDepartment, studentId, studentGender, studentContact, studentBlood, studentAddress;
	string feeStatus, studentQualification, studentMarks, studentPassword;

};

class addTeacherAndStudentByAdmin : public Admin //add student or teacher class inherited from admin class
{
protected:
	//struct object for students and teachers
	teacherDetails obj;
	studentDetails obj1;
public:
	friend class editDetails; //friend classes
	friend class viewDetails;
	addTeacherAndStudentByAdmin() //constructor
	{
		obj.firstNameOfTeahcer = obj.secondNameOfTeacher = obj.deptOfTeahcer = obj.idOfTeacher = obj.genderTeacher = "";
	}
	void addTeacher()override
	{
		bool checkDate = 0; //exception for date format
		bool checkDayMonth = 0; //validity for month and date
		//all inputs;
		obj.deptOfTeahcer = "";
		cout << "enter the credentials of teahcer\n" << endl;
		cout << "enter first name of teahcer" << endl;
		if (teacherCount > 0) //as user will press enter on the end after adding a teacher in per execution
			cin.ignore();
		getline(cin, obj.firstNameOfTeahcer);
		cout << "enter the second name of teacher" << endl;
		getline(cin, obj.secondNameOfTeacher);
		cout << "enter username of teacher" << endl;
		getline(cin, obj.userNameTeacher);
		cout << "enter password of teacher" << endl;
		getline(cin, obj.passwordTeacher);
		cout << "enter the qualification" << endl;
		getline(cin, obj.qualificationTeacher);
		cout << "enter address of teacher" << endl;
		getline(cin, obj.addressTeacher);
		while (1) //date input till correct
		{
			cout << "enter registration date as dd-mm-yyyy" << endl;
			getline(cin, obj.registrationTeacher);
			if (obj.registrationTeacher.length() > 10) //for format validation
			{
				cout << "invalid date" << endl;
				sound();
				continue;
			}
			else
			{
				for (int i = 0; i < 10; i++) //checing every character as numeric or a dash
				{
					if (obj.registrationTeacher[i] >= 48 && obj.registrationTeacher[i] <= 57 && i != 2 && i != 5) //for numeric and dashes
						checkDate = 1;
					else
						if (i == 2 || i == 5)//for dashes
						{
							if (obj.registrationTeacher[i] == 45)
								checkDate = 1;
						}
						else
						{
							checkDate = 0;
							break;
						}
				}
				if (checkDate)
				{
					for (int i = 0; i == 0; i++) //for single iteration of loop and "i" was required as 0
					{
						switch (obj.registrationTeacher[i]) //for first character of date(day)
						{
						case '0':

						case '1':

						case '2':

							switch (obj.registrationTeacher[i + 3]) //first character of month
							{
							case '0':
								checkDayMonth = 1;
								break;
							case '1':
								if (obj.registrationTeacher[i + 4] == '0' || obj.registrationTeacher[i + 4] == '1' || obj.registrationTeacher[i + 4] == '2')
								{
									checkDayMonth = 1;
								}
								else
								{
									cout << "enter valid month" << endl;
									sound();
									checkDayMonth = 0;
								}
								break;
							}
							break;
						case '3':
							if (obj.registrationTeacher[i + 1] == '0' || obj.registrationTeacher[i + 1] == '1')
							{
								switch (obj.registrationTeacher[i + 3]) //month validation
								{
								case '0':
									checkDayMonth = 1;
									break;
								case '1':
									if (obj.registrationTeacher[i + 4] == '0' || obj.registrationTeacher[i + 4] == '1' || obj.registrationTeacher[i + 4] == '2')
									{
										checkDayMonth = 1;

									}
									else
									{
										cout << "enter valid month" << endl;
										sound();
										checkDayMonth = 0;

									}
									break;

								}
								break;
							}
							else
							{
								cout << "enter valid date" << endl;
								sound();
								checkDayMonth = 0;
								break;
							}
							break;

						}
						if (checkDayMonth)
							break;
					}
					if (checkDayMonth)
						break;
					else
					{
						cout << "enter correct date or month" << endl;
						sound();
					}
				}
				else
				{
					cout << "enter date as given format" << endl;
					sound();
				}
			}
		}
		while (1) //contact input till correct input
		{
			bool checkContact = 0; //exception for contact
			cout << "enter contact number of teacher as 03001234567" << endl;
			getline(cin, obj.contactTeacher);
			if (obj.contactTeacher.length() > 11)//length of contact exceeds
			{
				cout << "enter 11 digit number" << endl;
				sound();
			}
			else
			{
				for (int i = 0; i < 11; i++) //cheking that digit of contact is numeric
				{
					if (obj.contactTeacher[i] >= 48 && obj.contactTeacher[i] <= 57)
						checkContact = 1;
					else
					{
						cout << "enter numeric digits for number" << endl;
						checkContact = 0;
						sound();
						break;
					}
				}
				if (checkContact)
					break;
				else
					continue;
			}
		}
		for (int i = 0; obj.deptOfTeahcer == ""; i++) //deptr exception
		{
			cout << "enter the department of teacher(business,computer science,software engineering, electrical engineering and social science)" << endl;
			getline(cin, obj.deptOfTeahcer);
			if (obj.deptOfTeahcer == "Electrical engineering" || obj.deptOfTeahcer == "electrical engineering" || obj.deptOfTeahcer == "computer science" || obj.deptOfTeahcer == "Computer science" || obj.deptOfTeahcer == "software engineering" || obj.deptOfTeahcer == "Software engineering" || obj.deptOfTeahcer == "Business" || obj.deptOfTeahcer == "business" || obj.deptOfTeahcer == "Social science" || obj.deptOfTeahcer == "social science")
				break;
			else
			{
				cout << "enter department from above" << endl;
				sound();
				obj.deptOfTeahcer = "";
			}
		}
		obj.genderTeacher = "";
		for (int i = 0; obj.genderTeacher == ""; i++) //gender exception
		{
			cout << "enter gender as m/M or f/F" << endl;
			getline(cin, obj.genderTeacher);
			if (obj.genderTeacher == "m" || obj.genderTeacher == "M" || obj.genderTeacher == "F" || obj.genderTeacher == "f")
				break;
			else
			{
				obj.genderTeacher = "";
				sound();
			}
		}

		obj.idOfTeacher = obj.deptOfTeahcer[0]; //first character of deptr
		obj.idOfTeacher = obj.idOfTeacher + obj.deptOfTeahcer[1]; //2nd char of dept
		teacherIDRead.open("teacherIDread.txt"); //to read initial id
		teacherIDWrite.open("teacherIDread.txt");
		if (!teacherIDRead.is_open()) //if not open,it will create file and write 1000
		{
			teacherIDRead.open("teacherIDread.txt");
			teacherIDWrite << teacherID;
			teacherIDWrite.close();
		}
		else
		{
			teacherIDWrite << teacherID;
			teacherIDWrite.close();
			teacherIDRead >> teacherID;
			//getting teacher id from file
			teacherID = teacherID + 1;
		}//adding one(for first student)
		teacherIDRead.close();
		obj.idOfTeacher = obj.idOfTeacher + "-" + to_string(teacherID);//int and string concatenation
		cout << "your id is " << obj.idOfTeacher << endl;
		teacherIDWrite.open("teacherIDread.txt");
		for (; !teacherIDRead.is_open();)
			teacherIDRead.open("teacherIDread.txt"); //if not open,it will create file and write 1000
		teacherIDWrite << teacherID;
		teacherIDWrite.close();
		addTeacherRecord.open("teacherRecords.txt", ios::app);//writing record to file
		for (; !addTeacherRecord.is_open();)
		{
			addStudentRecord.open("teacherRecords.txt", ios::app);//if not open,it will create file
		}

		//writing whole record of student into file
		addTeacherRecord << obj.firstNameOfTeahcer << endl << obj.secondNameOfTeacher << endl << obj.addressTeacher << endl << obj.contactTeacher << endl << obj.userNameTeacher << endl << obj.passwordTeacher << endl;
		addTeacherRecord << obj.qualificationTeacher << endl << obj.registrationTeacher << endl;
		addTeacherRecord << obj.genderTeacher << endl << obj.deptOfTeahcer << endl << obj.idOfTeacher << endl;
		addTeacherRecord.close();
		teachersRegisteredRead.open("teachersCount.txt"); //to count number f teachers
		if (!teachersRegisteredRead.is_open())//if not open,it will create file
		{
			teachersRegisteredwrite.open("teachersCount.txt");
			teachersRegisteredwrite << 1;
		}
		else
		{
			teachersRegisteredRead >> teacherCount; //getting teacher count from file
			teachersRegisteredwrite.open("teachersCount.txt");
			teachersRegisteredwrite << ++teacherCount; //writing new teacher count with increment in same file
		}
		teachersRegisteredwrite.close();
		teachersRegisteredRead.close();
		teacherUserNameAndPassword.open("teacherIdAndPass.txt", ios::app);
		for (; !teacherUserNameAndPassword.is_open();)
			teacherUserNameAndPassword.open("teacherIdAndPass.txt", ios::app);
		teacherUserNameAndPassword << obj.idOfTeacher << endl << obj.passwordTeacher << endl;;
		teacherUserNameAndPassword.close();
		system("pause");
		system("cls");

	}
	void addStudentByAdmin() override
	{
		bool checkMarks = 0; //exception for marks
		cout << "enter the credentials of student\n" << endl;
		cout << "enter first name of student" << endl;
		if (studentCount > 0) //getline error
			cin.ignore();
		getline(cin, obj1.studentFirstName);
		cout << "enter the second name of student" << endl;
		getline(cin, obj1.studentSecondName);
		cout << "enter the qualification of student" << endl;
		getline(cin, obj1.studentQualification);
		cout << "enter address of student" << endl;
		getline(cin, obj1.studentAddress);
		while (1)//exception for contact 
		{
			bool checkContact = 0;
			cout << "enter contact number of student as 03001234567" << endl;
			getline(cin, obj1.studentContact);
			if (obj1.studentContact.length() > 11) //length of contact check
			{
				cout << "enter 11 digit number" << endl;
				sound();
			}
			else
			{
				for (int i = 0; i < 11; i++) //checking every character should be numeric
				{
					if (obj1.studentContact[i] >= 48 && obj1.studentContact[i] <= 57)
						checkContact = 1;
					else
					{
						cout << "enter numeric digits for number" << endl;
						checkContact = 0;
						sound();
						break;

					}
				}
				if (checkContact) //breaking on true inpiut
					break;
				else
					continue;
			}
		}
		cout << "enter blood group" << endl;
		getline(cin, obj1.studentBlood);
		while (1)
		{
			cout << "enter marks in inter" << endl;
			getline(cin, obj1.studentMarks);
			if (obj1.studentMarks.length() > 3) //should not be more than 1000
			{
				cout << "enter marks out of 1000" << endl;
				sound();
				continue;
			}
			else

				for (int i = 0; i < obj1.studentMarks.length(); i++) //marks checking
				{
					if (obj1.studentMarks[i] >= 48 && obj1.studentMarks[i] <= 57)//marks shoudl be numeric
						checkMarks = 1;
					else
					{
						checkMarks = 0;
						break;
					}
				}
			if (checkMarks)
				break;
			else
			{
				cout << "enter marks as integer value" << endl;
				sound();
			}
		}
		cout << "enter password for your id" << endl;
		getline(cin, obj1.studentPassword);
		obj1.studentGender = "";
		for (int i = 0; obj1.studentGender == ""; i++)//gender exception
		{
			cout << "enter gender of student(m/M or f/F)" << endl;
			getline(cin, obj1.studentGender);
			if (obj1.studentGender == "m" || obj1.studentGender == "M" || obj1.studentGender == "F" || obj1.studentGender == "f")//should be m/f
				break;
			else
			{
				cout << "enter gender from above" << endl;
				obj1.studentGender = "";
				sound();
			}
		}
		obj1.feeStatus = "";
		for (int i = 0; obj1.feeStatus == ""; i++) //fee exception handlig
		{
			cout << "enter fee status as p/P for Paid and n/N for non paid" << endl;
			getline(cin, obj1.feeStatus);
			if (obj1.feeStatus == "n" || obj1.feeStatus == "N" || obj1.feeStatus == "p" || obj1.feeStatus == "P") //should be p or n
				break;
			else
			{
				cout << "enter from above" << endl;
				obj1.feeStatus = "";
				sound();
			}
		}
		obj1.studentDepartment = "";
		for (int i = 0; obj1.studentDepartment == ""; i++) //dept exception handling
		{
			cout << "enter the department of student(business,computer science,software engineering, electrical engineering and social science)" << endl;
			getline(cin, obj1.studentDepartment);
			//should b from given depts.
			if (obj1.studentDepartment == "Electrical engineering" || obj1.studentDepartment == "electrical engineering" || obj1.studentDepartment == "computer science" || obj1.studentDepartment == "Computer science" || obj1.studentDepartment == "software engineering" || obj1.studentDepartment == "Software engineering" || obj1.studentDepartment == "Business" || obj1.studentDepartment == "business" || obj1.studentDepartment == "Social science" || obj1.studentDepartment == "social science")
				break;
			else
			{
				cout << "enter department from above" << endl;
				obj1.studentDepartment = "";
				sound();
			}

		}


		studentIDRead.open("studentID.txt");
		studentIDRead >> studentID;//getting student id from file to generate new id
		studentID = studentID + 1;
		studentIDRead.close();
		obj1.studentId = "20F-" + to_string(studentID); //generating new std id
		cout << "your id is " << obj1.studentId << endl;
		studentIDwrite.open("studentID.txt");
		studentIDwrite << studentID; //writig new id to file for getting new id at next execution
		studentIDwrite.close();

		addStudentRecord.open("studentRecords.txt", ios::app);
		for (; !addStudentRecord.is_open();)
		{
			addStudentRecord.open("studentRecords.txt", ios::app);
		}
		//writing whole record of student into a file
		addStudentRecord << obj1.studentFirstName << endl << obj1.studentSecondName << endl << obj1.studentPassword << endl << obj1.studentAddress << endl << obj1.studentContact << endl << obj1.studentGender << endl << obj1.studentBlood << endl;
		addStudentRecord << obj1.studentQualification << endl << obj1.studentMarks << endl;
		addStudentRecord << obj1.feeStatus << endl << obj1.studentDepartment << endl << obj1.studentId << endl;
		addStudentRecord.close();
		studentRegisteredRead.open("studentCount.txt");
		if (!studentRegisteredRead.is_open())
		{
			studentRegisteredWrite.open("studentCount.txt");
			studentRegisteredWrite << 1;
		}
		else
		{
			studentRegisteredRead >> studentCount; //getting number of students from file
			studentRegisteredWrite.open("studentCount.txt");
			studentRegisteredWrite << ++studentCount; //writing number of students to file again with increment
		}
		studentRegisteredWrite.close();
		studentRegisteredRead.close();
		studentUserNameAndPassword.open("studentUserNameAndPass.txt", ios::app);
		if (!studentUserNameAndPassword.is_open())
			studentUserNameAndPassword.open("studentUserNameAndPass.txt", ios::app);
		studentUserNameAndPassword << obj1.studentId << endl << obj1.studentPassword << endl; //writing std credentials to file
		studentUserNameAndPassword.close();
		system("pause");
		system("cls");
	}

};

class viewDetails :public Admin {
	string readingData;
public:
	void viewTeacherDetails()override
	{
		viewTeacherRecords.open("teacherRecords.txt");
		if (!viewTeacherRecords.is_open())
			viewTeacherRecords.open("teacherRecords.txt");
		int i = 0;
		readingData = "";
		int count = 1;
		while (!viewTeacherRecords.eof()) //till end of file to show data of every teacher
		{
			cout << "Data of teacher " << count << " is :" << endl;
			for (i = 0; i < 11; i++)
				if (!viewTeacherRecords.eof())
				{
					getline(viewTeacherRecords, readingData);
					if (i == 0 && readingData == "") //if file is empty
					{
						cout << "data not entered yet" << endl;
						sound();
						break;
					}
					else
					{
						switch (i) //for displaying the attribute as followed by pattern
						{
						case 0:
							cout << "     firstName=";
							break;
						case 1:
							cout << "     secondName=";
							break;
						case 2:
							cout << "     address=";
							break;
						case 3:
							cout << "     contact=";
							break;
						case 4:
							cout << "     username=";
							break;
						case 5:
							cout << "     password=";
							break;
						case 6:
							cout << "     qualification=";
							break;
						case 7:
							cout << "     registartion date=";
							break;
						case 8:
							cout << "     gender=";
							break;
						case 9:
							cout << "     department=";
							break;
						case 10:
							cout << "     id of teacher=";
							count++;
							break;
						default:
							break;
						}

						cout << readingData << endl;
					}
				}
			if (i == 0)
				break;
		}
		viewTeacherRecords.close();
		system("pause");
	}
	void viewStudentDetails() override
	{
		viewStudentRecord.open("studentRecords.txt");
		if (!viewStudentRecord.is_open())
			viewStudentRecord.open("studentRecords.txt");
		int i = 0;
		readingData = "";
		int count = 1;
		while (!viewStudentRecord.eof()) //show data of every students
		{
			cout << "data of student " << count << endl;
			for (i = 0; i < 12; i++) //all attriubutes of students
				if (!viewStudentRecord.eof())
				{
					getline(viewStudentRecord, readingData);
					if (i == 0 && readingData == "") //if file empty then show error
					{
						cout << "no data of student" << endl;
						sound();
						break;
					}
					else
					{
						switch (i) //displaying on basis of number of line at file
						{
						case 0:
							cout << "    firstName=";
							break;
						case 1:
							cout << "    secondName=";
							break;
						case 2:
							cout << "    password=";
							break;
						case 3:
							cout << "    address=";
							break;
						case 4:
							cout << "    contact=";
							break;
						case 5:
							cout << "    gender=";
							break;
						case 6:
							cout << "    blood=";
							break;
						case 7:
							cout << "    qualification=";
							break;
						case 8:
							cout << "    marks in inter=";
							break;
						case 9:
							cout << "    fee status=";
							break;
						case 10:
							cout << "    department=";
							break;
						case 11:
							cout << "    id of student=";
							count++;
							break;
						default:
							break;
						}
						cout << readingData << endl;
					}
				}
			if (i == 0)
				break;
		}
		viewStudentRecord.close();
		system("pause");
	}
};
class editDetails :public Admin {
	string storeReading;
public:
	editDetails() {}
	void editTeacherDetails()override
	{
		string choiceToUpdateTeacher;
		addTeacherRecordRead.open("teacherRecords.txt");
		teachersRegisteredRead.open("teachersCount.txt");
		if (!teachersRegisteredRead.is_open()) //to get number of teachers registered
		{
			teachersRegisteredwrite.open("teachersCount.txt");
			teachersRegisteredwrite << 1;
		}
		else
		{
			teachersRegisteredRead >> teacherCount;
			teachersRegisteredwrite.close();
			teachersRegisteredRead.close();
		}
		addTeacherAndStudentByAdmin* dataOfTeachers = new addTeacherAndStudentByAdmin[teacherCount];//array for storing data of teachers upto nmber of tchrs
		for (int i = 0; i < teacherCount; i++) //getting alll attributes of teacher in one iteration
		{

			getline(addTeacherRecordRead, storeReading);
			if (i == 0 && storeReading == "") //empty file
			{
				cout << "you have not entered any teacher data" << endl;
				sound();
				break;
			}
			dataOfTeachers[i].obj.firstNameOfTeahcer = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.secondNameOfTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.addressTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.contactTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.userNameTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.passwordTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.qualificationTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.registrationTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.genderTeacher = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.deptOfTeahcer = storeReading;
			getline(addTeacherRecordRead, storeReading);
			dataOfTeachers[i].obj.idOfTeacher = storeReading;
		}
		addTeacherRecordRead.close();
		int i = 0;
		while (1) //updating records
		{
			string updateOrNot;
			cout << "press 7 for updating teacher record\npress 8 to quit from record updating of teacher record" << endl;
			getline(cin, updateOrNot);
			if (updateOrNot == "8")
				break;
			else
				if (updateOrNot == "7")
				{
					if (storeReading == "")
					{
						cout << "you have not entered any teachers data" << endl;
						sound();

						break;
					}
					string  idOfTeacherToSearch;
					cout << "enter id of teacher to search" << endl;
					getline(cin, idOfTeacherToSearch);
					for (i; i < teacherCount;)
					{
						if (idOfTeacherToSearch == dataOfTeachers[i].obj.idOfTeacher)
						{
							break;
						}
						else
							if (i != teacherCount - 1)//i is not at last iteration
							{
								i++;
							}
							else
								if (i == teacherCount - 1) //traveled through file and did not find id
								{
									sound();
									cout << "enter the id of teacher you want to edit details again because that does not match our record" << endl;
									getline(cin, idOfTeacherToSearch);
									i = 0;
								}
					}
					while (1) //edit menu
					{
						system("cls");
						cout << "press 1 to edit contact of teacher\npress 2 for editing address of teacher\npress 3 for editing qualification of teacher\npress 4 for quiting from edit of teacher\n";
						getline(cin, choiceToUpdateTeacher);
						if (choiceToUpdateTeacher == "1")
						{
							cout << "enter new contact of teacher\n";
							getline(cin, dataOfTeachers[i].obj.contactTeacher);
							cout << "contact of teacher updated now\n";
							system("pause");
						}
						else
							if (choiceToUpdateTeacher == "2")
							{
								cout << "enter new address of teacher\n";
								getline(cin, dataOfTeachers[i].obj.addressTeacher);
								cout << "address of teacher updated now\n";
								system("pause");
							}
							else
								if (choiceToUpdateTeacher == "3")
								{
									cout << "enter new qualification of teacher\n";
									getline(cin, dataOfTeachers[i].obj.qualificationTeacher);
									cout << "qualification of teacher updated now\n";
									system("pause");
								}
								else
									if (choiceToUpdateTeacher == "4")
									{
										cout << "you are quiting from teacher editing" << endl;
										break;
									}
									else
									{
										cout << "enter valid choice" << endl; sound();

									}
					}
				}
				else
				{
					cout << "enter valid choice" << endl;
					sound();

				}
			addTeacherRecord.open("teacherRecords.txt");
			addTeacherRecord.close();
			addTeacherRecord.open("teacherRecords.txt");
			if (storeReading != "") //writing whole data after editing
				for (int i = 0; i < teacherCount; i++)
				{
					addTeacherRecord << dataOfTeachers[i].obj.firstNameOfTeahcer << endl << dataOfTeachers[i].obj.secondNameOfTeacher << endl << dataOfTeachers[i].obj.addressTeacher << endl << dataOfTeachers[i].obj.contactTeacher << endl << dataOfTeachers[i].obj.userNameTeacher << endl << dataOfTeachers[i].obj.passwordTeacher << endl;
					addTeacherRecord << dataOfTeachers[i].obj.qualificationTeacher << endl << dataOfTeachers[i].obj.registrationTeacher << endl;
					addTeacherRecord << dataOfTeachers[i].obj.genderTeacher << endl << dataOfTeachers[i].obj.deptOfTeahcer << endl << dataOfTeachers[i].obj.idOfTeacher << endl;
				}
			addTeacherRecord.close();
		}

	}
	void editStudentDetails()override
	{
		string choiceToUpdateStudent;
		addStudentRecordRead.open("studentRecords.txt");

		studentRegisteredRead.open("studentCount.txt");
		if (!studentRegisteredRead.is_open()) //getting number of student
		{
			studentRegisteredWrite.open("studentCount.txt");
			studentRegisteredWrite << 1;
		}
		else
		{
			studentRegisteredRead >> studentCount;
			studentRegisteredWrite.close();
			studentRegisteredRead.close();
		}
		addTeacherAndStudentByAdmin* dataOfStudents = new addTeacherAndStudentByAdmin[studentCount];//array of total students
		for (int i = 0; i < studentCount && !addStudentRecord.eof(); i++) //whole data readimg
		{
			getline(addStudentRecordRead, storeReading);
			if (storeReading == "")//empty file
			{
				cout << "you have not entered any data of student" << endl;
				sound();

				break;
			}
			dataOfStudents[i].obj1.studentFirstName = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentSecondName = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentPassword = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentAddress = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentContact = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentGender = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentBlood = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentQualification = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentMarks = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.feeStatus = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentDepartment = storeReading;
			getline(addStudentRecordRead, storeReading);
			dataOfStudents[i].obj1.studentId = storeReading;
		}
		addStudentRecordRead.close();
		int i = 0;
		while (1) //menu for editing
		{
			string mainChoiceUpdateOrNot;
			cout << "press 7 to update another record of student\npress 8 to quit from record updating\n";
			getline(cin, mainChoiceUpdateOrNot);
			if (mainChoiceUpdateOrNot == "8")
				break;
			else
				if (mainChoiceUpdateOrNot == "7")
				{
					if (storeReading == "")
					{
						cout << "you have not entered any data of student" << endl;
						sound();

						break;
					}
					string idOfStudentToSearch;
					cout << "enter the id of student you want to edit details" << endl;
					getline(cin, idOfStudentToSearch);
					for (i; i < studentCount;)
					{
						if (idOfStudentToSearch == dataOfStudents[i].obj1.studentId)
						{
							break;
						}
						else
						{
							if (i != studentCount - 1)//last iteration
								i++;
							else

								if (i == studentCount - 1)//invalid id
								{
									sound();
									cout << "enter the id of student you want to edit details again because that does not match our record" << endl;
									getline(cin, idOfStudentToSearch);
									i = 0;
									continue;
								}
						}
					}

					while (1) //edit menu
					{
						system("cls");
						cout << "you can edit first name second name,contact, fee status,address" << endl;
						cout << "press 1 to edit first name\npress 2 for second name\npress 3 for fee status\npress 4 for address\npress 5 for contact\npress 6 to quit\n";
						getline(cin, choiceToUpdateStudent);
						if (choiceToUpdateStudent == "1")
						{
							cout << "\nEnter new first name" << endl;
							getline(cin, dataOfStudents[i].obj1.studentFirstName);
							cout << "first name updated successfully" << endl;
							system("pause");
						}
						else
							if (choiceToUpdateStudent == "2")
							{
								cout << "enter new second name" << endl;
								getline(cin, dataOfStudents[i].obj1.studentSecondName);
								cout << "second name updated successfully\n";
								system("pause");
							}
							else
								if (choiceToUpdateStudent == "3")
								{
									dataOfStudents[i].obj1.feeStatus = "";
									for (; dataOfStudents[i].obj1.feeStatus == "";)
									{
										cout << "enter new fee status p/P for paid or n/N for non paid" << endl;
										getline(cin, dataOfStudents[i].obj1.feeStatus);
										if (dataOfStudents[i].obj1.feeStatus == "n" || dataOfStudents[i].obj1.feeStatus == "N" || dataOfStudents[i].obj1.feeStatus == "p" || dataOfStudents[i].obj1.feeStatus == "P")
										{
											cout << "fee updated successfully\n";
											system("pause");
											break;
										}
										else

										{
											dataOfStudents[i].obj1.feeStatus = "";
											sound();
										}
									}
								}
								else
									if (choiceToUpdateStudent == "4")
									{
										cout << "enter new address\n";
										getline(cin, dataOfStudents[i].obj1.studentAddress);
										cout << "address updated successfully" << endl;
										system("pause");
									}
									else
										if (choiceToUpdateStudent == "5")
										{
											cout << "enter new contact number" << endl;
											getline(cin, dataOfStudents[i].obj1.studentContact);
											cout << "contact updated successfully" << endl;
											system("pause");
										}
										else
											if (choiceToUpdateStudent == "6")
											{
												cout << "you are quitting from update record if student" << endl;
												system("pause");
												break;
											}
											else
											{
												cout << "enter valid choice from edit details" << endl;
												sound();

											}

					}
				}
				else
				{
					cout << "enter valid choice please 7 or 8" << endl;
					sound();

					continue;
				}
			addStudentRecord.open("studentRecords.txt");
			addStudentRecord.close();
			addStudentRecord.open("studentRecords.txt");
			if (storeReading != "")//writing to file whole data
				for (int i = 0; i < studentCount; i++)
				{
					addStudentRecord << dataOfStudents[i].obj1.studentFirstName << endl << dataOfStudents[i].obj1.studentSecondName << endl << dataOfStudents[i].obj1.studentPassword << endl << dataOfStudents[i].obj1.studentAddress << endl << dataOfStudents[i].obj1.studentContact << endl << dataOfStudents[i].obj1.studentGender << endl << dataOfStudents[i].obj1.studentBlood << endl;
					addStudentRecord << dataOfStudents[i].obj1.studentQualification << endl << dataOfStudents[i].obj1.studentMarks << endl;
					addStudentRecord << dataOfStudents[i].obj1.feeStatus << endl << dataOfStudents[i].obj1.studentDepartment << endl << dataOfStudents[i].obj1.studentId << endl;
				}
			addStudentRecord.close();
		}
	}
};
class student : public Admin {
	string userNameStudent, passwordStudent;
public:
	void viewGrades()override //view grades
	{
		string matchId, tempRead;
		int countGrades = 0;
		gradesAssigningRead.open("studentGrades.txt");
		while (!gradesAssigningRead.eof())
		{
			getline(gradesAssigningRead, matchId); //getting id of student matched with login credentials
			if (matchId == copyIdStudent)
			{
				cout << "============your grades are below===============" << endl;
				cout << "id=" << matchId << endl;
				for (int i = 0; i < 3; i++)
				{
					getline(gradesAssigningRead, tempRead);
					cout << tempRead << endl;
				}
				countGrades++; //0 means no grade assigned
			}
			if (gradesAssigningRead.eof() && countGrades == 0)//if no grades are assigned ofr thi student
			{
				cout << "no marks entered by teacher" << endl;
				sound();
			}
		}
		gradesAssigningRead.close();
	}
	void signInPage()override {
		string readUserNameStudent, readPasswordStudent;
		bool flag = 0;
		userNameStudent = passwordStudent = "";
		sigInFlag = 0;
		while (1)
		{
			studentUserNameAndPasswordRead.open("studentUserNameAndPass.txt");

			cout << "enter your student id" << endl;
			getline(cin, userNameStudent);
			copyIdStudent = userNameStudent;
			cout << "enter your password" << endl;
			getline(cin, passwordStudent);
			while (!studentUserNameAndPasswordRead.eof()) //signIn credentials match
			{
				readPasswordStudent = readUserNameStudent = "";
				getline(studentUserNameAndPasswordRead, readUserNameStudent);
				getline(studentUserNameAndPasswordRead, readPasswordStudent);
				if (readPasswordStudent == "" || readUserNameStudent == "") //invalid credentials
				{
					cout << "admin has not entered any data of this student, no record found" << endl;
					sigInFlag = 1;
					sound();

					break;
				}

				if (userNameStudent == readUserNameStudent && passwordStudent == readPasswordStudent)
				{
					flag = 1;
					sigInFlag = 0;
					studentUserNameAndPasswordRead.close();
					break;
				}

			}
			if (sigInFlag)
				break;
			if (flag)
			{
				flag = 0;
				break;
			}
			studentUserNameAndPasswordRead.close();
			continue;

		}
		studentUserNameAndPasswordRead.close();
	}
	void studentRegisterCourses()override
	{
		addStudentRecordRead.open("studentRecords.txt");
		studentRegisteredRead.open("studentCount.txt");
		registerCourses.open("studentRegisterCourses.txt", ios::app);
		int studentCountTemp;
		studentRegisteredRead >> studentCountTemp; //getting number of students

		string tempReadId = "", tempReadDept = "", tempReadingData;
		bool flag = 0;
		for (int i = 0; i < studentCountTemp; i++) //for reading whole file of courses
		{

			for (int j = 0; j < 6 * studentCountTemp; j++) //for reading every line of file
			{

				getline(addStudentRecordRead, tempReadDept);
				getline(addStudentRecordRead, tempReadId);

				if (tempReadId == copyIdStudent)//match id
				{
					flag = 1;
					break;
					addStudentRecord.close();
				}
			}
			if (flag)
				break;
			studentRegisteredRead.close();
		}
		CoursesRegistration(tempReadDept, registerCourses, tempReadId); //registring courses by student
		registerCourses.close();
		studentRegisteredRead.close();
	}
	void viewRegisteredCourses()override
	{

		registerCoursesRead.open("studentRegisterCourses.txt");
		string tempReading;
		studentRegisteredRead.open("studentCount.txt");
		int studentCountTemp;
		studentRegisteredRead >> studentCountTemp;
		for (int i = 0; !registerCoursesRead.eof(); i++) //reading this file till end to get desired id student's courses
		{
			getline(registerCoursesRead, tempReading);
			if (tempReading == "") //file is empty
			{
				cout << "no student register any course" << endl;
				sound();

				break;
			}
			if (tempReading == copyIdStudent) //on same id it will display next four lines of courses
			{
				for (int j = 0; j < 4; j++)
				{
					cout << "you registered course number " << j + 1 << endl;
					getline(registerCoursesRead, tempReading);
					cout << tempReading << endl;
				}
				system("pause");
				break;
			}
		}
		registerCoursesRead.close();
		studentRegisteredRead.close();

	}
	void viewFeeStatus()override
	{
		addStudentRecordRead.open("studentRecords.txt");
		studentRegisteredRead.open("studentCount.txt");
		int tempStudentCount;
		string read1, read2, read3;
		studentRegisteredRead >> tempStudentCount;//number of students
		for (int i = 0; i < tempStudentCount; i++) //for reading whole file to get matched id if any
		{
			for (int j = 0; j < 12; j++) //12 attttributes for every student
			{
				getline(addStudentRecordRead, read1);
				getline(addStudentRecordRead, read2);
				getline(addStudentRecordRead, read3);
				if (read3 == copyIdStudent) //on match it will show fee status
				{
					cout << "->->->->->->->-->your Id is " << copyIdStudent << " and ";
					if (read1 == "p" || read1 == "P")
					{
						cout << "your fee of 150000 is Paid" << endl;
						studentRegisteredRead.close();
						addStudentRecordRead.close();

						return;
					}
					else
						if (read1 == "n" || read1 == "N")
						{
							cout << "your fee of 150000 is UnPaid" << endl;
							studentRegisteredRead.close();
							addStudentRecordRead.close();
							return;
						}
				}
			}
		}
		addStudentRecordRead.close();
		studentRegisteredRead.close();
	}
	void viewAttendance()override
	{
		cout << "==================YOUR ATTENDANCE IS==========================\n";
		attendanceOfStudentRead.open("studentAttendance.txt");
		int countAtt = 0;
		string arr, idRead = "";
		while (!attendanceOfStudentRead.eof()) //read till end of file
		{
			getline(attendanceOfStudentRead, idRead);
			if (idRead == "" && countAtt == 0) //file is empty
			{
				cout << "no attendance record found" << endl;
				sound();
				break;
			}
			if (idRead == copyIdStudent) //on match it will show
			{
				for (int i = 0; i < 3; i++)
				{
					getline(attendanceOfStudentRead, arr);
					cout << arr << endl;
				}
				countAtt++;
			}

		}
		if (countAtt == 0)
		{
			cout << "your attendance is not marked yet" << endl;
			sound();

		}
		attendanceOfStudentRead.close();

	}
	void viewMarks()override
	{
		marksAssigningRead.open("studentMarks.txt");
		string IdRead = "", subjectRead, marksRead;
		int countMarks = 0;
		cout << "================Your marks are below================\n";
		while (!marksAssigningRead.eof()) //till end reading
		{
			getline(marksAssigningRead, IdRead);
			getline(marksAssigningRead, subjectRead);
			getline(marksAssigningRead, marksRead);
			if (IdRead == copyIdStudent) //on match will show data
			{
				cout << "Id=" << IdRead << endl;
				cout << "subject=" << subjectRead << endl;
				cout << "Marks=" << marksRead << endl;
				countMarks++;
			}
			else
				if (marksAssigningRead.eof() && countMarks == 0 || IdRead == "")//file is empty or no marks of this student
				{
					cout << "teacher have not entered any marks" << endl;
					sound();
					break;
				}
		}
		marksAssigningRead.close();
	}

};
class Teacher :public Admin {
	string userNameTeacher, passwordTeacher;
public:
	void timeTableTeacher()override
	{
		string coursesForTimeTable[4] = { "--","--","--","--" };
		teacherCoursesRead.open("teachersCourses.txt");
		string matchId = "";
		while (!teacherCoursesRead.eof()) //if teacher does not register any courses
		{
			getline(teacherCoursesRead, matchId);
			if (matchId == copyIdTeacher) //match id
			{
				for (int i = 0; i < 4; i++)
				{
					getline(teacherCoursesRead, coursesForTimeTable[i]);
				}
				teacherCoursesRead.close();
				break;
			}
			if (matchId == "") //empty file
			{
				cout << "no courses are registered by teacher" << endl;
				sound();

				teacherCoursesRead.close();
				return;
			}

		}
		srand(time(0)); //to generate new time table for every week
		string temp;
		int swapp = rand() % 3;

		for (int i = 0; i < 4; i++)
		{
			temp = coursesForTimeTable[i];
			coursesForTimeTable[i] = coursesForTimeTable[swapp];
			coursesForTimeTable[swapp] = temp;
		}
		cout << "[";
		for (int i = 0; i < 85; i++) {
			cout << "~";
		}
		cout << "]";
		cout << endl;
		cout << "[" << setw(45) << "TIMES TABLE" << setw(42) << "]\n";
		cout << "[";
		for (int i = 0; i < 85; i++) {
			cout << "~";
		}
		cout << "]\n";
		cout << "[" << setw(13) << "" << "|   MONDAY   |   TUESDAY  |   WEDNESDAY   |   THURSDAY   |    FRIDAY    ]" << endl;
		cout << "[";
		for (int i = 0; i < 85; i++) {
			cout << "~";
		}
		cout << "]\n";
		cout << "[ 08:00-09:30 |" << "     " << (coursesForTimeTable[0])[0] << (coursesForTimeTable[0])[1] << "           " << (coursesForTimeTable[1])[0] << (coursesForTimeTable[1])[1] << "" << setw(15) << "" << endl;
		cout << "[ 09:30-11:00 |" << "   " << "               " << (coursesForTimeTable[3])[0] << (coursesForTimeTable[3])[1] << endl;
		cout << "[ 11:00-12:30 |" << "" << "" << setw(15) << "" << "                                  " << (coursesForTimeTable[2])[0] << (coursesForTimeTable[2])[1] << endl;
		cout << "[ 12:30-01:00 |" << "                                " << (coursesForTimeTable[0])[0] << (coursesForTimeTable[0])[1] << setw(15) << "" << "" << endl;
		cout << "[ 01:00-02:30 |" << "" << "                                                                " << (coursesForTimeTable[2])[0] << (coursesForTimeTable[2])[1] << setw(15) << "" << "" << endl;
		cout << "[ 02:30-04:00 |     " << (coursesForTimeTable[0])[0] << (coursesForTimeTable[0])[1] << "" << "" << setw(15) << "" << "                                          " << (coursesForTimeTable[3])[0] << (coursesForTimeTable[3])[1] << endl;

		cout << "[";
		for (int i = 0; i < 85; i++) {
			cout << "~";
		}
		cout << "]\n";
		system("pause");
		teacherCoursesRead.close();

	}
	void signInPage()override
	{
		string readUserNameTeacer, readPasswordTeacher;
		bool flag = 0;
		readUserNameTeacer = readPasswordTeacher = "";

		while (1)
		{
			teacherUserNameAndPasswordRead.open("teacherIdAndPass.txt");
			cout << "enter your teacher id" << endl;
			getline(cin, userNameTeacher);
			copyIdTeacher = userNameTeacher;
			cout << "enter your password" << endl;
			getline(cin, passwordTeacher);
			while (!teacherUserNameAndPasswordRead.eof())
			{
				readUserNameTeacer = readPasswordTeacher = "";
				getline(teacherUserNameAndPasswordRead, readUserNameTeacer);
				getline(teacherUserNameAndPasswordRead, readPasswordTeacher);
				if (readUserNameTeacer == "" && readPasswordTeacher == "") //file empty or no record
				{
					cout << "no record found of this teacher,please contact admin" << endl;
					sound();

					sigInFlagTeacher = 1;
					sigInFlag = 1;
					break;
				}
				if (userNameTeacher == readUserNameTeacer && passwordTeacher == readPasswordTeacher)//match found
				{
					flag = 1;
					sigInFlagTeacher = 0;
					teacherUserNameAndPasswordRead.close();
					break;
				}

			}
			if (flag || sigInFlagTeacher)
			{
				flag = 0;
				break;
			}

			teacherUserNameAndPasswordRead.close();
			continue;

		}
		teacherUserNameAndPasswordRead.close();
	}
	void coursesToTeach()override
	{
		addTeacherRecordRead.open("teacherRecords.txt");
		teachersRegisteredRead.open("teachersCount.txt");
		teacherCourses.open("teachersCourses.txt", ios::app);
		string readDeptOfTeacher = "", idOfTeacher;
		int numberOfTeachers;
		bool flag = 0;

		teachersRegisteredRead >> numberOfTeachers;//gettig number of tchrs
		system("pause");
		for (int i = 0; i < numberOfTeachers; i++) //reading whole file
		{
			for (int j = 0; j < 6; j++) //reading 2 lines in each iteration
			{
				if (j <= 4) //as no need of this data till 5ht iteration
				{
					getline(addTeacherRecordRead, readDeptOfTeacher);
					getline(addTeacherRecordRead, readDeptOfTeacher);
				}
				else //getting id and dept at last iteration
				{
					getline(addTeacherRecordRead, idOfTeacher);
					if (idOfTeacher == copyIdTeacher)
					{
						flag = 1;
						break;
					}
				}
			}
			if (flag)
			{
				addTeacherRecordRead.close();
				break;
			}
		}
		CoursesRegistration(readDeptOfTeacher, teacherCourses, idOfTeacher);
		addTeacherRecordRead.close();
		teachersRegisteredRead.close();
		teacherCourses.close();
	}
	void markAttendance() override
	{
		string idOfStudent;
		attendanceOfStudent.open("studentAttendance.txt", ios::app);
		teacherCoursesRead.open("teachersCourses.txt");
		string ReadData = "";
		string subjectsOfStudents[4];
		string subjectsRegStudent[4];
		bool flag = 0;
		bool flagForNoRegister = 0;
		while (1) //for taking id of student a valid one
		{
			registerCoursesRead.open("studentRegisterCourses.txt");
			cout << "enter id of student you want to mark attendance" << endl;

			getline(cin, idOfStudent);

			while (!registerCoursesRead.eof())
			{
				getline(registerCoursesRead, ReadData);
				if (ReadData == "") //empty file
				{
					cout << "file is empty no student have not registered any courses or wrong id" << endl;
					sound();

					flagForNoRegister = 1;
					break;
				}
				if (ReadData == idOfStudent)//match found
				{
					flag = 1;
					break;
				}
			}
			if (flagForNoRegister)
			{
				registerCoursesRead.close();
				return;
			}
			if (flag)
			{
				for (int i = 0; i < 4; i++)
				{
					getline(registerCoursesRead, subjectsOfStudents[i]);
				}
				break;
			}
			else
			{
				registerCoursesRead.close();
				cout << "enter id from our regsitered students" << endl;
				sound();
			}

		}
		registerCoursesRead.close();
		string read1, read2 = "", read3;
		addTeacherRecordRead.open("teacherRecords.txt");
		while (!addTeacherRecordRead.eof()) //student id matched now getting if tchr and studrent have same depts
		{
			for (int i = 0; i < 6; i++) //reading two lines per iteratiion
			{
				if (i < 5)
				{
					getline(addTeacherRecordRead, read1);
					getline(addTeacherRecordRead, read2);
				}
				else
					getline(addTeacherRecordRead, read3);
			}
			if (read3 == copyIdTeacher) //read3 means id here and when id found it will get read2(which will be dept of teacher) as stored data in this pattern in file
			{
				addStudentRecordRead.close();
				break;
			}
		}

		addStudentRecordRead.open("studentRecords.txt");
		bool flag2 = 0;
		string getDept = "", getId;
		while (!addStudentRecordRead.eof())
		{
			for (int i = 0; i < 6; i++) //same to get student dept
			{
				getline(addStudentRecordRead, getDept);
				getline(addStudentRecordRead, getId);
				if (getDept == read2 && getId == idOfStudent) //id match and now matchig dept
				{
					attendanceOfStudent << idOfStudent << endl;
					flag2 = 1;
					break;
				}
				else
					if (addStudentRecordRead.eof())
					{
						cout << "your department is not same" << endl;
						sound();


						closeFiles();
						registerCoursesRead.close();
						return;
					}
			}
			if (flag2)
				break;
		}
		string dateForAttendance;

		cout << "enter date for attendace as dd-mm-yyyy" << endl;//getting date for attendance
		getline(cin, dateForAttendance);

		while (1) //marking attendace till done for desired dept
		{

			if (getDept == "business" || getDept == "Business")
			{
				string subjects[6] = { "marketing","business","islamiat","critical business skills","accounting","pak studies" };
				while (1)
				{
					string selectCourse;
					system("cls");
					cout << "->marketing\n->business\n->critical business skills\n->islamiat\n->accounting\n->pak studies\n->write 'done' for mark as done\n";
					cout << "->select course" << endl;
					getline(cin, selectCourse);
					if (selectCourse == "done")//break if its done
					{
						closeFiles();
						break;
					}
					for (int i = 0; i < 6; i++) //check if entered course is in list of registered
					{

						if (selectCourse == subjects[i])
						{
							string attend;
							while (1) //get attendacne now
							{
								cout << "->press p/P for present\npress a/A for absent\n";
								getline(cin, attend);
								if (attend == "p" || attend == "P" || attend == "a" || attend == "A")
								{
									attendanceOfStudent << dateForAttendance << endl << selectCourse << endl << attend << endl;
									system("pause");
									break;
								}
								else
								{
									cout << "enter input again\n";
									sound();

								}

							}
							break;
						}
						else
							if (i == 5)
							{
								cout << "enter valid course\n";
								sound();
							}
					}
					cout << "enter another course and mark as done after all attendances\n";
				}
				break;
			}
			else
				if (getDept == "computer science" || getDept == "Computer science" || getDept == "software engineering" || getDept == "Software engineering")
				{

					while (1)
					{
						system("cls");
						string selectCourse;
						string subjects[6] = { "physics","pf","LA","islamiat","op","calculus" };
						cout << "->physics\n->pf\n->LA\n->islamiat\n->op\n->calculus\n->write 'done' for mark as done";
						cout << "->select course" << endl;
						getline(cin, selectCourse);
						if (selectCourse == "done")
						{
							closeFiles();	break;
						}
						for (int i = 0; i < 6; i++)
						{
							if (selectCourse == subjects[i])
							{

								string attend;
								while (1)
								{
									cout << "->press p/P for present\npress a/A for absent\n";
									getline(cin, attend);
									if (attend == "p" || attend == "P" || attend == "a" || attend == "A")
									{
										attendanceOfStudent << dateForAttendance << endl << selectCourse << endl << attend << endl;
										system("pause");
										break;
									}
									else
									{
										cout << "enter input again\n";
										sound();

									}

								}
								break;
							}
							else
								if (i == 5)
								{
									cout << "enter valid course\n";
									sound();
								}

						}
						cout << "enter another course and mark as done after all attendances\n";
					}
					break;
				}
				else
					if (getDept == "electrical engineering" || getDept == "Electrical engineering")
					{

						while (1)
						{
							system("cls");
							string selectCourse;
							string subjects[6] = { "physics","DLD","circuits","magnetism","controls","transmission" };
							cout << "->physics\n->dld\n->circuits\n->magnetism\n->controls\n->transmission\n->write 'done' for mark as done";
							cout << "->select course" << endl;
							getline(cin, selectCourse);
							if (selectCourse == "done")
							{
								closeFiles();	break;
							}
							for (int i = 0; i < 6; i++)
							{
								if (selectCourse == subjects[i])
								{

									string attend;
									while (1)
									{
										cout << "->press p/P for present\npress a/A for absent\n";
										getline(cin, attend);
										if (attend == "p" || attend == "P" || attend == "a" || attend == "A")
										{
											attendanceOfStudent << dateForAttendance << endl << selectCourse << endl << attend << endl;
											system("pause");
											break;
										}
										else
										{
											cout << "enter input again\n";
											sound();

										}

									}
									break;
								}
								else
									if (i == 5)
									{
										cout << "enter valid course\n";
										sound();

									}

							}
							cout << "enter another course and mark as done after all attendances\n";
							system("pause");
						}
						break;
					}
					else
						if (getDept == "social sciences" || getDept == "Social sciences")
						{

							while (1)
							{
								system("cls");
								string selectCourse;
								string subjects[6] = { "english","economics","humanities","agriculture","maths","social study" };
								cout << "->english\n->economics\n->humanities\n->agriculture\n->maths\n->social study\n->write 'done' for mark as done";
								cout << "->select course" << endl;
								getline(cin, selectCourse);
								if (selectCourse == "done")
								{
									closeFiles();	break;
								}
								for (int i = 0; i < 6; i++)
								{
									if (selectCourse == subjects[i])
									{

										string attend;
										while (1)
										{
											cout << "->press p/P for present\npress a/A for absent\n";
											getline(cin, attend);
											if (attend == "p" || attend == "P" || attend == "a" || attend == "A")
											{
												system("pause");
												attendanceOfStudent << dateForAttendance << endl << selectCourse << endl << attend << endl;
												break;
											}
											else
											{
												cout << "enter input again\n";
												sound();

											}

										}
										break;
									}
									else
										if (i == 5)
										{
											cout << "enter valid course\n";
											sound();

										}

								}
								cout << "enter another course and mark as done after all attendances\n";
								system("pause");
							}
							break;
						}
						else
						{
							cout << "your attendance is done,qutting you from this module" << endl;
							system("pause");
							break;
						}


		}
		closeFiles();
	}
	void assignMarks()override
	{
		string idOfStudent, toGetDept = "", toGetID;
		addStudentRecordRead.open("studentRecords.txt");
		addTeacherRecordRead.open("teacherRecords.txt");
		bool flagStudent = 0;
		bool flagCheckMarks = 0;
		int marks;
		while (1) //to get id of
		{
			system("cls");
			cout << "enter the id of student yu want to assign marks" << endl;
			getline(cin, idOfStudent);
			while (!addStudentRecordRead.eof())
			{
				getline(addStudentRecordRead, toGetDept);
				getline(addStudentRecordRead, toGetID);
				if (idOfStudent == toGetID)
				{
					addStudentRecordRead.close();
					flagStudent = 1;
					break;
				}
				else
					if (toGetDept == "")
					{
						cout << "id of student does not match our records" << endl;
						sound();
						addStudentRecordRead.close();
						addTeacherRecordRead.close();
						return;
					}

			}
			if (flagStudent)
				break;

		}
		string teacherRead1, teacherReadDept;
		while (!addTeacherRecordRead.eof())
		{
			for (int i = 0; i < 6; i++)
			{
				if (i < 5)
				{
					getline(addTeacherRecordRead, teacherRead1);
					getline(addTeacherRecordRead, teacherReadDept);
				}
				else
					getline(addTeacherRecordRead, teacherRead1);
			}
			if (teacherRead1 == copyIdTeacher)
			{
				addTeacherRecordRead.close();
				break;
			}
		}

		if (teacherReadDept != toGetDept)
		{
			addTeacherRecordRead.close();
			addStudentRecordRead.close();
			cout << "your department is not same,enter another id for student" << endl;
			sound();

			return;
		}
		if (teacherReadDept == toGetDept)
		{
			markAssigning.open("studentMarks.txt", ios::app);

		}
		while (1)
		{

			if (toGetDept == "business" || toGetDept == "Business")
			{
				string subjects[6] = { "marketing","business","islamiat","critical business skills","accounting","pak studies" };
				while (1)
				{
					string selectCourse;
					system("cls");
					cout << "->marketing\n->business\n->critical business skills\n->islamiat\n->accounting\n->pak studies\n->write 'done' for mark as done\n";
					cout << "->select course" << endl;
					getline(cin, selectCourse);
					if (selectCourse == "done")
					{
						closeFiles();
						break;
					}
					else

						if (marksDuplicationCheck(selectCourse, idOfStudent))
							continue;
					for (int i = 0; i < 6; i++)
					{

						if (selectCourse == subjects[i])
						{
							string attend; ;
							while (1)
							{

								cout << "->enter marks from 100\n";
								getline(cin, attend);
								for (int j = 0; j < attend.length(); j++)
								{
									if (attend[j] >= 48 && attend[j] <= 57)
										flagCheckMarks = 1;
									else
									{
										flagCheckMarks = 0;
										break;
									}
								}
								if (flagCheckMarks)
									marks = stoi(attend);
								else
								{
									cout << "enter integer value" << endl;
									sound();
									continue;
								}
								if (marks < 0 || marks>100)
								{
									cout << "enter marks from 100" << endl;
									sound();
									break;
								}
								else
								{
									cout << "done with this\n";
									markAssigning << idOfStudent << endl << selectCourse << endl << marks << endl;
									system("pause");
									break;
								}
							}
							break;
						}
						else
							if (i == 5)
							{
								sound();
								cout << "enter valid course\n";
							}
					}
					cout << "enter another course and mark as done after all marks\n";
					system("pause");
				}
				break;
			}
			else
				if (toGetDept == "computer science" || toGetDept == "Computer science" || toGetDept == "software engineering" || toGetDept == "Software engineering")
				{

					while (1)
					{
						system("cls");
						string selectCourse;
						string subjects[6] = { "physics","pf","LA","islamiat","op","calculus" };
						cout << "->physics\n->pf\n->LA\n->islamiat\n->op\n->calculus\n->write 'done' for mark as done";
						cout << "->select course" << endl;
						getline(cin, selectCourse);
						if (selectCourse == "done")
						{
							closeFiles();	break;
						}
						if (marksDuplicationCheck(selectCourse, idOfStudent))
							continue;
						for (int i = 0; i < 6; i++)
						{
							if (selectCourse == subjects[i])
							{
								string attend;
								while (1)
								{
									cout << "->enter marks from 100\n";
									getline(cin, attend);
									for (int j = 0; j < attend.length(); j++)
									{
										if (attend[j] >= 48 && attend[j] <= 57)
											flagCheckMarks = 1;
										else
										{
											flagCheckMarks = 0;
											break;
										}
									}

									if (flagCheckMarks)
										marks = stoi(attend);
									else
									{
										cout << "enter integer value please" << endl;
										sound();
									}
									if (marks < 0 || marks>100)
									{
										cout << "enter marks from 100" << endl;
										sound();
										break;
									}
									else
									{
										cout << "done with this\n";
										markAssigning << idOfStudent << endl << selectCourse << endl << marks << endl;
										system("pause");
										break;
									}
								}
								break;
							}
							else
								if (i == 5)
								{
									cout << "enter valid course\n";
									sound();
								}
						}
						cout << "enter another course and mark as done after all marks\n";
					}
					break;
				}
				else
					if (toGetDept == "electrical engineering" || toGetDept == "Electrical engineering")
					{
						while (1)
						{

							system("cls");
							string selectCourse;

							string subjects[6] = { "physics","DLD","circuits","magnetism","controls","transmission" };
							cout << "->physics\n->dld\n->circuits\n->magnetism\n->controls\n->transmission\n->write 'done' for mark as done";
							cout << "->select course" << endl;
							getline(cin, selectCourse);
							if (selectCourse == "done")
							{
								closeFiles();	break;
							}
							if (marksDuplicationCheck(selectCourse, idOfStudent))
								continue;
							for (int i = 0; i < 6; i++)
							{
								if (selectCourse == subjects[i])
								{
									string attend;
									while (1)
									{
										cout << "-> enter marks from 100\n";
										getline(cin, attend);
										for (int j = 0; j < attend.length(); j++)
										{
											if (attend[j] >= 48 && attend[j] <= 57)
												flagCheckMarks = 1;
											else
											{
												flagCheckMarks = 0;
												break;
											}
										}

										if (flagCheckMarks)
											marks = stoi(attend);
										else
										{
											cout << "enter integer value please" << endl;
											sound();
										}

										if (marks < 0 || marks>100)
										{
											cout << "enter marks from 100" << endl;
											sound();

											break;
										}
										else
										{
											cout << "done with this\n";
											markAssigning << idOfStudent << endl << selectCourse << endl << marks << endl;
											system("pause");
											break;
										}
									}
									break;
								}
								else
									if (i == 5)
									{
										cout << "enter valid course\n";
										sound();

									}
							}
							cout << "enter another course and mark as done after all marks\n";
							system("pause");
						}
						break;
					}
					else
						if (toGetDept == "social sciences" || toGetDept == "Social sciences")
						{
							while (1)
							{
								system("cls");
								string selectCourse;
								string subjects[6] = { "english","economics","humanities","agriculture","maths","social study" };
								cout << "->english\n->economics\n->humanities\n->agriculture\n->maths\n->social study\n->write 'done' for mark as done";
								cout << "->select course" << endl;
								getline(cin, selectCourse);
								if (selectCourse == "done")
								{
									closeFiles();	break;
								}
								if (marksDuplicationCheck(selectCourse, idOfStudent))
									continue;
								for (int i = 0; i < 6; i++)
								{
									if (selectCourse == subjects[i])
									{
										string attend;
										while (1)
										{
											cout << "enter marks from 100\n";
											getline(cin, attend);
											for (int j = 0; j < attend.length(); j++)
											{
												if (attend[j] >= 48 && attend[j] <= 57)
													flagCheckMarks = 1;
												else
												{
													flagCheckMarks = 0;
													break;
												}
											}
											int marks;
											if (flagCheckMarks)
												marks = stoi(attend);
											else
											{
												cout << "enter integer value please" << endl;
												sound();
											}
											if (marks < 0 || marks>100)
											{
												cout << "enter marks from 100" << endl;
												sound();

												break;
											}
											else
											{
												cout << "done with this\n";
												markAssigning << idOfStudent << endl << selectCourse << endl << marks << endl;
												system("pause");
												break;
											}
										}
										break;
									}
									else
										if (i == 5)
										{
											cout << "enter valid course\n";
											sound();

										}
								}
								cout << "enter another course and mark as done after all marks\n";
								system("pause");
							}
							break;
						}
						else
						{
							cout << "your marks is done,qutting you from this module" << endl;
							system("pause");
							break;
						}
		}
		closeFiles();
	}
	void assignGrade()override {
		string idOfStudent, toGetDept = "", toGetID;
		addStudentRecordRead.open("studentRecords.txt");
		addTeacherRecordRead.open("teacherRecords.txt");
		bool flagStudent = 0;
		while (1)
		{
			system("cls");
			cout << "enter the id of student yu want to assign grades" << endl;
			getline(cin, idOfStudent);
			while (!addStudentRecordRead.eof())
			{
				getline(addStudentRecordRead, toGetDept);
				getline(addStudentRecordRead, toGetID);
				if (idOfStudent == toGetID)
				{
					addStudentRecordRead.close();
					flagStudent = 1;
					break;
				}
				else
					if (toGetDept == "")
					{
						cout << "id of student does not match our records" << endl;
						sound();

						addStudentRecordRead.close();
						addTeacherRecordRead.close();
						return;
					}
			}
			if (flagStudent)
				break;
		}
		string teacherRead1, teacherReadDept;
		while (!addTeacherRecordRead.eof())
		{
			for (int i = 0; i < 6; i++)
			{
				if (i < 5)
				{
					getline(addTeacherRecordRead, teacherRead1);
					getline(addTeacherRecordRead, teacherReadDept);
				}
				else
					getline(addTeacherRecordRead, teacherRead1);
			}
			if (teacherRead1 == copyIdTeacher)
			{
				addTeacherRecordRead.close();
				break;
			}
		}
		if (teacherReadDept != toGetDept)
		{
			addTeacherRecordRead.close();
			addStudentRecordRead.close();
			cout << "your department is not same,enter another id for student" << endl;
			sound();

			return;
		}
		if (teacherReadDept == toGetDept)
		{
			marksAssigningRead.open("studentMarks.txt");
			gradesAssigning.open("studentGrades.txt", ios::app);
		}
		string IdRead, subjectRead, marksRead;
		int countMarks = 0;
		int marksForGrades;
		char grade;
		while (!marksAssigningRead.eof())
		{
			getline(marksAssigningRead, IdRead);
			getline(marksAssigningRead, subjectRead);
			getline(marksAssigningRead, marksRead);
			if (IdRead == idOfStudent)
			{
				marksForGrades = stoi(marksRead);
				if (marksForGrades >= 90)
					grade = 'A';
				else
					if (marksForGrades < 90 && marksForGrades >= 75)
						grade = 'B';
					else
						if (marksForGrades < 75 && marksForGrades >= 60)
							grade = 'C';
						else
							if (marksForGrades < 60 && marksForGrades >= 45)
								grade = 'D';
							else
								grade = 'F';
				countMarks++;
				gradesAssigning << IdRead << endl << subjectRead << endl << marksRead << endl << grade << endl;
			}
			else
				if (marksAssigningRead.eof() && countMarks == 0)
				{
					cout << "teacher have not entered any marks so enter marks first" << endl;
					sound();
				}
				else
					cout << "grades have been assigned with a particular percentage for marked subjects\n A grade for marks >=90\nB grade for marks <90 and marks>=75\nC grade for marks<75 and marks>=60\nD grade for marks<60 and marks>=45\nF for below 45\n" << endl;
		}
	}
};
int main()
{
	images("Main.jpg");

	Admin* signIn; //base pointer
	string mainChoice;
	while (1) //main menu loop
	{
		images("Admin.jpg");
		mainMenu();

		getline(cin, mainChoice);
		if (mainChoice == "1") //for admin
		{
			signIn = new Admin();
			images("sign.jpg");
			signIn->signInPage();
			if (Admin::flagForAdmin)
			{
				sound();
				Admin::flagForAdmin = 0;
				continue;
			}
			while (1) //for menu of admin module
			{
				images("AdminM.jpg");
				string adminChoice;
				menuAdmin();
				cout << "enter your choice" << endl;
				getline(cin, adminChoice);
				if (adminChoice == "1") //add teacher 
				{
					signIn = new addTeacherAndStudentByAdmin();
					signIn->addTeacher();
				}
				else
					if (adminChoice == "2")// for add student
					{
						signIn = new addTeacherAndStudentByAdmin();
						signIn->addStudentByAdmin();
					}
					else
						if (adminChoice == "3") //for teacher
						{
							signIn = new editDetails();
							signIn->editTeacherDetails();
						}
						else
							if (adminChoice == "4")//for student
							{
								signIn = new editDetails();
								signIn->editStudentDetails();

							}
							else
								if (adminChoice == "5") //view teacher
								{
									signIn = new viewDetails();
									signIn->viewTeacherDetails();

								}
								else
									if (adminChoice == "6")//view student
									{

										signIn = new viewDetails();
										signIn->viewStudentDetails();

									}
									else
										if (adminChoice == "7") //quit from admin
										{
											cout << "you are quitting from admin module" << endl;
											system("pause");
											break;
										}
										else
										{
											cout << "enter valid choice" << endl;
											sound();

										}
			}
		}
		else
			if (mainChoice == "2") //go to teacher module
			{
				images("sign.jpg");
				signIn = new Teacher();
				signIn->signInPage();
				bool goToMain = 0;
				while (1) //sub menu of teacher
				{
					if (sigInFlag)
					{
						goToMain = 1;
						sigInFlag = 0;
						break;

					}
					string subChoice;
					images("Teacher.jpg");
					menuTeacher();
					getline(cin, subChoice);
					if (subChoice == "1")
						signIn->coursesToTeach();
					else
						if (subChoice == "2")
							signIn->markAttendance();
						else
							if (subChoice == "3")
								signIn->timeTableTeacher();
							else
								if (subChoice == "4")
									signIn->assignMarks();
								else
									if (subChoice == "5")
									{
										signIn->assignGrade();
										system("pause");
									}
									else
										if (subChoice == "6")
										{
											cout << "you are qutting from this module\n";
											system("pause");
											break;
										}
										else
										{
											cout << "enter valid choiceee" << endl;
											sound();
										}

				}
				if (goToMain)
					continue;
			}
			else
				if (mainChoice == "3")//go to student module
				{
					images("sign.jpg");
					signIn = new student();
					signIn->signInPage();
					while (1) //for sub menu of student module
					{
						if (sigInFlag)
						{

							break;
						}
						string subChoice;
						images("Student.jpg");
						menuStudent();
						cout << "enter your choice" << endl;
						getline(cin, subChoice);
						if (subChoice == "1")
							signIn->studentRegisterCourses();
						else
							if (subChoice == "2")
								signIn->viewRegisteredCourses();
							else
								if (subChoice == "3")
								{
									signIn->viewFeeStatus();
									system("pause");
								}
								else
									if (subChoice == "4")
									{
										signIn->viewAttendance();
										system("pause");
									}
									else
										if (subChoice == "7")
										{
											cout << "you are qutting from this module\n";
											system("pause");
											break;
										}
										else
											if (subChoice == "5")
											{
												signIn->viewMarks();
												system("pause");
											}
											else
												if (subChoice == "6")
												{
													signIn->viewGrades();
													system("pause");

												}
												else
												{
													cout << "enter valid choiceeeee" << endl;
													sound();
												}
					}
					if (sigInFlag)
						continue;
				}
				else
					if (mainChoice == "4") //quiting from program
					{
						cout << "you are quiting from here" << endl;
						break;
					}
					else
					{
						cout << "enter valid choice\n";
						sound();
					}
	}
	system("pause");
	return 0;
}
