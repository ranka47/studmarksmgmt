//File defining all the basic operations performed on the database
//Also includes definitions of auxiliary functions that help in various information processing functions
//Author: Karthik Duddu

#include "BasicExcel1.h"
#include "ObjectDefinitions.h"
#include <afxwin.h>
#include <map>
#include <vector>

using namespace YExcel;
using namespace std;

DatabaseWrapper::DatabaseWrapper()
{
	BasicExcel text;
	if (!text.Load(COURSE_FILE))
	{
		text.New(0);
		text.SaveAs(COURSE_FILE);
	}

	if (!text.Load(PEOPLE_FILE))
	{
		text.New(3);
		text.RenameWorksheet("Sheet1", PROF_SHEET);
		text.RenameWorksheet("Sheet2", STUDENT_SHEET);
		text.RenameWorksheet("Sheet3", ADMIN_SHEET);
		text.SaveAs(PEOPLE_FILE);
		TRACE("people sheet created");
	}
	else
		TRACE("people sheet exists already"); 

	if (!text.Load(LOGIN_FILE))
	{
		text.New(3);
		text.RenameWorksheet("Sheet1", PROF_SHEET);
		text.RenameWorksheet("Sheet2", STUDENT_SHEET);
		text.RenameWorksheet("Sheet3", ADMIN_SHEET);
		text.SaveAs(LOGIN_FILE);		
	}

}

Course* DatabaseWrapper::createCourse(int numQuiz, string courseName, string courseId, int year)
{	
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	excelFile.AddWorksheet(courseId.c_str());
	excelFile.SaveAs(COURSE_FILE);
		
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet* curCourse = excelFile.GetWorksheet(courseId.c_str());
	if (curCourse)
	{
		TRACE("curCourse name is %s", curCourse->GetAnsiSheetName());
		curCourse->Cell(0, 0)->Set(courseName.c_str());
		curCourse->Cell(0, 1)->Set(courseId.c_str());
		curCourse->Cell(0, 3)->SetInteger(year);
		curCourse->Cell(0, 4)->SetInteger(numQuiz);
		curCourse->Cell(1, 0)->Set("RollNo\\Quiz");
		for (int i = 1; i <= numQuiz; i++)
		{
			curCourse->Cell(1, i)->SetInteger(i);
		}
		excelFile.SaveAs(COURSE_FILE);	
	}
	
	return new Course("","",-1);//make it return the new course object
}

bool DatabaseWrapper::addPerson(string name, long long int identifier, Person personType)
{
	BasicExcel e;
	e.Load(PEOPLE_FILE);
	BasicExcelWorksheet *a;
	if (personType == Person::STUDENT)
		a = e.GetWorksheet(STUDENT_SHEET);
	else if (personType == Person::PROF)
		a = e.GetWorksheet(PROF_SHEET);
	else if (personType == Person::ADMIN)
		a = e.GetWorksheet(ADMIN_SHEET);
	if (a)
	{
		int loc = a->GetTotalRows();
		a->Cell(loc, 1)->Set(name.c_str());
		a->Cell(loc, 0)->SetInteger(identifier);	
		a->Cell(loc, 2)->SetString("");
		e.SaveAs(PEOPLE_FILE);
	}
	return true;
}

