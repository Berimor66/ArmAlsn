
// ArmAlsnView.cpp : ���������� ������ CArmAlsnView
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "CntrItem.h"
#include "ArmAlsnView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT  WM_TOK = ::RegisterWindowMessage((LPCWSTR) L"MyMessage_TOK");
// CArmAlsnView

IMPLEMENT_DYNCREATE(CArmAlsnView, CView)

BEGIN_MESSAGE_MAP(CArmAlsnView, CView)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, &CArmAlsnView::OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, &CArmAlsnView::OnCancelEditCntr)
	ON_COMMAND(ID_FILE_PRINT, &CArmAlsnView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &CArmAlsnView::OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CArmAlsnView::OnFilePrintPreview)
	ON_REGISTERED_MESSAGE(WM_TOK, &CArmAlsnView::OnTok)
END_MESSAGE_MAP()

// ��������/����������� CArmAlsnView

CArmAlsnView::CArmAlsnView()
{
	m_pSelection = NULL;
	// TODO: �������� ��� ��������

}

CArmAlsnView::~CArmAlsnView()
{
}

BOOL CArmAlsnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs
	cs.cx=300;
	cs.cy=200;
	return CView::PreCreateWindow(cs);
}

// ��������� CArmAlsnView

void CArmAlsnView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CArmAlsnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �������� ����� ��� ��������� ��� ����������� ������
	// TODO: ����� ��������� ��� �������� OLE � ���������
		CRect rect(10, 10, 210, 210);
		pDC->DrawText(_T("������, ���"), -1, rect,
							DT_SINGLELINE | DT_CENTER | DT_VCENTER);


	// ��������� ���������� �������� � ������������ �����. ���� ��� ������ ����
	//  ������, ��������� ���������� ��� ���������. ��� ���������
	//  ����� ������������� ��������������, ������������� CArmAlsnCntrItem,
	//  ��� �������������� ����������� �������������� �� �����.


	// TODO: ������� ���� ��� ����� ���������� ������ ���� ���������.
	if (m_pSelection != NULL)
	{
		CSize size;
		
		if (m_pSelection->GetExtent(&size, m_pSelection->m_nDrawAspect))
		{
			pDC->HIMETRICtoLP(&size);
			rect.right = size.cx + 10;
			rect.bottom = size.cy + 10;
		}

		m_pSelection->Draw(pDC, rect);
	}

}

void CArmAlsnView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: ������� ���� ���, ����� ��������� ��� ������ ������ ����� �������
	m_pSelection = NULL;    // ������������� ���������

}


// ������ CArmAlsnView


void CArmAlsnView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CArmAlsnView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ���������� �� ���������
	return DoPreparePrinting(pInfo);
}

void CArmAlsnView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� �������������� ������������� ����� �������
}

void CArmAlsnView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �������� ������� ����� ������
}

void CArmAlsnView::OnDestroy()
{
	// ������������� ������� ��� ��������; ��� �����
	// � ������ ������������� ������������� �����������
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CView::OnDestroy();
}



// ������� � ��������� ������� OLE

BOOL CArmAlsnView::IsSelected(const CObject* pDocItem) const
{
	// ���������� ���� �����������, ���� ���������� �������� �������
	//  ������ �� �������� CArmAlsnCntrItem. ����� ��������� ����������
	//  ����������� ������ ������� �������� ����� ����������

	// TODO: ���������� ��� �������, ������� ��������� ��������� ������� ������� OLE

	return pDocItem == m_pSelection;
}

void CArmAlsnView::OnInsertObject()
{
	// �������� ����������� ���������� ���� "������� �������" ��� ��������� ����������
	//  ��� ������ ������� CArmAlsnCntrItem
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CArmAlsnCntrItem* pItem = NULL;
	TRY
	{
		// ������� ����� �������, ��������� � ���� ����������
		CArmAlsnDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CArmAlsnCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// ��������������� ������� �� ������ ����������� ����
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // ����� ���������� ��������
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// ��������� ������ ���������� ������������ ������������, ��� ������ ������� �����������
		//  ��������� � ��������� �������

		// TODO: ��������� ���������� ���������, ��� ��� ��������� � ����������
		m_pSelection = pItem;   // ��������� ���������� ������������ ��������
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// ��������� ���������� ������ ������������� ����������� ������������
//  ��������� ������������ ��� ������ ������ �������������� �� �����. �����
//  ��������� (�� ������) �������� �����������
void CArmAlsnView::OnCancelEditCntr()
{
	// �������� � ���� ������������� ��� �������� ������� �������������� �� �����
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// ��� ���������� ��������� ����������� ��������� OnSetFocus � OnSize,
//  ���� ������ ������������� �� �����
void CArmAlsnView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// ���������� ���������� ����� �� ���� ������, ���� �� ��������� � ��� �� �������������
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // �� ��������� ������� �����
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CArmAlsnView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

void CArmAlsnView::OnFilePrint()
{
	//�� ��������� ������ ��������� ��������� �������������
	//� ������� IOleCommandTarget. ���� ����� ��������� �� ���������,
	//������� ����� COleDocObjectItem::DoDefaultPrinting.
	//���� ����� ����� ��������� �� �����-���� �������, �� ��������� ����������
	//docobject � ������� ���������� IPrint.
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;
	
	CView::OnFilePrint();

}


void CArmAlsnView::OnRButtonUp(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);	 
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CArmAlsnView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	UNREFERENCED_PARAMETER(pWnd);
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

// ��������� ������� OLE

// ��������� ���������� ������ ������������� ����������� ������������
//  ��������� ������������ ��� ������ ������ �������������� �� �����. �����
//  ������ (�� ���������) �������� �����������
void CArmAlsnView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// ����������� CArmAlsnView

#ifdef _DEBUG
void CArmAlsnView::AssertValid() const
{
	CView::AssertValid();
}

void CArmAlsnView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArmAlsnDoc* CArmAlsnView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArmAlsnDoc)));
	return (CArmAlsnDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CArmAlsnView

afx_msg LRESULT CArmAlsnView::OnTok(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	AfxMessageBox(L"Tok ArmAlsnView");
	return 0;
}