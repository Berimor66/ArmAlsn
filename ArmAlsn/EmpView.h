#pragma once


// ������������� CEmpView

class CEmpView : public CListView
{
	DECLARE_DYNCREATE(CEmpView)

protected:
	CEmpView();           // ���������� �����������, ������������ ��� ������������ ��������
	virtual ~CEmpView();

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


