// CViewPut.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ViewPut.h"
#include "OscilloscopeFrm.h"
//p
#include "MainFrm.h"
//#include "bass.h
#include "SerialPort.h"
#include <io.h> // для access
#include <math.h>
//#include <mem.h>
//#include <afxdd.h> 
//#include "OscilloscopeFrm.h"

/////


//////////////////
//////////////////// pelix #define SPECWIDTH 3680	// display width ширина
////////
CSerialPort port;  // для потоковых функций
CSerialPort port2;
HANDLE hcomm01 = 0;
HANDLE hcomm02 = 0;

CWinThread *pThread;
CWinThread *pThread2;
HANDLE hThread = NULL;
HANDLE hThread2 = NULL;
CString strPiket;
CString str_2_Piket;

CString RMC;  // Сообщение RMC - Recommended Minimum Specific GNSS Data

//HWND win=NULL;

IDevice* deviceDisko = NULL;
IOscilloscope* oscDisko = NULL ;   //  - интерфейс осциллографа


// диалоговое окно CViewPut

IMPLEMENT_DYNAMIC(CViewPut, CDialog)

			// Внимание free
BYTE *specbuf_canal1;//=(BYTE*)malloc(SPECWIDTH*SPECHEIGHT);//не в стеке
BYTE *specbuf_canal2;//=(BYTE*)malloc(SPECWIDTH*SPECHEIGHT);//не в стеке
//CString *str_specbuf_canal2;

CViewPut::CViewPut(CWnd* pParent /*=NULL*/)
	: CDialog(CViewPut::IDD, pParent)
	 	, m_strAsCen1(_T(""))
		, m_strAsCen2(_T(""))
		, m_strAsimetr(_T(""))
		, m_strPiket(_T(""))
		, m_2_strPiket(_T("Задать"))
		, m_str_Latitude(_T(""))
		, m_str_Longitude(_T(""))
		, m_setpk(0)			// Предустановка
		, m_ipiketkp(1) //+
	//	, m_pkp(0)
	//	, m_pkm(false)
	//  , m_iAnswer(1)
//	, Kanal2(0)
		, m_strsetpk(_T("."))
 //, m_strsetpk(0)				// Предустановка
 , m_2_valueAsCen1(0)
 , m_2_valueAsCen2(0)
 , m_2_valueAsimetr(0)
{
	// на увеличение
	theApp.m_ipiketkp=m_ipiketkp; //1;
  		// Внимание free

	 // Instantiate and initialize the background brush to black.
	m_pEditBkBrush = new CBrush(RGB(0, 0, 0));
}

CViewPut::~CViewPut()
{
//	free(specbuf_canal1);
//	free(specbuf_canal2);
	BASS_RecordFree();
}

void CViewPut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_ASCHEN1, m_strAsCen1);
	DDX_Text(pDX, IDC_ASCHEN2, m_strAsCen2);
	DDX_Text(pDX, IDC_ASIMETR, m_strAsimetr);
	DDX_Text(pDX, IDC_2_ASCHEN1, m_2_valueAsCen1);
	//DDV_MinMaxDouble(pDX, m_2_valueAsCen1, 7, 0);
	DDX_Text(pDX, IDC_2_ASCHEN2, m_2_valueAsCen2);
	DDX_Text(pDX, IDC_2_ASIMETR, m_2_valueAsimetr);
	DDX_Control(pDX, IDC_ASCHEN1, m_chen1);
	DDX_Text(pDX, IDC_1_PK_V, m_strPiket);
	DDX_Text(pDX, IDC_2_PK_V, m_2_strPiket);
	DDX_Text(pDX, IDC_LATITUDE, m_str_Latitude);
	DDX_Text(pDX, IDC_LONGITUDE, m_str_Longitude);
	//	DDX_Text(pDX, IDC_KORECT, m_setpk);
	//	DDV_MinMaxDouble(pDX, m_setpk, 2, 7);
	DDX_Radio(pDX, IDC_SCHETP, m_ipiketkp);


	//	DDX_Text(pDX, IDC_2_ASCHEN2, Kanal2);
	//	DDV_MinMaxDouble(pDX, Kanal2, 2, 7);
	DDX_Text(pDX, IDC_KORECT, m_strsetpk);
	//	DDV_MinMaxDouble(pDX, m_strsetpk, 0, 7);
	//	DDV_MaxChars(pDX, m_strsetpk, 7);
	DDX_Control(pDX, IDC_KORECT, m_corect_pk);
	DDX_Control(pDX, IDC_2_PK_V, m_2_Piket);
	DDX_Control(pDX, IDC_SCHETP, m_piketkp);
	DDX_Control(pDX, IDC_SCHETM, m_piketkm);
}


BEGIN_MESSAGE_MAP(CViewPut, CDialog)
	//	ON_EN_CHANGE(IDC_ASCHEN1, &CViewPut::OnEnChangeAschen1)
	ON_BN_CLICKED(IDCANCEL, &CViewPut::OnBnClickedCancel)
	//	ON_EN_CHANGE(IDC_2_PK_V, &CViewPut::OnEnChange2PkV)
	ON_BN_CLICKED(IDC_PKOK, &CViewPut::OnBnClickedPkok)
	ON_BN_CLICKED(IDC_SCHETM, &CViewPut::OnBnClickedSchetm)
	ON_BN_CLICKED(IDC_SCHETP, &CViewPut::OnBnClickedSchetp)
	ON_EN_CHANGE(IDC_KORECT, &CViewPut::OnEnChangeKorect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD_PK, &CViewPut::OnBnClickedAddPk)
	ON_BN_CLICKED(IDC_INC_PK, &CViewPut::OnBnClickedIncPk)
	ON_BN_CLICKED(IDC_ADD_10M, &CViewPut::OnBnClickedAdd10m)
	ON_BN_CLICKED(IDC_INC_10M, &CViewPut::OnBnClickedInc10m)
//	ON_EN_CHANGE(IDC_2_PK_V, &CViewPut::OnEnChange2PkV)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// обработчики сообщений CViewPut

BOOL CViewPut::OnInitDialog()
{
	// AfxMessageBox (_T("InitDialog"), NULL, 0);
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	      HICON vIconBig = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_VIEWPUTBIG));
          HICON vIconSmall = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_VIEWPUTSMALL));
