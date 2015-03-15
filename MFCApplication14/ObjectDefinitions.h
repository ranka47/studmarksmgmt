//File for declaring all the database objects that are used, and their properties
//Author: Karthik Duddu

#include <string>
#include <map>
#include "BasicExcel1.h"
#include <afx.h>

#define COURSE_FILE "courses.xls"
#define PEOPLE_FILE "people.xls"
#define LOGIN_FILE "login.xls"
#define PROF_SHEET "profs"
#define STUDENT_SHEET "students"
#define ADMIN_SHEET "admin"
#define ID_COL 0
#define NAME_COL 1
#define COURSE_COL 2
#define PROF_COL 2
#define STUD_COL 3

using namespace std;
using namespace YExcel;

enum Person {PROF, STUDENT, ADMIN,NONE};

class DatabaseWrapper;
class Course;

class Prof
{
public:
	string profName;
	int profId;	
public:
	Prof(string, int, DatabaseWrapper*);

	//Course** getProfCourses(int, DatabaseWrapper*, int*);
};

class Student
{
public:
	string studentName;
	long long int studentRollNo;

	//Course** getStudentCourses();
	Student(string, long long int);
	Student();
};

class Quiz
{
public:
	int weightage, quizNumber;
	string courseId;
	std::map<long long int, int> grade_list;

	Quiz(int, int, string, map<long long int, int>);
};

class Course
{
public:
	string courseName;
	string courseId;
	int numQuiz;

	Course(string, string, int);
	Course();
	//Prof* getCourseProfs(DatabaseWrapper*, int*);
	Student* getCourseStudents(DatabaseWrapper*, int*);
	//Quiz* getCourseQuizzes(DatabaseWrapper*, int*);
};

class DatabaseWrapper
{
private:
	BasicExcel *excelFile;
public:
	DatabaseWrapper();
	Course* createCourse(int numQuiz, string courseName, string courseId, int year);
	Course* getCourseById(string courseId);
	Course* getCourses(long long int id, Person personType, int *size);
	bool addPerson(string, long long int, Person);
	bool linkPersonCourse(long long int identifier, Person personType, string courseId);
	bool setQuizWeights(string courseId, int *weights);
	int getQuizWeight(int quiznumber, string courseId);
	bool setQuizMarks(string courseId, long long int identifier, int quizNumber, int marks);
	int getStudQuizMarks(string courseId, long long int identifier, int quizNumber);
	Quiz *getQuizMarks(string courseId, int quizNumber);
	Student* getCourseStudents(string courseId, int *size);
	int DatabaseWrapper::getNumberQuiz(string);
	bool addLoginDetails(long long int identifier, string password, Person personType);
	bool checkLogin(long long int username, CString password, Person personType);
	Course* getStudentCourses(long long int identifier, int *size);
	Course* getProfCourses(long long int identifier, int *size);
	string* getCourseList(int *size);
};
