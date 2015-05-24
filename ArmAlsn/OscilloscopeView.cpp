
// OscilloscopeView.cpp : реализация класса COscilloscopeView
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "MainFrm.h"

#include "OscilloscopeDoc.h"
#include "OscilloscopeFrm.h"
#include "CntrItem.h"
#include "OscilloscopeView.h"
#include "bass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//static RGBQUAD rgbStd256[] =
//{
//	{   0,  0,  0, 0 }, {   0,  0,128, 0 }, {   0,128,  0, 0 }, {   0,128,128, 0 },
//	{ 128,  0,  0, 0 }, { 128,  0,128, 0 }, { 128,128,  0, 0 }, { 192,192,192, 0 },
//	{ 192,220,192, 0 }, { 240,202,166, 0 }, { 238,238,238, 0 }, { 221,221,221, 0 },
//	{ 204,204,204, 0 }, { 187,187,187, 0 }, { 170,170,170, 0 }, { 153,153,153, 0 },
//	{ 136,136,136, 0 }, { 119,119,119, 0 }, { 102,102,102, 0 }, {  85, 85, 85, 0 },
//	{  68, 68, 68, 0 }, {  51, 51, 51, 0 }, {  34, 34, 34, 0 }, {  17, 17, 17, 0 },
//	{ 204,255,255, 0 }, { 153,255,255, 0 }, { 102,255,255, 0 }, {  51,255,255, 0 },
//	{ 255,204,255, 0 }, { 204,204,255, 0 }, { 153,204,255, 0 }, { 102,204,255, 0 },
//	{  51,204,255, 0 }, {   0,204,255, 0 }, { 255,153,255, 0 }, { 204,153,255, 0 },
//	{ 153,153,255, 0 }, { 102,153,255, 0 }, {  51,153,255, 0 }, {   0,153,255, 0 },
//	{ 255,102,255, 0 }, { 204,102,255, 0 }, { 153,102,255, 0 }, { 102,102,255, 0 },
//	{  51,102,255, 0 }, {   0,102,255, 0 }, { 255, 51,255, 0 }, { 204, 51,255, 0 },
//	{ 153, 51,255, 0 }, { 102, 51,255, 0 }, {  51, 51,255, 0 }, {   0, 51,255, 0 },
//	{ 204,  0,255, 0 }, { 153,  0,255, 0 }, { 102,  0,255, 0 }, {  51,  0,255, 0 },
//	{ 255,255,204, 0 }, { 204,255,204, 0 }, { 153,255,204, 0 }, { 102,255,204, 0 },
//	{  51,255,204, 0 }, {   0,255,204, 0 }, { 255,204,204, 0 }, { 153,204,204, 0 },
//	{ 102,204,204, 0 }, {  51,204,204, 0 }, {   0,204,204, 0 }, { 255,153,204, 0 },
//	{ 204,153,204, 0 }, { 153,153,204, 0 }, { 102,153,204, 0 }, {  51,153,204, 0 },
//	{   0,153,204, 0 }, { 255,102,204, 0 }, { 204,102,204, 0 }, { 153,102,204, 0 },
//	{ 102,102,204, 0 }, {  51,102,204, 0 }, {   0,102,204, 0 }, { 255, 51,204, 0 },
//	{ 204, 51,204, 0 }, { 153, 51,204, 0 }, { 102, 51,204, 0 }, {  51, 51,204, 0 },
//	{   0, 51,204, 0 }, { 255,  0,204, 0 }, { 204,  0,204, 0 }, { 153,  0,204, 0 },
//	{ 102,  0,204, 0 }, {  51,  0,204, 0 }, { 255,255,153, 0 }, { 204,255,153, 0 },
//	{ 153,255,153, 0 }, { 102,255,153, 0 }, {  51,255,153, 0 }, {   0,255,153, 0 },
//	{ 255,204,153, 0 }, { 204,204,153, 0 }, { 153,204,153, 0 }, { 102,204,153, 0 },
//	{  51,204,153, 0 }, {   0,204,153, 0 }, { 255,153,153, 0 }, { 204,153,153, 0 },
//	{ 102,153,153, 0 }, {  51,153,153, 0 }, {   0,153,153, 0 }, { 255,102,153, 0 },
//	{ 204,102,153, 0 }, { 153,102,153, 0 }, { 102,102,153, 0 }, {  51,102,153, 0 },
//	{   0,102,153, 0 }, { 255, 51,153, 0 }, { 204, 51,153, 0 }, { 153, 51,153, 0 },
//	{ 102, 51,153, 0 }, {  51, 51,153, 0 }, {   0, 51,153, 0 }, { 255,  0,153, 0 },
//	{ 204,  0,153, 0 }, { 153,  0,153, 0 }, { 102,  0,153, 0 }, {  51,  0,153, 0 },
//	{ 255,255,102, 0 }, { 204,255,102, 0 }, { 153,255,102, 0 }, { 102,255,102, 0 },
//	{  51,255,102, 0 }, {   0,255,102, 0 }, { 255,204,102, 0 }, { 204,204,102, 0 },
//	{ 153,204,102, 0 }, { 102,204,102, 0 }, {  51,204,102, 0 }, {   0,204,102, 0 },
//	{ 255,153,102, 0 }, { 204,153,102, 0 }, { 153,153,102, 0 }, { 102,153,102, 0 },
//	{  51,153,102, 0 }, {   0,153,102, 0 }, { 255,102,102, 0 }, { 204,102,102, 0 },
//	{ 153,102,102, 0 }, {  51,102,102, 0 }, {   0,102,102, 0 }, { 255, 51,102, 0 },
//	{ 204, 51,102, 0 }, { 153, 51,102, 0 }, { 102, 51,102, 0 }, {  51, 51,102, 0 },
//	{   0, 51,102, 0 }, { 255,  0,102, 0 }, { 204,  0,102, 0 }, { 153,  0,102, 0 },
//	{ 102,  0,102, 0 }, {  51,  0,102, 0 }, { 255,255, 51, 0 }, { 204,255, 51, 0 },
//	{ 153,255, 51, 0 }, { 102,255, 51, 0 }, {  51,255, 51, 0 }, {   0,255, 51, 0 },
//	{ 255,204, 51, 0 }, { 204,204, 51, 0 }, { 153,204, 51, 0 }, { 102,204, 51, 0 },
//	{  51,204, 51, 0 }, {   0,204, 51, 0 }, { 255,153, 51, 0 }, { 204,153, 51, 0 },
//	{ 153,153, 51, 0 }, { 102,153, 51, 0 }, {  51,153, 51, 0 }, {   0,153, 51, 0 },
//	{ 255,102, 51, 0 }, { 204,102, 51, 0 }, { 153,102, 51, 0 }, { 102,102, 51, 0 },
//	{  51,102, 51, 0 }, {   0,102, 51, 0 }, { 255, 51, 51, 0 }, { 204, 51, 51, 0 },
//	{ 153, 51, 51, 0 }, { 102, 51, 51, 0 }, {   0, 51, 51, 0 }, { 255,  0, 51, 0 },
//	{ 204,  0, 51, 0 }, { 153,  0, 51, 0 }, { 102,  0, 51, 0 }, {  51,  0, 51, 0 },
//	{ 204,255,  0, 0 }, { 153,255,  0, 0 }, { 102,255,  0, 0 }, {  51,255,  0, 0 },
//	{ 255,204,  0, 0 }, { 204,204,  0, 0 }, { 153,204,  0, 0 }, { 102,204,  0, 0 },
//	{  51,204,  0, 0 }, { 255,153,  0, 0 }, { 204,153,  0, 0 }, { 153,153,  0, 0 },
//	{ 102,153,  0, 0 }, {   0,  0,238, 0 }, {   0,  0,221, 0 }, {   0,  0,204, 0 },
//	{   0,  0,187, 0 }, {   0,  0,170, 0 }, {   0,  0,153, 0 }, {   0,  0,136, 0 },
//	{   0,  0,119, 0 }, {   0,  0,102, 0 }, {   0,  0, 85, 0 }, {   0,  0, 68, 0 },
//	{   0,  0, 51, 0 }, {   0,  0, 34, 0 }, {   0,  0, 17, 0 }, {   0,238,  0, 0 },
//	{   0,221,  0, 0 }, {   0,204,  0, 0 }, {   0,187,  0, 0 }, {   0,170,  0, 0 },
//	{   0,153,  0, 0 }, {   0,136,  0, 0 }, {   0,119,  0, 0 }, {   0,102,  0, 0 },
//	{   0, 85,  0, 0 }, {   0, 68,  0, 0 }, {   0, 51,  0, 0 }, {   0, 34,  0, 0 },
//	{   0, 17,  0, 0 }, { 238,  0,  0, 0 }, { 221,  0,  0, 0 }, { 204,  0,  0, 0 },
//	{ 187,  0,  0, 0 }, { 170,  0,  0, 0 }, { 153,  0,  0, 0 }, { 136,  0,  0, 0 },
//	{ 119,  0,  0, 0 }, { 102,  0,  0, 0 }, {  85,  0,  0, 0 }, {  68,  0,  0, 0 },
//	{  51,  0,  0, 0 }, {  34,  0,  0, 0 }, { 240,251,255, 0 }, { 164,160,160, 0 },
//	{ 128,128,128, 0 }, {   0,  0,255, 0 }, {   0,255,  0, 0 }, {   0,255,255, 0 },
//	{ 255,  0,  0, 0 }, { 255,  0,255, 0 }, { 255,255,  0, 0 }, { 255,255,255, 0 }
//};
//
// COscilloscopeView