//        if ((vIconBig==NULL) || (vIconSmall==NULL))
//		{
//			MessageBox(L"Ресурс не найден",L"Ошибка",MB_OK);
//		}
		  this->SetIcon(vIconBig, TRUE);
          this->SetIcon(vIconSmall, FALSE);

		  // Устанавливаем Шрифт киломероожа
		  CFont *objFont = new CFont;
		  objFont->CreateFontW(24, 0, 0, 0, FW_BOLD, FALSE, 0, 0,  //FW_NORMAL
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Arial");
		m_2_Piket.SetFont(objFont);
	/*	
		  // Установим  RGB-цвет текста
		  COLORREF m_textColor;
		  m_textColor = RGB(0, 0, 255);
			//CPaintDC paintDC(this);
			//paintDC.SetTextColor(m_textColor);
		  CDC *pDC = m_2_Piket.GetDC();
		  pDC->SetBkColor(m_textColor);
		  pDC->SetTextColor(RGB(0, 255, 0));
		  //CBrush* m_pEditBkBrush;
		   //m_pEditBkBrush = new CBrush(RGB(0, 0, 0));
		  m_pEditBkBrush->GetSafeHandle();


			pDC->SetTextColor(RGB(0, 255, 0));
			pDC->SetBkColor(RGB(0, 0, 255));
			m_pEditBkBrush->GetSafeHandle();
			
			GetStockObject(GRAY_BRUSH); // NULL_BRUSH
			*/

		 // m_2_Piket.GetStockObject
		  
		 // m_2_Piket.SetReadOnly(1);

//free(specbuf_canal1);
//free(specbuf_canal2);
//p_free specbuf_canal1=(BYTE*)malloc(SPECWIDTH*SPECHEIGHT);//не в стеке
//specbuf_canal2=(BYTE*)malloc(SPECWIDTH*SPECHEIGHT);//не в стеке
// пробуем заменить на строку
CString str_specbuf_canal2;
str_specbuf_canal2.GetBuffer(SPECWIDTH*SPECHEIGHT);
//pstr_specbuf_canal2	 = &str_specbuf_canal2;

	kmpk_tek=0;
	

	// берем данные из dat
	//if (!CanSerialize())  // проверка, что файл есть
	//{
		CFile file;
		CFileException fe;
		//CFileStatus;

		if (file.Open(DATA_FILE_DAT, CFile::typeBinary | CFile::modeRead, &fe))
		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
			UpdateData(FALSE);
		}
		else 
		{
			AfxMessageBox( _T("Ошибка чтения файла данных .dat"));
			file.Open(DATA_FILE_DAT, CFile::typeBinary | CFile::modeCreate | CFile::modeWrite, &fe);
		}

		file.Close();
	//}
	//else AfxMessageBox( _T("Ошибка 2  файл данных .dat не найден"));

	///////////////////
	//	CString str;
	//	str.Format(_T("№ Устройства %x"), m_configdat.m_curDirectXSound1);
	//	AfxMessageBox(str,0,0);
	///////////////////
	////////////////////////////////////////////////////////////////////////////
		
    ////////////////////////////////////////////////////////////////////////////////	
	// Прежде чем воспользоваться функциями BASS, необходимо выполнить инициализацию звуковой подсистемы.
	// Исключение составляют лишь функции записи звука, которые доступны без предварительной инициализации.

	/* Мне не нужно пока
	if (!BASS_Init (m_configdat.m_curDirectXSound1,  // № Устройства (-1 - по умолчанию, -2 - без звука).
						22050,	// частота дискретизации в Герцах для выходного микшера (Output sample rate) 
						0 ,		// комбинация флагов, объединенных логическим ИЛИ и устанавливающим параметры работы устройства воспроизведения. 
						0,		// дескриптор окна приложения, с которым будет связано воспроизведение звука. Значение 0 соответствует текущему окну
						NULL))  // идентификатор DirectSound, который библиотека BASS должна использовать для инициализации DirectSound
	{
		AfxMessageBox (_T("Не удалось инициализировать BASS"), NULL, 0);
		return TRUE;
	}
	*/
	

	//***************************************************************** 

	
	// Функция BASS_GetVersion возвращает номер версии в виде 32-разрядного шестнадцатеричного числа. 
	// Например, результат 0x0203 соответствует версии 2.3
	DWORD vvv =	HIWORD(BASS_GetVersion());
	if (vvv != BASSVERSION) 
	{
		CString str;
		str.Format(_T("Нужна версия библиотеки BASS %s, а у Вас %x.%x"), // %x.%x
					_T(BASSVERSIONTEXT) , vvv/256,		// BASSVERSION/256, (BASSVERSION - BASSVERSION/16*16)
					vvv-vvv/16*16 );
		AfxMessageBox (str, NULL, 0);
		return false; //1 TRUE
	}
	////////////////////////////////////////////////////////////////////////////
	// Устройсва записи нумеруются с 0, а уменя с 1
	if (!BASS_RecordInit(m_configdat.m_curDirectXCapture1 - 1))	// m_configdat.m_curDirectXCapture1
				//Error("Can't initialize device")

	
	{
		AfxMessageBox (_T("Не удалось начать запись BASS \n Провере устройство записи"), NULL, 0);
		return false; //TRUE
	}


	// start recording (44100hz mono 16-bit)
	//The number of channels... 1 = mono, 2 = stereo, etc...
	// Комбинация флагов по умолчанию 16-bit
	// callback функция записи &DuffRecording		
	// Пользовательские данные экземпляра класса

	
			BASS_SetConfig(BASS_CONFIG_UPDATETHREADS, 1); 
								//5513	
			chancap1 = BASS_RecordStart(500, 2, 0, &DuffRecording, 0);
	if (!chancap1) 
		{
			AfxMessageBox (_T("Не удалось начать запись BASS"), NULL, 0);			
	//		Error("Can't start recording");
			return FALSE;
		}

	//		CString str;
	//		str.Format(_T("Канал RecordStart %x"), chancap1 );
	//		AfxMessageBox (str, NULL, 0);

	//////////////////////////////////////////////////////////

	m_strPiket.SetString(L"СОМ не открыт");
	m_2_strPiket.SetString(L"СОМ не открыт");
	m_strAsCen1.SetString(_T("Кат.1"));
	m_strAsCen2.SetString(_T("Кат.2"));
	m_strAsimetr.SetString(_T("Ассим."));
	UpdateData(false); //метод для передачи в контролы окна

	//OpenComPort(1,m_configdat.m_strComPort1);
	//	::Sleep(300);
	//OpenComPort(2,m_configdat.m_2_strComPort1);

	
	int pr;
	pr = m_configdat.m_strComPort1.Compare(L"Не использовать");
	//Назначение первый порт
	if (pr) 
	{
		CFileStatus status;
		CString ssport;
		ssport.Format(L"\\\\.\\%s",m_configdat.m_strComPort1.Left(5));

		if (CFile::GetStatus(ssport, status))
		{
			port01.Open(ComPortStrtoInt(m_configdat.m_strComPort1));
			port01.Set0ReadTimeout();  // без этого подвисает
		}
		else
		{
			CString sss;
			sss.Format(L"Порт %s не найден или не доступен, \r\n \r\n      Проверте настройки",m_configdat.m_strComPort1);
			AfxMessageBox(sss);
		}
	}
	pr =  m_configdat.m_2_strComPort1.Compare(L"Не использовать");
	// Назначение второй порт
	if (pr)	
	{
		CFileStatus status; //m_configdat.m_2_strComPort1
		CString ssport;
		ssport.Format(L"\\\\.\\%s",m_configdat.m_2_strComPort1.Left(5));
		if (CFile::GetStatus(ssport, status))
		{
			port02.Open(ComPortStrtoInt(m_configdat.m_2_strComPort1), 
											115200,CSerialPort::NoParity,8,
											CSerialPort::OneStopBit, CSerialPort::NoFlowControl,0);
			port02.Set0ReadTimeout();  // без этого подвисает
		}
				else
		{
			CString sss;
			sss.Format(L"Порт %s не найден или не доступен, \r\n \r\n            \t   Проверте настройки",m_configdat.m_2_strComPort1);
			AfxMessageBox(sss);
		//	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd());
		//	theApp.m_pMainWnd->ShowWindow(SW_RESTORE);
		//	//pMainFrame->ShowWindow(SW_RESTORE);
		//	pMainFrame->ShowWindow(SW_RESTORE);
		//	pMainFrame->OnConfigApp();
		//	//OnCancel();
			//CViewPut::OnBnClickedCancel();
		}

	}
	//if (!port02.IsOpen()) AfxMessageBox(L"ERROR");
		//	CFileException fe;
	/*
		if (!asfile.Open(_T("Data\\asim.txt"), //, &fe
			CFile::modeCreate |
			CFile::modeNoTruncate |	// если существует - дописать
			CFile::modeWrite |
			CFile::typeText, &fe))
		{
			fe.ReportError();
		}
*/
			
			if (!asimfile.Open(_T("Data\\asim.txt"), // &fe
					CFile::modeCreate |
					CFile::modeNoTruncate |	// если существует - дописать
					CFile::modeReadWrite, &fe))
		{
			fe.ReportError();
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/// Диско
	if (m_configdat.m_disko_onof)
	{
		if (!OnInitOscilloscopeDisko())
		{
			AfxMessageBox(_T("Осциллограф Диско не обнаружен"));
			m_configdat.m_disko_onof=false;
		}
		//else  AfxMessageBox(_T("Осциллограф Диско включен"));
	}

		// setup update timer (25 - 4hz)2c 1c	  950 50
	timer = timeSetEvent(750,	//  — интервал времени до наступления таймерного события в миллисекундах.
						20,	//  — разрешение таймера при отсчете интервала, в миллисекундах. Нулевое значение требует максимально возможного разрешения 
						(LPTIMECALLBACK) &UpdateAsim, //  — указатель функции уведомления.
						(DWORD)this, //  — произвольное 32-разрядное значение, передаваемое функции уведомления при вызове в качестве параметра.
						TIME_PERIODIC); // тип таймерного события: TIME_ONESHOT — однократное, TIME_PERIODIC — периодическое.
	if (!timer) 
	{
		AfxMessageBox (_T("Таймер НЕ запущен"), NULL, 0);
		return FALSE;
	}
	//AfxMessageBox (_T("Таймер запущен"), NULL, 0);
	kmpk_tek=0;	
	m_corect_pk.SetFocus();


	//В WIN 7 убрана задержка в очереди к диспетчеру памяти, которая позволяла висте (или 
	//приложениям в ней) не вылетать по нулевому возвращаемому адресу в malloc
	//specbuf_canal1=static_cast<BYTE *>(malloc(SPECWIDTH*SPECHEIGHT));//не в стеке
	//specbuf_canal2=static_cast<BYTE *>(malloc(SPECWIDTH*SPECHEIGHT));//не в стеке

	specbuf_canal1 = new BYTE [SPECWIDTH*SPECHEIGHT];
	specbuf_canal2 = new BYTE [SPECWIDTH*SPECHEIGHT];
/////////////////////////////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE

} // End OnInitDialog();

