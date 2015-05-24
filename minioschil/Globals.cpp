//
//

#include "StdAfx.h"
#include "Globals.h"
#include "bass.h"
#include <math.h>

DWORD quietcountInt=0;
DWORD quietcountImp=0;
DWORD quietcountInt1=0;
int quietcountIntN=0;

// display error messages
void ErrorBass(const wchar_t *es)
{
	CString mm,mes;    //(L"",200);
	switch (BASS_ErrorGetCode())
	{ 
	case 1:
		mm = L"";
		break;
	case 2:
		mm = L"";
		break;
	case 3:
		mm = L"";
		break;
	case BASS_ERROR_BUFLOST:
		mm = L"4. Не должен произойти... проверьте, что допустимый дескриптор окна использовался с BASS_Init.";
		break;
	case BASS_ERROR_HANDLE:// 5 Канал не существует:
		mm = L"5. Дескриптор на не допустимый канал. ";
		break;
	case 9:
		mm = L"9";
		break;
	case 6:
		mm = L"6";
		break;
	case 7:
		mm = L"7";
		break;
	case 8:
		mm = L"8";
		break;
	case BASS_ERROR_NOTAVAIL:
		mm = L"37. Флаг BASS_DATA_AVAILABLE был использован с каналом декодирования.";
		break;
	case BASS_ERROR_ENDED:
		mm = L"45. Канал достиг конца";
		break;
	}


	mes.Format(L"Ошибка №: %s",mm);
	MessageBox(0,mes,es,0);
}

BYTE *specbuf;
BYTE *specbuf_imp;
// Читаем звуковую карту
void CALLBACK UpdateSpectrum(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	//CDC *pDC = (CDC*)dwUser;// через функцию (не работает)
	UNREFERENCED_PARAMETER(uTimerID);
	UNREFERENCED_PARAMETER(uMsg);
	UNREFERENCED_PARAMETER(dwUser);
	UNREFERENCED_PARAMETER(dw1);
	UNREFERENCED_PARAMETER(dw2);
	static DWORD quietcount=0;
	
	if (specmode==3) 
	{
		//waveform();
		waveform_float();
		//GetImp();
	}
	if (specmode==2) form3D();
	if (specmode==1) logarithmic_FFT();
	if (!specmode) normal_FFT();

	// update the display
	RECT r={1,2,3,4};
	CWnd *wnd = AfxGetApp()->m_pMainWnd;
	// Таймер так быстр, что окно раньше уничтожается, чем таймер
	if (!wnd) return;
	CDC *pDC = wnd->GetDC() ;  //AfxGetApp()->m_pMainWnd->GetDC
	pDC->BitBlt(0,0,SPECWIDTH,SPECHEIGHT,&specdc,0,0,SRCCOPY);
	
	//////////////////////////////////////////////////////////////////////////
	////
	waveform_imp();
	pDC->BitBlt(0,SPECHEIGHT,SPECWIDTH,SPECHEIGHT/2,&specdc_imp,0,0,SRCCOPY);
	///
	//////////////////////////////////////////////////////////////////////////

	// Надписи
	pDC->SetTextColor(0xffffff);  //rrbbgg
	pDC->SetBkMode(TRANSPARENT);
	CString ssTok = GetTok(quietcount);   //ssTok=L"НЕТ КОДОВ!";
	if (ssTok==L"НЕТ КОДОВ!")  // Нет кодирования
	{
		RECT r1={0,0,SPECWIDTH,SPECHEIGHT};
		r = r1;
		PostMessage(hOtherWnd2, uMessageID , 0, 0 );
	}
	else 
	{
		RECT r1={SPECWIDTH*2-90,0,20,20};
		r = r1;
	}
	// Показать значение тока
	pDC->DrawText(ssTok,-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE); //AS
	///////////////////////////
	//AfxGetApp()->m_pMainWnd->ReleaseDC(pDC); --ошибка доступа

	// Показать длину интервала
	RECT r2={0,0,100,20};
	ssTok.Format(L"%dc %dN",quietcountInt1, quietcountIntN);    
	pDC->DrawText(ssTok,-1,&r2,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	
}

///////////////////
// Recording callback - not doing anything with the data
BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	UNREFERENCED_PARAMETER(handle);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(length);
	UNREFERENCED_PARAMETER(user);
	return TRUE; // continue recording
}
int Int1 = 0; // значение тока

