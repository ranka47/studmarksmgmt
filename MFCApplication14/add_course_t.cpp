// add_course_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_course_t.h"
#include "afxdialogex.h"


// add_course_t dialog

IMPLEMENT_DYNAMIC(add_course_t, CDialogEx)

add_course_t::add_course_t(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_course_t::IDD, pParent)
{

}

add_course_t::~add_course_t()
{
}

void add_course_t::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(add_course_t, CDialogEx)
	ON_BN_CLICKED(IDOK, &add_course_t::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &add_course_t::OnBnClickedButton1)
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
