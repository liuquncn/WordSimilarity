// WordSimilarityDlg.h : header file
//

#if !defined(AFX_WORDSIMILARITYDLG_H__DF77027A_951E_4A16_8E0A_90C64616E659__INCLUDED_)
#define AFX_WORDSIMILARITYDLG_H__DF77027A_951E_4A16_8E0A_90C64616E659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CWordSimilarityDlg dialog

class CWordSimilarityDlg : public CDialog
{
	Hownet TheHownet;
// Construction
public:
	CWordSimilarityDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWordSimilarityDlg)
	enum { IDD = IDD_WORDSIMILARITY_DIALOG };
	CListBox	m_meaninglist2;
	CListBox	m_meaninglist1;
	CString	m_input1;
	CString	m_input2;
	CString	m_output;
	CString	m_alpha;
	CString	m_beta1;
	CString	m_beta2;
	CString	m_beta3;
	CString	m_beta4;
	CString	m_delta;
	CString	m_gama;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordSimilarityDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWordSimilarityDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSememeDistance();
	afx_msg void OnSememeSimilarity();
	afx_msg void OnSememeLookup();
	afx_msg void OnMeaningLookup();
	afx_msg void OnSememeLookup2();
	afx_msg void OnMeaningLookup2();
	afx_msg void OnMeaningSimilarity();
	afx_msg void OnWordSimilarity();
	afx_msg void OnInputInFile();
	afx_msg void OnMeaningLookupInFile();
	afx_msg void OnWordSimilarityInFile();
	afx_msg void OnKillfocusAlpha();
	afx_msg void OnKillfocusBeta1();
	afx_msg void OnKillfocusBeta2();
	afx_msg void OnKillfocusBeta3();
	afx_msg void OnKillfocusBeta4();
	afx_msg void OnKillfocusDelta();
	afx_msg void OnKillfocusGama();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDSIMILARITYDLG_H__DF77027A_951E_4A16_8E0A_90C64616E659__INCLUDED_)
