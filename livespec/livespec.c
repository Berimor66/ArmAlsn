/*
	BASS "live" spectrum analyser example
	Copyright (c) 2002-2010 Un4seen Developments Ltd.
*/
#pragma comment( lib , "comctl32.lib" ) // error LNK2019: ссылка на неразрешенный внешний символ __imp__InitCommonControls@4 в функции _WinMain@16

#include <windows.h>
#include <commctrl.h> // // enable trackbar support
#include <stdio.h>
#include <math.h>
#include "bass.h"
#include "resource.h"

#define SPECWIDTH 400 //368	// display width
#define SPECHEIGHT 127	// height (changing requires palette adjustments too)
#define WM_MYMESSAGE WM_USER+5 //tmp

// организация разделяемой между процессами области данных на основе //специального сегмента данных
///////.......
#pragma data_seg ("MY_DATA") 
TCHAR cSharedData[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#pragma data_seg () 
/// sharefile
TCHAR * pGlobal;
///
/////...........

BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l);
HINSTANCE HInstance;

UINT uMessageID = 0;	   // UINT NEAR

HWND hOtherWnd;
HWND hOtherWnd1,hOtherWnd2;
int	n_ms=0	;// число милисисикунд счета тока
DWORD	m_tok_c=0	;// ток за секунду


HWND win=NULL;
HWND win2=NULL;
HWND winEq=NULL;
DWORD timer=0;
DWORD  As=0;
DWORD  AS=0;
DWORD  AS1=0;
DWORD  AS2=0;
char ss[] = "1111";
	int s3=0;

	DWORD quietcountInt=0;
	DWORD quietcountImp=0;
	int quietcountIntN=0;



HRECORD chan;	// recording channel

HDC specdc=0;
HBITMAP specbmp=0;
BYTE *specbuf;

int specmode=3,specpos=0; // spectrum mode (and marker pos for 2nd mode)

// display error messages
void Error(const char *es)
{
	char mes[200];
	wsprintf(mes,"%Is\n(код ошибки: %Id)",es,BASS_ErrorGetCode()); //спецификатор размера "I"
	MessageBox(win,mes,0,0);
}
  	int Int1 = 0; // значение тока
	//int t;
	RECT r1={SPECWIDTH*2-90,0,20,20};
	RECT r2={0,0,100,20};
	DWORD quietcountInt1=0;
// update the spectrum display - the interesting bit :)

	// т к CALLBACK -вне функции
	HWND hOtherWnd;

#define MESS(id,m,w,l) SendDlgItemMessage(winEq,id,m,(WPARAM)(w),(LPARAM)(l))
//OPENFILENAME ofn;
HFX fx[19];			//  eq bands 
int FCenter[19] = {25,26,50,51,76,100,130,150,250,420,480,580,720,750,780,5000,4545,5000,5555}; 


void UpdateFX(int b)
{
	int v=MESS(IDC_SLIDER1+b,TBM_GETPOS,0,0); //20
		BASS_DX8_PARAMEQ p;
	//	BASS_ChannelRemoveFX((FileStream, FX); // чтобы убрать предыдущую настройку
  //	fx[b] = FBASS_ChannelSetFX(FileStream, BASS_FX_DX8_PARAMEQ, 1);
		BASS_FXGetParameters(fx[b],&p);
		p.fGain=15.0-v;
		BASS_FXSetParameters(fx[b],&p);
		//MessageBox (0, "Error x%x", "CreateDialog", MB_ICONEXCLAMATION | MB_OK);
}


