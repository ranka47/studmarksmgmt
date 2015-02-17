// login_ats.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "login_ats.h"
#include "BasicExcel1.h"
#include "afxdialogex.h"
#include <string.h>
#include <iostream>
#include "ObjectDefinitions.h"
#include "dashboard_a.h"
#include "dashboard_s.h"
#include "dashboard_t.h"

// login_ats dialog
IMPLEMENT_DYNAMIC(login_ats, CDialogEx)

string password_string;
bool login_allowed = FALSE;


long long int roll_number;

login_ats::login_ats(CWnd* pParent /*=NULL*/)
	: CDialogEx(login_ats::IDD, pParent)
	, admin(false)
	, prof(false)
	, student(false)
	, roll_id(0)
	, password_cstring(_T(""))
{

}

login_ats::~login_ats()
{
}

void login_ats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, roll_id);
	DDX_Text(pDX, IDC_PASSWORD, password_cstring);
}


BEGIN_MESSAGE_MAP(login_ats, CDialogEx)
	ON_BN_CLICKED(IDLOGIN, &login_ats::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_ADMIN, &login_ats::OnBnClickedAdmin)
	ON_BN_CLICKED(IDC_FACULTY, &login_ats::OnBnClickedFaculty)
	ON_BN_CLICKED(IDC_STUDENT, &login_ats::OnBnClickedStudent)
END_MESSAGE_MAP()


void login_ats::OnBnClickedLogin()
{
	DatabaseWrapper *db = new DatabaseWrapper();
	Person type=Person::ADMIN;
	// TODO: Add your control notification handler code here
	if (admin == TRUE)
	{
		type = Person::ADMIN; login_allowed = TRUE;
	}
	else if (prof == TRUE)
	{
		type = Person::PROF; login_allowed = TRUE;
	}
	else if (student == TRUE)
	{
		type = Person::STUDENT; login_allowed = TRUE;
	}
	else
	{
		AfxMessageBox(_T("Please choose the person type.")); login_allowed = FALSE;
	}
	UpdateData();
	const TCHAR* pstring = (LPCTSTR)password_cstring;
	UpdateData(FALSE);
	login_allowed = db->checkLogin(roll_id, password_cstring, type);

	if (login_allowed == TRUE)
	{		
		roll_number = roll_id;
    		if (type == Person::ADMIN)
		{
			dashboard_a admin;
			admin.DoModal();
		}
		else if (type == Person::PROF)
		{
			dashboard_t prof;
			prof.DoModal();
		}
		else
		{
			dashboard_s student;
			student.DoModal();
		}
	}
	else
		MessageBox(_T("Enter valid username and password"));

	delete db;
}


void login_ats::OnBnClickedAdmin()
{
	// TODO: Add your control notification handler code here
	admin = !admin;
}


void login_ats::OnBnClickedFaculty()
{
	// TODO: Add your control notification handler code here
	prof = !prof;
}


void login_ats::OnBnClickedStudent()
{
	// TODO: Add your control notification handler code here
	student = !student;
}
