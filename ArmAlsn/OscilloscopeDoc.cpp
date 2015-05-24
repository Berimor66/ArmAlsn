
// OscilloscopeDoc.cpp : реализация класса COscilloscopeDoc
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "OscilloscopeDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COscilloscopeDoc

IMPLEMENT_DYNCREATE(COscilloscopeDoc, CDocument)

BEGIN_MESSAGE_MAP(COscilloscopeDoc, CDocument)
	// Включите реализацию контейнера OLE
END_MESSAGE_MAP()


// Примечание. Добавлена поддержка для IID_IArmAlsn для поддержки привязки typesafe
//  из VBA. IID должен совпадать с GUID, который вложен в 
//  disp-интерфейс в файле .IDL.

// {BCBF38A5-7B4C-48E1-A0C8-0F05733A6AF3}
static const IID IID_IArmAlsn =
{ 0xBCBF38A5, 0x7B4C, 0x48E1, { 0xA0, 0xC8, 0xF, 0x5, 0x73, 0x3A, 0x6A, 0xF3 } };


// создание/уничтожение COscilloscopeDoc

COscilloscopeDoc::COscilloscopeDoc()
{

	// TODO: добавьте код для одноразового вызова конструктора



}

COscilloscopeDoc::~COscilloscopeDoc()
{
	
}

BOOL COscilloscopeDoc::OnNewDocument()
{

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}


// реализация сервера COscilloscopeDoc



// сериализация COscilloscopeDoc

void COscilloscopeDoc::Serialize(CArchive& ar)
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
}


// диагностика COscilloscopeDoc

#ifdef _DEBUG
void COscilloscopeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COscilloscopeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды COscilloscopeDoc
