// AlsDbFrame.cpp: ���� ����������
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
	ID_SEPARATOR,           // ��������� ������ ���������
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
	// ���������� ��������� ��������� � ����� �� ������ ����������� ��������
//	CMainFrame::OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ����\n");
		return -1;      // �� ������� �������
	}
	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �������������� ����������� ������ ���� �� ��������� 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_ALSDBFRAME_256 : IDR_ALSDBFRAME)) //theApp.m_bHiColorIcons ? IDR_ALSDBFRAME_256 : 
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		AfxMessageBox(L"�� ������� ������� ������ ������������");
		return -1;      // �� ������� �������
	}
	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))

	{
		TRACE0("�� ������� ������� ������ ���������\n");
		return -1;      // �� ������� �������
	}
	//else AfxMessageBox(L"������ ���������");
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	

	// ��������: ������� ��� ���� �����, ���� ������ ������������ � ������ ���� �� ������ ���� �������������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);

	// �������� ����� ������ ������������ ���� ������ Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// �������� ����� ������ ��������������� ������� ������������ ���� ������ Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);



	return 0;
}


BOOL CAlsDbFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
//	return m_wndSplitter.Create(this,
//		2, 2,               // TODO: �������� ����� �����, ��������
//		CSize(10, 10),      // TODO: �������� ����������� ������ �������
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
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return TRUE;
}

// ����������� CMainFrame

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

// ����������� ��������� CAlsDbFrame