BOOL CViewPut::DestroyWindow()
{
	//free(specbuf_canal1);
	//free(specbuf_canal2);
	delete [] specbuf_canal1;
	delete [] specbuf_canal2;

	 // Освобождаем распределённое место для фоновой кисти
	 delete m_pEditBkBrush;

	//AfxMessageBox (L"DestroyWindow");
	// TODO: добавьте специализированный код или вызов базового класса
	//AfxMessageBox(L"DestroyWindow");
//	if (timer) timeKillEvent(timer);
//	free(specbuf_canal1);
//	free(specbuf_canal2);
	//AfxMessageBox (_T("Выход 2 - DestroyWindow"), NULL, 0);

//	free(specbuf_canal1);
//	free(specbuf_canal2);
//	BASS_RecordFree();
 
		//AfxMessageBox(_T("Порт Закрыт"));

		
	


/*
	if (asfile.m_hFile!=(HANDLE)-1)
	{			
			//CString ss;
			//ss.Format(_T(" %d"),asfile.m_hFile);
			//AfxMessageBox(ss);
		CTime time = CTime::GetCurrentTime();
		// CTime time; // = CTime::GetTime();
		// time.GetTime();
		// CString str;
		//  - Русский в упор не понимает
		CString str = time.Format("%Y %x %X \n ");
		//  CStdioFile - Русский с трудом
		// str = L"\З\а\п\и\с\а\н\о - " + str + L"\К\о\н\е\ц \n";
		//////////////// SaveFile.Write(m_text ,m_text.GetLength()*sizeof(TCHAR) );
		 str = L"Записано - " + str + L"Конец \n";
		//str.OemToCharA();
		asfile.SeekToEnd();
		asfile.WriteString(str); // (LPCTSTR)
		asfile.Close();
	}
*/


//*

	//Sleep(300);



		//else AfxMessageBox(_T("Открытых портов НЕ обнаружено"));



//*/
	//CString st;
	//st = _T("COM1");
	//ComGps.Close();

	// завершает работу библиотеки
	//BASS_Free ();


	//AfxMessageBox(_T("DestroyWindow()"));


//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	pFrame->ShowWindow(SW_SHOW);

	return CDialog::DestroyWindow();
}

void CViewPut::Serialize(CArchive& ar)
{
	m_configdat.Serialize(ar);  // вызываем общий метод архива
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CViewPut::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: добавьте специализированный код или вызов базового класса

	CString str;
	switch (message)
	{
		case WM_TIMER:
//			AfxMessageBox (_T("Таймер on"), NULL, 0);
			// Именно наш таймер
			ASSERT (timer);
		if (wParam == timer)
		{

					
	//		LRESULT rs = SendMessageW (put->m_hWnd, WM_TIMER, uTimerID, 0); // put->m_hWnd, 

//			CViewPut::SetWindowTextW(L"Start OnWndMsg");
			// Всегда активно, не дает другим
			// //Focus m_corect_pk.SetFocus();
			//AfxMessageBox (_T("Таймер on"), NULL, 0);

			if (port01.IsOpen())    // Читаем 1-й Com порт
			{

				OnReadComPort1();
				m_strPiket.SetString(strPiket);
				UpdateData(false);
					//	AfxMessageBox (_T("Таймер"), NULL, 0);
			}

///////////////////////////////////////////////////////////////////////////////
			if (port02.IsOpen())		  // Читаем 2-й Com порт
			{
				OnReadComPort2();
				OnGpsRmc();
				//UpdateData(false);
			}
///////////////////////////////////////////////////////////////////////////////
			// Конспектируем наши измерения
			if (asimfile.m_hFile!=(HANDLE)-1)
			{
				CString strif, strf;
				//////m_strAsimetr =L"33";
				strif = m_strAsimetr;//.GetString();
		
				if (m_Asimetr > 4)        //    strif !=_T("0 %"))// Строка = A
				{
					CString srtutf(L'\xFEFF');
					strif = srtutf+ strif;			// Строка = xFEFF A
					strif += _T("\t" );
					
					if (m_configdat.m_strComPort1.Compare(L"Не использовать"))
					{
						strif += m_strPiket.Trim();		// Строка = xFEFF A ПикетР
						strif += _T("\t" );
					}
					
					strif += m_2_strPiket;			// Строка = xFEFF A ПикетР ПикетВ
					strif += _T("\t" );
					
					strif += m_str_Latitude; 
					strif += _T("\t" );
					strif += m_str_Longitude;
					strif += _T("\r\n");            // Строка = xFEFF A ПикетР ПикетВ Широта Долгота
					asimfile.SeekToEnd();
					//AfxMessageBox (strif);
					asimfile.Write(strif, strif.GetLength()*sizeof(TCHAR ));
				}
			}
			if (m_configdat.m_disko_onof)
			{
				OnVoltageDisko();
			}

////////////////////////////////////////////////////
//			SetWindowTextW(L"Stop OnWndMsg");
			}
			//AfxMessageBox (_T("Таймер end"), NULL, 0);
			break;
		case  WM_RBUTTONDOWN:
			AfxMessageBox (_T("Правая"), NULL, 0);
			break;
		//default: ;
	}


	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}

void CViewPut::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса
	//AfxMessageBox (_T("Выход 1 - OnCancel()"), NULL, 0);
	if (timer) timeKillEvent(timer);
	BASS_ChannelStop(chancap1); // остановили запись
	BASS_RecordFree();
 	if (m_configdat.m_disko_onof)  {OnCloseOscilloscopeDisko();}
	UpdateData(false);
	theApp.m_pMainWnd->ShowWindow(SW_RESTORE);
  	if (port01.IsOpen()) // try не определяеться   && m_configdat.m_strComPort1.Compare(L"Не использовать")
	{
		port01.CancelIo();
		port01.Close();                      // try не определяеться
		//AfxMessageBox(_T("Порт1 Закрыт"));
	}
	if (port02.IsOpen()) // try не определяеться
	{
		port02.CancelIo();
		port02.Close();                      // try не определяеться
		//AfxMessageBox(_T("Порт2 Закрыт"));
	}

  	if (asimfile.m_hFile!=(HANDLE)-1)
	{			
			//CString ss;
			//ss.Format(_T(" %d"),asfile.m_hFile);
			//AfxMessageBox(ss);
		CTime time = CTime::GetCurrentTime();
		// CTime time; // = CTime::GetTime();
		// time.GetTime();
		// CString str;
		
		//  - Русский в упор не понимает
		CString str(L"Записано - ");
		str += time.Format("%Y %x %X\r\n"); //\n
		//  CStdioFile - Русский с трудом
		
		// str = L"\З\а\п\и\с\а\н\о - " + str + L"\К\о\н\е\ц \n";
		//////////////// SaveFile.Write(m_text ,m_text.GetLength()*sizeof(TCHAR) );
		// str = L"Записано - " + str + L"\r\n";
		 //str += L"Конец \r\n";
		 // _T("\r\n");
		//str.OemToCharA();
		asimfile.SeekToEnd(); // Количество байтов в строке
		asimfile.Write(str,str.GetLength()*sizeof(TCHAR)); // (LPCTSTR)
		asimfile.Close();
	}

	Sleep(900);		    // Ждем окончания уже начавшейся задачи
 	//p_free if ((BYTE *)specbuf_canal1) free(specbuf_canal1);
	//p if ((BYTE *)specbuf_canal2) free(specbuf_canal2);
  
	//::DestroyWindow(this);
	// Закрыли окно диалога
	CDialog::OnCancel();
	// Уничтожили данные
	
	DestroyWindow();
	//CDialog::OnCancel();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////




BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user)
{
	UNREFERENCED_PARAMETER(handle);
	UNREFERENCED_PARAMETER(user);
//	win = GetParent();  //AfxGetApp();	GetParent() позволяет получить дескриптор родителя дочернего окн
//	CDC* dc; //HDC
//	dc=GetDC(win);  // m_pMainWnd->
//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	dc  = pFrame->GetDC();
	
	//DrawText(dc,L"vvvvvvvvvvvvvvv",-1,0,0);
//	pFrame->m_ViewPut.SetWindowTextW(L"Start DuffRecording");
	
	return TRUE; // continue recording 

	///
		CFile file;
		CFileException fe;
		if (file.Open(_T("pcm.dat"), CFile::typeBinary | CFile::modeReadWrite, &fe))
		{
			//fwrite(buffer, 1, length, (FILE)file); // write the buffer to the file
			// return TRUE; // continue recording
			file.Write(buffer,length);
			//AfxMessageBox( _T("файл данных pcm.dat"));

			
		}
		else AfxMessageBox( _T("Ошибка 1 чтения файла данных pcm.dat"));

		//file.Close();
	

	///
//			pFrame->m_ViewPut.SetWindowTextW(L"Stop DuffRecording");
	return TRUE; // continue recording
}
//CViewPut viewput;


void CALLBACK UpdateAsim(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	UNREFERENCED_PARAMETER(uMsg);
	UNREFERENCED_PARAMETER(dw1);
	UNREFERENCED_PARAMETER(dw2);
		// Функция вне класса, передаем указатель this через DWORD dwUser
CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;			
	if (!pFrame) return;
#ifdef _DEBUG
	pFrame->m_ViewPut.SetWindowText(L"Start UpdateAsim");
#endif //_DEBUG	


		//CViewPut viewput;
		CViewPut* put = (CViewPut*)dwUser;
//		COscilloscopeView* Oscil;
//		put->SetWindowTextW(L"Start UpdateAsim");
		return;

		if (put) put->m_2_valueAsimetr=1;  //виснет в 8
		else return; //AfxMessageBox(L"Путь 0");
		

		//short 
		// unsigned short - OK
		// unsigned int long	
		// Данные поступают именно так signed short 1k signed short 2k
		//signed sizeof = 3459 unsigned 
		short  buf[SPECWIDTH*2];	 //  - буфер для стерео 
		//memset(buf,0,SPECWIDTH);
		CString str, strp;
		int A, a1, a2, i1, i2 ;//Assim2;
		A=0;
		a1=0;
		a2=0;
		i1=0;
		i2=0;
		double Assim2, chanleft2, chanright2;
	//float Assim2_i;
		
//		str.Format(_T("Канал - %x"), put->chancap1 );
//		AfxMessageBox (str, NULL, 0);
////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////
		//
// Читаем звуковую карту		
		//BYTE specbuf_canal1[SPECWIDTH*SPECHEIGHT];
		int x,xx,y=0,y2=0;
		memset(specbuf_canal1,0,SPECWIDTH*SPECHEIGHT); // *sizeof(BYTE)
		// free(specbuf_canal1);
		memset(specbuf_canal2,0,SPECWIDTH*SPECHEIGHT); //Стерео 2-й канал
//		memset(pstr_specbuf_canal2,0,SPECWIDTH*SPECHEIGHT);

		if (BASS_ChannelGetData(put->chancap1,buf,sizeof(buf))==-1) // получить порцию данных
		{
			//Error(L"Осциллоскоп Ошибка получения данных");
			return ;
		}
		xx=0; chanleft2=0; chanright2=0;
		for (x=0;(x<(SPECWIDTH*2));x++) //Стерео 1-й канал
		{
			int v=(32767-buf[x])*SPECHEIGHT/65536; // invert and scale to fit display
			if (!x) y=y2=v;
				do  // draw line from previous sample...
				{
					if (y<v) y++;
					else if (y>v) y--;
				specbuf_canal1[abs(y*SPECWIDTH+xx)]=(BYTE)(abs(y-SPECHEIGHT/2)*2+1);
				} 
				while (y!=v);
				x++;
				v=(32767- buf[x])*SPECHEIGHT/65536; // invert and scale to fit display
				//if (!x) y2=v;
				do 
				{ // draw line from previous sample...
					if (y2<v) y2++;
					else if (y2>v) y2--;
					specbuf_canal2[abs(y2*SPECWIDTH+xx)]=(BYTE)(abs(y2-SPECHEIGHT/2)*2+1);
				} 
				while (y2!=v);  
				xx++;
				chanright2 = chanright2 + abs(buf[x]);
				//if (!x) chanleft2 = 0;
				//else 
#pragma warning(push)
#pragma warning(disable:6201)
				if (x) chanleft2 = chanleft2 + abs(buf[x-1]);
#pragma warning(pop)				
		}
		chanleft2 = chanleft2/xx;
		chanright2 = chanright2/xx;

		if ((chanleft2 + chanright2) != 0) //вообще точно сравнивать чисел с плавающей точкой нельзя
		{
			Assim2 = abs((chanleft2 - chanright2)*100/ (chanleft2 + chanright2));
		}
		else Assim2 = 0;

		put->m_2_valueAsCen1= (int)abs(chanleft2);//     .SetString(str);
		put->m_2_valueAsCen2 = (int)abs(chanright2); //m_strAsCen2.SetString(str);
		put->m_2_valueAsimetr = (int)Assim2 ;
		Assim2 = 0;



		 ///////




			 				// (chanright - chanleft) *100 /(chanleft + chanright);
		//		if ((buf[x]+buf[x+1])!=0)
		//		{
		//			(buf[x]-buf[x+1])/(buf[x]+buf[x+1]);
		//		}










//	CDC dc;
 //  BitBlt(dc.GetSafeHdc(),0,0,SPECWIDTH,SPECHEIGHT,specdc,0,0,SRCCOPY);

 		///
//AfxMessageBox( _T("Ошибка STOP3"));	
		///////////////////////////////////
		//////
		//CFile file;
		//CFileException fe;
		//CFileStatus status;
		//if (!CFile::GetStatus(_T("pcm.dat"), status))
		//{
		//	AfxMessageBox( _T("файл данных pcm.dat не существует, \r\n\t создаем новый"));
		//	if (!file.Open(_T("pcm.dat"), CFile::typeBinary | CFile::modeCreate, &fe))
		//	AfxMessageBox( _T("Ошибка создания pcm.dat"));
		//}
		//if (file.Open(_T("pcm.dat"), CFile::typeBinary | CFile::modeReadWrite, &fe))
		//{
		//	file.SeekToEnd();
		//	file.Write(buf,sizeof(buf));
		//	//AfxMessageBox( _T("файл данных pcm.dat"));
		//}
		//else AfxMessageBox( _T("Ошибка 1 чтения файла данных pcm.da"));
///////////////////////////////////////////////
		///
		///
		DWORD level, chanleft=0, chanright=0;
		DWORD level2 = 0;

		for (int i=0; level2<(MIN_VALUE+MIN_VALUE+1); i++)
		{
			level=BASS_ChannelGetLevel(put->chancap1);
			chanleft = LOWORD(level);
			chanright = HIWORD(level);
			level2 = chanleft + chanright;
			if (i>400) level2 = MIN_VALUE+MIN_VALUE+3;
		}

		//int 
		DWORD min0 = MIN_VALUE;  // min
		// Уровень 0
		if (chanleft < min0)
		{
			if (chanright < chanleft)
			{
				chanright = 0;
				chanleft = 0;
			}
			else 
			{
				chanright = chanright - chanleft;
				chanleft = 0;
			}
		}
		if (chanright < min0)
		{
			if (chanleft < chanright)
			{
				chanleft = 0;
					chanright =  0;
			}
			else 
			{
				chanleft = chanleft - chanright;
				chanright=0;
			}
		}

		if ((chanleft + chanright) != 0)
		{
			if (chanleft > chanright) A = (chanleft - chanright) *100 /(chanleft + chanright);
			else A = (chanright - chanleft) *100 /(chanleft + chanright);
		}
		else A = 0;

		 
		CString ss;
		//str.Format(_T("%u"), a1/i1 );	 если 0 <= левый кан < 40 000, то выводим   N   //  && chanleft<40000
		if (0>chanleft) chanleft=0;
		str.Format(_T("%u"),chanleft);
		put->m_strAsCen1.SetString(str);
		//str.Format(_T("%u"), a2/i1 );	//  && chanright<40000
		if (0>chanright) chanright=0;
		str.Format(_T("%u"),chanright);
		put->m_strAsCen2.SetString(str);
		
		if (A < 200 && A >= 0)
		{
			put->m_Asimetr = A;
			str.Format(_T("%i %%"), A );  // %u PVS-STUDIU
			put->m_strAsimetr.SetString(str);
		}
		A = 0;

		Sleep(200);

		ASSERT (uTimerID);
		// Сообщение для диалога put"Сработал наш Таймер" 
		// для обновления экрана
		LRESULT rs = SendMessageW (put->m_hWnd, WM_TIMER, uTimerID, 0); // put->m_hWnd, 
//		rs = SendMessageW (FindWindow(L"AfxFrameOrView100ud", L"Осциллогаф1 - Осциллогаммы"),WM_QUIT, 0, 0);
//		BOOL b=PostMessageW(FindWindow(0, L"Осциллогаф1 - Осциллогаммы"), WM_QUIT, 0, 0);
//		Oscil->SendMessageW(WM_TIMER, uTimerID, 0);
		//ASSERT (rs);

		HWND hw = FindWindow(0, L"Осциллограф1 - Осциллограмы");	//L"AfxFrameOrView100ud"	
		CString dd;
		dd.Format(L"НЕ Нашли - %p",hw);  //было %d PVS-STUDIO
		 if (hw>0)
		 {
			 BOOL b=PostMessage(FindWindow(0, L"Осциллограф1 - Осциллограмы"), WM_MYTIMER, 55555, 0);  //uTimerID

			 //rs = SendMessageW (hw,WM_QUIT, 0, 0);
			 rs = SendMessageW (hw, WM_MYTIMER, 55555, 0);	 //uTimerID
			 dd.Format(L"Нашли - %p - %d -%d",hw,rs,b); //было %d PVS-STUDIO
			 pFrame->m_ViewPut.SetWindowTextW(dd);

		 }
		 else pFrame->m_ViewPut.SetWindowTextW(dd);



			//AfxMessageBox (_T("Таймер послали"), NULL, 0);	
//pFrame->m_ViewPut.SetWindowTextW(L"Stop UpdateAsim");
//		put->SetWindowTextW(L"Stop UpdateAsim");
		//put->m_strAsCen2.SetString(L"Stop UpdateAsim");
		//pelix if (put) put->m_2_valueAsimetr=2;



}
//// END CALLBACK UpdateAsim



