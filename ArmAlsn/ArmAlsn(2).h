
// ArmAlsn.h : главный файл заголовка для приложения ArmAlsn
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CArmAlsnApp:
// О реализации данного класса см. ArmAlsn.cpp
//

class CArmAlsnApp : public CWinAppEx
{
public:
	CArmAlsnApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	COleTemplateServer m_server;
		// Объект сервера для создания документа
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	//////////////////////////p
	// Текущая координата
	double	m_PK_current;
	// Текущая Широта
	CString m_str_Latitude_current;
	// Текущая Долгота
	CString m_str_Longitude_current;
	// Направление движения
	int m_ipiketkp;

	/////////////////////////p

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOscilloscope();
	afx_msg void OnDatabase();
	void OnSelectTemplate(CString TemplateName);
	afx_msg void OnIzmAlsn();
};

extern CArmAlsnApp theApp;
//extern double pelix;