IMPLEMENT_DYNCREATE(COscilloscopeView, CView)

BEGIN_MESSAGE_MAP(COscilloscopeView, CView)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, &COscilloscopeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COscilloscopeView::OnFilePrintPreview)
//	ON_WM_TIMER()
	ON_COMMAND(ID_TEST, &COscilloscopeView::OnTest)
END_MESSAGE_MAP()

// создание/уничтожение COscilloscopeView

COscilloscopeView::COscilloscopeView()
{

	// TODO: добавьте код создания

}

COscilloscopeView::~COscilloscopeView()
{
}

BOOL COscilloscopeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
		cs.cx=SPECWIDTH;  //Устанавливает ширину нового окна, в пикселях. 
	cs.cy=SPECHEIGHT;//Устанавливает высоту нового окна, в пикселях.
	cs.lpszName = L"Главное окно приложения \"Стили\"";

	return CView::PreCreateWindow(cs);
}

// рисование COscilloscopeView

void COscilloscopeView::OnDraw(CDC* pDC)
{
	if (!pDC) return;
	COscilloscopeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;
	// TODO: добавьте здесь код отрисовки для собственных данных
	//MemSpecDC.SelectPalette(m_hPalette, FALSE );;
//	m_pOldPalette = (HPALETTE)::SelectPalette( specdcmem, m_hPalette, FALSE );
//	RealizePalette(specdcmem);

//////////////////////////////////////////
//====================================
	PAINTSTRUCT p;
    if (!BeginPaint(&p)) return;
pDC->BitBlt(0,0,SPECWIDTH,SPECHEIGHT,&specdc_i,0,0,SRCCOPY | BLACKNESS);
pDC->BitBlt(0, SPECHEIGHT, SPECWIDTH, SPECHEIGHT, &specdc_can2, 0, 0, SRCCOPY | BLACKNESS); //&specdc1

    EndPaint(&p);   
			//if (!GetUpdateRect(NULL,0)) //Если lpRect параметр установлен к NULL, возвращаемое значение отлично от нуля если область модификации существует, иначе 0.

		 //{
			// //AfxMessageBox(L"rrrr");
			//PAINTSTRUCT p;
   //         CDC *dc;
   //         if (!(dc=BeginPaint(&p))) return;
			//BitBlt(pDC->GetSafeHdc(),0,0,SPECWIDTH,SPECHEIGHT,specdc_i,0,0,SRCCOPY);
   //         EndPaint(&p);
		 //}
}

