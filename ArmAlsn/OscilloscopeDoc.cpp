
// OscilloscopeDoc.cpp : ���������� ������ COscilloscopeDoc
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "OscilloscopeDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COscilloscopeDoc

IMPLEMENT_DYNCREATE(COscilloscopeDoc, CDocument)

BEGIN_MESSAGE_MAP(COscilloscopeDoc, CDocument)
	// �������� ���������� ���������� OLE
END_MESSAGE_MAP()


// ����������. ��������� ��������� ��� IID_IArmAlsn ��� ��������� �������� typesafe
//  �� VBA. IID ������ ��������� � GUID, ������� ������ � 
//  disp-��������� � ����� .IDL.

// {BCBF38A5-7B4C-48E1-A0C8-0F05733A6AF3}
static const IID IID_IArmAlsn =
{ 0xBCBF38A5, 0x7B4C, 0x48E1, { 0xA0, 0xC8, 0xF, 0x5, 0x73, 0x3A, 0x6A, 0xF3 } };


// ��������/����������� COscilloscopeDoc

COscilloscopeDoc::COscilloscopeDoc()
{

	// TODO: �������� ��� ��� ������������ ������ ������������



}

COscilloscopeDoc::~COscilloscopeDoc()
{
	
}

BOOL COscilloscopeDoc::OnNewDocument()
{

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}


// ���������� ������� COscilloscopeDoc



// ������������ COscilloscopeDoc

void COscilloscopeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}

	// ����� �������� ������ COleServerDocEx �������� ������������
	//  �������� COleClientItem ��������� ����������.
}


// ����������� COscilloscopeDoc

#ifdef _DEBUG
void COscilloscopeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COscilloscopeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// ������� COscilloscopeDoc
