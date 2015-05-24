// DBVListView.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "DBVListView.h"


// CDBVListView

IMPLEMENT_DYNCREATE(CDBVListView, CFormView)

CDBVListView::CDBVListView()
	: CFormView(CDBVListView::IDD)
{

	EnableAutomation();
}

CDBVListView::~CDBVListView()
{
}

void CDBVListView::OnFinalRelease()
{
	// Когда будет освобождена последняя ссылка на объект автоматизации,
	// вызывается OnFinalRelease. Базовый класс автоматически
	// удалит объект. Перед вызовом базового класса добавьте
	// дополнительную очистку, необходимую вашему объекту.

	CFormView::OnFinalRelease();
}

void CDBVListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDBVListView, CFormView)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDBVListView, CFormView)
END_DISPATCH_MAP()

// Примечание: мы добавили поддержку для IID_IDBVListView, чтобы обеспечить безопасную с точки зрения типов привязку
//  из VBA. Этот IID должен соответствовать GUID, связанному с 
//  disp-интерфейсом в файле .IDL.

// {2853546B-F22C-4199-8CB4-AAFB4F1803AA}
static const IID IID_IDBVListView =
{ 0x2853546B, 0xF22C, 0x4199, { 0x8C, 0xB4, 0xAA, 0xFB, 0x4F, 0x18, 0x3, 0xAA } };

BEGIN_INTERFACE_MAP(CDBVListView, CFormView)
	INTERFACE_PART(CDBVListView, IID_IDBVListView, Dispatch)
END_INTERFACE_MAP()


// диагностика CDBVListView

#ifdef _DEBUG
void CDBVListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDBVListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CDBVListView
