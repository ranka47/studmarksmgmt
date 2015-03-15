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
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	
	int left = 230, top = 40, right = 500, bottom = 100, origtop = top, origbot = bottom;
	char rn[10]; ltoa(roll_number, rn, 10);
	CString name(rn);
	name.Append(_T("'s Report Card"));
	CStatic *l;
	l = new CStatic;
	l->Create(name, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
	top += 25;	bottom += 25;
	for (int i = 0; i < size; i++){

		if (i % 2 == 1){
			left = left + 300;	top = origtop + 50; bottom = origbot + 50; right = right + 300;
		}
		else
		{
			left = 150, right = 500, top = top + 25, bottom += 25;
		}
		//pEdit[i] = new CEdit();
		//pEdit[i]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_READONLY, CRect(left, top, right, bottom), this, i);
		//	int a = db->getStudQuizMarks(courseId, roll_number, i);
		////char tmp[5];
		////itoa(a, tmp, 10);
		////GetDlgItem(i)->SetWindowTextW(L"abcd");
		//pEdit[i]->SetDlgItemTextW(i, L"ABCD");
		//glo[i] = this.i;
		CString courseName(courses[i].courseName.c_str());
		top += 25;	bottom += 25;
		courseName.Append(_T(" Performance: "));
		CStatic *label;
		label = new CStatic;
		label->Create(courseName, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		top += 25;	bottom += 25;
		int total = 0, complTotal=0;
		for (size_t j = 0; j < db->getNumberQuiz(courses[i].courseId); j++)
		{
			CString quizz;
			int marks = db->getStudQuizMarks(courses[i].courseId, roll_number, (j + 1));
			if (marks >= 0)
			{
				int temp = db->getQuizWeight(j + 1, courses[i].courseId);
				quizz.Format(_T("Quiz %d : %d out of %d Marks"), j + 1, marks, temp);
				complTotal += temp;
				total += marks;
			}
			else
				quizz.Format(_T("Quiz %d : NA"), j + 1);
			CStatic *label2;
			label2 = new CStatic;
			label2->Create(quizz, WS_CHILD | WS_VISIBLE, CRect(left - 90, top, right - 60, bottom), this, 90210);
			top += 25;	bottom += 25;
		}
		CString ag("");
		ag.Format(_T("Total (so far): %d/%d (%.2f percent)"), total, complTotal, (complTotal!=0)?100 * (total / (float)complTotal):0 );
		CStatic *labe;
		labe = new CStatic;
		//top += 40;	bottom += 40;
		labe->Create(ag, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		top += 25;	bottom += 25;
	}
	if (size >= 2)
	{
		::SetWindowPos(m_hWnd, HWND_TOPMOST, top, 150, 650, bottom + 10, SWP_NOZORDER);
	}
	else
	{
		::SetWindowPos(m_hWnd, HWND_TOPMOST, top, 150, 350, bottom + 10, SWP_NOZORDER);
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

BOOL result_s::OnInitDialog()
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