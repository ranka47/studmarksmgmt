// add_student_a.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_student_a.h"
#include "afxdialogex.h"


// add_student_a dialog

IMPLEMENT_DYNAMIC(add_student_a, CDialogEx)

add_student_a::add_student_a(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_student_a::IDD, pParent)
{

}

add_student_a::~add_student_a()
{
}

void add_student_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(add_student_a, CDialogEx)
END_MESSAGE_MAP()


// add_student_a message handlers
