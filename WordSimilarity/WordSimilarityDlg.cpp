// WordSimilarityDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "WordSimilarity.h"
#include "WordSimilarityDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordSimilarityDlg dialog

CWordSimilarityDlg::CWordSimilarityDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordSimilarityDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWordSimilarityDlg)
	m_input1 = _T("");
	m_input2 = _T("");
	m_output = _T("");
	m_alpha = _T("");
	m_beta1 = _T("");
	m_beta2 = _T("");
	m_beta3 = _T("");
	m_beta4 = _T("");
	m_delta = _T("");
	m_gama = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordSimilarityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordSimilarityDlg)
	DDX_Control(pDX, IDC_MEANING2, m_meaninglist2);
	DDX_Control(pDX, IDC_MEANING1, m_meaninglist1);
	DDX_Text(pDX, IDC_INPUT1, m_input1);
	DDX_Text(pDX, IDC_INPUT2, m_input2);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
	DDX_Text(pDX, IDC_ALPHA, m_alpha);
	DDX_Text(pDX, IDC_BETA1, m_beta1);
	DDX_Text(pDX, IDC_BETA2, m_beta2);
	DDX_Text(pDX, IDC_BETA3, m_beta3);
	DDX_Text(pDX, IDC_BETA4, m_beta4);
	DDX_Text(pDX, IDC_DELTA, m_delta);
	DDX_Text(pDX, IDC_GAMA, m_gama);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWordSimilarityDlg, CDialog)
	//{{AFX_MSG_MAP(CWordSimilarityDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEMEME_DISTANCE, OnSememeDistance)
	ON_BN_CLICKED(IDC_SEMEME_SIMILARITY, OnSememeSimilarity)
	ON_BN_CLICKED(IDC_SEMEME_LOOKUP, OnSememeLookup)
	ON_BN_CLICKED(IDC_MEANING_LOOKUP, OnMeaningLookup)
	ON_BN_CLICKED(IDC_SEMEME_LOOKUP2, OnSememeLookup2)
	ON_BN_CLICKED(IDC_MEANING_LOOKUP2, OnMeaningLookup2)
	ON_BN_CLICKED(IDC_MEANING_SIMILARITY, OnMeaningSimilarity)
	ON_BN_CLICKED(IDC_WORD_SIMILARITY, OnWordSimilarity)
	ON_BN_CLICKED(IDC_INPUT_IN_FILE, OnInputInFile)
	ON_BN_CLICKED(IDC_MEANING_LOOKUP_IN_FILE, OnMeaningLookupInFile)
	ON_BN_CLICKED(IDC_WORD_SIMILARITY_IN_FILE, OnWordSimilarityInFile)
	ON_EN_KILLFOCUS(IDC_ALPHA, OnKillfocusAlpha)
	ON_EN_KILLFOCUS(IDC_BETA1, OnKillfocusBeta1)
	ON_EN_KILLFOCUS(IDC_BETA2, OnKillfocusBeta2)
	ON_EN_KILLFOCUS(IDC_BETA3, OnKillfocusBeta3)
	ON_EN_KILLFOCUS(IDC_BETA4, OnKillfocusBeta4)
	ON_EN_KILLFOCUS(IDC_DELTA, OnKillfocusDelta)
	ON_EN_KILLFOCUS(IDC_GAMA, OnKillfocusGama)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordSimilarityDlg message handlers

BOOL CWordSimilarityDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	char parameter[20];
	sprintf(parameter,"%1.2f",Hownet::alpha); m_alpha=parameter;
	sprintf(parameter,"%1.2f",Hownet::beta1); m_beta1=parameter;
	sprintf(parameter,"%1.2f",Hownet::beta2); m_beta2=parameter;
	sprintf(parameter,"%1.2f",Hownet::beta3); m_beta3=parameter;
	sprintf(parameter,"%1.2f",Hownet::beta4); m_beta4=parameter;
	sprintf(parameter,"%1.2f",Hownet::gama); m_gama=parameter;
	sprintf(parameter,"%1.2f",Hownet::delta); m_delta=parameter;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWordSimilarityDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWordSimilarityDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWordSimilarityDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWordSimilarityDlg::OnSememeDistance() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int id1=TheHownet.getSememeID(m_input1);
	int id2=TheHownet.getSememeID(m_input2);
	if (id1==-1 || id2==-1)
	{
		m_output=((id1==-1)?m_input1:m_input2)+"：不是一个义原！";
		UpdateData(FALSE);
		return;
	}
	int i,par1=id1,par2=id2;
	i=m_meaninglist1.GetCount();
	while (i>0) { i--; m_meaninglist1.DeleteString(i); }
	while (true)
	{
		char sememetext[1024];
		Sememe sememe=TheHownet.getSememe(par1);
		sprintf(sememetext,"%d %s %s",par1,sememe.getEnglish().data(),sememe.getChinese().data());
		m_meaninglist1.AddString(sememetext);
		if (sememe.getIDparent()==par1) break;
		par1=sememe.getIDparent();
	}
	i=m_meaninglist2.GetCount();
	while (i>0) { i--; m_meaninglist2.DeleteString(i); }
	while (true)
	{
		char sememetext[1024];
		Sememe sememe=TheHownet.getSememe(par2);
		sprintf(sememetext,"%d %s %s",par2,sememe.getEnglish().data(),sememe.getChinese().data());
		m_meaninglist2.AddString(sememetext);
		if (sememe.getIDparent()==par2) break;
		par2=sememe.getIDparent();
	}
	int distance=TheHownet.getSememeDistance(id1,id2);
	char strdistance[10];
	itoa(distance,strdistance,10);
	m_output=strdistance;
	UpdateData(FALSE);
}

