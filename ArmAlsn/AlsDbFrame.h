#pragma once


// Фрейм CAlsDbFrame

class CAlsDbFrame : public CFrameWndEx
{
	DECLARE_DYNCREATE(CAlsDbFrame)
protected:
	CAlsDbFrame();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CAlsDbFrame();
	// Реализация
public:
	//virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
protected:  // встроенные члены панели элементов управления
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
//	COutputWnd        m_wndOutput;

	// Атрибуты
protected:
	CSplitterWnd m_wndSplitter;
	// Переопределение
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); //,CCreateContext* pContext);
};


