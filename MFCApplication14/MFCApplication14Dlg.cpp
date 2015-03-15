// MFCApplication14Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFCApplication14.h"
#include "MFCApplication14Dlg.h"
#include "afxdialogex.h"
#include "BasicExcel1.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "login_ats.h"
#include "ObjectDefinitions.h"

#define IDC_EDIT1
using namespace YExcel;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for App About



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCApplication14Dlg dialog



CMFCApplication14Dlg::CMFCApplication14Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication14Dlg::IDD, pParent)
	, test(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication14Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CMFCApplication14Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication14Dlg::OnBnClickedButton1)

	
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication14Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication14Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication14Dlg message handlers

BOOL CMFCApplication14Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Using built-in function for background image
	SetBackgroundImage(IDB_BITMAP1);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(hIcon, FALSE);			// Set big icon
	SetIcon(hIcon, TRUE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication14Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication14Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication14Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication14Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("Student Marks Management System: Software Engineering Lab Assignment 2"));

}


void CMFCApplication14Dlg::OnBnClickedButton2()
{
	/*DatabaseWrapper* db;
	db = new DatabaseWrapper();
	int quizWts[5] = { 20, 20, 20, 20, 20 };
	db->createCourse(5, "Chemistry", "ch101", 2015);
	db->createCourse(6, "Physics", "ph102", 2015);
	db->addPerson("chatto", 101010, Person::PROF);
	db->addPerson("jainam", 130101055, Person::STUDENT);
	db->addPerson("admin", 1, Person::ADMIN);
	db->addLoginDetails(1, "admin", Person::ADMIN);
	db->addPerson("ranka", 130101033, Person::STUDENT);
	db->linkPersonCourse(130101055, Person::STUDENT, "ch101");
	db->linkPersonCourse(130101033, Person::STUDENT, "ph102");
	db->linkPersonCourse(130101033, Person::STUDENT, "ch101");
	db->linkPersonCourse(101010, Person::PROF, "ch101");
	db->linkPersonCourse(101010, Person::PROF, "ph102");
	db->addLoginDetails(101010, "prof", Person::PROF);
	db->setQuizWeights("ch101", quizWts);
	int a = db->getQuizWeight(3, "ch101");
	db->setQuizMarks("ch101", 130101033, 3, 15);
	db->setQuizMarks("ch101", 130101055, 3, 17);
	Quiz *q = db->getQuizMarks("ch101", 3);
	Student* st = NULL;
	st = db->getCourseStudents("ch101", &a);
	db->addLoginDetails(130101033, "yomanas", Person::STUDENT);*/
	/*CString a("yomanas");
	db->checkLogin(130101033, "yomanas", Person::STUDENT);
	db->checkLogin(130101033, "yomanas", Person::STUDENT);
	
	Course *co = db->getStudentCourses(130101033, &a);
	string *cs = db->getCourseList(&a);	*/
	login_ats dlg;
	dlg.DoModal();
	
	// TODO: Add your control notification handler code here
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CMFCApplication14Dlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("Choose the Login option on the Main Screen to go to the Login page. From there, depending of the category of user, login to the respective dashboard. For more help, consult the technical manual"));
}