void CWordSimilarityDlg::OnSememeSimilarity() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int id1=TheHownet.getSememeID(m_input1);
	int id2=TheHownet.getSememeID(m_input2);
	if (id1==-1 || id2==-1)
	{
		m_output=((id1==-1)?m_input1:m_input2)+"：不是一个义原！";
		UpdateData(FALSE);
		return;
	}
	float similarity=TheHownet.getSememeSimilarity(id1,id2);
	char strsimilarity[100];
	sprintf(strsimilarity,"%f",similarity);
	m_output=strsimilarity;
	UpdateData(FALSE);
}

void CWordSimilarityDlg::OnSememeLookup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int id=TheHownet.getSememeID(m_input1);
	if (id==-1) m_output="没找到！";
	else
	{
		Sememe sememe=TheHownet.getSememe(id);
		char strid[10],stridparent[10];
		itoa(id,strid,10);
		itoa(sememe.getIDparent(),stridparent,10);
		m_output=(string(strid)+' '+sememe.getEnglish()+' '+sememe.getChinese()+' '+stridparent).data();\
		int i,par1=id,par2=id;
		i=m_meaninglist1.GetCount();
		while (i>0) { i--; m_meaninglist1.DeleteString(i); }
		while (true)
		{
			char sememetext[1024];
			Sememe sememe=TheHownet.getSememe(par1);
			sprintf(sememetext,"%d %s %s",par1,sememe.getEnglish().data(),sememe.getChinese().data());
			m_meaninglist1.AddString(sememetext);
			if (sememe.getIDparent()==par1) break;
			par1=sememe.getIDparent();
		}
	}
	UpdateData(false);
}

void CWordSimilarityDlg::OnSememeLookup2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int id=TheHownet.getSememeID(m_input2);
	if (id==-1) m_output="没找到！";
	else
	{
		Sememe sememe=TheHownet.getSememe(id);
		char strid[10],stridparent[10];
		itoa(id,strid,10);
		itoa(sememe.getIDparent(),stridparent,10);
		m_output=(string(strid)+' '+sememe.getEnglish()+' '+sememe.getChinese()+' '+stridparent).data();
		int i,par1=id,par2=id;
		i=m_meaninglist1.GetCount();
		while (i>0) { i--; m_meaninglist2.DeleteString(i); }
		while (true)
		{
			char sememetext[1024];
			Sememe sememe=TheHownet.getSememe(par2);
			sprintf(sememetext,"%d %s %s",par2,sememe.getEnglish().data(),sememe.getChinese().data());
			m_meaninglist2.AddString(sememetext);
			if (sememe.getIDparent()==par2) break;
			par2=sememe.getIDparent();
		}
	}
	UpdateData(false);

}

void CWordSimilarityDlg::OnMeaningLookup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	string word=m_input1;
	multimap<string,Meaning>::const_iterator iter;
	if (TheHownet.getMeaningIter(word,iter)==true)
	{
		Meaning meaning;
		int i=m_meaninglist1.GetCount();
		while (i>0) { i--; m_meaninglist1.DeleteString(i); }
		while (true)
		{
			meaning=TheHownet.getMeaningNext(word,iter);
			if (meaning.getPOS().empty()) break;
			m_meaninglist1.AddString((meaning.getPOS()+" "+meaning.getDEF()).data());
		}
	}
	else m_output="没找到！";
	UpdateData(false);
}

void CWordSimilarityDlg::OnMeaningLookup2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	string word=m_input2;
	multimap<string,Meaning>::const_iterator iter;
	if (TheHownet.getMeaningIter(word,iter)==true)
	{
		Meaning meaning;
		int i=m_meaninglist2.GetCount();
		while (i>0) { i--; m_meaninglist2.DeleteString(i); }
		while (true)
		{
			meaning=TheHownet.getMeaningNext(word,iter);
			if (meaning.getPOS().empty()) break;
			m_meaninglist2.AddString((meaning.getPOS()+" "+meaning.getDEF()).data());
		}
	}
	else m_output="没找到！";
	UpdateData(false);
}

