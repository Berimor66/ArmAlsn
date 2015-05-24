
// ArmAlsnDoc.cpp : реализация класса CArmAlsnDoc
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
	// Включите реализацию контейнера OLE
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

// Примечание. Добавлена поддержка для IID_IArmAlsn для поддержки привязки typesafe
//  из VBA. IID должен совпадать с GUID, который вложен в 
//  disp-интерфейс в файле .IDL.

// {BCBF38A5-7B4C-48E1-A0C8-0F05733A6AF3}
static const IID IID_IArmAlsn =
{ 0xBCBF38A5, 0x7B4C, 0x48E1, { 0xA0, 0xC8, 0xF, 0x5, 0x73, 0x3A, 0x6A, 0xF3 } };

BEGIN_INTERFACE_MAP(CArmAlsnDoc, COleServerDocEx)
	INTERFACE_PART(CArmAlsnDoc, IID_IArmAlsn, Dispatch)
END_INTERFACE_MAP()


// создание/уничтожение CArmAlsnDoc

CArmAlsnDoc::CArmAlsnDoc()
{
	// Используйте объединенные файлы OLE
	EnableCompoundFile();

	// TODO: добавьте код для одноразового вызова конструктора

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

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}


// реализация сервера CArmAlsnDoc

COleServerItem* CArmAlsnDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem вызывается рабочей средой для получения COleServerItem,
	//  который связан с этим документом. Вызывается при необходимости.

	CArmAlsnSrvrItem* pItem = new CArmAlsnSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}




// сериализация CArmAlsnDoc

void CArmAlsnDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}

	// Вызов базового класса COleServerDocEx включает сериализацию
	//  объектов COleClientItem документа контейнера.
	COleServerDocEx::Serialize(ar);
}


// диагностика CArmAlsnDoc

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


// команды CArmAlsnDoc
