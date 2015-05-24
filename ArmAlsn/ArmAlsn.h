
// ArmAlsn.h : ������� ���� ��������� ��� ���������� ArmAlsn
// 222
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CArmAlsnApp:
// � ���������� ������� ������ ��. ArmAlsn.cpp
//

class CArmAlsnApp : public CWinAppEx
{
public:
	CArmAlsnApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// ���������������
public:
	virtual BOOL InitInstance();

// ����������
	COleTemplateServer m_server;
		// ������ ������� ��� �������� ���������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	//////////////////////////p
	double	PK_c;
	CString m_Latitude_c;
	CString m_Longitude_c;
	//////////////////////////p
	// ������� ����������
	double	m_PK_current;
	// ������� ������
	CString m_str_Latitude_current;
	// ������� �������
	CString m_str_Longitude_current;
	// ����������� ��������
	INT_PTR m_ipiketkp;	 // ����������� ��������
	/////////////////////////p
	
	BYTE *specbuf;
	BYTE MemSpecBuf[SPECWIDTH*SPECHEIGHT];
	INT_PTR specbuf1can[SPECWIDTH*SPECHEIGHT]; //������ 1-� �����
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
