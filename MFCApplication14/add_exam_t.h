#pragma once


// add_exam_t dialog

class add_exam_t : public CDialogEx
{
	DECLARE_DYNAMIC(add_exam_t)

public:
	add_exam_t(CWnd* pParent = NULL);   // standard constructor
	virtual ~add_exam_t();

// Dialog Data
	enum { IDD = t_add_exam };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
