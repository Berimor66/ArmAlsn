// DBVListDoc.cpp: ���� ����������
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "DBVListDoc.h"


// CDBVListDoc

IMPLEMENT_DYNCREATE(CDBVListDoc, CDocument)

CDBVListDoc::CDBVListDoc()
{
}

BOOL CDBVListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDBVListDoc::~CDBVListDoc()
{
}


BEGIN_MESSAGE_MAP(CDBVListDoc, CDocument)
END_MESSAGE_MAP()


// ����������� CDBVListDoc

#ifdef _DEBUG
void CDBVListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CDBVListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// ������������ CDBVListDoc

void CDBVListDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}
#endif


// ������� CDBVListDoc
