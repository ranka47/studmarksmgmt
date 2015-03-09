// result_s.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "result_s.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"

// result_s dialog

IMPLEMENT_DYNAMIC(result_s, CDialogEx)

result_s::result_s(CWnd* pParent /*=NULL*/)
	: CDialogEx(result_s::IDD, pParent)
{

}

result_s::~result_s()
{
}

void result_s::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	extern long long int roll_number;
	DatabaseWrapper *db = new DatabaseWrapper();
	int size = 0;
	Course *courses = db->getStudentCourses(roll_number, &size);

	int left = 150, top = 30, right = 500, bottom = 100, origtop = top, origbot = bottom;

	for (int i = 0; i < size; i++){

		/*if (i == 8){
			left = left + 200;	top = origtop; bottom = origbot; right = right + 200;
		}*/
		//pEdit[i] = new CEdit();
		//pEdit[i]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY, CRect(left, top, right, bottom), this, i);
		//	int a = db->getStudQuizMarks(courseId, roll_number, i);
		////char tmp[5];
		////itoa(a, tmp, 10);
		////GetDlgItem(i)->SetWindowTextW(L"abcd");
		//pEdit[i]->SetDlgItemTextW(i, L"ABCD");
		//glo[i] = this.i;
		CString courseName(courses[i].courseName.c_str());		
		courseName.Append(_T(" Details"));
		CStatic *label;
		label = new CStatic;
		label->Create(courseName, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		top += 25;	bottom += 25;

		for (size_t j = 0; j < db->getNumberQuiz(courses[i].courseId); j++)
		{
			CString quizz;
			int marks = db->getStudQuizMarks(courses[i].courseId, roll_number, (j + 1));
			if (marks >= 0)
				quizz.Format(_T("Quiz %d : %d Marks"), j + 1, marks);
			else
				quizz.Format(_T("Quiz %d : NA"), j + 1);
			CStatic *label2;
			label2 = new CStatic;
			label2->Create(quizz, WS_CHILD | WS_VISIBLE, CRect(left - 90, top, right - 60, bottom), this, 90210);
			top += 25;	bottom += 25;
		}
	}
}


BEGIN_MESSAGE_MAP(result_s, CDialogEx)
	ON_BN_CLICKED(IDOK, &result_s::OnBnClickedOk)
END_MESSAGE_MAP()


// result_s message handlers


void result_s::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
