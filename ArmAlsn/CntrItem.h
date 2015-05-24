
// CntrItem.h : ��������� ������ CArmAlsnCntrItem
//

#pragma once

class CArmAlsnDoc;
class CArmAlsnView;

class CArmAlsnCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CArmAlsnCntrItem)

// ������������
public:
	CArmAlsnCntrItem(CArmAlsnDoc* pContainer = NULL);
		// ����������. pContainer ����� ����� �������� NULL ��� ���������� IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE ������� ������� � ������ ������������ �
		//  ������� �����������. ������ �������� OLE ��������� �
		//  ����������� �� ��������, �� ������� NULL

// ��������
public:
	CArmAlsnDoc* GetDocument()
		{ return reinterpret_cast<CArmAlsnDoc*>(COleClientItem::GetDocument()); }
	CArmAlsnView* GetActiveView()
		{ return reinterpret_cast<CArmAlsnView*>(COleClientItem::GetActiveView()); }

public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();

protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL OnShowControlBars(CFrameWnd* pFrameWnd, BOOL bShow);
	virtual BOOL CanActivate();

// ����������
public:
	~CArmAlsnCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