void CWordSimilarityDlg::OnMeaningSimilarity() 
{
	// TODO: Add your control notification handler code here
	if (m_meaninglist1.GetCount()==0 || m_meaninglist2.GetCount()==0) return;
	UpdateData(TRUE);
	Meaning mn1,mn2;
	char meaning1[1024],meaning2[1024];
	int selected1=m_meaninglist1.GetCurSel();
	int selected2=m_meaninglist2.GetCurSel();
	if (selected1==LB_ERR) selected1=0;
	if (selected2==LB_ERR) selected2=0;
	m_meaninglist1.GetText(selected1,meaning1);
	m_meaninglist2.GetText(selected2,meaning2);
	TheHownet.readMeaning(mn1,meaning1);
	TheHownet.readMeaning(mn2,meaning2);
	float sim=TheHownet.getMeaningSimilarity(mn1,mn2);
	char simoutput[100];
	sprintf(simoutput,"%f",sim);
	m_output=simoutput;
	UpdateData(FALSE);
}

void CWordSimilarityDlg::OnWordSimilarity() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	float sim=TheHownet.getWordSimilarity(m_input1,m_input2);
	char simoutput[100];
	sprintf(simoutput,"%f",sim);
	m_output=simoutput;
	UpdateData(FALSE);
	
}

#include "..\\BasicModule\\function.h"
#include "..\\BasicModule\\code.h"
const char * FileNameWords="TestWords.Txt";
const char * FileNameMeanings="TestMeanings.Txt";
const char * FileNameSimilarities="TestSimilarities.Txt";

void CWordSimilarityDlg::OnInputInFile() 
{
	// TODO: Add your control notification handler code here
	ShellTextOpen(FileNameWords);
}

void CWordSimilarityDlg::OnMeaningLookupInFile() 
{
	// TODO: Add your control notification handler code here
	fstream filewords, filemeanings;
	filewords.open(FileNameWords,ios::in|ios::binary);
	filemeanings.open(FileNameMeanings,ios::out|ios::binary);
	char word[1024];
	while (!filewords.eof())
	{
		filewords.getline(word,1023);
		char * p0=word;
		while (*p0 && isSpcChar(p0)) goNext(p0);
		char * p1=p0;
		while (*p1 && !isSpcChar(p1)) goNext(p1);
		*p1=0;
		strcpy(word,p0);
		if (*word==0)
		{
			filemeanings << word << "\r\n";
			continue;
		}
		filemeanings << ":" << word << "\r\n";
		multimap<string,Meaning>::const_iterator iter;
		if (TheHownet.getMeaningIter(string(word),iter)==true)
		{
			Meaning meaning;
			while (true)
			{
				meaning=TheHownet.getMeaningNext(string(word),iter);
				if (meaning.getPOS().empty()) break;
				filemeanings << meaning.getPOS() << " " << meaning.getDEF() << "\r\n";
			}
		}
	}
	filewords.close();
	filemeanings.close();
	ShellTextOpen(FileNameMeanings);
}

void CWordSimilarityDlg::OnWordSimilarityInFile() 
{
	// TODO: Add your control notification handler code here
	fstream filemeanings, filesimilarities;
	filemeanings.open(FileNameMeanings,ios::in);
	filesimilarities.open(FileNameSimilarities,ios::out);
	while (!filemeanings.eof())
	{ // for each group of words
		char line[1024];
		map<string,set<Meaning> > dict;
		filemeanings.getline(line,1023);
		if (*line!=':') continue;
		while (*line==':')
		{ // for each word
			filesimilarities << line << endl;
			char word[128];
			strcpy(word,line+1);
			set<Meaning> meaningset;
			filemeanings.getline(line,1023);
			while (*line && *line!=':')
			{ // for each meaning
				filesimilarities << line << endl;
				Meaning meaning;
				TheHownet.readMeaning(meaning,line);
				meaningset.insert(meaning);
				filemeanings.getline(line,1023);
			}
			dict.insert(pair<string,set<Meaning> >(word,meaningset));
		}
		filesimilarities << "------------------------------------------" << endl;
		map<string,set<Meaning> >::iterator iter1,iter2;
		for (iter1=dict.begin();iter1!=dict.end();iter1++)
		{
			for (iter2=iter1,iter2++;iter2!=dict.end();iter2++)
			{
				float sim=TheHownet.getMeaningSetSimilarity(iter1->second,iter2->second);
				filesimilarities << iter1->first << ','
								 << iter2->first << ':'
								 << sim << endl;
			}
		}
		filesimilarities << "===================================================" << endl;
	}
	filemeanings.close();
	filesimilarities.close();
	ShellTextOpen(FileNameSimilarities);
}

void CWordSimilarityDlg::OnKillfocusAlpha() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::alpha=atof(m_alpha);	
}

void CWordSimilarityDlg::OnKillfocusBeta1() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::beta1=atof(m_beta1);	
}

void CWordSimilarityDlg::OnKillfocusBeta2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::beta2=atof(m_beta2);	
}

void CWordSimilarityDlg::OnKillfocusBeta3() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::beta3=atof(m_beta3);	
}

void CWordSimilarityDlg::OnKillfocusBeta4() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::beta4=atof(m_beta4);	
}

void CWordSimilarityDlg::OnKillfocusDelta() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::delta=atof(m_delta);
}

void CWordSimilarityDlg::OnKillfocusGama() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Hownet::gama=atof(m_gama);
}
