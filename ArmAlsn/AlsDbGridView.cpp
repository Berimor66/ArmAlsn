// AlsDbGridView.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "AlsDbGridView.h"


// CAlsDbGridView

IMPLEMENT_DYNCREATE(CAlsDbGridView, CListView)

CAlsDbGridView::CAlsDbGridView()
{

}

CAlsDbGridView::~CAlsDbGridView()
{
}

BEGIN_MESSAGE_MAP(CAlsDbGridView, CListView)
END_MESSAGE_MAP()


// диагностика CAlsDbGridView

#ifdef _DEBUG
void CAlsDbGridView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CAlsDbGridView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CAlsDbGridView
