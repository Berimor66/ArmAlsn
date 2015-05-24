
// MainFrm.h : интерфейс класса CMainFrame
//

#pragma once
#include "OutputWnd.h"
//#include "ViewPut.h"		// Диалог Ассимметрии

class CMainFrame : public CFrameWndEx
{
	
protected: // создать только из сериализации
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Атрибуты
protected:
	CSplitterWnd m_wndSplitter;
public:
	//p
	CConfigAppDlg	m_ConfigAppDlg;
	CViewPut		m_ViewPut;
	CWnd pParent;
	// Операции
public:
protected:
	afx_msg LRESULT OnTok(WPARAM wParam, LPARAM lParam);

// Переопределение
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	void OnLanguageFirst(UINT nID);
	void OnUpdateLanguageFirst(CCmdUI *pCmdUI);
	CMFCStatusBar     m_wndStatusBar;

protected:  // встроенные члены панели элементов управления
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;

	CMFCToolBarImages m_UserImages;
	COutputWnd        m_wndOutput;
	void OnUpdateTime(CCmdUI *pCmdUI);

// Созданные функции схемы сообщений
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
	// Вывести текст в строке состояния
	void OnSetPaneText(CString txtstr);
	// Выводим в вывод - отладка
	void OnOutputDebugAddString(CString outputstr);
//	void OnLanguageFirst ( UINT nID ) ;
//	void OnUpdateLanguageFirst ( CCmdUI * pCmdUI );
//	afx_msg void OnUserChanged();
};


