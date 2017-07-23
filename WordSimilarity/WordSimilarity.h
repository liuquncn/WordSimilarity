// WordSimilarity.h : main header file for the WORDSIMILARITY application
//

#if !defined(AFX_WORDSIMILARITY_H__DBF176D7_1D49_493E_9BB5_36378C1FA4DF__INCLUDED_)
#define AFX_WORDSIMILARITY_H__DBF176D7_1D49_493E_9BB5_36378C1FA4DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "..\\hownet\\hownet.h"

/////////////////////////////////////////////////////////////////////////////
// CWordSimilarityApp:
// See WordSimilarity.cpp for the implementation of this class
//

class CWordSimilarityApp : public CWinApp
{
public:
	CWordSimilarityApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordSimilarityApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWordSimilarityApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDSIMILARITY_H__DBF176D7_1D49_493E_9BB5_36378C1FA4DF__INCLUDED_)
