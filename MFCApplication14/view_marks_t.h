#pragma once


// view_marks_t dialog

class view_marks_t : public CDialogEx
{
	DECLARE_DYNAMIC(view_marks_t)

public:
	view_marks_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~view_marks_t();

// Dialog Data
	enum { IDD = t_view_marks };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
