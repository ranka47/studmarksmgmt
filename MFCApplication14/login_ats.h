#pragma once
#include "afxwin.h"


// login_ats dialog

class login_ats : public CDialogEx
{
	DECLARE_DYNAMIC(login_ats)

public:
	login_ats(CWnd* pParent = NULL);   // standard constructor
	virtual ~login_ats();

// Dialog Data
	enum { IDD = login };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();

	bool admin;
	bool prof;
	bool student;
	afx_msg void OnBnClickedAdmin();
	afx_msg void OnBnClickedFaculty();
	afx_msg void OnBnClickedStudent();
	LONGLONG roll_id;
	
	CString password_cstring;
	afx_msg void OnEnChangeUsername();
};
