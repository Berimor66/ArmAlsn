
// minioschil.h : главный файл заголовка для приложения minioschil
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CminioschilApp:
// О реализации данного класса см. minioschil.cpp
//

class CminioschilApp : public CWinAppEx
{
public:
	CminioschilApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	UINT  m_nAppLook;
	UINT  specmodeLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CminioschilApp theApp;
