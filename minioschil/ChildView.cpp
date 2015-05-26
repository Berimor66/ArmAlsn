
// ChildView.cpp : ���������� ������ CChildView
//

#include "stdafx.h"
#include "minioschil.h"
#include "ChildView.h"
#include "Globals.h"
#include "bass.h"

//#include <MMSystem.h >
//#include <windows.h>
//#include <stdio.h>
//#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HWND hOtherWnd2;
UINT uMessageID;
// CChildView

CChildView::CChildView()
{
	timer=0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_CHECK_IZM, &CChildView::OnCheckIzm)
	//ON_COMMAND_RANGE(ID_WAVE_FORM, ID_NORM_FFT, &CChildView::OnViewMenuItems)
	//ON_COMMAND(ID_WAVE_FORM, &CChildView::OnWaveform)
	//ON_COMMAND(ID_FORM3D, &CChildView::OnForm3d)
	//ON_COMMAND(ID_LOG_FFT, &CChildView::OnLogFft)
	//ON_COMMAND(ID_NORM_FFT, &CChildView::OnNormFft)
	//ON_UPDATE_COMMAND_UI(ID_WAVE_FORM, &CChildView::OnUpdateWaveform)
	//ON_COMMAND_RANGE(ID_WAVE_FORM, ID_NORM_FFT, &CChildView::OnViewMenuItems)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_WAVE_FORM, ID_NORM_FFT, &CChildView::OnUpdateViewMenuItems)

	
END_MESSAGE_MAP()



// ����������� ��������� CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
	cs.cx=SPECWIDTH;
	cs.cy=SPECHEIGHT;
	return TRUE;
}
	CDC specdc;
	CDC specdc_imp;
	HBITMAP specbmp;
	HBITMAP specbmp_imp;

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // �������� ���������� ��� ���������
	
	// TODO: �������� ��� ��������� ���������

	//PAINTSTRUCT p;
	//if (!BeginPaint(&p)) return;
	dc.BitBlt(0,0,SPECWIDTH,SPECHEIGHT,&specdc,0,0,SRCCOPY | BLACKNESS);
	//EndPaint(&p);   

	
	
	// �� ��������� CWnd::OnPaint() ��� ��������� ���������
}



BOOL CChildView::DestroyWindow()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	//p
	
	CWaitCursor wait;
	if (timer) timeKillEvent(timer);
	// ������� ������
	specdc_imp.SelectObject(pOldBitmap_imp);
	specdc.SelectObject(pOldBitmap);
	BASS_RecordFree();
	if (specdc) specdc.DeleteDC();
	if (specdc_imp) specdc_imp.DeleteDC();
	if (specbmp) DeleteObject(specbmp);
	if (specbmp_imp) DeleteObject(specbmp_imp);
	//p-
	return CWnd::DestroyWindow();
}

HRECORD chan=0;	// recording channel
//HBITMAP specbmp=0;
//HDC     specdc=0;
//	BYTE *specbuf=(BYTE*)malloc(SPECWIDTH*SPECHEIGHT);//�� � �����
BOOL CChildView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	UNREFERENCED_PARAMETER(rect);
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	//p
	// ���������������� ����� ��������� ��� ������������� � ����
	// �����������. ��� ������ ������ ��������� � ����� �����������.
	//.................................................
	uMessageID = ::RegisterWindowMessage(L"MyMessage_TOK"); //(LPCWSTR)

	// initialize BASS recording (default device)
	if (!BASS_RecordInit(-1)) 
	{
		ErrorBass(L"�� ���� ���������������� �������");
		return -1;
	}
	// start recording (44100hz mono 16-bit)
	chan=BASS_RecordStart(200,1,0,&DuffRecording,0);
	if (!chan) 
	{
		ErrorBass(L"�� ���� ������ ������");
		return -1;
	}
	//RECT  rct;
	//rct.left=100;
	CRect(0, 0, 20, 20);

	//p-
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, CRect(0, 0, SPECWIDTH, SPECHEIGHT), pParentWnd, nID, pContext);
}

