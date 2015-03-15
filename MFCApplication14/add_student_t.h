#pragma once


// add_student_t dialog

class add_student_t : public CDialogEx
{
	DECLARE_DYNAMIC(add_student_t)

public:
	add_student_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~add_student_t();

// Dialog Data
	enum { IDD = t_add_student };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString crc;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChoosefile();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedUpload();
	afx_msg void OnBnClickedBack();
};
