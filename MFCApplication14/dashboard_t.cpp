// dashboard_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "dashboard_t.h"
#include "afxdialogex.h"
#include "update_marks_t.h"
#include "login_ats.h"
#include "add_course_t.h"
#include "add_student_t.h"
#include "view_marks_t.h"

// dashboard_t dialog

IMPLEMENT_DYNAMIC(dashboard_t, CDialogEx)

dashboard_t::dashboard_t(CWnd* pParent /*=NULL*/)
	: CDialogEx(dashboard_t::IDD, pParent)
{

}

dashboard_t::~dashboard_t()
{
}

void dashboard_t::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(dashboard_t, CDialogEx)
	ON_BN_CLICKED(IDUPDATE, &dashboard_t::OnBnClickedUpdate)
	ON_BN_CLICKED(IDADDCOURSE, &dashboard_t::OnBnClickedAddcourse)
	ON_BN_CLICKED(IDLOGOUT, &dashboard_t::OnBnClickedLogout)
	ON_BN_CLICKED(IDC_BUTTON1, &dashboard_t::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &dashboard_t::OnBnClickedButton2)
END_MESSAGE_MAP()


// dashboard_t message handlers


void dashboard_t::OnBnClickedUpdate()
{
	// TODO: Add your control notification handler code here
	update_marks_t dlg;
	dlg.DoModal();

}


void dashboard_t::OnBnClickedAddcourse()
{
	// TODO: Add your control notification handler code here
	add_course_t dlg;
	dlg.DoModal();
}

void dashboard_t::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void dashboard_t::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	add_student_t dlg;
	dlg.DoModal();
}


void dashboard_t::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	view_marks_t dlg;
	dlg.DoModal();
}

BOOL dashboard_t::OnInitDialog()
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