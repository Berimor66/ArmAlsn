
// ArmAlsnDoc.h : интерфейс класса CArmAlsnDoc
//


#pragma once


class CArmAlsnSrvrItem;

class CArmAlsnDoc : public COleServerDocEx
{
protected: // создать только из сериализации
	CArmAlsnDoc();
	DECLARE_DYNCREATE(CArmAlsnDoc)

// Атрибуты
public:
	CArmAlsnSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<CArmAlsnSrvrItem*>(COleServerDocEx::GetEmbeddedItem()); }

// Операции
public:

// Переопределение
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Реализация
public:
	virtual ~CArmAlsnDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	// Автоматически созданные функции диспетчерской карты OLE

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


