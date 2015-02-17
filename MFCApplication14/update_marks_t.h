#pragma once


// update_marks_t dialog

class update_marks_t : public CDialogEx
{
	DECLARE_DYNAMIC(update_marks_t)

public:
	update_marks_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~update_marks_t();

// Dialog Data
	enum { IDD = t_update_marks };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUpload();
	afx_msg void OnBnClickedChoosefile();
	CString course;
	int exam;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
};
