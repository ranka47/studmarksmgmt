// add_faculty_a.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_faculty_a.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"


// add_faculty_a dialog

IMPLEMENT_DYNAMIC(add_faculty_a, CDialogEx)

add_faculty_a::add_faculty_a(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_faculty_a::IDD, pParent)
	, facultyname(_T(""))
	, facultyid()
{

}

add_faculty_a::~add_faculty_a()
{
}

void add_faculty_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, facultyname);
	DDX_Text(pDX, IDC_EDIT1, facultyid);
}


BEGIN_MESSAGE_MAP(add_faculty_a, CDialogEx)
	
	ON_BN_CLICKED(IDOK2, &add_faculty_a::OnBnClickedOk2)
	ON_EN_CHANGE(IDC_EDIT1, &add_faculty_a::OnEnChangeEdit1)
END_MESSAGE_MAP()


// add_faculty_a message handlers





void add_faculty_a::OnBnClickedOk2()
{
	CString facultynamevar; long long int facultyidvar;
	// TODO: Add your control notification handler code here
	
	UpdateData();
	facultynamevar = facultyname;
	facultyidvar = facultyid;
	if (facultynamevar != "" &&facultyidvar >= 100000 && facultyidvar<=999999 )
	{
		
		const size_t newsizew = (facultynamevar.GetLength() + 1) * 2;
		char *nstringw = new char[newsizew];
		size_t convertedCharsw = 0;
		wcstombs_s(&convertedCharsw, nstringw, newsizew, facultynamevar, _TRUNCATE);
		facultyidvar = facultyid;
		DatabaseWrapper *pr = new DatabaseWrapper();
		pr->addPerson(nstringw, facultyidvar, Person::PROF);
		AfxMessageBox(_T("Faculty added successfully!!!"));
		EndDialog(0);



	}
	else if (facultynamevar == "")
		AfxMessageBox(_T("Please fill in all the details before submitting"));
	else if (facultyidvar < 1000000 || facultyidvar > 999999)
	{
		AfxMessageBox(_T("The roll number should be 6 digits long"));
	}
	


	UpdateData(FALSE);
}


void add_faculty_a::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
