
// ChildView.h : интерфейс класса CChildView
//


#pragma once




// окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
public:
	//p
	DWORD timer;
	//UINT uMessageID;
	HWND hOtherWnd,hOtherWnd1;// HWND  CWnd*
	HGDIOBJ pOldBitmap;
	HGDIOBJ pOldBitmap_imp;
	//HBITMAP specbmp;
	//CDC specdc;
// Операции
public:

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void PreSubclassWindow();
	afx_msg void OnCheckIzm();
	//afx_msg void OnWaveform();
	//afx_msg void OnForm3d();
	//afx_msg void OnLogFft();
	//afx_msg void OnNormFft();
	//afx_msg void OnUpdateWaveform(CCmdUI *pCmdUI);
	//afx_msg void OnViewMenuItems(UINT nID);
	//afx_msg void OnUpdateViewMenuItems(CCmdUI* pCmdUI);
};

