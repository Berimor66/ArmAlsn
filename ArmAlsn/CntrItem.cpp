
// CntrItem.cpp : ���������� ������ CArmAlsnCntrItem
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "ArmAlsnView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� CArmAlsnCntrItem

IMPLEMENT_SERIAL(CArmAlsnCntrItem, COleClientItem, 0)

CArmAlsnCntrItem::CArmAlsnCntrItem(CArmAlsnDoc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: �������� ��� ��� ������������ ������ ������������
}

CArmAlsnCntrItem::~CArmAlsnCntrItem()
{
	// TODO: �������� ��� �������
}

void CArmAlsnCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// �� ����� �������������� �������� (���� �� �����, ���� ����� �� ��������� ������),
	//  ������������ ����������� OnChange �� ��������� ���������
	//  ����� �������� ��� ����������� ����������� ��� �����������.

	// TODO: �������� ������� ������������ ����������� ������ UpdateAllViews
	//  (� ����������, ����������� ��� ������ ����������)

	GetDocument()->UpdateAllViews(NULL);
		// �������� ��� ������������� ��� ��������
}

BOOL CArmAlsnCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// �� ����� ��������� �� ����� CArmAlsnCntrItem::OnChangeItemPosition
	//  ���������� �������� ��� ��������� ��������� ����
	//  �� �����. ������ ��� ��������� � ������, ����� ������ ���������
	//  �� ������� �������� ����� �������, ��� ���������� ��� ��������, ���� � ������
	//  ��������� �������� �� �����.
	//
	// �� ��������� ���������� ������� �����, ������� ��������
	//  COleClientItem::SetItemRects ��� ����������� ��������
	//  � ����� ���������.

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: �������� ��������� ��� �������������� ��� ��������

	return TRUE;
}

BOOL CArmAlsnCntrItem::OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow)
{
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, pFrameWnd);

	if (pMainFrame != NULL)
	{
		ASSERT_VALID(pMainFrame);
		return pMainFrame->OnShowPanes(bShow);
	}

	return FALSE;
}

void CArmAlsnCntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);

	// �� ����� ��������� �� ����� CArmAlsnCntrItem::OnGetItemPosition
	//  ����� ������ ��� ����������� ������������ ����� ��������. ������ ���� 
	//  ������������� ���������� ������� ��������� �������� �� ��������� � 
	//  �������������, ������������� ��� ���������. ����� �������� ��� �������������, �������� 
	//  CArmAlsnCntrItem::GetActiveView.

	// TODO: ���������� ���������� ������������� (� ��������) � rPosition

	CSize size;
	rPosition.SetRectEmpty();
	if (GetExtent(&size, m_nDrawAspect))
	{
		CArmAlsnView* pView = GetActiveView();
		ASSERT_VALID(pView);
		if (!pView)
			return;
		CDC *pDC = pView->GetDC();
		ASSERT(pDC);
		if (!pDC)
			return;
		pDC->HIMETRICtoLP(&size);
		rPosition.SetRect(10, 10, size.cx + 10, size.cy + 10);
	}
	else
		rPosition.SetRect(10, 10, 210, 210);
}

void CArmAlsnCntrItem::OnActivate()
{
    // ��������� ������ ���� ������� ��������� �� ����� ��� ����� �����
    CArmAlsnView* pView = GetActiveView();
    ASSERT_VALID(pView);
	if (!pView)
		return;
    COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
    if (pItem != NULL && pItem != this)
        pItem->Close();
    
    COleClientItem::OnActivate();
}

void CArmAlsnCntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CArmAlsnCntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// �������� ������� ������� ����� ��� ������ ������ COleClientItem.
	// ��������� ��� ���� ������������� ��������� ��������� m_pDocument, ������������� ��
	//  CArmAlsnCntrItem::GetDocument, ������������� ������� �������
	//  ������� ����� Serialize.
	COleClientItem::Serialize(ar);

	// ��� �������� ��� ���������� ������, ����������� � CArmAlsnCntrItem
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

BOOL CArmAlsnCntrItem::CanActivate()
{
	// ����� �������������� �� �����, ����� ��� ������ ������������� �� �����,
	//  �� �������� � �� ��������������. ������� � ���� ������
	//  ��������� �� ����� ������� ���������.
	CArmAlsnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	ASSERT_KINDOF(COleServerDoc, pDoc);
	if (!pDoc->IsKindOf(RUNTIME_CLASS(COleServerDoc)))
	{
		return FALSE;
	}
	if (pDoc->IsInPlaceActive())
		return FALSE;

	// � ��������� ������ ������������ ��������� �� ���������
	return COleClientItem::CanActivate();
}


// ����������� CArmAlsnCntrItem

#ifdef _DEBUG
void CArmAlsnCntrItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CArmAlsnCntrItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif

