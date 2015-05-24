
// SrvrItem.h : ��������� ������ CArmAlsnSrvrItem
//

#pragma once

class CArmAlsnSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CArmAlsnSrvrItem)

// ������������
public:
	CArmAlsnSrvrItem(CArmAlsnDoc* pContainerDoc);

// ��������
	CArmAlsnDoc* GetDocument() const
		{ return reinterpret_cast<CArmAlsnDoc*>(COleServerItem::GetDocument()); }

// ���������������
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// ����������
public:
	~CArmAlsnSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // ���������� ��� �����/������ ���������
};

