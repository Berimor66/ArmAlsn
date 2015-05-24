
// SrvrItem.cpp : ���������� ������ CArmAlsnSrvrItem
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� CArmAlsnSrvrItem

IMPLEMENT_DYNAMIC(CArmAlsnSrvrItem, COleServerItem)

CArmAlsnSrvrItem::CArmAlsnSrvrItem(CArmAlsnDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: �������� ��� ��� ������������ ������ ������������
	//  (��������, ���������� �������������� �������� ��� ������ ������ � ��������� ������ ��������)
}

CArmAlsnSrvrItem::~CArmAlsnSrvrItem()
{
	// TODO: �������� ��� �������
}

void CArmAlsnSrvrItem::Serialize(CArchive& ar)
{
	// CArmAlsnSrvrItem::Serialize ���������� ������� ������, ����
	//  ������� ���������� � ����� ������. ��� ����� ��������� �������������
	//  ����������� ��������� ������ OLE OnGetClipboardData. ��� ����������� ��������
	//  �� ��������� ������������� ������ ������������ � ������� Serialize
	//  ���������. � ������ ��������� ������ �������� ����������� �������������
	//  ��������� ����� ���������.

	if (!IsLinkedItem())
	{
		CArmAlsnDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL CArmAlsnSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// ����������� ����������, �������� ����� ��� ���, ������������ ������ ��������� ��������� �����������
	//  ��������. ��� ��������� ������ ���������, ��������
	//  DVASPECT_THUMBNAIL (����� ���������� OnDrawEx) ���
	//  ���������� OnGetExtent ������ ���� �������� �� ���������
	//  �������������� ���������.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CArmAlsnSrvrItem::OnGetExtent ���������� ��� ��������� �������� �
	//  �������� HIMETRIC ������ ��������. � ���������� �� ���������
	//  ������ ������������ ���������� ������.

	// TODO: �������� ���� ��������� ������

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC ������

	return TRUE;
}

BOOL CArmAlsnSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// ������� ���� ���, ���� �� ����������� rSize
	UNREFERENCED_PARAMETER(rSize);

	// TODO: ������� ����� ����������� � ��������
	//  (�������� ������ ��������� � ��������, ������������ �� OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: �������� ��� ���������. ����� ����, ��������� �������� HIMETRIC.
	//  ��� ������� ������������ � ��������� ���������� ��������� (pDC).

	// TODO: ����� ��������� ���������� ������� CArmAlsnCntrItem.

	// ��������� ��� �������� ������ ������� � ��������� ���������.

	// TODO: ������� ���� ��� ����� ���������� ������ ���� ���������

	CArmAlsnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;

	POSITION pos = pDoc->GetStartPosition();
	CArmAlsnCntrItem* pItem = DYNAMIC_DOWNCAST(CArmAlsnCntrItem, pDoc->GetNextClientItem(pos));
	if (pItem != NULL)
		pItem->Draw(pDC, CRect(10, 10, 1010, 1010));
	return TRUE;
}


// ����������� CArmAlsnSrvrItem

#ifdef _DEBUG
void CArmAlsnSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CArmAlsnSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

