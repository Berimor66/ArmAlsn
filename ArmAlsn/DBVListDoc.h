#pragma once

// документ CDBVListDoc

class CDBVListDoc : public CDocument
{
	DECLARE_DYNCREATE(CDBVListDoc)

public:
	CDBVListDoc();
	virtual ~CDBVListDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // перезапись для входа/выхода документа
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
