// add_student_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "add_student_t.h"
#include "afxdialogex.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "BasicExcel1.h"
#include "ObjectDefinitions.h"
#include "login_ats.h"

CString crName(""), path2;
int fileUpload = 0;

// add_student_t dialog

IMPLEMENT_DYNAMIC(add_student_t, CDialogEx)

static string ConvertToString(CString a)
{
	const size_t newsizew = (a.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, a, _TRUNCATE);
	string t(nstringw);

	return t;
}

add_student_t::add_student_t(CWnd* pParent /*=NULL*/)
	: CDialogEx(add_student_t::IDD, pParent)
{

}

add_student_t::~add_student_t()
{
}

void add_student_t::DoDataExchange(CDataExchange* pDX)
{
	extern long long int roll_number;
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, crc);
	CComboBox *Majors = (CComboBox*)GetDlgItem(IDC_COMBO1);
	DatabaseWrapper *db = new DatabaseWrapper();
	int size; Course* courses = db->getCourses(roll_number, Person::PROF, &size);

	for (size_t i = 0; i < size; i++)
	{
		CString temp(courses[i].courseId.c_str());
		Majors->AddString(temp);
	}
}


BEGIN_MESSAGE_MAP(add_student_t, CDialogEx)
	ON_BN_CLICKED(IDCHOOSEFILE, &add_student_t::OnBnClickedChoosefile)
	ON_CBN_SELCHANGE(IDC_COMBO1, &add_student_t::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDUPLOAD, &add_student_t::OnBnClickedUpload)
	ON_BN_CLICKED(IDC_BACK, &add_student_t::OnBnClickedBack)
END_MESSAGE_MAP()


// add_student_t message handlers


void add_student_t::OnBnClickedChoosefile()
{
	// TODO: Add your control notification handler code here
	TCHAR filtri[] = _T("CSV files (*.csv)|*.csv||");

	if (crName == "")
	{
		CString strErrorMsg;
		strErrorMsg.Format(_T("Please choose course before uploading file"));
		AfxMessageBox(strErrorMsg);
		return;
	}

	CFileDialog dlg(TRUE, _T("csv"), _T("*.csv"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filtri);
	dlg.m_ofn.lpstrTitle = _T("Open...");

	if (dlg.DoModal() == IDOK) //OK
	{
		path2 = dlg.GetPathName();
		//
		CStdioFile readFile;
		CFileException fileException;
		CString strLine;

		if (readFile.Open(path2, CFile::modeRead, &fileException))
		{
			while (readFile.ReadString(strLine))
			{
				fileUpload = 1;
				GetDlgItem(IDUPLOAD)->EnableWindow(TRUE);
				GetDlgItem(IDCHOOSEFILE)->EnableWindow(FALSE);
			}
		}
		else
		{
			CString strErrorMsg;
			strErrorMsg.Format(_T("Can't open file %s , error : %u"), crName, fileException.m_cause);
			AfxMessageBox(strErrorMsg);
			fileUpload = 0;
		}
		readFile.Close();
	}
}


void add_student_t::OnCbnSelchangeCombo1()
{
	CComboBox *corid = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int selIndex = corid->GetCurSel();
	CString name;
	corid->GetLBText(selIndex, name);
	crName = name;
}


void add_student_t::OnBnClickedUpload()
{
	if (fileUpload == 1)
	{
		DatabaseWrapper *db = new DatabaseWrapper();
		// TODO: Add your control notification handler code here
		ifstream in(path2);
		string line, field;

		int i; int error = 0;
		while (getline(in, line))    // get next line in file
		{
			i = 0;
			long long int temp1 = 0;
			stringstream ss(line);
			while (getline(ss, field, ','))  // break line into comma delimitted fields
			{
				if (field != "")
				{
					if (!i)
					{	stringstream(field) >> temp1;	i++;	}					
					else
					{
						error = 1;
						AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
						return;
					}					
				}
				else
				{
					error = 1;
					AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
				}				
			}
			string t((CStringA)crName);
			if (temp1 < 100000000 || temp1 > 999999999)
			{
				error = 1;
				AfxMessageBox(_T("Roll number %ld found. The roll number should be 9 digits long."), temp1);
				continue;
			}
			if (!db->linkPersonCourse(temp1, Person::STUDENT, t))
			{
				error = 1;
				CString err("");
				err.Format(_T("Unable to add roll number %ld to the file"), temp1);
				AfxMessageBox(err);
			}
		}
		if (error == 0)
			AfxMessageBox(_T("File Uploaded Successfully."));
		else
			AfxMessageBox(_T("File Uploaded with some errors."));
		GetDlgItem(IDUPLOAD)->EnableWindow(FALSE);
		GetDlgItem(IDCHOOSEFILE)->EnableWindow(TRUE);
	}
	else AfxMessageBox(_T("No File Chosen for uploading"));
}


void add_student_t::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}

BOOL add_student_t::OnInitDialog()
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