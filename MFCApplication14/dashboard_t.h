#pragma once


// dashboard_t dialog

class dashboard_t : public CDialogEx
{
	DECLARE_DYNAMIC(dashboard_t)

public:
	dashboard_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~dashboard_t();

// Dialog Data
	enum { IDD = t_dashboard };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedAddcourse();
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
