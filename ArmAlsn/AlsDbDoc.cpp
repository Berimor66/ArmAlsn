// AlsDbDoc.cpp: ���� ����������
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "AlsDbDoc.h"


// CAlsDbDoc

IMPLEMENT_DYNCREATE(CAlsDbDoc, CDocument)

CAlsDbDoc::CAlsDbDoc()
{
}

BOOL CAlsDbDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAlsDbDoc::~CAlsDbDoc()
{
}


BEGIN_MESSAGE_MAP(CAlsDbDoc, CDocument)
END_MESSAGE_MAP()


// ����������� CAlsDbDoc

#ifdef _DEBUG
void CAlsDbDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CAlsDbDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// ������������ CAlsDbDoc

void CAlsDbDoc::Serialize(CArchive& ar)
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


// ������� CAlsDbDoc