void CALLBACK UpdateSpectrum(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{

	HDC dc;
	static DWORD quietcount=0;
	static DWORD quietcountA=0;

	int x,y,y1,t;
   
	if (specmode==3) 
	{ // waveform
			
		short buf[SPECWIDTH];
		memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
		BASS_ChannelGetData(chan,buf,sizeof(buf)); // get the sample data
		for (x=0;x<SPECWIDTH;x++) {
			//x=x/2;
			int v=(32767-buf[x])*SPECHEIGHT/65536; //32767 invert and scale to fit display
			if (!x) y=v;
			do { // draw line from previous sample...
				if (y<v) y++;
				else if (y>v) y--;
				specbuf[y*SPECWIDTH+x]=abs(y-SPECHEIGHT/2)+1;
				//specbuf[y*SPECWIDTH+x+1]=abs(y-SPECHEIGHT/2)+1;
 			//	specbuf[y*SPECWIDTH+x+2]=abs(y-SPECHEIGHT/2)+1;
				//specbuf[y*SPECWIDTH+x+3]=abs(y-SPECHEIGHT/2)+1;
				//specbuf[y*SPECWIDTH+x+4]=abs(y-SPECHEIGHT/2)+1;
				//specbuf[y*SPECWIDTH+x+5]=abs(y-SPECHEIGHT/2)+1;
 			//	specbuf[y*SPECWIDTH+x+6]=abs(y-SPECHEIGHT/2)+1;
				//specbuf[y*SPECWIDTH+x+7]=abs(y-SPECHEIGHT/2)+1;

			
			
			} while (y!=v);
		}
	//////////////////////////////////////////////////////////////////
	///	Первый интервал
	/// #define SPECWIDTH 400 (368)   freq = 200 Гц
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	///
		//quietcountIntN = 0;
		//quietcountImp=0;
		//quietcountInt=0;

	Int1 = abs(buf[0]);
	//dc=GetDC(win);
//	for (x=0;x<SPECWIDTH;x=x+2) 
//	{
	x=0;
		for (t=0; t<2; t++)
		{
			if (Int1<abs(buf[x+t])) Int1 = abs(buf[x+t]);
		}

		Int1 = abs(buf[1]) ;
		// это интервал?
		if (Int1 < 1600)		//	  400 - 6000  2000
		{
			//MessageBox(win,ss,"ИНТЕРВАЛ",0);
			quietcountInt++;
			//  Да интервал

			if (quietcountInt>20)	 // Большой ИНТЕРВАЛ  72  -65- 55
			{
				//sprintf(ss,"%d", quietcountIntN);
				//MessageBox(win,ss,"Большой ИНТЕРВАЛ",0);

				quietcountIntN=0;
				//quietcountInt=0;
				quietcountImp=0;
	
			}
			////////
			if (quietcountInt>3)
			{
			  quietcountImp=0;
			}
			////////
		}
		else   // импульс
		{
			////////
			quietcountImp++;
			if (quietcountImp>3)	 //	 -190
			{
			////////
				//MessageBox(win,ss,"ИМПУЛЬС",0);
				if (quietcountInt>3)  	// интервал был?
				{

				//sprintf(ss,"%d", quietcountIntN);
				//MessageBox(win,ss,"ИНТЕРВАЛ",0);


					if	(quietcountIntN==1)  // 1-й
					{
						quietcountInt1 = quietcountInt+6;
						//sprintf(ss,"%d", quietcountInt1);
						//MessageBox(win,ss,"11",0);
					}
					quietcountIntN++;

				}
				quietcountInt=0;
			}
		}
	// } 	  end for
	///
	///
	//////////////////////////////////////////////////////////////////
	} // waveform END
	else {
		float fft[1024];
		BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data

		if (!specmode) { // "normal" FFT
			memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
			for (x=0;x<SPECWIDTH/2;x++) {
#if 1
				y=sqrt(fft[x+1])*3*SPECHEIGHT-4; // scale it (sqrt to make low values more visible)
#else
				y=fft[x+1]*10*SPECHEIGHT; // scale it (linearly)
#endif
				if (y>SPECHEIGHT) y=SPECHEIGHT; // cap it
				if (x && (y1=(y+y1)/2)) // interpolate from previous to make the display smoother
					while (--y1>=0) specbuf[y1*SPECWIDTH+x*2-1]=y1+1;
				y1=y;
				while (--y>=0) specbuf[y*SPECWIDTH+x*2]=y+1; // draw level
			}
		} else if (specmode==1) { // logarithmic, acumulate & average bins
			int b0=0;
			memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
#define BANDS 28
			for (x=0;x<BANDS;x++) {
				float peak=0;
				int b1=pow(2,x*10.0/(BANDS-1));
				if (b1>1023) b1=1023;
				if (b1<=b0) b1=b0+1; // make sure it uses at least 1 FFT bin
				for (;b0<b1;b0++)
					if (peak<fft[1+b0]) peak=fft[1+b0];
				y=sqrt(peak)*3*SPECHEIGHT-4; // scale it (sqrt to make low values more visible)
				if (y>SPECHEIGHT) y=SPECHEIGHT; // cap it
				while (--y>=0)
					memset(specbuf+y*SPECWIDTH+x*(SPECWIDTH/BANDS),y+1,0.9*(SPECWIDTH/BANDS)); // draw bar
			}
		} else { // "3D"
			for (x=0;x<SPECHEIGHT;x++) {
				y=sqrt(fft[x+1])*3*127; // scale it (sqrt to make low values more visible)
				if (y>127) y=127; // cap it
				specbuf[x*SPECWIDTH+specpos]=128+y; // plot it
			}
			// move marker onto next position
			specpos=(specpos+1)%SPECWIDTH;
			for (x=0;x<SPECHEIGHT;x++) specbuf[x*SPECWIDTH+specpos]=255;
		}// "3D" END
	}

	// update the display
	
	dc=GetDC(win);
	BitBlt(dc,0,0,SPECWIDTH,SPECHEIGHT,specdc,0,0,SRCCOPY);
	As = BASS_ChannelGetLevel(chan);
	if (LOWORD(As)<500) //400
	{ // check if it's quiet
		quietcount++;
		if ((quietcount>16))	  //18 16  && (quietcount<=30)
		{
			AS=0;
		}
		if (quietcount>43 && (quietcount&16)) { // пауза и мигание it's been quiet for over a second
			RECT r={0,0,SPECWIDTH,SPECHEIGHT};
			SetTextColor(dc,0xffffff);
			SetBkMode(dc,TRANSPARENT);
			DrawText(dc,"НЕТ КОДОВ!",-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
			 PostMessage(hOtherWnd2, uMessageID , 0, 0 );
		}
	} else //cигнал
	{
		quietcount=0; // not quiet
			if (AS<As) AS=As;
	}
	//////
	AS1 = LOWORD(AS); //AS
	AS2 = AS1/80;	 //	 176.5	 Наш ток
	s3=AS2/10;

	wsprintf(ss, "%Id.%Id А",AS2/10,AS2-s3*10);       //LOWORD(AS)/113);
	SetTextColor(dc,0xffffff);	//	0xffffff
	SetBkMode(dc,TRANSPARENT);

	if (AS>0) DrawText(dc,ss,-1,&r1,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //AS
 ///////////////////////////
	////
	
	if (n_ms<15) 
	{
		if (m_tok_c<AS2) m_tok_c=AS2;	  //AS
		n_ms++;
	}
	else  //  
	{
		n_ms=0;

		////
		//////////////////
			 //AS1= 2.3; //LOWORD(AS)/150;
//		AS1 = LOWORD(m_tok_c); //AS
		
	
			///////////////////////////////////////////////////////////////////////////////////////////////////
			/////////
			/// - Отправить ток всем заинтересованным
			//...................................
			// Всем фреймам верхнего уровня
			//			PostMessage( HWND_BROADCAST, uMessageID, AS2, 0 );
			////////////////////////////////////////////////////////////////
			//  Нашли окно верхнего уровня Измерения
			// AfxFrameOrView100ud -debug
			// AfxFrameOrView100u  -release
#ifndef _DEBUG
#ifdef _VS100
#define ClassName "AfxFrameOrView100u"
#define MDIFrameName "AfxMDIFrame100u"
#endif
#ifdef _VS120
#define ClassName "AfxFrameOrView120u"
#define MDIFrameName "AfxMDIFrame120u"
#endif
#ifdef _VS140
#define ClassName "AfxFrameOrView140u"
#define MDIFrameName "AfxMDIFrame140u"
#endif	
#endif



#ifdef _DEBUG
	#ifdef _VS100
	#define ClassName "AfxFrameOrView100ud"
	#define MDIFrameName "AfxMDIFrame100ud"
	#endif
	#ifdef _VS120
	#define ClassName "AfxFrameOrView120ud"
	#define MDIFrameName "AfxMDIFrame120ud"
	#endif
	#ifdef _VS140
	#define ClassName "AfxFrameOrView140ud"
	#define MDIFrameName "AfxMDIFrame140ud"
	#endif	
#endif
		hOtherWnd = FindWindow( ClassName, "Измерение1 - Измерения" ); 
		if ( hOtherWnd )
		{
				// Нашли фрейм окна с названием Измерения
			hOtherWnd1= FindWindowEx(hOtherWnd,NULL,MDIFrameName,0); //MAKEINTATOM(32770)//hOtherWnd1=(HWND)3216274; //0x00311392
			// Нашли окно диалога с током
			hOtherWnd2= FindWindowEx(hOtherWnd1,NULL,MAKEINTATOM(32770),0); //MAKEINTATOM(32770)
			// Послали значение тока
			//	AS2=6;
			if (m_tok_c>0.5) PostMessage(hOtherWnd2, uMessageID , m_tok_c, 0 );
			//PostMessage(hOtherWnd2, WM_MYMESSAGE, AS2, 0);
				m_tok_c=0;
		}
	//else MessageBox( win, "Окно Измерения НЕ найдено", 0, MB_OK );
	}
			/////////////////////////////////////////////////////////////////////////


	

	
		
			wsprintf(ss, "%Idc %IdN",quietcountInt1, quietcountIntN);  //спецификатор размера "I"  
			SetTextColor(dc,0xffffff);	//	0xffffff
			SetBkMode(dc,TRANSPARENT);
	//		DrawText(dc,ss,-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);


	//////

	ReleaseDC(win,dc);

}

// Recording callback - not doing anything with the data
BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	return TRUE; // continue recording
}


// window procedure
long FAR PASCAL SpectrumWindowProc(HWND h, UINT m, WPARAM w, LPARAM l)
{
	switch (m) {
		case WM_PAINT:
			if (GetUpdateRect(h,0,0)) {
				PAINTSTRUCT p;
				HDC dc;
				if (!(dc=BeginPaint(h,&p))) return 0;
				BitBlt(dc,0,0,SPECWIDTH,SPECHEIGHT,specdc,0,0,SRCCOPY);
				EndPaint(h,&p);
			}
			return 0;

		case WM_RBUTTONUP:
			specmode=(specmode+1)%4; // swap spectrum mode
			memset(specbuf,0,SPECWIDTH*SPECHEIGHT);	// clear display
			return 0;

		case WM_LBUTTONUP:
//			PostMessage( HWND_BROADCAST, uMessageID, AS2, 0 );
			
		//// enable trackbar support
		//INITCOMMONCONTROLSEX cc={sizeof(cc),ICC_BAR_CLASSES};
		//InitCommonControlsEx(&cc);
	

			if (!IsWindow(winEq)) 
			{ 
				winEq = CreateDialog(HInstance, 
				MAKEINTRESOURCE(IDD_DIALOG1), 
				h, (DLGPROC)dialogproc); //0,&
				ShowWindow(winEq, SW_SHOW); 
			} 


			//DialogBox(HInstance,(LPCSTR)IDD_DIALOG1,0,&dialogproc);  // (char*)
			//ShowWindow(winEq, SW_SHOWNORMAL);



			        









			
			
			////////////////////////////////////////////////////////////////
			//  Нашли окно верхнего уровня Измерения
			// AfxFrameOrView100ud -debug
			// AfxFrameOrView100u  -release


			hOtherWnd = FindWindow( ClassName, "Измерение1 - Измерения" ); 
			if ( hOtherWnd )
			{
				// Нашли фрейм окна с названием Измерения
				hOtherWnd1= FindWindowEx(hOtherWnd,NULL,MDIFrameName,0); //MAKEINTATOM(32770)//hOtherWnd1=(HWND)3216274; //0x00311392
				// Нашли окно диалога с током
				hOtherWnd2= FindWindowEx(hOtherWnd1,NULL,MAKEINTATOM(32770),0); //MAKEINTATOM(32770)

				//SendMessage(hOtherWnd2, WM_COMMAND, MAKEWPARAM(1000, BN_CLICKED), (LPARAM)hOtherWnd1);
				//PostMessage(hOtherWnd2, WM_ACTIVATE, WA_ACTIVE, NULL);
				//PostMessage(hOtherWnd2, WM_LBUTTONDOWN, 0, 0);
				//PostMessage(hOtherWnd2, WM_LBUTTONUP, 0, 0);
				// Послали значение тока
				AS2=6;
				PostMessage(hOtherWnd2, uMessageID , AS2, 0 );
				//PostMessage(hOtherWnd2, WM_MYMESSAGE, AS2, 0);
				
				//SendMessage( hOtherWnd, uMessageID, AS2, 0);
			}
			else MessageBox( win, "Окно Измерения НЕ найдено", 0, MB_OK );

			/////////////////////////////////////////////////////////////////////////

						
		return 0;

		case WM_CREATE:
			// Зарегистрировать общее сообщение для использования в двух
			// приложениях. Эта строка должна совпадать в обоих
			// приложениях.
			//.................................................
			uMessageID = RegisterWindowMessage( "MyMessage_TOK" );
			//sprintf(ss, "%d",uMessageID);
			//MessageBox(NULL,ss,"11",0);




			win=h;
			// initialize BASS recording (default device)
			if (!BASS_RecordInit(-1)) {
				Error("Не могу инициализировать драйвер");
				return -1;
			}
			// start recording (44100hz mono 16-bit)
			if (!(chan=BASS_RecordStart(200,1,0,&DuffRecording,0))) {
				Error("Не могу начать запись");
				return -1;
			}

			{ // create bitmap to draw spectrum in (8 bit for easy updating)
				BYTE data[2000]={0};
				BITMAPINFOHEADER *bh=(BITMAPINFOHEADER*)data;
				RGBQUAD *pal=(RGBQUAD*)(data+sizeof(*bh));
				int a;
				bh->biSize=sizeof(*bh);
				bh->biWidth=SPECWIDTH;
				bh->biHeight=SPECHEIGHT; // upside down (line 0=bottom)
				bh->biPlanes=1;
				bh->biBitCount=8;
				bh->biClrUsed=bh->biClrImportant=256;
				// setup palette
				for (a=1;a<128;a++) {
					pal[a].rgbGreen=256-2*a;
					pal[a].rgbRed=2*a;
				}
				for (a=0;a<32;a++) {
					pal[128+a].rgbBlue=8*a;
					pal[128+32+a].rgbBlue=255;
					pal[128+32+a].rgbRed=8*a;
					pal[128+64+a].rgbRed=255;
					pal[128+64+a].rgbBlue=8*(31-a);
					pal[128+64+a].rgbGreen=8*a;
					pal[128+96+a].rgbRed=255;
					pal[128+96+a].rgbGreen=255;
					pal[128+96+a].rgbBlue=8*a;
				}
				// create the bitmap
				specbmp=CreateDIBSection(0,(BITMAPINFO*)bh,DIB_RGB_COLORS,(void**)&specbuf,NULL,0);
				specdc=CreateCompatibleDC(0);
				SelectObject(specdc,specbmp);
			}
			// setup update timer (40hz)
			timer=timeSetEvent(25,250,(LPTIMECALLBACK)&UpdateSpectrum,0,TIME_PERIODIC);
			break;

		case WM_DESTROY:
			if (timer) timeKillEvent(timer);
			BASS_RecordFree();
			if (specdc) DeleteDC(specdc);
			if (specbmp) DeleteObject(specbmp);
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(h, m, w, l);
}
////1
HINSTANCE TheInstance1 = 0; 
//int NewHandler (size_t size)
//{
////    throw WinException ( "Out of memory" );
//    return 0;
//}
	HWND hDialog = 0;

BOOL CALLBACK DialogProc2 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	win2=hwnd;
	//static Controller* control = 0;
    switch (message)
    {
    case WM_INITDIALOG:
	//		ShowWindow(hDialog, SW_SHOW);
	//	MessageBox (0, "Unknown", "Exception", MB_ICONEXCLAMATION | MB_OK);
						// initialize eq/reverb sliders
			MESS(IDC_SLIDER101,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER101,TBM_SETPOS,TRUE,0);
        return TRUE;
    case WM_COMMAND:
   ;
        return TRUE;
    case WM_DESTROY:
        PostQuitMessage(0);
        return TRUE;
    case WM_CLOSE:
        //delete control;
        DestroyWindow (hwnd);
        return TRUE;
    }
    return FALSE;
}

   int status;
//////1


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASS wc={0};
    MSG msg;
	MSG msg2;
	HInstance = hInstance;

	
	{ // enable trackbar support
		INITCOMMONCONTROLSEX cc={sizeof(cc),ICC_BAR_CLASSES};
		InitCommonControlsEx(&cc);
	}
	///////////////////////////////////////////////////////////////

	//организация разделяемой области
/*	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hMap = ::CreateFileMapping(hFile,
		NULL,
		PAGE_READWRITE,
		0,
		4096,
		"_MY_SHARE_"
		);
	if(hMap == NULL){
		::MessageBox(NULL,"Ошибка CreateFileMapping",
			"Тестовый пример",MB_OK);
		return -1;
	}

	pGlobal = (TCHAR *)::MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,100);

	if(pGlobal == NULL){
		::MessageBox(NULL,_T("Ошибка MapViewOfFile"),
			_T("Тестовый пример"),MB_OK);
		return -1;
	}

*/

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) 
	{
		MessageBox(0,"Не коректная версия BASS.DLL",0,MB_ICONERROR);
		return 0;
	}



	// register window class and create the window
	wc.lpfnWndProc = SpectrumWindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE (IDI_ICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "МиниBASS-Spectrum";

	
	if (!RegisterClass(&wc) || !CreateWindow("МиниBASS-Spectrum",
			"Мини Осциллограф (клик для смены режима)",
			WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE|WS_MINIMIZEBOX, 200, 200,
			SPECWIDTH+2*GetSystemMetrics(SM_CXDLGFRAME),
			SPECHEIGHT+GetSystemMetrics(SM_CYCAPTION)+2*GetSystemMetrics(SM_CYDLGFRAME),
			NULL, NULL, hInstance, NULL)) 
	{
		Error("Не могу создать окно");
		return 0;
	}




	///////////////////////////////////////////////////////////////////////////
	///
	////
//	TheInstance1 = hInstance; 
////	_set_new_handler (& NewHandler);
//	 
//
// //hDialog = IDD_DIALOG2
//
//	   hDialog = CreateDialog (hInstance, MAKEINTRESOURCE (IDD_DIALOG1), 0, (DLGPROC)dialogproc); //DialogProc2
//
//	   if (!hDialog)
//    {
//        char buf [100];
//        wsprintf (buf, "Error x%x", GetLastError ());
//  //      MessageBox (0, buf, "CreateDialog", MB_ICONEXCLAMATION | MB_OK);
//        return 1;
//    }
//
//	  // MSG  msg2;
// 	ShowWindow(hDialog, SW_SHOW);
//    while ((status = GetMessage (&msg2, 0, 0, 0)) != 0)
//    {
//        if (status == -1)
//            return -1;
//        if (!IsDialogMessage (hDialog, &msg2))
//        {
//            TranslateMessage ( &msg2 );
//            DispatchMessage ( &msg2 );
//        }
//    }

	 // MessageBox (0, "CreateDialog", "CreateDialog11", MB_ICONEXCLAMATION | MB_OK);
   // return msg2.wParam;



	////
	//////////
////////////////////////////////////







			ShowWindow(winEq, SW_SHOW); 
	//DialogBox(hInstance,(LPCSTR)IDD_DIALOG1,0,&dialogproc);  // (char*)
	ShowWindow(win, SW_SHOWNORMAL);
	////

	while (GetMessage(&msg,NULL,0,0)>0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


//

BOOL CALLBACK dialogproc(HWND h,UINT m,WPARAM w,LPARAM l)
{
	//winEq=h;
	switch (m) 
	{
	case WM_COMMAND:
		switch (LOWORD(w)) 
		{
			case IDCANCEL:
				DestroyWindow(h);
				break;
			case 10:
				{
					// setup the effects
					int k;
					BASS_DX8_PARAMEQ p;
					p.fGain=0;
					p.fBandwidth=19;  
					for (k=0; k<19; k++)
					{
						fx[k]=BASS_ChannelSetFX(chan,BASS_FX_DX8_PARAMEQ,0);
						p.fCenter=FCenter[k];
						BASS_FXSetParameters(fx[k],&p);
						UpdateFX(k);
					}
      			}
				break;
		}
		break;

	case WM_VSCROLL:
		if (l) 
		{
			UpdateFX(GetDlgCtrlID((HWND)l)-IDC_SLIDER1); //IDC_SLIDER1  20
//			char buf [100];
       // wsprintf (buf, "Error x%x", GetDlgCtrlID((HWND)l)-IDC_SLIDER1);
        //MessageBox (0, "Error x%x", "CreateDialog", MB_ICONEXCLAMATION | MB_OK);
		}
		break;

	case WM_INITDIALOG:
			winEq=h;
			//// check that DX8 features are available
			//BASS_INFO bi={sizeof(bi)};
			//BASS_GetInfo(&bi);
			//if (bi.dsver<8) 
			//{
			//	BASS_Free();
			// 	Error("DirectX 8 is not installed");
			//	DestroyWindow(winEq);
			//}
		
			// initialize eq/reverb sliders
			MESS(IDC_SLIDER1,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER1,TBM_SETPOS,TRUE,0);
			MESS(IDC_SLIDER2,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER2,TBM_SETPOS,TRUE,0);
			MESS(IDC_SLIDER3,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER3,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER4,TBM_SETRANGE,FALSE,MAKELONG(0,30)); //IDC_SLIDER4
			MESS(IDC_SLIDER4,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER5,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER5,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER6,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER6,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER7,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER7,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER8,TBM_SETRANGE,FALSE,MAKELONG(0,30)); //IDC_SLIDER4
			MESS(IDC_SLIDER8,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER9,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER9,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER10,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER10,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER11,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER11,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER12,TBM_SETRANGE,FALSE,MAKELONG(0,30)); //IDC_SLIDER4
			MESS(IDC_SLIDER12,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER13,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER13,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER14,TBM_SETRANGE,FALSE,MAKELONG(0,30)); //IDC_SLIDER4
			MESS(IDC_SLIDER14,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER15,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER15,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER16,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER16,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER17,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER17,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER18,TBM_SETRANGE,FALSE,MAKELONG(0,30)); //IDC_SLIDER4
			MESS(IDC_SLIDER18,TBM_SETPOS,TRUE,30);
			MESS(IDC_SLIDER19,TBM_SETRANGE,FALSE,MAKELONG(0,30));
			MESS(IDC_SLIDER19,TBM_SETPOS,TRUE,30);

			return 1;

		case WM_DESTROY:
		//	BASS_Free();
			break;
	}

		return 0;
}
