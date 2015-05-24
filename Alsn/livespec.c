/*
	BASS "live" spectrum analyser example
	Copyright (c) 2002-2010 Un4seen Developments Ltd.
*/

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "bass.h"
#include "resource.h"

#define SPECWIDTH 1004	// display width 368
#define SPECHEIGHT 127	// height (changing requires palette adjustments too)
#define WM_MYMESSAGE WM_USER+5

HWND win=NULL;
DWORD timer=0;
int impcount;
int m_impcount;

HRECORD chan;	// recording channel

HDC specdc=0;
HBITMAP specbmp=0;
BYTE *specbuf;
int vv=0, Pm=0, MM=0, M=0, II=0, I=0;

//////////////
char ss[] = "1111";
RECT r2={0,0,100,20};

int specmode=3,specpos=0; // spectrum mode (and marker pos for 2nd mode)

// display error messages
void Error(const char *es)
{
	char mes[200];
	wsprintf(mes,"%Is\n(код ошибки: %Id)",es,BASS_ErrorGetCode()); //спецификатор размера "I"
	MessageBox(win,mes,0,0);
}

// update the spectrum display - the interesting bit :)
void CALLBACK UpdateSpectrum(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	static DWORD quietcount=0;
	HDC dc;
	int x,y=0,y1=0;
	RECT r1={0,0,SPECWIDTH,SPECHEIGHT};

	if (specmode==3) { // waveform
		short buf[SPECWIDTH];
		memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
		BASS_ChannelGetData(chan,buf,sizeof(buf)); // get the sample data
		for (x=0;x<SPECWIDTH-1;x++) {
			int v=abs(buf[x]); // ()*SPECHEIGHT/65536 invert and scale to fit display32767+
			if ((v > 5000) || (abs(buf[x+1]) > 5000) ) v=60;
			else v=0;
			if (!x) y=v;
			do { // draw line from previous sample...
				if (y<v) y++;
				else if (y>v) y--;
				specbuf[y*SPECWIDTH+x]=abs(y-SPECHEIGHT/2)*2+1;
			} while (y!=v);
			if (x==1) vv=y;
		}
	} else {
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
		}
	}

	// update the display
	dc=GetDC(win);
	BitBlt(dc,0,0,SPECWIDTH,SPECHEIGHT,specdc,0,0,SRCCOPY);
	if (LOWORD(BASS_ChannelGetLevel(chan))<500) { // check if it's quiet
		quietcount++;
		if (quietcount>40 && (quietcount&16)) { // it's been quiet for over a second
			RECT r={0,0,SPECWIDTH,SPECHEIGHT};
			SetTextColor(dc,0xffffff);
			SetBkMode(dc,TRANSPARENT);
			DrawText(dc,"НЕТ КОДОВ!",-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	} else
		quietcount=0; // not quiet
	
		if (vv==0)
		{
			impcount++;
			//DrawText(dc,"0",-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
		if (vv==60)
		{
			m_impcount=impcount;
			impcount=0;
			wsprintf(ss, " %Id c",m_impcount); // "%dc %dN",m_impcount
			DrawText(dc,ss,-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

			//DrawText(dc,"600",-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

		//////////////////////////////////////////////////////////////////
		/// - Временны к
		if (Pm == 0 && vv == 60)
		{
			MM = M; M = 0; Pm = 1;   // импулс
		}
		if (Pm == 1 && vv == 0)
		{
			II = I; I = 0; Pm = 0;   // интервал
		}

		if (Pm == 1 && vv == 60) M++;
		if (Pm == 0 && vv == 0)  I++;

		wsprintf(ss, "%Idc %Idc",MM, II); // спецификатор размера "I"   
		SetTextColor(dc,0xffffff);	//	0xffffff
		SetBkMode(dc,TRANSPARENT);
		DrawText(dc,ss,-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		


		///
		//////////////////////////////////////////////////////////////////
		

	/*
			sprintf(ss, "%dc %dN",quietcountInt1, quietcountIntN);    
			SetTextColor(dc,0xffffff);	//	0xffffff
			SetBkMode(dc,TRANSPARENT);
			DrawText(dc,ss,-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	*/


	ReleaseDC(win,dc);
}

// Recording callback - not doing anything with the data
BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	return TRUE; // continue recording
}

// window procedure
LRESULT FAR PASCAL SpectrumWindowProc(HWND h, UINT m, WPARAM w, LPARAM l)
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

		case WM_LBUTTONUP:
			specmode=(specmode+1)%4; // swap spectrum mode
			memset(specbuf,0,SPECWIDTH*SPECHEIGHT);	// clear display
			return 0;

		case WM_CREATE:
			win=h;
			// initialize BASS recording (default device)
			if (!BASS_RecordInit(-1)) {
				Error("Can't initialize device");
				return -1;
			}
			// start recording (44100hz mono 16-bit)
			if (!(chan=BASS_RecordStart(400,1,0,&DuffRecording,0))) {
				Error("Can't start recording");
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
			timer=timeSetEvent(25,25,(LPTIMECALLBACK)&UpdateSpectrum,0,TIME_PERIODIC);
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

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc={0};
    MSG msg;

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		MessageBox(0,"An incorrect version of BASS.DLL was loaded",0,MB_ICONERROR);
		return 0;
	}

	// register window class and create the window
	wc.lpfnWndProc = (WNDPROC)SpectrumWindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "BASS-Spectrum";
	if (!RegisterClass(&wc) || !CreateWindow("BASS-Spectrum",
			"BASS \"live\" spectrum (click to toggle mode)",
			WS_POPUPWINDOW|WS_CAPTION|WS_VISIBLE, 200, 200,
			SPECWIDTH+2*GetSystemMetrics(SM_CXDLGFRAME),
			SPECHEIGHT+GetSystemMetrics(SM_CYCAPTION)+2*GetSystemMetrics(SM_CYDLGFRAME),
			NULL, NULL, hInstance, NULL)) {
		Error("Can't create window");
		return 0;
	}
	ShowWindow(win, SW_SHOWNORMAL);

	while (GetMessage(&msg,NULL,0,0)>0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