//BYTE *specbuf_canal1;//не в стеке
//BYTE *specbuf_canal2;//не в стеке


void COscilloscopeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetWindowPos(NULL,0,0,SPECWIDTH,SPECHEIGHT,SWP_SHOWWINDOW);
	// TODO: удалите этот код, когда финальный код модели выбора будет написан
//	m_pSelection = NULL;    // инициализация выделения
	/////////////////////////////////////////////////////////////////
	/////////
	// create bitmap to draw spectrum
	// Создаем контекст устройства в памяти
//==========================================//
	
	         // initialize BASS recording (default device)
   //      if (!BASS_RecordInit(-1)) {
   //         Error(L"Ошибка инициализации устройсва BASS");
   //         return ;
   //      }
   //      // start recording (44100hz mono 16-bit)
   //      if (!(chan=BASS_RecordStart(5513,2,0,&DuffRecording,0))) //5513, 2, 44100
		 //{
   //         Error(L"Ошибка записи");
   //         return ;
   //      }

		 ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////
//specdc_i=0;
specbmp_i=0;
int a;
////////////////////////////////////////////////////
// create bitmap to draw spectrum in (8 bit for easy updating)
            BYTE data[2000]={0};
            BITMAPINFOHEADER *bh=(BITMAPINFOHEADER*)data;
            RGBQUAD *pal=(RGBQUAD*)(data+sizeof(*bh));
            //int a_i;
            bh->biSize=sizeof(*bh);
            bh->biWidth=SPECWIDTH;
            bh->biHeight=SPECHEIGHT; // upside down (line 0=bottom)
            bh->biPlanes=1;
            bh->biBitCount=8; //8 32 не работает
            bh->biClrUsed=bh->biClrImportant=256;
			            // setup palette
            for (a=1;a<128;a++) {
               pal[a].rgbGreen=(BYTE)(256-2*a);
               pal[a].rgbRed=(BYTE)(2*a);
            }
            for (a=0;a<32;a++) {
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
			// create the bitmap
			//memset(pspecbuf_canal1,66,SPECWIDTH*SPECHEIGHT);

			//BYTE specbuf_canal1[SPECWIDTH*SPECHEIGHT];
			//pp BYTE specbuf_canal2[SPECWIDTH*SPECHEIGHT];
            specbmp_i=CreateDIBSection(0,(BITMAPINFO*)bh,DIB_RGB_COLORS,(void**)&specbuf_canal1,NULL,0); //specbuf_i
			_ASSERTE(specbmp_i);
		//	specbmp_i=CreateCompatibleBitmap(0,SPECWIDTH,SPECHEIGHT);//
            specbmp_can2=CreateDIBSection(0,(BITMAPINFO*)bh,DIB_RGB_COLORS,(void**)&specbuf_canal2,NULL,0);
			_ASSERTE(specbmp_can2);
			
			BOOL res = specdc_i.CreateCompatibleDC(this->GetDC()); //pDC->GetSafeHdc()
			_ASSERTE(res);
			res = specdc_can2.CreateCompatibleDC(this->GetDC()); //pDC->GetSafeHdc()
			_ASSERTE(res);

			HGDIOBJ pOldBitmap,pOldBitmap2;
			pOldBitmap = specdc_i.SelectObject(specbmp_i);
			pOldBitmap2 = specdc_can2.SelectObject(specbmp_can2);

//==========================================
////////////////////////////////////////////
	SetTimer(1, 1, NULL); //1000
}

