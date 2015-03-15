#pragma once


// add_student_a dialog

class add_student_a : public CDialogEx
{
	DECLARE_DYNAMIC(add_student_a)

public:
	add_student_a(CWnd* pParent = NULL);   // standard constructor
	virtual ~add_student_a();

// Dialog Data
	enum { IDD = a_add_student };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString studentname;
	LONGLONG studentid;
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnBnClickedCancel();
	CString s_password;
	afx_msg void OnEnChangePassword();
	afx_msg void OnEnChangeEdit3();
};
