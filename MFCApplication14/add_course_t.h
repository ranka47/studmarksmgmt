#pragma once


// add_course_t dialog

class add_course_t : public CDialogEx
{
	DECLARE_DYNAMIC(add_course_t)

public:
	add_course_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~add_course_t();

// Dialog Data
	enum { IDD = t_add_course };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int no_of_exams;
	CString coursename;
	CString coursenumber;
};
