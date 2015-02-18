// add_student_a.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_student_a.h"
#include "afxdialogex.h"
#include"ObjectDefinitions.h"


// add_student_a dialog

IMPLEMENT_DYNAMIC(add_student_a, CDialogEx)

add_student_a::add_student_a(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_student_a::IDD, pParent)
	, studentname(_T(""))
	, studentid(0)
{

}

add_student_a::~add_student_a()
{
}

void add_student_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, studentname);
	DDX_Text(pDX, IDC_EDIT3, studentid);
}


BEGIN_MESSAGE_MAP(add_student_a, CDialogEx)
	ON_BN_CLICKED(IDOK, &add_student_a::OnBnClickedOk)
END_MESSAGE_MAP()


// add_student_a message handlers


void add_student_a::OnBnClickedOk()
{
	
	CString studentnamevar; long long int studentidvar;
	// TODO: Add your control notification handler code here

	UpdateData();
	studentnamevar = studentname;
	studentidvar = studentid;
	if (studentnamevar != "" &&studentidvar >= 100000000 && studentidvar <= 999999999)
	{

		const size_t newsizew = (studentnamevar.GetLength() + 1) * 2;
		char *nstringw = new char[newsizew];
		size_t convertedCharsw = 0;
		wcstombs_s(&convertedCharsw, nstringw, newsizew, studentnamevar, _TRUNCATE);
		studentidvar = studentid;
		DatabaseWrapper *pr = new DatabaseWrapper();
		pr->addPerson(nstringw, studentidvar, Person::STUDENT);
		AfxMessageBox(_T("Student added successfully!!!"));
		EndDialog(0);


	}
	else if (studentnamevar == "")
		AfxMessageBox(_T("Please fill in all the details before submitting"));

	else if (studentidvar < 100000000 || studentidvar > 999999999)
	{
		AfxMessageBox(_T("The roll number should be 9 digits long"));
	}
	


	UpdateData(FALSE);
}
