
// ArmAlsnDoc.h : ��������� ������ CArmAlsnDoc
//


#pragma once


class CArmAlsnSrvrItem;

class CArmAlsnDoc : public COleServerDocEx
{
protected: // ������� ������ �� ������������
	CArmAlsnDoc();
	DECLARE_DYNCREATE(CArmAlsnDoc)

// ��������
public:
	CArmAlsnSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CArmAlsnSrvrItem*>(COleServerDocEx::GetEmbeddedItem()); }

// ��������
public:

// ���������������
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����������
public:
	virtual ~CArmAlsnDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

	// ������������� ��������� ������� ������������� ����� OLE

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