bool DatabaseWrapper::linkPersonCourse(long long int identifier, Person personType, string courseId)
{
	BasicExcel excelFile;
	excelFile.Load(PEOPLE_FILE);
	BasicExcelWorksheet *sheet;
	if (personType == Person::PROF)
		sheet = excelFile.GetWorksheet(PROF_SHEET);
	else if (personType == Person::STUDENT)
		sheet = excelFile.GetWorksheet(STUDENT_SHEET);
	
	if (!sheet)
		return false;

	int found = -1;
	for (size_t i = 0; i < sheet->GetTotalRows(); i++)
	{
		if (identifier == sheet->Cell(i, ID_COL)->GetInteger())
		{
			found = i;
			break;
		}
	}
	if (found == -1)
		return false;
	
	BasicExcelCell *c = sheet->Cell(found, COURSE_COL);
	string temp = "";
	if (c->Type() == BasicExcelCell::STRING)
		temp = (sheet->Cell(found, COURSE_COL)->GetString());
	
	temp += (courseId + ",");
	sheet->Cell(found, COURSE_COL)->SetString(temp.c_str());
	excelFile.SaveAs(PEOPLE_FILE);

	excelFile.Load(COURSE_FILE);
	sheet = excelFile.GetWorksheet(courseId.c_str());
	if (!sheet)
		return false;

	if (personType == Person::PROF)
	{
		string temp2 = "";
		char valTmp[33];
		ltoa(identifier, valTmp, 10);
		string tmpId(valTmp);
		c = sheet->Cell(0, 2);
		if (c->Type() == BasicExcelCell::STRING)
			temp2 = (sheet->Cell(0, PROF_COL)->GetString());
		temp2 += (tmpId + ",");
		sheet->Cell(0, PROF_COL)->SetString(temp2.c_str());
	}
	else if (personType == Person::STUDENT)
	{
		sheet->Cell(sheet->GetTotalRows(), 0)->SetInteger(identifier);
	}

	excelFile.SaveAs(COURSE_FILE);
	return true;
}	

Course* DatabaseWrapper::getCourseById(string courseId)
{
	BasicExcel file;
	file.Load(COURSE_FILE);
	BasicExcelWorksheet* sheet = file.GetWorksheet(courseId.c_str());

	if (!sheet)
		return NULL;
	string name="", id="";
	int nQ=-1;

	if (sheet->Cell(0, 0)->Type() == BasicExcelCell::STRING)
		name = sheet->Cell(0, 0)->GetString();
	if (sheet->Cell(0, 1)->Type() == BasicExcelCell::STRING)
		id = sheet->Cell(0, 1)->GetString();
	if (sheet->Cell(0, 4)->Type() == BasicExcelCell::INT)
		nQ = sheet->Cell(0, 0)->GetInteger();

	return new Course(name, id, nQ);
}

bool DatabaseWrapper::setQuizWeights(string courseId, int *weights)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet* sheet = excelFile.GetWorksheet(courseId.c_str());

	if (!sheet)
		return false;
	if (sheet->Cell(0, 4)->Type() != BasicExcelCell::INT)
		return false;
	int numQuiz = sheet->Cell(0, 4)->GetInteger(), startCol = (numQuiz+2);
	for (size_t i = 1; i <= numQuiz; i++)
		sheet->Cell(i, startCol)->SetInteger(weights[i - 1]);
	excelFile.SaveAs(COURSE_FILE);
	return true;
}

bool DatabaseWrapper::setQuizMarks(string courseId, long long int identifier, int quizNumber, int marks)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(courseId.c_str());

	if (!sheet)
		return false;
	int found = -1;
	for (size_t i = 0; i < sheet->GetTotalRows(); i++)
	{
		if (identifier == sheet->Cell(i, ID_COL)->GetInteger())
		{	found = i;	break;	}
	}
	if (found == -1)
		return false;
	sheet->Cell(found, quizNumber)->SetInteger(marks);
	excelFile.SaveAs(COURSE_FILE);
	return true;
}

int DatabaseWrapper::getStudQuizMarks(string courseId, long long int identifier, int quizNumber)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(courseId.c_str());

	if (!sheet)
		return -1;
	int found = -1;
	for (size_t i = 0; i < sheet->GetTotalRows(); i++)
	{
		if (identifier == sheet->Cell(i, ID_COL)->GetInteger())
		{	found = i;	break;	}
	}
	if (found == -1)
		return -1;
	if (sheet->Cell(found, quizNumber)->Type() != BasicExcelCell::INT)
		return -1;
	return sheet->Cell(found, quizNumber)->GetInteger();
}

int DatabaseWrapper::getQuizWeight(int quizNumber, string courseId)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet* sheet = excelFile.GetWorksheet(courseId.c_str());

	if (!sheet)
		return -1;
	if (sheet->Cell(0, 4)->Type() != BasicExcelCell::INT)
		return -1;
	int numQuiz = sheet->Cell(0, 4)->GetInteger(), startCol = (numQuiz + 2);
	if (sheet->Cell(quizNumber, startCol)->Type() != BasicExcelCell::INT)
		return -1;
	return sheet->Cell(quizNumber, startCol)->GetInteger();
}

