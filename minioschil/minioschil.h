
// minioschil.h : ������� ���� ��������� ��� ���������� minioschil
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CminioschilApp:
// � ���������� ������� ������ ��. minioschil.cpp
//

class CminioschilApp : public CWinAppEx
{
public:
	CminioschilApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������

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
