// view_marks_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "view_marks_t.h"
#include "afxdialogex.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "BasicExcel1.h"
#include "ObjectDefinitions.h"
#include "login_ats.h"
#include <stack>



// view_marks_t dialog
CString path3, cName3;
int qNum3 = -1;
stack<CStatic*> useless;

IMPLEMENT_DYNAMIC(view_marks_t, CDialogEx)

view_marks_t::view_marks_t(CWnd* pParent /*=NULL*/)
	: CDialogEx(view_marks_t::IDD, pParent)
{

}

view_marks_t::~view_marks_t()
{
}

void view_marks_t::DoDataExchange(CDataExchange* pDX)
{
	extern long long int roll_number;
	CDialogEx::DoDataExchange(pDX);
	CComboBox *Majors = (CComboBox*)GetDlgItem(IDC_COMBO1);
	DatabaseWrapper *db = new DatabaseWrapper();
	int size; Course* courses = db->getCourses(roll_number, Person::PROF, &size);

	for (size_t i = 0; i < size; i++)
	{
		CString temp(courses[i].courseId.c_str());
		Majors->AddString(temp);
	}
}

static string ConvertToString(CString a)
{
	const size_t newsizew = (a.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, a, _TRUNCATE);
	string t(nstringw);

	return t;
}
BEGIN_MESSAGE_MAP(view_marks_t, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &view_marks_t::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &view_marks_t::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDCANCEL, &view_marks_t::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &view_marks_t::OnBnClickedOk)
END_MESSAGE_MAP()


// view_marks_t message handlers


void view_marks_t::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	DatabaseWrapper *db = new DatabaseWrapper();
	CComboBox *corid = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox *corid2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	int selIndex = corid->GetCurSel();
	CString name;
	corid->GetLBText(selIndex, name);
	cName3 = name;
	int size2 = db->getNumberQuiz(ConvertToString(name));

	//DatabaseWrapper *db = new DatabaseWrapper();
	//	int size; Course* courses = db->getCourses(roll_number, Person::PROF, &size);
	corid2->ResetContent();
	for (size_t i = 0; i < size2; i++)
	{
		CString temp;
		temp.Format(_T("Quiz %d"), i + 1);
		corid2->AddString(temp);
	}
	delete db;
}



void view_marks_t::OnCbnSelchangeCombo2()
{

	// TODO: Add your control notification handler code here
	CComboBox *corid2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	qNum3 = corid2->GetCurSel() + 1;
}


void view_marks_t::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void view_marks_t::OnBnClickedOk()
{
	CString t("");
	//int lt = 300, tp = 60, rt = 500, bom = 100, op = tp, ot = bom;
	//for (size_t i = 0; i < 200; i++) //Hardcoded max number of students
	//{
	//	CStatic *label;
	//	label = new CStatic;
	//	label->Create(t, WS_CHILD | WS_VISIBLE, CRect(lt - 60, tp, rt - 60, bom), this, 90210);
	//	tp += 25;	bom += 25;
	//}
	// TODO: Add your control notification handler code here
	extern long long int roll_number;
	DatabaseWrapper *db = new DatabaseWrapper();
	CComboBox *cmb = (CComboBox*)GetDlgItem(IDC_COMBO2);
	int selIndex = cmb->GetCurSel();
	CString courseName("");
	cmb->GetLBText(selIndex, courseName);
	courseName = cName3;
	const size_t newsizew = (courseName.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, courseName, _TRUNCATE);
	string courseId(nstringw);

	while (!useless.empty())
	{
		CStatic *tmp = useless.top();
		useless.pop();
		tmp->SetWindowTextW(L"");
	}

	Quiz *q = db->getQuizMarks(courseId, selIndex + 1);
	int size = q->grade_list.size(), i=0, total=0, complTotal = 0, sqTotal=0;
	int left = 300, top = 60, right = 500, bottom = 100, origtop = top, origbot = bottom;
	map<long long int, int>::iterator it;
	for (it = q->grade_list.begin(), i=0; it != q->grade_list.end(); it++, i++){

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
		total += it->second;
		sqTotal += (it->second * it->second);
		quizz.Format(_T("%ld Marks : %ld "), it->second, it->first);
		CStatic *label;
		label = new CStatic;		
		label->Create(quizz, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		useless.push(label);
		top += 25;	bottom += 25;
	}
	CString tx(""), tn, tt;
	float mean = (float)total / (i), dev = sqrt((sqTotal - ((mean*mean) / i)) / (float)i);
	tx.Format(_T("Class Average : %.2f"), mean);
	tn.Format(_T("Total Marks: %d"), db->getQuizWeight(selIndex+1, courseId));
	tt.Format(_T("Standard Deviation : %.2f"), dev);
	CStatic *lab, *lab2, *lab3;
	lab3 = new CStatic;
	lab3->Create(tn, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
	top += 25;	bottom += 25;
	lab = new CStatic;
	lab->Create(tx, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
	top += 25;	bottom += 25;
	lab2 = new CStatic;
	lab2->Create(tt, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
	top += 25;	bottom += 25;
	useless.push(lab); useless.push(lab2); useless.push(lab3);
	for (size_t i = 0; i < (200 - size); i++) //Hardcoded max number of students
	{
		CStatic *label;
		label = new CStatic;
		label->Create(t, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		top += 25;	bottom += 25;
		useless.push(label);
	}	
}

BOOL view_marks_t::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Using built-in function for background image
	SetBackgroundImage(IDB_BITMAP1);
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);			// Set big icon
	SetIcon(hIcon, TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}