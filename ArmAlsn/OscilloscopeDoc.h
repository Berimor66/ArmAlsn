
// OscilloscopeDoc.h : ��������� ������ COscilloscopeDoc
//


#pragma once


class COscilloscopeDoc : public CDocument
{
protected: // ������� ������ �� ������������
	COscilloscopeDoc();
	DECLARE_DYNCREATE(COscilloscopeDoc)

// ��������
public:
	HDC specdc;
	HBITMAP specbmp;
	CDC speCDC;


// ��������
public:

// ���������������
protected:

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����������
public:
	virtual ~COscilloscopeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

	// ������������� ��������� ������� ������������� ����� OLE

};


