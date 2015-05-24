
// IpFrame.h : интерфейс класса CInPlaceFrame
//

#pragma once

class CInPlaceFrame : public COleIPFrameWndEx
{
	DECLARE_DYNCREATE(CInPlaceFrame)
public:
	CInPlaceFrame();

// Атрибуты
public:

// Операции
public:

// Переопределение
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CInPlaceFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolBar    m_wndToolBar;
	COleDropTarget	m_dropTarget;
	COleResizeBar   m_wndResizeBar;

// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


