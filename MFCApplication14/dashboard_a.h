#pragma once


// dashboard_a dialog

class dashboard_a : public CDialogEx
{
	DECLARE_DYNAMIC(dashboard_a)

public:
	dashboard_a(CWnd* pParent = NULL);   // standard constructor
	virtual ~dashboard_a();

// Dialog Data
	enum { IDD = a_dashboard };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedFaculty();
	afx_msg void OnBnClickedStudent();
	afx_msg void OnBnClickedLogout();
};
