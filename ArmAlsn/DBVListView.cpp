// DBVListView.cpp: ���� ����������
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
	// ����� ����� ����������� ��������� ������ �� ������ �������������,
	// ���������� OnFinalRelease. ������� ����� �������������
	// ������ ������. ����� ������� �������� ������ ��������
	// �������������� �������, ����������� ������ �������.

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

// ����������: �� �������� ��������� ��� IID_IDBVListView, ����� ���������� ���������� � ����� ������ ����� ��������
//  �� VBA. ���� IID ������ ��������������� GUID, ���������� � 
//  disp-����������� � ����� .IDL.

// {2853546B-F22C-4199-8CB4-AAFB4F1803AA}
static const IID IID_IDBVListView =
{ 0x2853546B, 0xF22C, 0x4199, { 0x8C, 0xB4, 0xAA, 0xFB, 0x4F, 0x18, 0x3, 0xAA } };

BEGIN_INTERFACE_MAP(CDBVListView, CFormView)
	INTERFACE_PART(CDBVListView, IID_IDBVListView, Dispatch)
END_INTERFACE_MAP()


// ����������� CDBVListView

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


// ����������� ��������� CDBVListView
