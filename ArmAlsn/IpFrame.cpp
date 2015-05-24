
// IpFrame.cpp : реализация класса CInPlaceFrame
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWndEx)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWndEx)
	ON_WM_CREATE()
	// Команды глобальной справки
	ON_COMMAND(ID_HELP_FINDER, &COleIPFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_HELP, &COleIPFrameWndEx::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &COleIPFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, &COleIPFrameWndEx::OnContextHelp)
END_MESSAGE_MAP()


// создание/уничтожение CInPlaceFrame

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar реализует изменение размеров по месту.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Не удалось создать панель изменения размера\n");
		return -1;      // не удалось создать
	}

	// По умолчанию рекомендуется регистрировать раскрывающиеся конечные объекты, которые не изменяют
	//  окно рамки. Это позволяет избежать
	//  передачи управления в контейнер, поддерживающий перетаскивание.
	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars вызывается рабочей средой для создания панелей элементов управления в
//  окнах приложения контейнера. pWndFrame – окно рамки верхнего уровня для
//  контейнера и никогда не принимает значение NULL. pWndDoc – окно рамки уровня документа
//  и может принимать значение NULL, когда контейнер является приложением SDI. Сервер
//  может размещать панели управления MFC в любом окне.
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// Удалите этот код, если вы используете pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// Задайте владельца окна, чтобы сообщения доставлялись соответствующему приложению
	m_wndToolBar.SetOwner(this);

	// Создайте панель инструментов в окне рамки клиента
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_SRVR_INPLACE_256 : IDR_SRVR_INPLACE))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		return FALSE;
	}

	// TODO: Удалите эти три строки, если не собираетесь закреплять панель инструментов
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  измените класс Window или стили посредством изменения CREATESTRUCT cs

	return COleIPFrameWndEx::PreCreateWindow(cs);
}


// диагностика CInPlaceFrame

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWndEx::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// команды CInPlaceFrame