void CViewPut::OnBnClickedCancel()
{
	//AfxMessageBox (L"OnBnClickedCancel");

	// TODO: добавьте свой код обработчика уведомлений
	OnCancel();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Обработка сообщения RMC от GPS
void CViewPut::OnGpsRmc(void)
{
	#ifdef _DEBUG 
	CViewPut::SetWindowTextW(L"Start OnGpsRmc");
	#endif

	if (!RMC.GetLength()) RMC = L"Нет данных";
	/// выводим в статусную строку
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	pFrame->OnSetPaneText(RMC);


////////////////////////////////////////////////////////////////////////////
	if (RMC.Find(L'*',RMC.GetLength()-3))  //AfxMessageBox(L'k');	
	{


//		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//st		pStatus->SetPaneText(0, RMC);
		

		/// Разбор сообщения RMC
		//AfxMessageBox(GetParametr(RMC,3));
		CString strSpeed;
	
		strSpeed = GetParametr(RMC,3);

		if (strSpeed.Compare(L"V") == 0)     //V A
		{
			m_str_Longitude.SetString(_T("Данные не валидны")) ;
			m_str_Latitude.SetString(_T("Данные не валидны")) ;
			m_2_strPiket.SetString(_T("Дата ")+GetParametr(RMC,10)+_T("  Время UTS ") + GetParametr(RMC,2));
		}
		else
		{
			if (strSpeed.Compare(L"A") == 0)     //V A
			{
				CString strTime;
				double speed=0;
				double mmm;

				m_str_Latitude.SetString(GetParametr(RMC,4));   // Широта
				m_str_Longitude.SetString(GetParametr(RMC,6));  // Долгота 
				strTime = GetParametr(RMC,2);               // Время словом
				strSpeed = GetParametr(RMC,8);              // Скорость в узлах словом
				speed = _wtof(strSpeed.GetBuffer());        // Юникод строка
				//speed = speed*1.852;
				///
				theApp.m_str_Latitude_current=m_str_Latitude;
				theApp.m_str_Longitude_current=m_str_Longitude;
				//kmpk_tek=0;	
				//speed=35;
				////
				
				if (!vTime1)	vTime1 = TimeStrtoCount(strTime);	// первый запуск
				vTime2 = TimeStrtoCount(strTime);				// обновили
				
				if (speed < 1.0) speed = 0;				/////////////// 
				
				//mmm = vTime2 - vTime1;							// прошло сек. 
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/////
				///
				// Вычисляем пройденный путь
				mmm = (vTime2-vTime1)*speed*0.518;	//5144	0.5148	0.516-отстает			// метры * V в м/с	5144
				vTime1 = vTime2;
				// направление
				switch (m_ipiketkp) 
				{
				case 0:
					kmpk_tek = kmpk_tek - (mmm/1000);
				break;
				case 1:
					kmpk_tek = mmm/1000 + kmpk_tek;					// kmpk_tek = kkkk.mmm	
				break;
				}
							
				if (kmpk_tek<-2000) kmpk_tek=0;
				if (kmpk_tek>2000) kmpk_tek=0;

				//strTime.Format(L"%.3f",vTime1);
				//m_2_strPiket.SetString(strTime);
				//AfxMessageBox(strTime);
				///
				// Текущий пикет
				theApp.m_PK_current = kmpk_tek;
				
				strSpeed.Format(_T(" %.3f км    %.1f км/ч    %.1f м/c"),kmpk_tek, speed*1.852, speed*0.5144); // g  %.1f км/ч"),kmpk_tek, speed*1.852)
				m_2_strPiket.SetString(strSpeed);
				//
				strSpeed.Format(_T(" %.3f км    CPU-%.0f %%"),kmpk_tek,	BASS_GetCPU());
				pFrame->m_ViewPut.SetWindowTextW(strSpeed);
				//
			}
			else pFrame->OnSetPaneText(RMC+L" - Некорректрое сообщение") ;
		}

		
	}
	UpdateData(false);
				
//////////////////////////////////////////////////////////////////////////
	#ifdef _DEBUG
	CViewPut::SetWindowTextW(L"Stop OnGpsRmc");
	#endif
}

// Получить параметр по его номеру
CString CViewPut::GetParametr(CString stroka, int np)
{
	#ifdef _DEBUG
	CViewPut::SetWindowTextW(L"Start GetParametr");
	#endif
	// для однообразия - ',' как разделитель 	
	stroka = stroka + _T(',');
	CString sss;

	
	// Все - 1-й
	//int len = stroka.GetLength();
	for (int i=1; i<np; ++i)
	{
		sss = stroka.Right(stroka.GetLength() - stroka.Find(_T(','))-1);
		stroka = sss;
	}

	sss = stroka.Left(stroka.Find(_T(',')));

			/// выводим в статусную строку
//		CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//		pStatus->SetPaneText(0, sss);
#ifdef _DEBUG
	CViewPut::SetWindowTextW(L"Stop GetParametr");
#endif
	return sss;//CString();
}

void CViewPut::OnBnClickedPkok()
{
	//AfxMessageBox( _T("Ошибка 21 чтения файла"));
	if (UpdateData())
	{
		kmpk_tek = _wtof(m_strsetpk.GetBuffer());
		//kmpk_tek = m_strsetpk;

	}

	
	//UpdateData(true);
	CString ss;
	// TODO: добавьте свой код обработчика уведомлений
	//ss = m_setpk.GetString(); //m_setpk.GetString();//UpdateData(true);


	m_2_strPiket.SetString(ss);
	//.SetString(ss);
	//m_Longitude.SetString(_T("Данные не валидны")) ;
	//m_Latitude.SetString(m_Longitude.GetString());
	//AfxMessageBox(ss);
	//	UpdateData(false);
}


// Преобразует название порта в его номер
int CViewPut::ComPortStrtoInt(CString strComPort)
{
	//CString sss;
	strComPort.Delete(strComPort.Find(L"<")-1,50); //до конца строки
	int n_port = _ttoi(strComPort.Mid(3,3));

	return n_port;
}

void CViewPut::OnReadComPort1(void)
{
#ifdef _DEBUG
		CViewPut::SetWindowTextW(L"Start OnReadComPort1");
#endif
		////////////////////////////////
	///
	// Читаем Com порт
	//ComGps.WriteString((LPCTSTR)str);
	//ComGps.ReadString(str);

			//char WCHAR
/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Процедура чтения 1-го порта  //AfxMessageBox(mStart);
//AfxMessageBox(L"Читаем0");
			CString mStart;
			mStart	= L"$AS  Путь   $AVСк. "; //_T("$ASошибка!!$AVerror") ;


			////

		 //mStart1.GetBufferSetLength(400);
		// char* mStart2[400];
		 //port01.ReadEx(mStart1.GetBuffer(), 20);  // (void*)(LPCTSTR)mStart1
			////

				//COMMTIMEOUTS timeouts;
				//timeouts.ReadTotalTimeoutMultiplier = 1000; // 100000
				//port01.SetTimeouts(timeouts);

				//port01.Set0ReadTimeout();  // без этого подвисает // Перенесли в InitInstance
				
//AfxMessageBox(L"Читаем1");

				port01.ReadEx(mStart.GetBuffer(), 20);  // (void*)(LPCTSTR)mStart1 - то же работает
				// port.ClearReadBuffer();sRxBuf
				//port01.
				//port01.ClearReadBuffer(); // почему-то ошибка
				
				int ns = mStart.Find(_T("$AS"),0)+3;
				int nv = mStart.Find(_T("$AV"),0)+3;
				if (ns<nv)
				{
					strPiket = mStart.Mid(ns, ns+5) + _T("км ") + //+8	// если приняли лишнее
								mStart.Mid(nv, nv+2) + _T("км/ч");//+5

				}
#ifdef _DEBUG
	CViewPut::SetWindowTextW(L"Stop OnReadComPort1");
#endif
/// Конец процедуры чтения 1-го порта
	//////////////////////////////////////////////////////////////////////////////////////

}  //// CViewPut::OnReadComPort1 END


void CViewPut::OnReadComPort2(void)
{
#ifdef _DEBUG
	CViewPut::SetWindowTextW(L"Start OnReadComPort2");
#endif
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Процедура чтения 2-го порта
	// кодировка из GPS ОЕМ
	//if (port2.IsOpen()) AfxMessageBox(L"ERROR222");		
	RMC = L"Ошибка чтения порта";
	CString mStart;
	mStart	= _T("$GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598,,*10");
	
	// 0.13 скорость в узлах // 1 узел = 1.852 км/ч = 0.5144 м/с = 30.86667 м/мин 
				
	char buf[804];  //404
	memset(buf,0,804);

	//COMMTIMEOUTS timeouts;
	//timeouts.ReadTotalTimeoutMultiplier = 100000;
	//port2.SetTimeouts(timeouts);
	//port2.Set0ReadTimeout();
	port02.Set0ReadTimeout();  
	port02.ReadEx(buf,792);  // port02.ClearReadBuffer();sRxBuf 396
	port02.ClearReadBuffer();
	
	mStart.GetBuffer(800);
	mStart = buf;
	mStart.TrimRight();
	
	int ns;
	ns = mStart.Find(L"$GPRMC",0);

	if (0<=ns)
	{

		//AfxMessageBox(L"Не найдено");
		// Начало нужного сообщения
		int ks = mStart.Find(L"*",ns);  // длина 62 \r\n
		//ks=800;
		if ((ns < ks) && (ks < (ns+95))) RMC = mStart.Mid(ns, ks-ns+3); //

//	CString ss1;
//	ss1.Format(L"%d, %i - %s",ns,ks,RMC);
//	AfxMessageBox(ss1);

	}
	// else AfxMessageBox(L" найдено");

	//
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	if (240<mStart.GetLength())
	{
		pFrame->OnOutputDebugAddString(mStart.Left(240));
		pFrame->OnOutputDebugAddString(mStart.Mid(240,mStart.GetLength()));
	}
	else pFrame->OnOutputDebugAddString(mStart);

	
/// Конец процедуры чтения 2-го порта
#ifdef _DEBUG
			CViewPut::SetWindowTextW(L"Stop OnReadComPort2");
#endif

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Функции потоков
void CViewPut::OpenComPort(int nPort, CString strComPort)
{
			/// выводим в статусную строку
	//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	//	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	//	pStatus->SetPaneText(0, strComPort);


	sPort.Format(_T("\\\\.\\%s"), strComPort);
	sPort.Delete(sPort.Find(L"<")-1,50); //до конца строки

	//if (nPort == 1) // && hcomm01 == 0
//	CWinThread *pThread;  //pelix
//	CWinThread *pThread2;
	switch (nPort)
	{
	case 1:	
		{
			pThread = ::AfxBeginThread (ThreadFunc, static_cast<LPVOID>(&sPort));
		}
		break;
	case 2:
			pThread2 = ::AfxBeginThread (ThreadFunc2, static_cast<LPVOID>(&sPort));
		break;
	default:;
	}

}
// Поток, открывающий порт №1
UINT ThreadFunc (LPVOID pParam)
{	
	CString* nPort = static_cast<CString*>(pParam);
	CString strPort;
	// Переводим название порта в номер порта
	strPort = nPort->GetString();
	//AfxMessageBox(nPort->GetString());
	//strPort.Format(_T("%i"),pParam);
	//AfxMessageBox(strPort);
	int n_port = _ttoi(strPort.Mid(7,3));

	//n_port = 1;
  try
  {
	COMMTIMEOUTS timeouts;
    COMMCONFIG config;
	CSerialPort::GetDefaultConfig(n_port, config);

	port.Open(n_port);//(nPort->GetString()); //
	hcomm01 = port.Detach();
	port.Attach(hcomm01);
	port.GetTimeouts(timeouts);
	timeouts.ReadTotalTimeoutConstant=1000;
	port.SetTimeouts(timeouts);
  }
  catch (CSerialException* pEx)
  {
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
	CString soob;
	soob.Format(_T("Ошибка открытия порта №1 %s:\n %s\n"),
				strPort.Mid(4,6),
				pEx->GetErrorMessage().operator LPCTSTR());
	AfxMessageBox(soob);
    pEx->Delete();
  }

	return FALSE;
} // END ThreadFunc 1

// Поток, открывающий порт №2
   COMMCONFIG config2;
   DCB dcb2;
UINT ThreadFunc2 (LPVOID pParam)
{	
	CString* nPort = static_cast<CString*>(pParam);
	CString strPort;
	// Переводим название порта в номер порта
	strPort = nPort->GetString();
	//AfxMessageBox(nPort->GetString());
	int n_port = _ttoi(strPort.Mid(7,3));
	//AfxMessageBox(strPort);
	
//   COMMTIMEOUTS timeouts;
  try
  {

	//CSerialPort::GetDefaultConfig(n_port, config2);
	port2.Open(n_port,115200,CSerialPort::NoParity,8,CSerialPort::OneStopBit,
											CSerialPort::NoFlowControl,0);
	//port2.Open(n_port);

	hcomm02 = port2.Detach();
	port2.Attach(hcomm02);
//	port2.GetTimeouts(timeouts);
//	timeouts.ReadTotalTimeoutConstant=1000;
//	port2.SetTimeouts(timeouts);
//	port2.Set0ReadTimeout();
//	config.dcb.BaudRate=115200;
//	port2.SetConfig(config);

	port2.GetConfig(config2);
	config2.dcb.BaudRate=115200;
	port2.SetConfig(config2);

//	port2.GetState(dcb2);
//    dcb2.BaudRate = 115200;
//    port2.SetState(dcb2);


  }
  catch (CSerialException* pEx)
  {
    TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
	CString soob;
	soob.Format(_T("Ошибка открытия порта №2 %s:\n %s\n"),
				strPort.Mid(4,6),  //nPort->GetString(),
				pEx->GetErrorMessage().operator LPCTSTR());
	AfxMessageBox(soob);
    pEx->Delete();
  }
	//strPort.Format(_T("Порт COM%i открыт"),n_port);
	//AfxMessageBox(strPort);


 // 	port2.GetConfig(config2);
//	strPort.Format(_T("%i"),config2.dcb.BaudRate);
//	AfxMessageBox(strPort);

	return FALSE;
} // END ThreadFunc2

void CViewPut::OnReadComPort1Thread(void)
{
				////////////////////////////////
				///
				// Читаем 1-й Com порт
				if (hThread)
				{
					if (::WaitForSingleObject(pThread->m_hThread, 0) != WAIT_OBJECT_0)
						::ExitThread(0); //TerminateThread(hThread,0)
					
					//AfxMessageBox(_T("еще есть старый поток"));
				}
//					::TerminateThread(pThread->m_hThread,0);
				//CWinThread *
					pThread = ::AfxBeginThread (ThreadFuncRead, NULL);
				//HANDLE 
					hThread = pThread->m_hThread;
								//Sleep(1);
}

// Поток в котором читаем из порта 1
UINT ThreadFuncRead (LPVOID pParam)
{
	UNREFERENCED_PARAMETER(pParam);
	////////////////////////////////
	///
	// Читаем Com порт
	//ComGps.WriteString((LPCTSTR)str);
	//ComGps.ReadString(str);

			//char WCHAR
/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Процедура чтения 1-го порта
//			unsigned char	sRxBuf[] =  "$ASошибка!!$AVerror";
			CString mStart;
			mStart	= _T("$AS  Путь   $AVСк. "); //_T("$ASошибка!!$AVerror") ;
	//		strPiket = _T("Ждемс координаты");
//			DWORD dwRead;
	//		*sRxBuf = *mStart;

	try
	{
// 		if (port.IsOpen())
//		{
			//char sRxBuf[38]; // 19 символов  Unicode ?
			//_T("$AS1234,567км $AV123,4");
			

			//AfxMessageBox(_T("читаем"));
			//dwRead = 
		// Проверить &mStart
				
				//port.DataWaiting(10);
				COMMTIMEOUTS timeouts;
				timeouts.ReadTotalTimeoutMultiplier = 100000;
				port.SetTimeouts(timeouts);
				port.Set0ReadTimeout();
				port.ReadEx(&mStart,20);  // port.ClearReadBuffer();sRxBuf
				//AfxMessageBox(mStart);
			
			//mStart = sRxBuf;
		
			///
			//dwRead = 1;
			//port.Write(sRxBuf,38);
			//port.ClearWriteBuffer();
			//if (!dwRead)
			//{
				port.ClearReadBuffer();
				// Приходит строка вида "$ASkkkk,mmm$AVsss,s"
				
//				int		pos;
				
	//			mStart = sRxBuf;
//				strPiket = sRxBuf;

	

				//return FALSE; 

				int ns = mStart.Find(_T("$AS"),0)+3;
				int nv = mStart.Find(_T("$AV"),0)+3;
				if (ns<nv)
				{
					strPiket = mStart.Mid(ns, ns+5) + _T("км ") + //+8	// если приняли лишнее
								mStart.Mid(nv, nv+2) + _T("км/ч");//+5

				}

				///
				//mStart =  _T("$AS1234,567$AV123,4");
				///

				//strPiket.Format(_T("%s"),mStart);

					//AfxMessageBox(mStart);
//				if ((mStart.Find(_T("$AS"),0)) && (mStart.Find(_T("$AV"),0)))
//				{
//				int ns = mStart.Find(_T("$AS"),0)+3;
//				int nv = mStart.Find(_T("$AV"),0)+3;
//				strPiket = mStart.Mid(ns, ns+5) + _T("км ") + //+8	// если приняли лишнее
//							mStart.Mid(nv, nv+2) + _T("км/ч");//+5
//				}
//				else strPiket = _T("Ошибка приема");

				
				//strPiket.Format(_T("%X%X%X %X "), 
				//sRxBuf[1], sRxBuf[2], sRxBuf[3], sRxBuf[4] );
				//m_strPiket.SetString(str);
			//}
			//strPiket = _T("Нет приема");
//		}
//		strPiket = _T("Порт не открыт");
	}
	catch (CSerialException* pEx)
	{
		TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
		CString soob;
		soob.Format(_T("Ошибка чтения первого СОМ порта:\n %s\n"),
		pEx->GetErrorMessage().operator LPCTSTR());
		//AfxMessageBox(soob);
		///
//st		CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//st		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//st		pStatus->SetPaneText(0, soob);
		///
		strPiket = _T("ОШИБКА");
		pEx->Delete();
	}

/// Конец процедуры чтения 1-го порта
	//////////////////////////////////////////////////////////////////////////////////////


	return FALSE;
} // END ThreadFuncRead

void CViewPut::OnReadComPort2Thread(void)
{
					////////////////////////////////
				///
				// Читаем 2-й Com порт
				if (hThread2)
				{
					if (::WaitForSingleObject(pThread2->m_hThread, 0) != WAIT_OBJECT_0)
						::ExitThread(0); //TerminateThread(hThread2,0)
					//AfxMessageBox(_T("еще есть старый поток"));
				}
//					::TerminateThread(pThread->m_hThread,0);
				//CWinThread *
					pThread2 = ::AfxBeginThread (ThreadFuncRead2, NULL);
				//HANDLE 
					hThread2 = pThread2->m_hThread;
								//Sleep(1);
}
// Поток в котором читаем из второго порта
UINT ThreadFuncRead2 (LPVOID pParam)
{
	UNREFERENCED_PARAMETER(pParam);
/////////////////////////////////////////////////////////////////////////////////////////////////
	//// Процедура чтения 2-го порта

			CString mStart;
			RMC = L"Ошибка чтения порта";
			/////// mStart	= _T("$GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598,,*10");
			// 0.13 скорость в узлах
			// 1 узел = 1.852 км/ч = 0.5144 м/с = 30.86667 м/мин 
			//return FALSE;

			//т.к. кодировка из GPS ОЕМ
			char buf[404];
//			setmem(buf,404,'S');
			//const wchar_t buf2[] = _T("FFF");
		
	//		AfxMessageBox(mStart);
			
	try
	{
			
				//COMMTIMEOUTS timeouts;
				//timeouts.ReadTotalTimeoutMultiplier = 100000;
				//port2.SetTimeouts(timeouts);
				//port2.Set0ReadTimeout();
				port2.ReadEx(buf,400);  // port.ClearReadBuffer();sRxBuf
				port2.ClearReadBuffer();

		

				//str_2_Piket.Format(_T("%s"),mStart);
				//AfxMessageBox(_T("FF"));
				//mStart.Format(_T("%s"),buf);
				//AfxMessageBox(mStart);
	}
	catch (CSerialException* pEx)
	{
		TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
		CString soob;
		soob.Format(_T("Ошибка чтения порта №2:\n %s\n"),
						pEx->GetErrorMessage().operator LPCTSTR());
		//AfxMessageBox(soob);
		/// выводим в статусную строку
//st		CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//st		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//st		pStatus->SetPaneText(0, soob);
		pEx->Delete();		
	}
			////////////////////////////////////////////////////////////////////////////
	///


	mStart = buf;
	
	mStart.TrimRight();
	int ns = mStart.Find(L"$GPRMC",0); // Начало нужного сообщения
	int ks = mStart.Find(L"\r\n",ns);  // длина 62
	
//		if (mStart.GetAt(ks-3) == _T('*')) AfxMessageBox(L'*');
//if (ns<ks<(ns+62))		AfxMessageBox(mStart.GetAt(ks-3));

	if (ns < ks && ks < (ns+62)) RMC = mStart.Mid(ns, ks-ns); //
//	else str_2_Piket = mStart.Mid(ns,61);
	

 //	if (mStart.Find(_T('*'),ns))
//	{
//		CString sss;
//		sss.Format(_T("Начало= %i, конец= %i, длина= %i"),ns,ks,ks-ns);
//		AfxMessageBox(sss);
//	}
		//RMC; str_2_Piket =
	///
	////////////////////////////////////////////////////////////////////////////////////

		
/// Конец процедуры чтения 2-го порта
	//////////////////////////////////////////////////////////////////////////////////////

	return FALSE;
} // END ThreadFuncRead2



/////////////////
double CViewPut::TimeStrtoCount(CString strTime)
{
	CString sss = strTime;
	double vtime;
	 // Часы
	vtime = _wtof(sss.Left(2))*3600 + _wtof(sss.Mid(2,2))*60 + _wtof(sss.Right(6));

	

	return vtime;
}

// Нужен т. к. UpdateData 1 рас в сек.
void CViewPut::OnBnClickedSchetm()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_ipiketkp=0;
	theApp.m_ipiketkp=0;
				  // Устанавливаем Шрифт киломероожа
		  CFont *objFont = new CFont;
		  objFont->CreateFontW(10, 0, 0, 0, FW_NORMAL, FALSE, 0, 0,  //FW_NORMAL
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Arial");
	m_piketkp.SetFont(objFont,1);
	m_piketkp.SetButtonStyle(10,1);
			  objFont->CreateFontW(-35, 0, 0, 800, FW_BOLD, TRUE, 0, 0,  //FW_NORMAL
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Arial");
	m_piketkm.SetFont(objFont,1);
	m_piketkm.SetButtonStyle(BS_TOP,1); //WS_EX_CLIENTEDGE | BS_TOP | TBBS_WRAPPED
}

void CViewPut::OnBnClickedSchetp()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_ipiketkp=1;
	theApp.m_ipiketkp=1;
			  // Устанавливаем Шрифт киломероожа

		  CFont *objFont = new CFont;
		  objFont->CreateFontW(10, 0, 0, 0, FW_NORMAL, FALSE, 0, 0,  //FW_NORMAL
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Arial");
	m_piketkm.SetFont(objFont,1);
	m_piketkm.SetButtonStyle(10,1);
		  objFont->CreateFontW(32, 0, 0, 0, FW_BOLD, TRUE, 0, 0,  //FW_NORMAL
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Arial");
	m_piketkp.SetFont(objFont,1);
	m_piketkp.SetButtonStyle(BS_TOP,1);
}

////////////////
void CViewPut::OnEnChangeKorect()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	UpdateData(true);
	
}


// Инициализировать интерфейс Диско
VARIANT_BOOL CViewPut::OnInitOscilloscopeDisko(void)
{
	// Доступ к функциям осциллографа с помощью DiSco API
	CoInitialize(NULL);
	VARIANT_BOOL	res=0;
	try
	{
		// создать COM-объект и получить интерфейс устройства
		HRESULT hr = CoCreateInstance( CLSID_CoDiscoAPI,
			          NULL, CLSCTX_INPROC_SERVER, IID_IDevice, (LPVOID*) &deviceDisko );  //(void**)

		if (FAILED(hr)) AfxMessageBox(L"Ошибка создания сервера\n");
 
		// запросить интерфейс осциллографа
		hr = deviceDisko->QueryInterface(IID_IOscilloscope, (LPVOID*) &oscDisko);
		if (FAILED(hr)) AfxMessageBox(L"Ошибка создания Oscilloscope\n");

		res = deviceDisko->Init(-1,DisableAutoUpdate);  //NormalAutoUpdate
		if (!res) 
		{
			MessageBox(L"Не удалось проинициализировать устройство",L"Диско Осциллограф",0);
			deviceDisko->Release();
			CoUninitialize();
			return res;
		}
		 // получить номер версии устройства и отобразить его в окне
		CComBSTR v;
		v.m_str = deviceDisko->GetFirmwareVersion();
		//	AfxMessageBox(v.m_str);

		// Задать параметры осциллографа
		oscDisko->SetSamplingFrequency(100000);  // частота дискретизации в Гц
		oscDisko->SetChannelOnOff(A, On);      // включить канал A
		oscDisko->SetChannelOnOff(B, On);      // включить канал B
		oscDisko->SetChannelMaxGain(A, 2);     // установить шкалу канала A 2В
		oscDisko->SetChannelMaxGain(B, 2);     // установить шкалу канала B 2В
		
	}
	catch (_com_error& e)
	{
		MessageBox(e.ErrorMessage(),0,0);
		deviceDisko->Release();
        CoUninitialize();
	}
 	return 	res;
}

// Измерить напряжение на входе Диско
HRESULT CViewPut::OnVoltageDisko(void)
{
	double valueA=0, valueB=0, resalts=0;
	//oscDisko->SetChannelOnOff(A,On);
	valueA = oscDisko->GetVoltage(A);
	valueB = oscDisko->GetVoltage(B);
	resalts = fabs(valueA - valueB) * 100 / (valueA + valueB);
	m_2_valueAsCen1 = valueA;
	m_2_valueAsCen2 = valueB;
	m_2_valueAsimetr = resalts;
	UpdateData(false);
			
	return E_NOTIMPL;
}

void CViewPut::OnCloseOscilloscopeDisko(void)
{
	oscDisko->Release();
	deviceDisko->Release();
	CoUninitialize();
}
// Отключаем ENTER
BOOL CViewPut::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	BOOL bHandledMsg = FALSE;
	
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		OnBnClickedPkok();
		bHandledMsg =  TRUE;
		//AfxMessageBox(L"Нажали ВВОД");
		//::SetFocus((HWND)GetDlgItem(IDC_KORECT));

	}

	return ( bHandledMsg ? bHandledMsg
			: CDialog::PreTranslateMessage(pMsg));
}


double CViewPut::OnPK_car(void)
{
	AfxMessageBox(m_2_strPiket);
	return kmpk_tek;
}


void CViewPut::OnBnClickedAddPk()
{
	// TODO: добавьте свой код обработчика уведомлений
	kmpk_tek += 0.1;
}


void CViewPut::OnBnClickedIncPk()
{
	// TODO: добавьте свой код обработчика уведомлений
	kmpk_tek -= 0.1;
}


void CViewPut::OnBnClickedAdd10m()
{
	// TODO: добавьте свой код обработчика уведомлений
	kmpk_tek += 0.01;
}


void CViewPut::OnBnClickedInc10m()
{
	// TODO: добавьте свой код обработчика уведомлений
	kmpk_tek -= 0.01;
}




// Цвет
HBRUSH CViewPut::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Вернуть другое значение дескриптора кисти, если оно не определено по умолчанию
	// Instantiate and initialize the background brush to black.
	m_pEditBkBrush = new CBrush(RGB(255, 255, 255));
	switch (nCtlColor) 
	{
		case CTLCOLOR_EDIT:
		case CTLCOLOR_MSGBOX:
		//pDC = m_2_Piket.GetDC();
		//pDC = 	m_2_Piket.GetWindowDC();
		//pWnd = m_2_Piket.GetWindow(1);
		// Устанавливаем цвет зелёный на чёрном и возвращаем чёрную кисть.
		pDC->SetTextColor(RGB(90, 0, 0));
		pDC->SetBkColor(RGB(0, 0, 255));
		return (HBRUSH)(m_pEditBkBrush->GetSafeHandle());
	default:
	return hbr;
	}
    //return (HBRUSH)GetStockObject(NULL_BRUSH);  // BLACK_BRUSH  GRAY_BRUSH
}
