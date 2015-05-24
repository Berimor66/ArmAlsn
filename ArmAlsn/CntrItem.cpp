
// CntrItem.cpp : реализация класса CArmAlsnCntrItem
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "ArmAlsnView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// реализация CArmAlsnCntrItem

IMPLEMENT_SERIAL(CArmAlsnCntrItem, COleClientItem, 0)

CArmAlsnCntrItem::CArmAlsnCntrItem(CArmAlsnDoc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: добавьте код для одноразового вызова конструктора
}

CArmAlsnCntrItem::~CArmAlsnCntrItem()
{
	// TODO: добавьте код очистки
}

void CArmAlsnCntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// Во время редактирования элемента (либо по месту, либо когда он полностью открыт),
	//  отправляются уведомления OnChange об изменении состояния
	//  этого элемента или визуального изображения его содержимого.

	// TODO: сделайте элемент недопустимым посредством вызова UpdateAllViews
	//  (с указаниями, подходящими для вашего приложения)

	GetDocument()->UpdateAllViews(NULL);
		// обновите ВСЕ представления без указаний
}

BOOL CArmAlsnCntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// Во время активации по месту CArmAlsnCntrItem::OnChangeItemPosition
	//  вызывается сервером для изменения положения окна
	//  по месту. Обычно это возникает в случае, когда данные документа
	//  на сервере изменены таким образом, что изменяется его величина, либо в случае
	//  изменения размеров по месту.
	//
	// По умолчанию вызывается базовый класс, который вызывает
	//  COleClientItem::SetItemRects для перемещения элемента
	//  в новое положение.

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: обновите имеющийся кэш прямоугольника или величины

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

	// Во время активации по месту CArmAlsnCntrItem::OnGetItemPosition
	//  будет вызван для определения расположения этого элемента. Обычно этот 
	//  прямоугольник определяет текущее положение элемента по отношению к 
	//  представлению, используемому для активации. Чтобы получить это представление, вызовите 
	//  CArmAlsnCntrItem::GetActiveView.

	// TODO: возвратите правильный прямоугольник (в пикселах) в rPosition

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
    // Разрешить только один элемент активации по месту для одной рамки
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

	// Вызовите сначала базовый класс для чтения данных COleClientItem.
	// Поскольку при этом настраивается положение указателя m_pDocument, возвращенного из
	//  CArmAlsnCntrItem::GetDocument, рекомендуется сначала вызвать
	//  базовый класс Serialize.
	COleClientItem::Serialize(ar);

	// для хранения или извлечения данных, относящихся к CArmAlsnCntrItem
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

BOOL CArmAlsnCntrItem::CanActivate()
{
	// Режим редактирования по месту, когда сам сервер редактируется по месту,
	//  не работает и не поддерживается. Поэтому в этом случае
	//  активацию по месту следует отключить.
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

	// в противном случае используется поведение по умолчанию
	return COleClientItem::CanActivate();
}


// диагностика CArmAlsnCntrItem

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

