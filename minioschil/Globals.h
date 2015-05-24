// Globals.h  вне классов
//

#pragma once
#include "bass.h"

#define SPECWIDTH 368 //368	// ширина дисплея
#define SPECHEIGHT 127	// Высота (изменение требует корректировки палитры тоже)
#define WM_MYMESSAGE WM_USER+5 //

#ifndef _DEBUG
#define ClassName L"AfxFrameOrView100u"
#define ClassNameMDI L"AfxMDIFrame100ud"
#endif
//#pragma warning(push)
//#pragma warning(disable:4005)
#ifdef _DEBUG
#define ClassName L"AfxFrameOrView100ud"
#define ClassNameMDI L"AfxMDIFrame100ud"
#endif
//#pragma warning(pop)

extern CDC specdc;
extern CDC specdc_imp;
extern HBITMAP specbmp;
extern HBITMAP specbmp_imp;
extern BYTE *specbuf;
extern BYTE *specbuf_imp;
extern HRECORD chan;	// recording channel
extern int specmode;
extern HWND hOtherWnd2;
extern UINT uMessageID;
extern signed int interval_max;
extern signed int impuls1;

// display error messages
void ErrorBass(const wchar_t *es);
// Читаем звуковую карту
void CALLBACK UpdateSpectrum(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user);
// - Отправить ток всем заинтересованным
void On_Tok_Message(DWORD tok);
inline void waveform();  //3
inline void waveform_float();  
inline void normal_FFT();  //0
inline void logarithmic_FFT(); //1
inline void form3D(); //2
inline void waveform_imp();
inline void sum(float *buf,BASS_CHANNELINFO ci, int c);

inline void GetImp();
inline CString GetTok(DWORD quietcount);