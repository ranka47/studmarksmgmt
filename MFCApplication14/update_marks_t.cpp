// update_marks_t.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication14.h"
#include "update_marks_t.h"
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


CString path, cName;
int qNum=-1;

// update_marks_t dialog

IMPLEMENT_DYNAMIC(update_marks_t, CDialogEx)

update_marks_t::update_marks_t(CWnd* pParent /*=NULL*/)
: CDialogEx(update_marks_t::IDD, pParent)
, course(_T(""))
, exam(0)
{
	
}
update_marks_t::~update_marks_t()
{
}
int file_upload = 0;

static string ConvertToString(CString a)
{
	const size_t newsizew = (a.GetLength() + 1) * 2;
	char *nstringw = new char[newsizew];
	size_t convertedCharsw = 0;
	wcstombs_s(&convertedCharsw, nstringw, newsizew, a, _TRUNCATE);
	string t(nstringw);

	return t;
}

void update_marks_t::DoDataExchange(CDataExchange* pDX)
{
	extern long long int roll_number;
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, course);
	DDX_CBIndex(pDX, IDC_COMBO2, exam);
	CComboBox *Majors = (CComboBox*)GetDlgItem(IDC_COMBO1);
	DatabaseWrapper *db = new DatabaseWrapper();
	int size; Course* courses = db->getCourses(roll_number, Person::PROF, &size);
	
	for (size_t i = 0; i < size; i++)
	{
		CString temp(courses[i].courseId.c_str());
		Majors->AddString(temp);
	}	
}


BEGIN_MESSAGE_MAP(update_marks_t, CDialogEx)
	ON_BN_CLICKED(IDUPLOAD, &update_marks_t::OnBnClickedUpload)
	ON_BN_CLICKED(IDCHOOSEFILE, &update_marks_t::OnBnClickedChoosefile)
	ON_BN_CLICKED(IDC_BACK, &update_marks_t::OnBnClickedBack)
	ON_CBN_SELCHANGE(IDC_COMBO2, &update_marks_t::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &update_marks_t::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// update_marks_t message handlers

void update_marks_t::OnBnClickedChoosefile()
{
	// TODO: Add your control notification handler code here
	TCHAR filtri[] = _T("CSV files (*.csv)|*.csv||");


	CFileDialog dlg(TRUE, _T("csv"), _T("*.csv"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filtri);
	dlg.m_ofn.lpstrTitle = _T("Open...");

	if (dlg.DoModal() == IDOK) //OK
	{
		path = dlg.GetPathName();
		//
		CStdioFile readFile;
		CFileException fileException;
		CString strLine;

		if (readFile.Open(path, CFile::modeRead, &fileException))
		{
			while (readFile.ReadString(strLine))
			{
				file_upload = 1;
				GetDlgItem(IDUPLOAD)->EnableWindow(TRUE);
				GetDlgItem(IDCHOOSEFILE)->EnableWindow(FALSE);
			}
		}
		else
		{
			CString strErrorMsg;
			strErrorMsg.Format(_T("Can't open file %s , error : %u"), path, fileException.m_cause);
			AfxMessageBox(strErrorMsg);
			file_upload = 0;
		}
		readFile.Close();
	}
}

void update_marks_t::OnBnClickedUpload()
{
	if (file_upload == 1)
	{
		DatabaseWrapper *db = new DatabaseWrapper();
		// TODO: Add your control notification handler code here
		ifstream in(path);
		string line, field;

		vector<long long int> rollno;  // the 2D array
		vector<int> marks;                // array of values for one line only
		int i; int error = 0;
		while (getline(in, line))    // get next line in file
		{
			i = 0;
			int temp1 = 0, temp2 = 101;
			stringstream ss(line);
			while (getline(ss, field, ','))  // break line into comma delimitted fields
			{
				if (field != "")
				{
					if (i == 0)
					{
						//int temp1;
						stringstream(field) >> temp1;
						rollno.push_back(temp1);  // add each field to the 1D array
						i = i + 1;
						/*cout << temp1 << "\n";*/
					}
					else if (i == 1)
					{
						//int temp2;
						stringstream(field) >> temp2;
						marks.push_back(temp2);  // add each field to the 1D array
						i = i + 1;
						/*cout << temp2 << endl;*/
					}
					else
					{
						error = 1;
						AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
					}
					//error
				}
				else
				{
					error = 1;
					AfxMessageBox(_T("Sorry!!File is in wrong format..Please Re-Upload"));
				}
				//error
			}
			string t((CStringA)cName);
			if (t == "" || qNum == -1)
			{
				error = 1;
				AfxMessageBox(_T("Sorry!! Please select valid quiz and course number"));
				return;
			}
			int maxWeight = db->getQuizWeight(qNum, t);
			if (temp2 > maxWeight || maxWeight < 0) // NEGATIVE MARKING ALLOWED!! || temp2 < 0)
			{
				error = 1;
				CString a("");
				a.Format(_T("Marks for student %d exceed maximum marks %d....skipping writing to file"), temp1, maxWeight);
				AfxMessageBox(a);
				continue;
			}
			db->setQuizMarks(t, temp1, qNum, temp2);
			// LINK BOTH COURSE AND EXAM
		}
		if (error == 0)
		{
			AfxMessageBox(_T("File Uploaded Successfully."));
			EndDialog(0);
		}
	}
	else AfxMessageBox(_T("No File Chosen for uploading"));
}






void update_marks_t::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	EndDialog(0);
}


void update_marks_t::OnCbnSelchangeCombo2()
{
	CComboBox *corid2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	qNum = corid2->GetCurSel() + 1;
	GetDlgItem(IDCHOOSEFILE)->EnableWindow(TRUE);
}


void update_marks_t::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	DatabaseWrapper *db = new DatabaseWrapper();
	CComboBox *corid = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CComboBox *corid2 = (CComboBox*)GetDlgItem(IDC_COMBO2);
	int selIndex = corid->GetCurSel();
	CString name;
	corid->GetLBText(selIndex, name);
	cName = name;
	int size2 = db->getNumberQuiz(ConvertToString(name));

	//DatabaseWrapper *db = new DatabaseWrapper();
	//	int size; Course* courses = db->getCourses(roll_number, Person::PROF, &size);
	corid2->ResetContent();
	for (size_t i = 0; i < size2; i++)
	{
		CString temp;
		temp.Format(_T("Quiz %d"), i + 1);
		corid2->AddString(temp);
	}
	delete db;
}

BOOL update_marks_t::OnInitDialog()
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