
// ArmAlsnView.h : интерфейс класса CArmAlsnView
//


#pragma once

class CArmAlsnCntrItem;

class CArmAlsnView : public CView
{
protected: // создать только из сериализации
	CArmAlsnView();
	DECLARE_DYNCREATE(CArmAlsnView)

// Атрибуты
public:
	CArmAlsnDoc* GetDocument() const;
	// m_pSelection захватывает выделенную область в текущий CArmAlsnCntrItem.
	// Для многих приложений, такая переменная-член не достаточна для
	//  представления выделенной области, например в случае выделения не смежных областей или
	//  выделения объектов, которые не являются объектами CArmAlsnCntrItem. Данный способ выделения
	//  предоставляется с целью помощи начинающим

	// TODO: замените данный способ выделения в вашем приложении
	CArmAlsnCntrItem* m_pSelection;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Поддержка контейнера

// Реализация
public:
	virtual ~CArmAlsnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFilePrint();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnTok(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // отладочная версия в ArmAlsnView.cpp
inline CArmAlsnDoc* CArmAlsnView::GetDocument() const
   { return reinterpret_cast<CArmAlsnDoc*>(m_pDocument); }
#endif

