
// SrvrItem.h : интерфейс класса CArmAlsnSrvrItem
//

#pragma once

class CArmAlsnSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CArmAlsnSrvrItem)

// Конструкторы
public:
	CArmAlsnSrvrItem(CArmAlsnDoc* pContainerDoc);

// Атрибуты
	CArmAlsnDoc* GetDocument() const
		{ return reinterpret_cast<CArmAlsnDoc*>(COleServerItem::GetDocument()); }

// Переопределение
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);

// Реализация
public:
	~CArmAlsnSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // перезапись для входа/выхода документа
};

