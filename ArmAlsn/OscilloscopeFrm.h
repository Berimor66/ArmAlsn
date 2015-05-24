
// OscilloscopeFrm.h : ��������� ������ COscilloscopeFrm
//

#pragma once
#include "OutputWnd.h"
//#include "ViewPut.h"		// ������ �����������

class COscilloscopeFrm : public CFrameWndEx
{
	
protected: // ������� ������ �� ������������
public:
	COscilloscopeFrm();
	DECLARE_DYNCREATE(COscilloscopeFrm)

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

// ���������������
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ����������
public:
	virtual ~COscilloscopeFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	void OnLanguageFirst(UINT nID);
	void OnUpdateLanguageFirst(CCmdUI *pCmdUI);
public:
	CMFCStatusBar     m_wndStatusBar;
//static	CMFCStatusBar*     m_wndStatusBar1;

protected:  // ���������� ����� ������ ��������� ����������
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;

	CMFCToolBarImages m_UserImages;
	COutputWnd        m_wndOutput;

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
	// ����� � ������ ���������
	void OnSetStatusBar(int pos, CString m_text);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
