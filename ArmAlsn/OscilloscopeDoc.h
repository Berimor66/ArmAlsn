
// OscilloscopeDoc.h : интерфейс класса COscilloscopeDoc
//


#pragma once


class COscilloscopeDoc : public CDocument
{
protected: // создать только из сериализации
	COscilloscopeDoc();
	DECLARE_DYNCREATE(COscilloscopeDoc)

// Атрибуты
public:
	HDC specdc;
	HBITMAP specbmp;
	CDC speCDC;


// Операции
public:

// Переопределение
protected:

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Реализация
public:
	virtual ~COscilloscopeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	// Автоматически созданные функции диспетчерской карты OLE

};


