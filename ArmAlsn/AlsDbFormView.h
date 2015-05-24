#pragma once
#include "AlsDbDoc.h"
#include "afxwin.h"


// представление формы CAlsDbFormView

class CAlsDbFormView : public CFormView
{
	

protected:
	public:
	DECLARE_DYNCREATE(CAlsDbFormView)
	CAlsDbFormView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CAlsDbFormView();

	// Атрибуты
public:
	CAlsDbDoc* GetDocument() const;

public:
	enum { IDD = IDD_ALSDBFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора

	DECLARE_MESSAGE_MAP()
public:
	// Список перегонов
	CComboBox m_Coupe;
	afx_msg void OnCbnSelchangeItinerary();
	// Список маршрутов
	CComboBox m_Itinerary;
	afx_msg void OnCbnKillfocusItinerary();
	CString m_strItinerary;
};


