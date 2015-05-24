
// ArmAlsnView.cpp : реализация класса CArmAlsnView
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

// создание/уничтожение CArmAlsnView

CArmAlsnView::CArmAlsnView()
{
	m_pSelection = NULL;
	// TODO: добавьте код создания

}

CArmAlsnView::~CArmAlsnView()
{
}

BOOL CArmAlsnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	cs.cx=300;
	cs.cy=200;
	return CView::PreCreateWindow(cs);
}

// рисование CArmAlsnView

void CArmAlsnView::OnDraw(CDC* pDC)
{
	if (!pDC)
		return;

	CArmAlsnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	// TODO: также нарисуйте все элементы OLE в документе
		CRect rect(10, 10, 210, 210);
		pDC->DrawText(_T("Привет, МИР"), -1, rect,
							DT_SINGLELINE | DT_CENTER | DT_VCENTER);


	// Отрисуйте выделенный фрагмент в произвольном месте. Этот код должен быть
	//  удален, поскольку реализован код отрисовки. Это положение
	//  точно соответствует прямоугольнику, возвращенному CArmAlsnCntrItem,
	//  для предоставления возможности редактирования по месту.


	// TODO: удалите этот код после завершения вашего кода рисования.
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


	// TODO: удалите этот код, когда финальный код модели выбора будет написан
	m_pSelection = NULL;    // инициализация выделения

}


// печать CArmAlsnView


void CArmAlsnView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CArmAlsnView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CArmAlsnView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CArmAlsnView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CArmAlsnView::OnDestroy()
{
	// Деактивируйте элемент при удалении; это важно
	// в случае использования представления разделителя
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CView::OnDestroy();
}



// Команды и поддержка клиента OLE

BOOL CArmAlsnView::IsSelected(const CObject* pDocItem) const
{
	// Реализация ниже справедлива, если выделенный фрагмент состоит
	//  только из объектов CArmAlsnCntrItem. Чтобы управлять различными
	//  механизмами выбора следует заменить здесь реализацию

	// TODO: Реализуйте эту функцию, которая проверяет выбранный элемент клиента OLE

	return pDocItem == m_pSelection;
}

void CArmAlsnView::OnInsertObject()
{
	// Откройте стандартное диалоговое окно "Вставка объекта" для получения информации
	//  для нового объекта CArmAlsnCntrItem
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CArmAlsnCntrItem* pItem = NULL;
	TRY
	{
		// Создать новый элемент, связанный с этим документом
		CArmAlsnDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CArmAlsnCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Инициализируйте элемент из данных диалогового окна
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // любое исключение выполнит
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);
		// Поскольку дизайн интерфейса пользователя произвольный, это задает вставку выделенного
		//  фрагмента в последний элемент

		// TODO: повторите реализацию выделения, как это требуется в приложении
		m_pSelection = pItem;   // выделение последнего вставленного элемента
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

// Следующий обработчик команд предоставляет стандартный клавиатурный
//  интерфейс пользователя для отмены сеанса редактирования по месту. Здесь
//  контейнер (не сервер) вызывает деактивацию
void CArmAlsnView::OnCancelEditCntr()
{
	// Закройте в этом представлении все активные объекты редактирования по месту
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Для контейнера требуется специальная обработка OnSetFocus и OnSize,
//  если объект редактируется по месту
void CArmAlsnView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// необходимо установить фокус на этот объект, если он находится в том же представлении
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // не вызывайте базовый класс
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
	//По умолчанию печать активного документа запрашивается
	//с помощью IOleCommandTarget. Если такое поведение не требуется,
	//удалите вызов COleDocObjectItem::DoDefaultPrinting.
	//Если вызов будет неудачным по какой-либо причине, мы попробуем напечатать
	//docobject с помощью интерфейса IPrint.
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

// Поддержка сервера OLE

// Следующий обработчик команд предоставляет стандартный клавиатурный
//  интерфейс пользователя для отмены сеанса редактирования по месту. Здесь
//  сервер (не контейнер) вызывает деактивацию
void CArmAlsnView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// диагностика CArmAlsnView

#ifdef _DEBUG
void CArmAlsnView::AssertValid() const
{
	CView::AssertValid();
}

void CArmAlsnView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArmAlsnDoc* CArmAlsnView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArmAlsnDoc)));
	return (CArmAlsnDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CArmAlsnView

afx_msg LRESULT CArmAlsnView::OnTok(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	AfxMessageBox(L"Tok ArmAlsnView");
	return 0;
}