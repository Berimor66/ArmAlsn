
// IpFrame.cpp : ���������� ������ CInPlaceFrame
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
	// ������� ���������� �������
	ON_COMMAND(ID_HELP_FINDER, &COleIPFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_HELP, &COleIPFrameWndEx::OnHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &COleIPFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, &COleIPFrameWndEx::OnContextHelp)
END_MESSAGE_MAP()


// ��������/����������� CInPlaceFrame

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

	// CResizeBar ��������� ��������� �������� �� �����.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("�� ������� ������� ������ ��������� �������\n");
		return -1;      // �� ������� �������
	}

	// �� ��������� ������������� �������������� �������������� �������� �������, ������� �� ��������
	//  ���� �����. ��� ��������� ��������
	//  �������� ���������� � ���������, �������������� ��������������.
	m_dropTarget.Register(this);

	return 0;
}

// OnCreateControlBars ���������� ������� ������ ��� �������� ������� ��������� ���������� �
//  ����� ���������� ����������. pWndFrame � ���� ����� �������� ������ ���
//  ���������� � ������� �� ��������� �������� NULL. pWndDoc � ���� ����� ������ ���������
//  � ����� ��������� �������� NULL, ����� ��������� �������� ����������� SDI. ������
//  ����� ��������� ������ ���������� MFC � ����� ����.
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// ������� ���� ���, ���� �� ����������� pWndDoc
	UNREFERENCED_PARAMETER(pWndDoc);

	// ������� ��������� ����, ����� ��������� ������������ ���������������� ����������
	m_wndToolBar.SetOwner(this);

	// �������� ������ ������������ � ���� ����� �������
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_SRVR_INPLACE_256 : IDR_SRVR_INPLACE))
	{
		TRACE0("�� ������� ������� ������ ������������\n");
		return FALSE;
	}

	// TODO: ������� ��� ��� ������, ���� �� ����������� ���������� ������ ������������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �������� ����� Window ��� ����� ����������� ��������� CREATESTRUCT cs

	return COleIPFrameWndEx::PreCreateWindow(cs);
}


// ����������� CInPlaceFrame

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


// ������� CInPlaceFrame

