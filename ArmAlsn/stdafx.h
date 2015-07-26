
// stdafx.h: �������� ���� ��� ���������� ����������� ��������� ������
//��� ���������� ������ ��������, ����� ������������,
// �� ����� ����������

#pragma once

#pragma comment( user, "����� ����� �������, �������:" __DATE__ " � " __TIME__ )
#pragma comment( compiler )

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ��������� ����� ������������ ���������� �� ���������� Windows
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ��������� ������������ CString ����� ������

// ��������� ������� ������� ��������� ����� � ����� ������������ �������������� MFC
#define _AFX_ALL_WARNINGS


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers



#include <afxwin.h>         // �������� � ����������� ���������� MFC
#include <afxext.h>         // ���������� MFC

#include <afxole.h>         // ������ MFC OLE
#include <afxodlgs.h>       // ������ ���������� ���� MFC OLE

#include <afxdisp.h>        // ������ ������������� MFC

//�����: Vadun
//����� CRT ������������� ������������� heap �� ��������������� ����� ������ ������ ������ � ������ ����� ������������ ��������� ����� � ������, ��� ���� �������� ��������������� ������.
//
////p20121012 #include <vld.h>
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

//#ifdef _DEBUG
//#ifdef _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif /* _CRTDBG_MAP_ALLOC */
//#endif /* _DEBUG */
/////


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // ��������� MFC ��� ������� ��������� ���������� Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // ��������� MFC ��� ������� ��������� ���������� Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // ��������� MFC ��� ���� � ������� ����������

// p

#define MAX_LANGUAGES 10
#include "ConfigAppDlg.h"   // ������ ��������
#include "ViewPut.h"		// ������ �����������


// ��� ���������	  "MyMessage_TOK"
//#define WM_DIALOG_CNF_CLOSE WM_APP + 2
//#define WM_MYICONNOTIFY WM_USER + 3
#define WM_DIALOG_CNF_CLOSE WM_APP + 2
#define WM_MYICONNOTIFY WM_APP + 3
#define WM_MYTIMER	WM_APP + 4
// tmp
#define WM_MYMESSAGE WM_USER+5

// ��� ����� ��������
#define DATA_FILE_DAT _T("\\ArmALSN\\Config\\Alsn.dat") // C:\\ProgramData
#define DATA_FILE_DB C:\\SAP_SAN\\ArmAlsn\\Alsn.mdb
#define DATA_FILE_DB_ACC C:\\SAP_SAN\\ArmAlsn\\����.accdb
#define DATA_STRING_DB_MDB "Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=C:\\SAP_SAN\\ArmAlsn\\Alsn.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False"
#define DATA_STRING_DB_ACC "Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=C:\\SAP_SAN\\ArmAlsn\\����.accdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False"
// Provider=Microsoft.Jet.OLEDB.4.0;
//#define DATA_STRING_DB_ACC "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\SAP_SAN\\ArmAlsn\\����.accdb;User ID=Admin;Data Source=C:\\SAP_SAN\\ArmAlsn\\����.accdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False"
//#define DATA_STRING_DB_ACC "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:\\SAP_SAN\\ArmAlsn\\����.accdb"

//
#include <mmsystem.h>    // ��� dsound.h
#include <dsound.h>      // DirectX
//#include <windows.h>
// #include <afx.h>
/* ���������� ���������� BASS */
#include "bass.h" 
/* ���������� ���������� ������� */
//#pragma comment (lib, "bass.lib")
//#define BASSVERSION	0x0204//0x02040304 //��� ���� � bass.h
#define SPECWIDTH 368	// display width 368
#define SPECHEIGHT 127	// height (changing requires palette adjustments too)

//CString m_name_sound;

#import "DiscoAPI.dll" no_namespace named_guids 
//#import "OziAPI.dll" no_namespace named_guids 
// D:\WINDOWS\SysWOW64\

//#ifndef HEADER_H
//#define HEADER_H 1
#include "Globals.h"
//#endif
//extern	BYTE *specbuf_i;
extern	BYTE *specbuf_canal1;
extern	BYTE *specbuf_canal2;
extern	CString *pstr_specbuf_canal2;
extern CWnd *Stb123;
extern CWnd *Stb1;


//extern	BYTE specbuf_canal1[SPECWIDTH*SPECHEIGHT];

#include <atldbcli.h>
#include <afxcview.h>

// �������������� VS
#include <setupapi.h>
#include <winspool.h>
#include <WBemCli.h>

#include <windows.h> //  ��������� <winsock2.h> ������������� �� ��������� <windows.h>
//���  WIN32_LEAN_AND_MEAN - ��� �������� ���������� ���� �� ������ ����� �������������� SDK
//#define WIN32_LEAN_AND_MEAN


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