// display error messages
void Error(const wchar_t *es)
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
// печать COscilloscopeView


void COscilloscopeView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL COscilloscopeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void COscilloscopeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void COscilloscopeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void COscilloscopeView::OnDestroy()
{
   if (specdc) DeleteDC(specdc);
   if (specbmp) DeleteObject(specbmp);

   CView::OnDestroy();
}



void COscilloscopeView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	SetWindowPos(this,0,0,SPECWIDTH,SPECHEIGHT,SWP_SHOWWINDOW);

}

void COscilloscopeView::OnSize(UINT nType, int cx, int cy)
{
	UNREFERENCED_PARAMETER(nType);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
//	CView::OnSize(nType, cx, cy);
//	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
//	if (pActiveItem != NULL)
//		pActiveItem->SetItemRects();
}

void COscilloscopeView::OnFilePrint()
{
	//По умолчанию печать активного документа запрашивается
	//с помощью IOleCommandTarget. Если такое поведение не требуется,
	//удалите вызов COleDocObjectItem::DoDefaultPrinting.
	//Если вызов будет неудачным по какой-либо причине, мы попробуем напечатать
	//docobject с помощью интерфейса IPrint.
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL); 
	if (S_OK == COleDocObjectItem::DoDefaultPrinting(this, &printInfo))
		return;
	
	CView::OnFilePrint();

}


void COscilloscopeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	UNREFERENCED_PARAMETER(nFlags);
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COscilloscopeView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	UNREFERENCED_PARAMETER(pWnd);
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}



// диагностика COscilloscopeView

#ifdef _DEBUG
void COscilloscopeView::AssertValid() const
{
	CView::AssertValid();
}

void COscilloscopeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COscilloscopeDoc* COscilloscopeView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COscilloscopeDoc)));
	return (COscilloscopeDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений COscilloscopeView
int ttt;

//void COscilloscopeView::OnTimer(UINT nIDEvent)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	//UpdateSpectrum();
//	// = AfxGetApp();;//new COscilloscopeFrm; //NULL ; //
//	//ofrm->GetWindow(0);// = (COscilloscopeFrm*) ::GetWindow(); //AfxGetMainWnd();
//
//										  
//	CString m_strCpu;
//	m_strCpu.Format(L"CPU-%.0f%%",BASS_GetCPU());
//	
//	// Ищем копию нашего приложения
//	CWnd *pWnd = CWnd::FindWindowExW(NULL, NULL, NULL, L"Осциллограф1 - Осциллограмы");
//	// Если таковая есть, то ...
//	if(pWnd != NULL) 
//	{ 
//		COscilloscopeFrm *frm =	(COscilloscopeFrm*) pWnd;
//		frm->OnSetStatusBar(4,m_strCpu);
//	}
//	
//
//	++ttt;	
//	m_strCpu.Format(L"%d",ttt);
//	//COscilloscopeFrm *scr = (COscilloscopeFrm*) AfxGetApp()->m_pMainWnd; //m_pMainWnd)m_pActiveWnd
//	//COscilloscopeFrm *dst = dynamic_cast<COscilloscopeFrm*>(scr);
//
//	//dst->OnSetStatusBar(1,L"11");
//	//scr = theApp.m_OscilloscopeFrm;
///	typedef void (COscilloscopeFrm :: *POnSetStatusBar)(int,CString);
///	POnSetStatusBar pmf = &COscilloscopeFrm::OnSetStatusBar;
//	//COscilloscopeFrm *scr = new COscilloscopeFrm();
///		(scr->*pmf)(1,L"566");
//
//			/// выводим в статусную строку CMainFrame
//	//COscilloscopeFrm* pFrame = (COscilloscopeFrm*) AfxGetApp()->m_pActiveWnd;
//	//pFrame->OnSetPaneText(L"567890ewe");
//
//	//COscilloscopeFrm::OnSetStatusBar(0,L"567890ewe");
//		//CWnd *Stb123;
//	COscilloscopeFrm *frm =	(COscilloscopeFrm*) Stb123;
//	//frm->OnSetPaneText(L"567890ewe");
//
//	COscilloscopeFrm::m_wndStatusBar1.SetPaneText(1,L"444",1);
//	//	CMainFrame* pFrame;// = (CMainFrame*) AfxGetApp()->m_pMainWnd; //m_pMainWnd;m_pActiveWnd
//	
//	//	pFrame->m_wndStatusBar.SetPaneText(3,m_strCpu,1);
//		
//		//pFrame->m_wndStatusBar.SetPaneText(3,m_strCpu,1);
//		
//
//
//
//
//
//
//	//ofrm.OnSetStatusBar(1,L"11");
//	InvalidateRect(NULL,FALSE);//TRUE FALSE
//	UpdateWindow();
//	//AfxMessageBox(L"timer");
//	CView::OnTimer(nIDEvent);
//}


// Читаем звуковую карту
void COscilloscopeView::UpdateSpectrum(void)
{

}


void COscilloscopeView::OnTest()
{
	// TODO: добавьте свой код обработчика команд
	
		// Заголовок будем брать из ресурсов
//CString csCaption;
//BOOL rescap = csCaption.LoadStringW(IDR_OSCILLOSCOPEFRAME);


}


//BOOL COscilloscopeView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
//{
//	// TODO: добавьте специализированный код или вызов базового класса
//		CString str;
//	switch (message)
//	{
//		case WM_MYTIMER:
//			AfxMessageBox (_T("Таймер on"), NULL, 0);
//			// Именно наш таймер
//		//	ASSERT (cvp.timer);
//			if (wParam != 1)
//			{
//				str.Format(L"%d" ,	 wParam );
//				AfxMessageBox(str);
//			}
//		if (wParam == 55555)
//		{
//			  AfxMessageBox (_T("Таймер on"), NULL, 0);
//		}
//	
//		break;
//	}
//
//
//	return CView::OnWndMsg(message, wParam, lParam, pResult);
//}
