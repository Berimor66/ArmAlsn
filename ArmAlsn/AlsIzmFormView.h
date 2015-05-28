#pragma once
#include "afxwin.h"
//#include "OziExplorerMap.h"
//#include "oziapi.h"
#include "OziExplorerApi.h"

#include "ProgressCtrlX.h"


// представление формы CAlsIzmFormView

class CAlsIzmFormView : public CFormView
{
	DECLARE_DYNCREATE(CAlsIzmFormView)

protected:
	CAlsIzmFormView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CAlsIzmFormView();

public:
	enum { IDD = IDD_ALSIZMFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV


public:
	CComboBox m_Coupe;
	// Маршрут
	CComboBox m_Itinerary;
	CComboBox m_Obgect;
	CComboBox m_Obgect_old;


//	DWORD timer;
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnCbnSelchangeItineraryIzm();
	afx_msg void OnBnClickedStartIzm();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	///
protected:
	afx_msg LRESULT OnTok(WPARAM wParam, LPARAM lParam);

	////

//protected:
	// Ордината объекта от которого едем
	double m_PK_obgect_start;
	// Ордината объекта на который едем
	double m_PK_obgect;
	//Текущая ордината
	double m_PK_current;
	CString m_strPK_current;
	CMFCEditBrowseCtrl m_PK_current_Ctrl;
	CMFCEditBrowseCtrl m_TOK_current_Ctrl;
	CString m_strPK_n;
	CString m_strPK_k;
 	CString m_str_Latitude;
	CString m_str_Longitude;
	CString m_strTOK_current;
	//Текущий ток
	INT_PTR m_TOK;
	//Предыдущий ток
	INT_PTR m_TOK1;
	//Текущий км столб
	CString m_strStolbKm_current;
	//COziExplorerMap OziExplorer;  // Доступ к карте

	int  m_ozi; // Доступ к API OziExplorer

	// Добавляем CBrush* для хранения новой кисти фона edit controls.
	CFont  m_pObjFont;
	CFont  m_pObjFontTOK;

protected:
	CViewPut *put;
	CString sss, ssf;
	
	CFileException fe;
	CFile	FileTok;
	bool OpenFileTok(CString filename);
	bool WriteFileTok(CString filename);
	
	int m_CurSel; //INT_PTR
	afx_msg void OnBnClickedStik();


public:
	//afx_msg void OnEnChangePkVIzm();
	//CEdit 



	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
//	virtual BOOL DestroyWindow();
	afx_msg void OnOziMap();
	//afx_msg void OnOzimap();
//	COziExplorerMap OziExplorer; // Доступ к карте

	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	afx_msg void OnDestroy();
	CButton StartIzm;
	afx_msg void OnNMCustomdrawProgressH(NMHDR *pNMHDR, LRESULT *pResult);

	// Progress bar
	CProgressCtrlX	m_progressH;
	BOOL	m_fUseBrush;
	BOOL	m_fRubberBar;
	BOOL	m_fTiedText;
	BOOL	m_fVertText;
	int		m_nBorder;
	int		m_iTextMode;
	int		m_iProgressMode;
	int		m_nRange; //UINTdouble
	int 	m_nStepSize;
	UINT	m_nTailSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressBarTestDlg)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	//HICON m_hIcon;
	//CFont m_fontV;
	CFont m_fontH;
	int m_pos;
	BOOL m_inc;
	CBrush m_brBk;
	CBrush m_brBar;
	// Generated message map functions
	//{{AFX_MSG(CAlsIzmFormView)
	afx_msg void OnChangeRange();
	afx_msg void OnChangeStepsize();
	
	//}}AFX_MSG
	// Progress bar end
};


