
// ArmAlsn.h : главный файл заголовка для приложения ArmAlsn
// 222
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
	double	PK_c;
	CString m_Latitude_c;
	CString m_Longitude_c;
	//////////////////////////p
	// Текущая координата
	double	m_PK_current;
	// Текущая Широта
	CString m_str_Latitude_current;
	// Текущая Долгота
	CString m_str_Longitude_current;
	// Направление движения
	INT_PTR m_ipiketkp;	 // Направление движения
	/////////////////////////p
	
	BYTE *specbuf;
	BYTE MemSpecBuf[SPECWIDTH*SPECHEIGHT];
	INT_PTR specbuf1can[SPECWIDTH*SPECHEIGHT]; //Стерео 1-й канал
	//COscilloscopeFrm *m_OscilloscopeFrm;
	

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
	//afx_msg LRESULT OnTok(WPARAM wParam, LPARAM lParam);
};

extern CArmAlsnApp theApp;
//extern double pelix;
