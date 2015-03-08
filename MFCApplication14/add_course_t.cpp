// add_course_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_course_t.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"


// add_course_t dialog

IMPLEMENT_DYNAMIC(add_course_t, CDialogEx)
int glob[16];
CEdit* pEdit[15];
// CAboutDlg dialog used for App About
CString str[16][5];
add_course_t::add_course_t(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_course_t::IDD, pParent)
	, no_of_exams(0)
	, coursename(_T(""))
	, coursenumber(_T(""))
{

}

add_course_t::~add_course_t()
{
}

void add_course_t::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, no_of_exams);
	DDV_MinMaxInt(pDX, no_of_exams, 1, 16);
	DDX_Text(pDX, IDC_EDIT2, coursename);
	DDX_Text(pDX, IDC_EDIT1, coursenumber);
}


BEGIN_MESSAGE_MAP(add_course_t, CDialogEx)
	ON_BN_CLICKED(IDOK, &add_course_t::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &add_course_t::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &add_course_t::OnBnClickedButton2)
END_MESSAGE_MAP()


// add_course_t message handlers


void add_course_t::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	UpdateData();
	int noquiz = no_of_exams;
	CString cname = coursename;
	CString cid = coursenumber;
	int quizzes = noquiz;
	int i;
	for (size_t i = 0; i < quizzes; i++)
	{
		pEdit[i]->GetWindowText(*str[i]);
	}
	UpdateData(FALSE);

	//pEdit[0]->GetWindowText(str);
	//result = str;
}


void add_course_t::OnBnClickedButton1()
{
	AfxMessageBox(_T("This code is still in progress"));
	return;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int noquiz = no_of_exams;
	CString cname = coursename;
	CString cid = coursenumber;
	int quizzes = noquiz;
	int left = 200, top = 280, right = 260, bottom = 300, origtop = top, origbot = bottom;

	for (int i = 0; i < quizzes; i++){

		if (i == 8){
			left = left + 200;	top = origtop; bottom = origbot; right = right + 200;
		}
		pEdit[i] = new CEdit();
		pEdit[i]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, CRect(left, top, right, bottom), this, i);
		//glo[i] = this.i;
		CStatic *label;
		label = new CStatic;
		CString quizz;
		quizz.Format(_T("Quiz %d"), i + 1);
		label->Create(quizz, WS_CHILD | WS_VISIBLE, CRect(left - 60, top, right - 60, bottom), this, 90210);
		top += 25;	bottom += 25;
	}
	UpdateData(FALSE);

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

void add_course_t::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int noquiz = no_of_exams;
	CString cname = coursename;
	CString cid = coursenumber;
	
	string t1 = ConvertToString(cname);
	string t2 = ConvertToString(cid);
	
	UpdateData(FALSE);
	DatabaseWrapper *db = new DatabaseWrapper();
	db->createCourse(noquiz, t1, t2, 2015);
	int *weights = new int[noquiz], sum=0;
	for (size_t i = 0; i < (noquiz-1); i++)
	{
		weights[i] = (100) / noquiz;
		sum += weights[i];
	}
	weights[noquiz - 1] = 100 - sum;
	db->setQuizWeights(ConvertToString(cname), weights);

	AfxMessageBox(_T("Course added successfully"));
}
