
// Curs1Dlg.h : header file
//

#pragma once


// CCurs1Dlg dialog
class CCurs1Dlg : public CDialogEx
{
// Construction
public:
	CCurs1Dlg(CWnd* pParent = nullptr);	// standard constructor

	void UpdArea();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CURS1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT ID);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedMyLabel();
	CProgressCtrl ProgressBar;
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnStnClickedCountfigures();
};
