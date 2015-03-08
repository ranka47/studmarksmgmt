// view_marks_s.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "view_marks_s.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"
#include<stdlib.h>


// view_marks_s dialog

IMPLEMENT_DYNAMIC(view_marks_s, CDialogEx)

view_marks_s::view_marks_s(CWnd* pParent /*=NULL*/)
	: CDialogEx(view_marks_s::IDD, pParent)
	, course(_T(""))
{
	
}

view_marks_s::~view_marks_s()
{
}

void view_marks_s::DoDataExchange(CDataExchange* pDX)
{
	extern long long int roll_number;
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, course);
	CComboBox *Majors = (CComboBox*)GetDlgItem(IDC_COMBO1);
	DatabaseWrapper *db = new DatabaseWrapper();
	int size; Course* courses = db->getCourses(roll_number, Person::STUDENT, &size);

	for (size_t i = 0; i < size; i++)
	{
		CString temp(courses[i].courseId.c_str());
		Majors->AddString(temp);
	}
	DDX_CBString(pDX, IDC_COMBO1, course);
}


BEGIN_MESSAGE_MAP(view_marks_s, CDialogEx)
	ON_BN_CLICKED(IDCANCEL2, &view_marks_s::OnBnClickedCancel2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &view_marks_s::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &view_marks_s::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &view_marks_s::OnBnClickedCancel)
END_MESSAGE_MAP()


// view_marks_s message handlers

static string ConvertToStringTwo(CString a)
{
	CString bg(a);
	const size_t newsizew = (bg.GetLength() + 1) * 2;	
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, bg, _TRUNCATE);
	string t(nstringw);

	return t;
}

void view_marks_s::OnBnClickedCancel2()
{
	//CEdit* pEdit[16];
	// TODO: Add your control notification handler code here
	extern long long int roll_number;
	DatabaseWrapper *db = new DatabaseWrapper();
	CComboBox *cmb = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int selIndex = cmb->GetCurSel();
	CString courseName("");
	cmb->GetLBText(selIndex, courseName);
	
	const size_t newsizew = (courseName.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, courseName, _TRUNCATE);
	string courseId(nstringw);
		
	int size = db->getNumberQuiz(courseId);
	int quizzes = size;
	int left = 250, top = 30, right = 500, bottom = 100, origtop = top, origbot = bottom;

	for (int i = 0; i < quizzes; i++){

		if (i == 8){
			left = left + 200;	top = origtop; bottom = origbot; right = right + 200;
		}
		//pEdit[i] = new CEdit();
		//pEdit[i]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY, CRect(left, top, right, bottom), this, i);
		//	int a = db->getStudQuizMarks(courseId, roll_number, i);
		////char tmp[5];
		////itoa(a, tmp, 10);
		////GetDlgItem(i)->SetWindowTextW(L"abcd");
		//pEdit[i]->SetDlgItemTextW(i, L"ABCD");
		//glo[i] = this.i;
		CString quizz;
		int marks = db->getStudQuizMarks(courseId, roll_number, (i+1));
		if (marks >= 0)
			quizz.Format(_T("Quiz %d : %d Marks"), i + 1, marks);
		else
			quizz.Format(_T("Quiz %d : NA"), i + 1);
		CStatic *label;
		label = new CStatic;
		label->Create(quizz, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);		
		top += 25;	bottom += 25;		
	}
}


void view_marks_s::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void view_marks_s::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void view_marks_s::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}
