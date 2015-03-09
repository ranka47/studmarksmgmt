#pragma once


// result_s dialog

class result_s : public CDialogEx
{
	DECLARE_DYNAMIC(result_s)

public:
	result_s(CWnd* pParent = NULL);   // standard constructor
	virtual ~result_s();

// Dialog Data
	enum { IDD = s_result };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
