
// ArmAlsnView.h : ��������� ������ CArmAlsnView
//


#pragma once

class CArmAlsnCntrItem;

class CArmAlsnView : public CView
{
protected: // ������� ������ �� ������������
	CArmAlsnView();
	DECLARE_DYNCREATE(CArmAlsnView)

// ��������
public:
	CArmAlsnDoc* GetDocument() const;
	// m_pSelection ����������� ���������� ������� � ������� CArmAlsnCntrItem.
	// ��� ������ ����������, ����� ����������-���� �� ���������� ���
	//  ������������� ���������� �������, �������� � ������ ��������� �� ������� �������� ���
	//  ��������� ��������, ������� �� �������� ��������� CArmAlsnCntrItem. ������ ������ ���������
	//  ��������������� � ����� ������ ����������

	// TODO: �������� ������ ������ ��������� � ����� ����������
	CArmAlsnCntrItem* m_pSelection;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���������� � ������ ��� ����� ������������
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// ��������� ����������

// ����������
public:
	virtual ~CArmAlsnView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
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

#ifndef _DEBUG  // ���������� ������ � ArmAlsnView.cpp
inline CArmAlsnDoc* CArmAlsnView::GetDocument() const
   { return reinterpret_cast<CArmAlsnDoc*>(m_pDocument); }
#endif

