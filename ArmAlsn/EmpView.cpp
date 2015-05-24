// EmpView.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "EmpView.h"


// CEmpView

IMPLEMENT_DYNCREATE(CEmpView, CListView)

CEmpView::CEmpView()
{

}

CEmpView::~CEmpView()
{
}

BEGIN_MESSAGE_MAP(CEmpView, CListView)
END_MESSAGE_MAP()


// диагностика CEmpView

#ifdef _DEBUG
void CEmpView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CEmpView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CEmpView
