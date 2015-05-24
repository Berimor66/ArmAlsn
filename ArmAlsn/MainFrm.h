
// MainFrm.h : ��������� ������ CMainFrame
//

#pragma once
#include "OutputWnd.h"
//#include "ViewPut.h"		// ������ �����������

class CMainFrame : public CFrameWndEx
{
	
protected: // ������� ������ �� ������������
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ��������
protected:
	CSplitterWnd m_wndSplitter;
public:
	//p
	CConfigAppDlg	m_ConfigAppDlg;
	CViewPut		m_ViewPut;
	CWnd pParent;
	// ��������
public:
protected:
	afx_msg LRESULT OnTok(WPARAM wParam, LPARAM lParam);

// ���������������
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ����������
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	void OnLanguageFirst(UINT nID);
	void OnUpdateLanguageFirst(CCmdUI *pCmdUI);
	CMFCStatusBar     m_wndStatusBar;

protected:  // ���������� ����� ������ ��������� ����������
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;

	CMFCToolBarImages m_UserImages;
	COutputWnd        m_wndOutput;
	void OnUpdateTime(CCmdUI *pCmdUI);

// ��������� ������� ����� ���������
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileClose();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	//p
	public:
	afx_msg void OnConfigApp();
	afx_msg LRESULT OnDialogCnfClose(WPARAM wParam, LRESULT lParam);
	afx_msg LRESULT OnIcon(WPARAM wp, LPARAM lp);
	afx_msg void OnHide();

	afx_msg void OnAppUp();
//	afx_msg void On32781();
	afx_msg void OnViewPut();
	afx_msg void OnDisco();


	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	// ������� ����� � ������ ���������
	void OnSetPaneText(CString txtstr);
	// ������� � ����� - �������
	void OnOutputDebugAddString(CString outputstr);
//	void OnLanguageFirst ( UINT nID ) ;
//	void OnUpdateLanguageFirst ( CCmdUI * pCmdUI );
//	afx_msg void OnUserChanged();
};


