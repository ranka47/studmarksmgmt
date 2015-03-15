// dashboard_a.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "dashboard_a.h"
#include "afxdialogex.h"
#include "add_faculty_a.h"
#include "add_student_a.h"
#include "login_ats.h"


// dashboard_a dialog

IMPLEMENT_DYNAMIC(dashboard_a, CDialogEx)

dashboard_a::dashboard_a(CWnd* pParent /*=NULL*/)
	: CDialogEx(dashboard_a::IDD, pParent)
{

}

dashboard_a::~dashboard_a()
{
}

void dashboard_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dashboard_a, CDialogEx)
	
	ON_BN_CLICKED(IDFACULTY, &dashboard_a::OnBnClickedFaculty)
	ON_BN_CLICKED(IDSTUDENT, &dashboard_a::OnBnClickedStudent)
	ON_BN_CLICKED(IDLOGOUT, &dashboard_a::OnBnClickedLogout)
END_MESSAGE_MAP()


// dashboard_a message handlers




void dashboard_a::OnBnClickedFaculty()
{
	// TODO: Add your control notification handler code here
	add_faculty_a dlg;
	dlg.DoModal();
	GetOwner()->ShowWindow(FALSE);
}


void dashboard_a::OnBnClickedStudent()
{
	// TODO: Add your control notification handler code here
	add_student_a dlg;
	dlg.DoModal();
	GetOwner()->ShowWindow(FALSE);
}


void dashboard_a::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

BOOL dashboard_a::OnInitDialog()
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