Quiz* DatabaseWrapper::getQuizMarks(string courseId, int quizNumber)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(courseId.c_str());
	if (!sheet) return NULL;
	if (sheet->Cell(1, quizNumber)->Type() != BasicExcelCell::INT) return NULL;
	map<long long int, int> marks;
	for (size_t i = 2; i < sheet->GetTotalRows(); i++)
	{
		if (sheet->Cell(i, 0)->Type() != BasicExcelCell::INT || sheet->Cell(i, quizNumber)->Type() != BasicExcelCell::INT) break;
		marks[sheet->Cell(i, 0)->GetInteger()] = sheet->Cell(i, quizNumber)->GetInteger();
	}
	Quiz* q = new Quiz(quizNumber, getQuizWeight(quizNumber, courseId), courseId, marks);
	return q;
}

Student* DatabaseWrapper::getCourseStudents(string courseId, int *size)
{
	Student* st = new Student[100];
	BasicExcel excelFile, excelFile2;
	excelFile.Load(COURSE_FILE);
	excelFile2.Load(PEOPLE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(courseId.c_str()), *sheet2 = excelFile2.GetWorksheet(STUDENT_SHEET);
	if (!sheet || !sheet2) { return NULL; }
	*size = 0;
	for (size_t i = 2; i < sheet->GetTotalRows(); i++)
	{
		if (sheet->Cell(i, 0)->Type() != BasicExcelCell::INT) break;
		int identifier = sheet->Cell(i, 0)->GetInteger();
		int found = -1;
		for (size_t j = 0; j < sheet2->GetTotalRows();j++)
		{
			if (sheet2->Cell(j, ID_COL)->Type() == BasicExcelCell::INT && identifier == sheet2->Cell(j, ID_COL)->GetInteger())	{	found = j;	break;	}
		}
		if (found == -1) { return NULL; }
		st[*size].studentName = sheet2->Cell(found, 1)->GetString();
		st[*size].studentRollNo = (long long)identifier;
		(*size)++;
	}

	return st;
}

Course* DatabaseWrapper::getStudentCourses(long long int identifier, int *size)
{
	BasicExcel excelFile;
	excelFile.Load(PEOPLE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(STUDENT_SHEET);
	if (!sheet) return NULL;
	int found = -1;
	for (size_t j = 0; j < sheet->GetTotalRows(); j++)
	{
		if (sheet->Cell(j, ID_COL)->Type() == BasicExcelCell::INT && identifier == sheet->Cell(j, ID_COL)->GetInteger())	{ found = j;	break; }
	}
	if (found == -1) return NULL;
	if (sheet->Cell(found, 2)->Type() != BasicExcelCell::STRING) return NULL;
	char *list = strtok((char*)sheet->Cell(found, 2)->GetString(), ",");
	Course* cs = new Course[1000];
	*size = 0;
	while (list != NULL)
	{
		string w(list);
		cs[*size] = *getCourseById(w);
		list = strtok(NULL, " ,.-");
		(*size)++;
	}
	return cs;
}

Course* DatabaseWrapper::getProfCourses(long long int identifier, int *size)
{
	BasicExcel excelFile;
	excelFile.Load(PEOPLE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(PROF_SHEET);
	if (!sheet) return NULL;
	int found = -1;
	for (size_t j = 0; j < sheet->GetTotalRows(); j++)
	{
		if (sheet->Cell(j, ID_COL)->Type() == BasicExcelCell::INT && identifier == sheet->Cell(j, ID_COL)->GetInteger())	{ found = j;	break; }
	}
	if (found == -1) return NULL;
	if (sheet->Cell(found, 2)->Type() != BasicExcelCell::STRING) return NULL;
	char *list = strtok((char*)sheet->Cell(found, 2)->GetString(), ",");
	Course* cs = new Course[1000];
	*size = 0;
	while (list != NULL)
	{
		string w(list);
		cs[*size] = *getCourseById(w);
		list = strtok(NULL, " ,.-");
		(*size)++;
	}
	return cs;
}

int DatabaseWrapper::getNumberQuiz(string courseId)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	BasicExcelWorksheet *sheet = excelFile.GetWorksheet(courseId.c_str());
	if (!sheet) return -1;
	if (sheet->Cell(0, 4)->Type() != BasicExcelCell::INT) return -1;
	return sheet->Cell(0, 4)->GetInteger();
}

string* DatabaseWrapper::getCourseList(int *size)
{
	BasicExcel excelFile;
	excelFile.Load(COURSE_FILE);
	long int s = excelFile.GetTotalWorkSheets();
	string *files = new string[s];
	*size = 0;
	for (*size = 0; *size < s; (*size)++)
	{
		files[*size] = excelFile.GetAnsiSheetName(*size);
	}
	return files;
}

bool DatabaseWrapper::checkLogin(long long int username, CString password, Person personType)
{
	BasicExcel excelFile;
	excelFile.Load(LOGIN_FILE);
	BasicExcelWorksheet *sheet;
	switch (personType)
	{
	case Person::STUDENT: sheet = excelFile.GetWorksheet(STUDENT_SHEET);
		break;
	case Person::ADMIN: sheet = excelFile.GetWorksheet(ADMIN_SHEET);
		break;
	case Person::PROF: sheet = excelFile.GetWorksheet(PROF_SHEET);
		break;
	}
	if (!sheet)
		return false;
	int found = -1;
	for (size_t j = 0; j < sheet->GetTotalRows(); j++)
	{	if (sheet->Cell(j, ID_COL)->Type() == BasicExcelCell::INT && username == sheet->Cell(j, ID_COL)->GetInteger())	{ found = j;	break; }	}
	if (found == -1) return false;
	if (sheet->Cell(found, NAME_COL)->Type() != BasicExcelCell::STRING) return false;
	//string temp(sheet->Cell(found, NAME_COL)->GetString()), temp2(password);
	CString t(sheet->Cell(found, NAME_COL)->GetString());
	return (t == password);
}

bool DatabaseWrapper::addLoginDetails(long long int identifier, string password, Person personType)
{
	BasicExcel excelFile;
	excelFile.Load(LOGIN_FILE);
	BasicExcelWorksheet *sheet;
	switch (personType)
	{
	case Person::STUDENT: sheet = excelFile.GetWorksheet(STUDENT_SHEET);
		break;
	case Person::ADMIN: sheet = excelFile.GetWorksheet(ADMIN_SHEET);
		break;
	case Person::PROF: sheet = excelFile.GetWorksheet(PROF_SHEET);
		break;
	}
	if (!sheet)
		return false;
	sheet->Cell(sheet->GetTotalRows(), 0)->SetInteger(identifier);
	sheet->Cell(sheet->GetTotalRows() - 1, 1)->SetString(password.c_str());
	excelFile.SaveAs(LOGIN_FILE);
	return true;
}

Course* DatabaseWrapper::getCourses(long long int identifier, Person personType, int *size)
{
	BasicExcel excelFile;
	excelFile.Load(PEOPLE_FILE);
	BasicExcelWorksheet *sheet;
	int found = -1;
	switch (personType)
	{
	case Person::PROF:
		sheet = excelFile.GetWorksheet(PROF_SHEET);
		break;
	case Person::STUDENT:
		sheet = excelFile.GetWorksheet(STUDENT_SHEET);
		break;
	case Person::ADMIN:
		sheet = excelFile.GetWorksheet(ADMIN_SHEET);
		break;
	}

	if (!sheet) return NULL;

	for (size_t i = 0; i < sheet->GetTotalRows(); i++)
	{	if (sheet->Cell(i, ID_COL)->GetInteger() == identifier)	{	found = i;	break;	}	}

	char *a;
	if (found == -1) return NULL;
	else a = (char*)sheet->Cell(found, COURSE_COL)->GetString();
	
	char *list = strtok(a, ",");
	Course* cs = new Course[1000];
	*size = 0;
	while (list != NULL)
	{
		string w(list);
		cs[*size] = *getCourseById(w);
		list = strtok(NULL, " ,.-");
		(*size)++;		
	}
	return cs;
}