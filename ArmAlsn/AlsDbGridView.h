#pragma once


// ������������� CAlsDbGridView

class CAlsDbGridView : public CListView
{
	DECLARE_DYNCREATE(CAlsDbGridView)

protected:
	CAlsDbGridView();           // ���������� �����������, ������������ ��� ������������ ��������
	virtual ~CAlsDbGridView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


