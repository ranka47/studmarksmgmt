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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString studentname;
	LONGLONG studentid;
	afx_msg void OnBnClickedOk();
};
