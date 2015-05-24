// AlsDbFrame.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
//#include "MainFrm.h"
#include "AlsDbFormView.h"
#include "AlsDbGridView.h"
#include "AlsDbFrame.h"


// CAlsDbFrame

IMPLEMENT_DYNCREATE(CAlsDbFrame, CFrameWndEx)

CAlsDbFrame::CAlsDbFrame()
{
	//	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
}

CAlsDbFrame::~CAlsDbFrame()
{
}


BEGIN_MESSAGE_MAP(CAlsDbFrame, CFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};




int CAlsDbFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	//,	CCreateContext* pContext)

{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// установите наглядный диспетчер и стиль на основе постоянного значения
//	CMainFrame::OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Не удалось создать строку меню\n");
		return -1;      // не удалось создать
	}
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// предотвращение фокусировки строки меню на активации 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_ALSDBFRAME_256 : IDR_ALSDBFRAME)) //theApp.m_bHiColorIcons ? IDR_ALSDBFRAME_256 : 
	{
		TRACE0("Не удалось создать панель инструментов\n");
		AfxMessageBox(L"Не удалось создать панель инструментов");
		return -1;      // не удалось создать
	}
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))

	{
		TRACE0("Не удалось создать строку состояния\n");
		return -1;      // не удалось создать
	}
	//else AfxMessageBox(L"строку состояния");
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	

	// Действие: удалите эти пять строк, если панель инструментов и строка меню не должны быть закрепляемыми
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	// включить режим работы закрепляемых окон стилей Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// включить режим работы автоматического скрытия закрепляемых окон стилей Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);



	return 0;
}


BOOL CAlsDbFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
//	return m_wndSplitter.Create(this,
//		2, 2,               // TODO: измените число строк, столбцов
//		CSize(10, 10),      // TODO: измените минимальный размер области
//		pContext);

	if (!m_wndSplitter.CreateStatic(this,2,1))
	{
		TRACE0("Failed to create split bar ");
		return FALSE;    // failed to create
	}
	if(!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CAlsDbFormView),CSize(10,200),pContext))
	{
		TRACE0("Failed to create CDBVListView ");
		return FALSE;    // failed to create
	}
	if(!m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CAlsDbGridView),CSize(10,100),pContext))
	{
		TRACE0("Failed to create CEmpView ");
		return FALSE;    // failed to create
	}

	return TRUE;
}
BOOL CAlsDbFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return TRUE;
}

// диагностика CMainFrame

#ifdef _DEBUG
void CAlsDbFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CAlsDbFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

// обработчики сообщений CAlsDbFrame