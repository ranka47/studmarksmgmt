// add_course_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_course_t.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"


// add_course_t dialog

IMPLEMENT_DYNAMIC(add_course_t, CDialogEx)

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
}


void add_course_t::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
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


}
