#pragma once


// view_marks_s dialog

class view_marks_s : public CDialogEx
{
	DECLARE_DYNAMIC(view_marks_s)

public:
	view_marks_s(CWnd* pParent = NULL);   // standard constructor
	virtual ~view_marks_s();

// Dialog Data
	enum { IDD = s_view_marks };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnCbnSelchangeCombo1();
	CString course;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
};
