#pragma once



// представление формы CDBVListView

class CDBVListView : public CFormView
{
	DECLARE_DYNCREATE(CDBVListView)

protected:
	CDBVListView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CDBVListView();

public:
	enum { IDD = IDD_DBVLIST_FORM };

	virtual void OnFinalRelease();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


