#pragma once


// dashboard_s dialog

class dashboard_s : public CDialogEx
{
	DECLARE_DYNAMIC(dashboard_s)

public:
	dashboard_s(CWnd* pParent = NULL);   // standard constructor
	virtual ~dashboard_s();

// Dialog Data
	enum { IDD = s_dashboard };

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogout();
	afx_msg void OnBnClickedView();
	afx_msg void OnBnClickedResult();
	afx_msg void OnCbnSelchangeCombo1();
};
