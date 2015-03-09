#pragma once


// add_faculty_a dialog

class add_faculty_a : public CDialogEx
{
	DECLARE_DYNAMIC(add_faculty_a)

public:
	add_faculty_a(CWnd* pParent = NULL);   // standard constructor
	virtual ~add_faculty_a();

// Dialog Data
	enum { IDD = a_add_faculty };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	CString facultyname;
	LONGLONG facultyid;
	afx_msg void OnEnChangeEdit1();
	
	afx_msg void OnBnClickedCancel3();
	CString t_password;
	afx_msg void OnBnClickedOk2();
};
