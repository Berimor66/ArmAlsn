
// ArmAlsnDoc.cpp : ���������� ������ CArmAlsnDoc
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CArmAlsnDoc

IMPLEMENT_DYNCREATE(CArmAlsnDoc, COleServerDocEx)

BEGIN_MESSAGE_MAP(CArmAlsnDoc, COleServerDocEx)
	// �������� ���������� ���������� OLE
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &COleServerDocEx::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, &COleServerDocEx::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, &COleServerDocEx::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &COleServerDocEx::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &COleServerDocEx::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CArmAlsnDoc, COleServerDocEx)
END_DISPATCH_MAP()

// ����������. ��������� ��������� ��� IID_IArmAlsn ��� ��������� �������� typesafe
//  �� VBA. IID ������ ��������� � GUID, ������� ������ � 
//  disp-��������� � ����� .IDL.

// {BCBF38A5-7B4C-48E1-A0C8-0F05733A6AF3}
static const IID IID_IArmAlsn =
{ 0xBCBF38A5, 0x7B4C, 0x48E1, { 0xA0, 0xC8, 0xF, 0x5, 0x73, 0x3A, 0x6A, 0xF3 } };

BEGIN_INTERFACE_MAP(CArmAlsnDoc, COleServerDocEx)
	INTERFACE_PART(CArmAlsnDoc, IID_IArmAlsn, Dispatch)
END_INTERFACE_MAP()


// ��������/����������� CArmAlsnDoc

CArmAlsnDoc::CArmAlsnDoc()
{
	// ����������� ������������ ����� OLE
	EnableCompoundFile();

	// TODO: �������� ��� ��� ������������ ������ ������������

	EnableAutomation();

	AfxOleLockApp();
}

CArmAlsnDoc::~CArmAlsnDoc()
{
	AfxOleUnlockApp();
}

BOOL CArmAlsnDoc::OnNewDocument()
{
	if (!COleServerDocEx::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}


// ���������� ������� CArmAlsnDoc

COleServerItem* CArmAlsnDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem ���������� ������� ������ ��� ��������� COleServerItem,
	//  ������� ������ � ���� ����������. ���������� ��� �������������.

	CArmAlsnSrvrItem* pItem = new CArmAlsnSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}




// ������������ CArmAlsnDoc

void CArmAlsnDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}

	// ����� �������� ������ COleServerDocEx �������� ������������
	//  �������� COleClientItem ��������� ����������.
	COleServerDocEx::Serialize(ar);
}


// ����������� CArmAlsnDoc

#ifdef _DEBUG
void CArmAlsnDoc::AssertValid() const
{
	COleServerDocEx::AssertValid();
}

void CArmAlsnDoc::Dump(CDumpContext& dc) const
{
	COleServerDocEx::Dump(dc);
}
#endif //_DEBUG


// ������� CArmAlsnDoc
