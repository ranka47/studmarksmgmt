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
	, s_password(_T(""))
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
	DDX_Text(pDX, IDC_PASSWORD, s_password);
	DDV_MaxChars(pDX, s_password, 32);
}


BEGIN_MESSAGE_MAP(add_student_a, CDialogEx)
	ON_BN_CLICKED(IDOK, &add_student_a::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &add_student_a::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_PASSWORD, &add_student_a::OnEnChangePassword)
	ON_EN_CHANGE(IDC_EDIT3, &add_student_a::OnEnChangeEdit3)
END_MESSAGE_MAP()


// add_student_a message handlers

static string ConvertToString(CString a)
{
	const size_t newsizew = (a.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, a, _TRUNCATE);
	string t(nstringw);

	return t;
}


void add_student_a::OnBnClickedOk()
{
	
	CString studentnamevar; long long int studentidvar;
	// TODO: Add your control notification handler code here

	UpdateData();
	studentnamevar = studentname;
	studentidvar = studentid;
	int len = studentnamevar.GetLength();
	string dummy = ConvertToString(studentnamevar).c_str();
	char *tmp = (char*)(dummy.c_str());
	int flag = 0;
	for (int i = 0; i < len; i++)
	{
		if (!isalpha(tmp[i]) || tmp[i] != ' ')
		{
			AfxMessageBox(_T("Enter proper Name (albhabets only)"));
			flag = 1;
			return;
		}
	}

	if (studentnamevar != "" && studentnamevar != " " && flag==0 &&studentidvar >= 100000000 && studentidvar <= 999999999 )
	{
		
		CString password = s_password;
		
		const size_t newsizew = (studentnamevar.GetLength() + 1) * 2;
		char *nstringw = new char[newsizew];
		size_t convertedCharsw = 0;
		wcstombs_s(&convertedCharsw, nstringw, newsizew, studentnamevar, _TRUNCATE);
		studentidvar = studentid;
		DatabaseWrapper *pr = new DatabaseWrapper();
		pr->addPerson(nstringw, studentidvar, Person::STUDENT);
		pr->addLoginDetails(studentidvar, ConvertToString(password), Person::STUDENT);
		AfxMessageBox(_T("Student added successfully!!!"));
		EndDialog(0);

	}
	else if (studentnamevar == "" || studentnamevar == " ")
		AfxMessageBox(_T("Please fill in all the details before submitting"));

	else if (studentidvar < 100000000 || studentidvar > 999999999)
	{
		AfxMessageBox(_T("The roll number should be 9 digits long"));
	}
	


	UpdateData(FALSE);
}


void add_student_a::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void add_student_a::OnEnChangePassword()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void add_student_a::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
