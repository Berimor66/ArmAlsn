#pragma once
#include "AlsDbDoc.h"
#include "afxwin.h"


// ������������� ����� CAlsDbFormView

class CAlsDbFormView : public CFormView
{
	

protected:
	public:
	DECLARE_DYNCREATE(CAlsDbFormView)
	CAlsDbFormView();           // ���������� �����������, ������������ ��� ������������ ��������
	virtual ~CAlsDbFormView();

	// ��������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
protected:
	virtual void OnInitialUpdate(); // ���������� � ������ ��� ����� ������������

	DECLARE_MESSAGE_MAP()
public:
	// ������ ���������
	CComboBox m_Coupe;
	afx_msg void OnCbnSelchangeItinerary();
	// ������ ���������
	CComboBox m_Itinerary;
	afx_msg void OnCbnKillfocusItinerary();
	CString m_strItinerary;
};