// Осцилограмма 
void waveform()
{
	short buf[SPECWIDTH];
	memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
	BASS_ChannelGetData(chan,buf,sizeof(buf)); // get the sample data
	int y=0;
	for (int x=0;x<SPECWIDTH;x++) 
	{
		//x=x/2;
		int v=(32767-buf[x])*SPECHEIGHT/65536; //32767 invert and scale to fit display
		if (!x) y=v;
		do { // draw line from previous sample...
			if (y<v) y++;
			else if (y>v) y--;
#pragma warning(push)
#pragma warning(disable:4244)
			specbuf[y*SPECWIDTH+x]=abs(y-SPECHEIGHT/2)+1;
#pragma warning(pop)
		} while (y!=v);
	}


}
///////////////////
//
void waveform_float()
{
	int x=0,y=0;
	unsigned int c=0;
	float *buf;
	BASS_CHANNELINFO ci;
	memset(specbuf,0xFF,SPECWIDTH*SPECHEIGHT); //0 0xffffff, ff - белый 0xRRGGBB
	BASS_ChannelGetInfo(chan,&ci); // get number of channels
	buf=(float*) alloca(ci.chans*SPECWIDTH*sizeof(float)); // allocate buffer for data
	BASS_ChannelGetData(chan,buf,(ci.chans*SPECWIDTH*sizeof(float))|BASS_DATA_FLOAT); // get the sample data (floating-point to avoid 8 & 16 bit processing)
	for (c=0;c<ci.chans;c++)
	{
		for (x=0;x<SPECWIDTH;x++) 
		{
			int v=(int)((1-buf[x*ci.chans+c])*SPECHEIGHT/2); // invert and scale to fit display
			if (v<0) v=0;
			else if (v>=SPECHEIGHT) v=SPECHEIGHT-1;
			if (!x) y=v;
			do 
			{ // draw line from previous sample...
				if (y<v) y++;
				else if (y>v) y--;
				specbuf[y*SPECWIDTH+x]=c&1?127:1; // left=green, right=red (could add more colours to palette for more chans)
			} while (y!=v);
		}
	}


}



int specpos=0; // spectrum mode (and marker pos for 2nd mode)
// "3D"
void form3D()
{
	float fft[1024];
	BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data
	for (int x=0;x<SPECHEIGHT;x++) 
	{
		int y=(int)(sqrt(fft[x+1])*3*127); // scale it (sqrt to make low values more visible)
		if (y>127) y=127; // cap it
#pragma warning(push)
#pragma warning(disable:4244)
		specbuf[x*SPECWIDTH+specpos]=128+y; // plot it
#pragma warning(pop)
	}
	// move marker onto next position
	specpos=(specpos+1)%SPECWIDTH;
	for (int x=0;x<SPECHEIGHT;x++) specbuf[x*SPECWIDTH+specpos]=255;
}// "3D" END




void logarithmic_FFT()
{
	float fft[1024];
	BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data
	int b0=0;
	memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
#define BANDS 28
	for (int x=0;x<BANDS;x++) 
	{
		float peak=0;
		int b1=(int)(pow(2,x*10.0/(BANDS-1)));
		if (b1>1023) b1=1023;
		if (b1<=b0) b1=b0+1; // make sure it uses at least 1 FFT bin
		for (;b0<b1;b0++)
		if (peak<fft[1+b0]) peak=fft[1+b0];
		int y=(int)(sqrt(peak)*3*SPECHEIGHT-4); // scale it (sqrt to make low values more visible)
		if (y>SPECHEIGHT) y=SPECHEIGHT; // cap it
		while (--y>=0)
#pragma warning(push)
#pragma warning(disable:4244)
		memset(specbuf+y*SPECWIDTH+x*(SPECWIDTH/BANDS),y+1,0.9*(SPECWIDTH/BANDS)); // draw bar
#pragma warning(pop)
	}


}



// "normal" FFT  0
void normal_FFT()
{
	int y1=0;
	float fft[1024];
	BASS_ChannelGetData(chan,fft,BASS_DATA_FFT2048); // get the FFT data

	memset(specbuf,0,SPECWIDTH*SPECHEIGHT);
	for (int x=0;x<SPECWIDTH/2;x++) 
	{
#if 1
		int y=(int)(sqrt(fft[x+1])*3*SPECHEIGHT-4); // scale it (sqrt to make low values more visible)
#else
		y=fft[x+1]*10*SPECHEIGHT; // scale it (linearly)
#endif
		if (y>SPECHEIGHT) y=SPECHEIGHT; // cap it
//#pragma warning(push)
//#pragma warning(disable:4706)
		if ((x!= 0) && (y1=(y+y1)/2) != 0) // interpolate from previous to make the display smoother
//#pragma warning(pop)	
#pragma warning(push)
#pragma warning(disable:4244)
		while (--y1>=0) specbuf[y1*SPECWIDTH+x*2-1]=y1+1;
		y1=y;
		while (--y>=0) specbuf[y*SPECWIDTH+x*2]=y+1; // draw level
#pragma warning(pop)	
	}
		
}





