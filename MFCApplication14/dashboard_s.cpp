// dashboard_s.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "dashboard_s.h"
#include "afxdialogex.h"
#include "view_marks_s.h"
#include "login_ats.h"
#include "result_s.h"
#include "ObjectDefinitions.h"

// dashboard_s dialog

IMPLEMENT_DYNAMIC(dashboard_s, CDialogEx)

dashboard_s::dashboard_s(CWnd* pParent /*=NULL*/)
	: CDialogEx(dashboard_s::IDD, pParent)
{

}

dashboard_s::~dashboard_s()
{
}

void dashboard_s::DoDataExchange(CDataExchange* pDX)
{
	extern long long int roll_number;
	CDialogEx::DoDataExchange(pDX);
	CStatic *label;
	label = new CStatic;
	CString quizz;
	quizz.Format(_T("%ld"),roll_number);
	label->Create(quizz, WS_CHILD | WS_VISIBLE, CRect( 180, 20,280,80), this, 90210);
	CComboBox *Majors = (CComboBox*)GetDlgItem(IDC_COMBO1);
	DatabaseWrapper *db = new DatabaseWrapper();
	int size; Course* courses = db->getCourses(roll_number, Person::STUDENT, &size);

	for (size_t i = 0; i < size; i++)
	{
		CString temp(courses[i].courseId.c_str());
		Majors->AddString(temp);
	}
	
}


BEGIN_MESSAGE_MAP(dashboard_s, CDialogEx)
	ON_BN_CLICKED(IDLOGOUT, &dashboard_s::OnBnClickedLogout)
	ON_BN_CLICKED(IDVIEW, &dashboard_s::OnBnClickedView)
	ON_BN_CLICKED(IDRESULT, &dashboard_s::OnBnClickedResult)
END_MESSAGE_MAP()


// dashboard_s message handlers


void dashboard_s::OnBnClickedLogout()
{
	// TODO: Add your control notification handler code here
	login_ats dlg;
	dlg.DoModal();
	EndDialog(0);
}


void dashboard_s::OnBnClickedView()
{
	// TODO: Add your control notification handler code here
	view_marks_s dlg;
	dlg.DoModal();
}


void dashboard_s::OnBnClickedResult()
{
	// TODO: Add your control notification handler code here
	//result_s dlg;
	//dlg.DoModal();
	AfxMessageBox(_T("The feature has not been added yet!"));
}
