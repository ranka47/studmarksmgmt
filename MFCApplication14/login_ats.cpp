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
	ON_EN_CHANGE(IDC_USERNAME, &login_ats::OnEnChangeUsername)
END_MESSAGE_MAP()


void login_ats::OnBnClickedLogin()
{
	bool login_allowed = FALSE;
	DatabaseWrapper *db = new DatabaseWrapper();
	Person type=Person::NONE;
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
	if (type != Person::NONE)
	{

		if (login_allowed == TRUE)
		{
			roll_number = roll_id;
			if (type == Person::ADMIN)
			{
				dashboard_a admin;
				admin.DoModal();

				EndDialog(0);
			}
			else if (type == Person::PROF)
			{
				dashboard_t prof;
				prof.DoModal();

				EndDialog(0);
			}
			else
			{
				dashboard_s student;
				student.DoModal();

				EndDialog(0);
			}
		}
		else
			MessageBox(_T("Enter valid username and password"));

		delete db;
	}
	}


void login_ats::OnBnClickedAdmin()
{
	// TODO: Add your control notification handler code here
	admin = TRUE;
	prof = FALSE;
	student = FALSE;
}


void login_ats::OnBnClickedFaculty()
{
	// TODO: Add your control notification handler code here
	admin = FALSE;
	prof = TRUE;
	student = FALSE;
}


void login_ats::OnBnClickedStudent()
{
	// TODO: Add your control notification handler code here
	admin = FALSE;
	prof = FALSE;
	student = TRUE;
}

BOOL login_ats::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	GetDlgItem(IDC_USERNAME)->SetWindowTextW(L" ");
	// TODO: Add extra initialization here
	//Using built-in function for background image
	SetBackgroundImage(IDB_BITMAP1);
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);			// Set big icon
	SetIcon(hIcon, TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void login_ats::OnEnChangeUsername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
