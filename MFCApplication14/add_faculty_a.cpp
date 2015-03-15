// add_faculty_a.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_faculty_a.h"
#include "afxdialogex.h"
#include "ObjectDefinitions.h"


// add_faculty_a dialog

IMPLEMENT_DYNAMIC(add_faculty_a, CDialogEx)

add_faculty_a::add_faculty_a(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_faculty_a::IDD, pParent)
	, facultyname(_T(""))
	, facultyid()
	, t_password(_T(""))
{

}

add_faculty_a::~add_faculty_a()
{
}

void add_faculty_a::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, facultyname);
	DDX_Text(pDX, IDC_EDIT1, facultyid);
	DDX_Text(pDX, IDC_PASSWORD, t_password);
	DDV_MaxChars(pDX, t_password, 32);
}


BEGIN_MESSAGE_MAP(add_faculty_a, CDialogEx)
	
	ON_EN_CHANGE(IDC_EDIT1, &add_faculty_a::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL3, &add_faculty_a::OnBnClickedCancel3)
	ON_BN_CLICKED(IDOK2, &add_faculty_a::OnBnClickedOk2)
END_MESSAGE_MAP()


// add_faculty_a message handlers


static string ConvertToString(CString a)
{
	const size_t newsizew = (a.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, a, _TRUNCATE);
	string t(nstringw);

	return t;
}






void add_faculty_a::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void add_faculty_a::OnBnClickedCancel3()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void add_faculty_a::OnBnClickedOk2()
{
	// TODO: Add your control notification handler code here
	CString facultynamevar; long long int facultyidvar;

	UpdateData();
	facultynamevar = facultyname;
	int len = facultynamevar.GetLength();
	facultyidvar = facultyid;
	int flag = 0;
	string dummy = ConvertToString(facultynamevar).c_str();
	char *tmp = (char*)dummy.c_str();
	for (int i = 0; i < len; i++)
	{
		if (!isalpha(tmp[i]) && tmp[i] != ' ')
		{
			AfxMessageBox(_T("Enter proper Name (albhabets only)"));
			flag = 1;
			return;
		}
	}
	if (facultynamevar != "" && flag == 0 && facultyidvar >= 100000 && facultyidvar <= 999999)
	{
		UpdateData();
		CString password = t_password;
		UpdateData(FALSE);
		const size_t newsizew = (facultynamevar.GetLength() + 1) * 2;
		char *nstringw = new char[newsizew];
		size_t convertedCharsw = 0;
		wcstombs_s(&convertedCharsw, nstringw, newsizew, facultynamevar, _TRUNCATE);
		facultyidvar = facultyid;
		DatabaseWrapper *pr = new DatabaseWrapper();
		pr->addPerson(nstringw, facultyidvar, Person::PROF);
		pr->addLoginDetails(facultyidvar, ConvertToString(password), Person::PROF);
		AfxMessageBox(_T("Faculty added successfully!!!"));
		EndDialog(0);
	}
	else if (facultynamevar == "" || facultyidvar < 100000 || facultyidvar >= 999999 || facultynamevar == " ")
	{
		AfxMessageBox(_T("Please fill properly before submitting. ID should be 6 digits long. Name and password are required fields."));
	}
	UpdateData(FALSE);
}

BOOL add_faculty_a::OnInitDialog()
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