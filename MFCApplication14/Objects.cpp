#include <map>
#include <string>
#include "ObjectDefinitions.h"

#define MAX_LENGTH  100

using namespace std;

Prof::Prof(string profName, int profId, DatabaseWrapper* db)
{
	this->profName = profName;
	this->profId = profId;	
}

Quiz::Quiz(int quizNumber, int weightage, string courseId, map<long long int, int> grade_list)
{
	this->quizNumber = quizNumber;
	this->weightage = weightage;
	this->courseId = courseId;
	this->grade_list = grade_list;
}

Student::Student(string studentName, long long int rollNo)
{
	this->studentName = studentName;
	this->studentRollNo = rollNo;
}

Student::Student()
{
	this->studentName = "";
	this->studentRollNo = -1;
}

//Course** Prof::getProfCourses(int profId, DatabaseWrapper* db, int* size)
//{
//	return db->getCourses(profId, Person::PROF, size);
//}

Course::Course(string courseName, string courseId, int numQuiz)
{
	this->courseName = courseName;
	this->courseId = courseId;
	this->numQuiz = numQuiz;
}

Course::Course()
{
	this->courseName = "";
	this->courseId = "";
	this->numQuiz = -1;
}