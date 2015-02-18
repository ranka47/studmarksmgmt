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
	login_ats dlg;
	dlg.DoModal();
}
