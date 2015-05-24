
// SrvrItem.cpp : реализация класса CArmAlsnSrvrItem
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "ArmAlsnDoc.h"
#include "SrvrItem.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// реализация CArmAlsnSrvrItem

IMPLEMENT_DYNAMIC(CArmAlsnSrvrItem, COleServerItem)

CArmAlsnSrvrItem::CArmAlsnSrvrItem(CArmAlsnDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: добавьте код для одноразового вызова конструктора
	//  (например, добавление дополнительных форматов для буфера обмена в источнике данных элемента)
}

CArmAlsnSrvrItem::~CArmAlsnSrvrItem()
{
	// TODO: добавьте код очистки
}

void CArmAlsnSrvrItem::Serialize(CArchive& ar)
{
	// CArmAlsnSrvrItem::Serialize вызывается рабочей средой, если
	//  элемент копируется в буфер обмена. Это может произойти автоматически
	//  посредством обратного вызова OLE OnGetClipboardData. Для внедренного элемента
	//  по умолчанию рекомендуется просто делегировать в функцию Serialize
	//  документа. В случае поддержки ссылок возможно потребуется сериализовать
	//  отдельную часть документа.

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
	// Большинство приложений, например такие как это, обрабатывают только отрисовку элементов содержимого
	//  элемента. Для поддержки других элементов, например
	//  DVASPECT_THUMBNAIL (путем перезаписи OnDrawEx) эта
	//  реализация OnGetExtent должна быть изменена на обработку
	//  дополнительных элементов.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// CArmAlsnSrvrItem::OnGetExtent вызывается для получения величины в
	//  единицах HIMETRIC целого элемента. В реализации по умолчанию
	//  просто возвращается количество единиц.

	// TODO: замените этот случайный размер

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC единиц

	return TRUE;
}

BOOL CArmAlsnSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// Удалите этот код, если вы используете rSize
	UNREFERENCED_PARAMETER(rSize);

	// TODO: задайте режим отображения и величину
	//  (Величина обычно совпадает с размером, возвращенным из OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	// TODO: добавьте код отрисовки. Кроме того, заполните величину HIMETRIC.
	//  Все рисунки производятся в контексте устройства метафайла (pDC).

	// TODO: также нарисуйте внедренные объекты CArmAlsnCntrItem.

	// Следующий код нарисует первый элемент в случайном положении.

	// TODO: удалите этот код после завершения вашего кода рисования

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


// диагностика CArmAlsnSrvrItem

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