int specmode;
signed int interval_max;
signed int impuls1;
// DC ��� ������ ����
void CChildView::PreSubclassWindow()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	//specmode=3;
	interval_max=0;
	impuls1=0;
	// create bitmap to draw spectrum in (8 bit for easy updating)
	// ��� ������������
	BYTE data[2000]={0};
	BITMAPINFOHEADER *bh=(BITMAPINFOHEADER*)data;
	RGBQUAD *pal=(RGBQUAD*)(data+sizeof(*bh));
	int a;
	specbmp=0;
	specbmp_imp=0;

	bh->biSize=sizeof(*bh);
	bh->biWidth=SPECWIDTH;
	bh->biHeight=SPECHEIGHT; // upside down (line 0=bottom)  + SPECHEIGHT/2
	bh->biPlanes=1;
	bh->biBitCount=8;
	bh->biClrUsed=bh->biClrImportant=256;//256
	// setup palette
	for (a=1;a<128;a++) 
	{
		pal[a].rgbGreen=(BYTE)(256-2*a); //(256-2*a)
		pal[a].rgbRed=(BYTE)(2*a);
	}
	for (a=0;a<32;a++) 
	{
		pal[128+a].rgbBlue=(BYTE)(8*a);
		pal[128+32+a].rgbBlue=255;
		pal[128+32+a].rgbRed=(BYTE)(8*a);
		pal[128+64+a].rgbRed=255;
		pal[128+64+a].rgbBlue=(BYTE)(8*(31-a));
		pal[128+64+a].rgbGreen=(BYTE)(8*a);
		pal[128+96+a].rgbRed=255;
		pal[128+96+a].rgbGreen=255;
		pal[128+96+a].rgbBlue=(BYTE)(8*a);
	}

	//AfxGetApp()->
	//CChildView* pFrame = (CChildView*) AfxGetApp()->m_pActiveWnd;
	//;

	//memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
	// create the bitmap
	specbmp=CreateDIBSection(0,(BITMAPINFO*)bh,DIB_RGB_COLORS,(void**)&specbuf,NULL,0);
	_ASSERTE(specbmp);
	BOOL res = specdc.CreateCompatibleDC(this->GetDC()); //pFrame->GetDC()   this->GetDC()
	_ASSERTE(res);
	UNREFERENCED_PARAMETER(res);
	pOldBitmap = specdc.SelectObject(specbmp);
	////////////////////////////////////////////////////
	// ��� ���������
	bh->biHeight=SPECHEIGHT/2;
	// setup palette
	for (a=1;a<256;a++) 
	{
		pal[a].rgbGreen=(BYTE)(256-2*a); //(256-2*a)
		pal[a].rgbRed=(BYTE)(256-2*a);
	}
	// create the bitmap �������
	specbmp_imp=CreateDIBSection(0,(BITMAPINFO*)bh,DIB_RGB_COLORS,(void**)&specbuf_imp,NULL,0);
	_ASSERTE(specbmp_imp);
	res = specdc_imp.CreateCompatibleDC(this->GetDC()); //pFrame->GetDC()   this->GetDC()
	_ASSERTE(res);
	pOldBitmap_imp = specdc_imp.SelectObject(specbmp_imp);


	// setup update timer (40hz)
	//DWORD_PTR win = (DWORD_PTR) AfxGetApp()->m_pMainWnd;  // CDC
	DWORD_PTR dc = (DWORD) AfxGetApp()->m_pMainWnd->GetDC();
	timer=timeSetEvent(25,250,(LPTIMECALLBACK)&UpdateSpectrum,dc,TIME_PERIODIC); //0
	//p-

	CWnd::PreSubclassWindow();
}


void CChildView::OnCheckIzm()
{
	// TODO: �������� ���� ��� ����������� ������


	hOtherWnd = ::FindWindow(ClassName, L"���������1 - ���������" );  // (HWND)
	if ( hOtherWnd )
	{
			// ����� ����� ���� � ��������� ���������
		hOtherWnd1= ::FindWindowEx(hOtherWnd,NULL, MDIFrameName,0); //MAKEINTATOM(32770)//hOtherWnd1=(HWND)3216274; //0x00311392
		//hOtherWnd1= FindWindowEx(hOtherWnd,NULL,ClassNameMDI,0);
		if(!hOtherWnd1) AfxMessageBox(L"����� ��������� �� ������", 0, MB_OK );
		// ����� ���� ������� � �����
		hOtherWnd2= ::FindWindowEx(hOtherWnd1,NULL,MAKEINTATOM(32770),0); //MAKEINTATOM(32770)
		if(!hOtherWnd2) AfxMessageBox(L"������ ��������� �� ������", 0, MB_OK );

		// ������� �������� ����
		::PostMessage(hOtherWnd2, uMessageID, 60, 0 );
		//::SendMessage( hOtherWnd2, uMessageID, 70, 0);
	}
	else AfxMessageBox(L"���� ��������� �� �������", 0, MB_OK );

}

//
//void CChildView::OnWaveform()
//{
//	// TODO: �������� ���� ��� ����������� ������
//	specmode=3;
//	//CMenu menu;
//	//menu.CheckMenuItem(4,MF_CHECKED);//ID_WAVE_FORM
//	//menu.CheckMenuRadioItem();
//	
//		
//}
//
//
//void CChildView::OnForm3d()
//{
//	// TODO: �������� ���� ��� ����������� ������
//	specmode=2;
//	
//}
//
//
//
//void CChildView::OnLogFft()
//{
//	// TODO: �������� ���� ��� ����������� ������
//	specmode=1;
//	   // Get the popup menu which contains the "Toggle State" menu item.
//   CMenu* mmenu = GetMenu();//AfxGetApp()->m_pMainWnd->GetMenu();
//   CMenu* submenu = mmenu->GetSubMenu(2);
//   
//   // Check the state of the "Toggle State" menu item. Check the menu item
//   // if it is currently unchecked. Otherwise, uncheck the menu item
//   // if it is not currently checked.
//   UINT state = submenu->GetMenuState(ID_LOG_FFT, MF_BYCOMMAND);
//   ASSERT(state != 0xFFFFFFFF);
//
//  // if (state & MF_CHECKED)
// //     submenu->CheckMenuItem(ID_LOG_FFT, MF_UNCHECKED | MF_BYCOMMAND);
////   else
////      submenu->CheckMenuItem(ID_LOG_FFT, MF_CHECKED | MF_BYCOMMAND);
//
//}
//
//
//void CChildView::OnNormFft()
//{
//	// TODO: �������� ���� ��� ����������� ������
//	specmode=0;
//}
//
//
//void CChildView::OnUpdateWaveform(CCmdUI *pCmdUI)
//{
//	// TODO: �������� ���� ��� ����������� �� ���������� ������
//	// CMenu* mmenu = GetMenu();
//	//mmenu->CheckMenuItem(5,1);
//
//}
//
//
//void CChildView::OnViewMenuItems(UINT nID)
//{
//	  CMenu* mmenu = GetMenu();
//   CMenu* submenu = mmenu->GetSubMenu(0);
//   submenu->CheckMenuRadioItem(ID_WAVE_FORM, ID_NORM_FFT, nID, MF_BYCOMMAND);
//}