void GetImp()
{
	short buf[SPECWIDTH];
	//////////////////////////////////////////////////////////////////
	///	Первый интервал
	//////////////////////////////////////////////////////////////////
	///
	Int1 = abs(buf[0]);
	int x=0;
		for (int t=0; t<2; t++)
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

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// - Отправить ток всем заинтересованным
//...................................
void On_Tok_Message(DWORD tok)
{
	HWND hOtherWnd,hOtherWnd1;
	hOtherWnd = FindWindow( ClassName, L"Измерение1 - Измерения" ); 
	if ( hOtherWnd )
	{
		// Нашли фрейм окна с названием Измерения
		hOtherWnd1= FindWindowEx(hOtherWnd,NULL,ClassNameMDI,0); //MAKEINTATOM(32770)//hOtherWnd1=(HWND)3216274; //0x00311392
		// Нашли окно диалога с током
		hOtherWnd2= FindWindowEx(hOtherWnd1,NULL,MAKEINTATOM(32770),0); //MAKEINTATOM(32770)
		// Послали значение тока
		//	AS2=6;
		if (tok>0.5) PostMessage(hOtherWnd2, uMessageID , tok, 0 ); //m_tok_c
		tok=0;
	}
	//	else MessageBox( win, "Окно Измерения НЕ найдено", 0, MB_OK );
}
CString GetTok(DWORD quietcount)
{
	CString ssTok;
	DWORD  As=0,AS=0;
	DWORD  AS1=0;
	DWORD  AS2=0;
	int	   s3=0;
	int	n_ms=0	;// число милисисикунд счета тока
	DWORD	m_tok_c=0	;// ток за секунду

	As = BASS_ChannelGetLevel(chan);
	if (LOWORD(As)<500) //400   -- Это НЕТ сигнала или интервал
	{ // check if it's quiet
		quietcount++;
		if ((quietcount>16))	  //18 16  && (quietcount<=30)
		{
			AS=0;
		}
		if (quietcount>40 && (quietcount&16)) 
		{ // пауза и мигание it's been quiet for over a second
			return L"НЕТ КОДОВ!";
		}
	}
	else //cигнал
	{
		quietcount=0; // not quiet
		if (AS<As) AS=As;
	}
	//////
	AS1 = LOWORD(AS); //AS
	AS2 = AS1/80;	 //	 176.5	 Наш ток
	s3=AS2/10;
// return AS2;
	if (n_ms<15) 
	{
		if (m_tok_c<AS2) m_tok_c=AS2;	  //AS
		n_ms++;
	}
	else  n_ms=0;

	ssTok.Format(L"%d.%d А",AS2/10,AS2-s3*10);       //LOWORD(AS)/113);
	
	On_Tok_Message(m_tok_c);
	if (AS==0) return L"";
	return ssTok;
}


void waveform_imp()
{
	int y=0;
	unsigned int x=0,c=0;
	float *buf;
	BASS_CHANNELINFO ci;
	memset(specbuf_imp,0,SPECWIDTH*SPECHEIGHT/2); //0 0xffffff, ff - белый 0xRRGGBB
	BASS_ChannelGetInfo(chan,&ci); // get number of channels
	/* захватывает память в стеке  */
	buf=(float*) alloca(ci.chans*SPECWIDTH*sizeof(float)+1); // allocate buffer for data
	//memset(buf,0,ci.chans*SPECWIDTH*sizeof(float));
	BASS_ChannelGetData(chan,buf,(ci.chans*SPECWIDTH*sizeof(float))|BASS_DATA_FLOAT); // get the sample data (floating-point to avoid 8 & 16 bit processing)
	for (c=0;c<ci.chans;c++) //для каждого канала
	{
		int v=0;
//		int g,g2;
		for (x=0;x<SPECWIDTH;x++) 
		{
			// v = (1-buf[x])*высота/2
			//g=buf[x*ci.chans+c];
			//g2=(buf[x*ci.chans+c])*SPECHEIGHT/4;


			

			v=(int) ((1-buf[x*ci.chans+c])*SPECHEIGHT/4); // invert and scale to fit display тк наш экран в 2 раза ниже
			
			//нижняя половина
			//if (v<SPECHEIGHT/2) v=SPECHEIGHT/1-v;
			
			if (v<0) v=0;
			//else 

			//////////////////////////////////////////////////////////////////////////
			//p
			// НОЛЬ = SPECHEIGHT/2
			#define NOLL 1

			//v=v-SPECHEIGHT/4; // положение на экране
			
			if (v>(SPECHEIGHT/4+NOLL)) v = SPECHEIGHT/2-3;  // 1
			
			//
			if (v<SPECHEIGHT/4) v=SPECHEIGHT/4;  //0
			//v = v-SPECHEIGHT/4;  // опустили
			//if (v>=SPECHEIGHT/2) v=SPECHEIGHT/2-1; // ограничение по высоте-1
			//else v=SPECHEIGHT/4;
			//else v = 0;




			//p
			//////////////////////////////////////////////////////////////////////////
			if (!x) y=v;
			do 
			{ // draw line from previous sample...
				if (y<v) y++;
				else if (y>v) y--;
				specbuf_imp[y*SPECWIDTH+x]=c&1?127:1; // left=green, right=red (could add more colours to palette for more chans)
				
			} while (y!=v);
		}

		///================= +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Вывод нижнего графика
		long vv;
		interval_max=0;
		impuls1=0;
		for (x=0;x<SPECWIDTH;x++) 
		{
			vv= buf[x*ci.chans+c]; // invert and scale to fit display тк наш экран в 2 раза ниже  (int)
			if (vv<0.0) vv=abs(vv);
			if (vv>0.05) 
			{
				v=20;  //
				interval_max=0;
				impuls1++;
				if (impuls1>30)
				{
					//AfxMessageBox(L"Импульс");
					impuls1=0;
					interval_max=0;
				}
			}
			else 
			{
				v=0;
				interval_max++;
				if (interval_max>100)
				{ 
					//AfxMessageBox(L"Большой интервал");
					impuls1=0;
					interval_max=0;
				}
			}
			//if (v>(SPECHEIGHT/4+NOLL) || (SPECHEIGHT/4-3)<v<(SPECHEIGHT/4)) v = SPECHEIGHT/4 ;  // 0
			//if (v<(SPECHEIGHT/4)) v = SPECHEIGHT/4;  // 0
			//
			//if (v<SPECHEIGHT/4-NOLL) v=SPECHEIGHT/2-3;   //1
			if (!x) y=v;
			y=0;
			do 
			{ // draw line from previous sample...
				if (y<v) y++;
				//else if (y>v) y--;
				
				specbuf_imp[y*SPECWIDTH+x]=c&1?127:1; // left=green, right=red (could add more colours to palette for more chans)
				
			} while (y!=v);
		}
		/// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		///////////++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Апроксимация
		////=============
//sum(buf,ci,c);
//		///=================
//
//	for (x=0;x<SPECWIDTH;x++) 
//		{
//			v=(int) ((1-buf[x*ci.chans+c])*SPECHEIGHT/4); // invert and scale to fit display тк наш экран в 2 раза ниже
//			if (v<0) v=0;
//			if (v>(SPECHEIGHT/4+NOLL)) v = SPECHEIGHT/2-5;  // 1
//			if (v<SPECHEIGHT/4-NOLL) v=SPECHEIGHT/2-5;   //1
//			if (v<SPECHEIGHT/2-5) v=SPECHEIGHT/4;  //0
//			v = v-SPECHEIGHT/4+2;  // опустили
//// Обработка
//			////
//			//if (v<(SPECHEIGHT/4-4)) v=0;
//
//
//
//			// Вывод
//			if (!x) y=v;
//			do 
//			{ // draw line from previous sample...
//				if (y<v) y++;
//				else if (y>v) y--;
//				specbuf_imp[y*SPECWIDTH+x]=c&1?127:1; // left=green, right=red (could add more colours to palette for more chans)
//				
//			} while (y!=v);
//		}
//

		////=============



	}



}
// усредняем (работает неожиданно - уменьшает кол-во точек)
void sum(float *buf,BASS_CHANNELINFO ci, int c)
{
			//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		//p_impuls
//		int pp=0;
		#define Freq 15
		float S=0.0,S1=0; //,S2,S3,S4,S5,S6,S7,S8,S9,S10
//		unsigned int fofor; //x3=Freq,
		int xf=0,xn=0;
		//#define SPECWIDTH 10
//сколько кусков
	//	fofor = SPECWIDTH/Freq;
		//S=5.0;
		do 
		{
			if ((xn<Freq) && (xf<SPECWIDTH))  //368  <=
			{
				//pp=xf+1;
				S=buf[xf*ci.chans+c];    // S=S+buf[xf*ci.chans+c];
				S1=buf[(xf+1)*ci.chans+c];    //368
				if (S1<0) S1=S;
			
				xn++;
				//pp=0;
			}
			else 
			{
				//S=S/xn;
				if (S<S1) S=S1;
				for (xn;xn>0;xn--)
				{
					////pp=xf-xn+1;
					
					buf[(xf-xn)*ci.chans+c]=S;
					S=0;
					S1=0;
					//pp=0;
				}
				xf--;
			}
			
			xf++;
		} while (xf<(SPECWIDTH));

		buf[(xf-1)*ci.chans+c]=S;

		//x=0;
		//
		//////////////////////////////////////////////////////////////////////////

}