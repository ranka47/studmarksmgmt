// dashboard_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "dashboard_t.h"
#include "afxdialogex.h"
#include "update_marks_t.h"
#include "login_ats.h"
#include "add_course_t.h"

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
END_MESSAGE_MAP()


// dashboard_t message handlers


void dashboard_t::OnBnClickedUpdate()
{
	// TODO: Add your control notification handler code here
	update_marks_t dlg;
	dlg.DoModal();
	GetOwner()->ShowWindow(FALSE);

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
	login_ats dlg;
	dlg.DoModal();
}
