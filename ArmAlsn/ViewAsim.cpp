// ViewAsim.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ViewAsim.h"
#include "afxdialogex.h"

///////////
CSerialPort port1;  // для потоковых функций
HANDLE hcomm01 = 0; // для потоковых функций
CWinThread *pThread1;
HANDLE hThread1 = NULL;






//////////////




// диалоговое окно СViewAsim

IMPLEMENT_DYNAMIC(СViewAsim, CDialogEx)

СViewAsim::СViewAsim(CWnd* pParent /*=NULL*/)
	: CDialogEx(СViewAsim::IDD, pParent)
		, m_1_strPiket(_T(""))
		, m_strAsCen1(_T(""))
		, m_strAsCen2(_T(""))
		, m_strAsimetr(_T(""))
		, m_2_valueAsimetr(0)
{

}

СViewAsim::~СViewAsim()
{
}

void СViewAsim::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_1_PK_V, m_1_strPiket);
	DDX_Text(pDX, IDC_ASCHEN1, m_strAsCen1);
	DDX_Text(pDX, IDC_ASCHEN2, m_strAsCen2);
	DDX_Text(pDX, IDC_ASIMETR, m_strAsimetr);
	DDX_Text(pDX, IDC_2_ASIMETR, m_2_valueAsimetr);
}


BEGIN_MESSAGE_MAP(СViewAsim, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений СViewAsim


BOOL СViewAsim::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	// берем данные из dat
	//CConfigDat dat;
	//CConfigDat m_configdat;
	m_configdat.OutSerialize();

	m_strPiket1.SetString(L"СОМ не открыт");
	m_strAsCen1.SetString(_T("Кат.1"));
	m_strAsCen2.SetString(_T("Кат.2"));
	m_strAsimetr.SetString(_T("Ассим."));
	UpdateData(false); //метод для передачи в контролы окна

	// Назначение 1 порта
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

	CFileException fe;
	if (!asimfile.Open(_T("Data\\asim.txt"), // &fe
					CFile::modeCreate |
					CFile::modeNoTruncate |	// если существует - дописать
					CFile::modeReadWrite, &fe))
	{
			fe.ReportError();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

// Преобразует название порта в его номер
int СViewAsim::ComPortStrtoInt(CString strComPort)
{
	//CString sss;
	strComPort.Delete(strComPort.Find(L"<")-1,50); //до конца строки
	int n_port = _ttoi(strComPort.Mid(3,3));

	return n_port;
}

BOOL СViewAsim::DestroyWindow()
{
	// TODO: добавьте специализированный код или вызов базового класса
	port01.Close();

	return CDialogEx::DestroyWindow();
}


BOOL СViewAsim::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: добавьте специализированный код или вызов базового класса
		CString str;
	switch (message)
	{
		case WM_TIMER:
//			AfxMessageBox (_T("Таймер on"), NULL, 0);
			// Именно наш таймер
			ASSERT (m_gtimer);
		if (wParam == m_gtimer)
		{
			if (port01.IsOpen())    // Читаем 1-й Com порт
			{

				OnReadComPort1();
				m_strPiket1.SetString(m_gstrPiket);
				UpdateData(false);
					//	AfxMessageBox (_T("Таймер"), NULL, 0);
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
						strif += m_gstrPiket.Trim(L" ");		// Строка = xFEFF A ПикетР
						strif += _T("\t" );
					}
					
					strif += m_gstrPiket;			// Строка = xFEFF A ПикетР ПикетВ
					strif += _T("\t" );
					
					strif += m_gstr_Latitude; 
					strif += _T("\t" );
					strif += m_gstr_Longitude;
					strif += _T("\r\n");            // Строка = xFEFF A ПикетР ПикетВ Широта Долгота
					asimfile.SeekToEnd();
					//AfxMessageBox (strif);
					asimfile.Write(strif, strif.GetLength()*sizeof(TCHAR ));
				}
			}
			if (m_configdat.m_disko_onof)
			{
//				OnVoltageDisko();
			}

////////////////////////////////////////////////////

		}
		break;
	}
	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}


void СViewAsim::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса
	if (port01.IsOpen()) // try не определяеться   && m_configdat.m_strComPort1.Compare(L"Не использовать")
	{
		port01.CancelIo();
		port01.Close();                      // try не определяеться
		//AfxMessageBox(_T("Порт1 Закрыт"));
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
		asimfile.SeekToEnd();
		asimfile.Write(str,str.GetLength()*sizeof(TCHAR)); // (LPCTSTR)
		asimfile.Close();
	}

	CDialogEx::OnCancel();
}



void СViewAsim::OnReadComPort1(void)
{
#ifdef _DEBUG
		СViewAsim::SetWindowTextW(L"Start OnReadComPort1");
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
					m_strPiket1 = mStart.Mid(ns, ns+5) + _T("км ") + //+8	// если приняли лишнее
								mStart.Mid(nv, nv+2) + _T("км/ч");//+5

				}
#ifdef _DEBUG
	СViewAsim::SetWindowTextW(L"Stop OnReadComPort1");
#endif
/// Конец процедуры чтения 1-го порта
	//////////////////////////////////////////////////////////////////////////////////////

}  //// CViewPut::OnReadComPort1 END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// Функции потоков
void СViewAsim::OpenComPort(int nPort, CString strComPort)
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
			pThread1 = ::AfxBeginThread (ThreadFunc, static_cast<LPVOID>(&sPort));
		}
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

	port1.Open(n_port);//(nPort->GetString()); //
	hcomm01 = port1.Detach();
	port1.Attach(hcomm01);
	port1.GetTimeouts(timeouts);
	timeouts.ReadTotalTimeoutConstant=1000;
	port1.SetTimeouts(timeouts);
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

void СViewAsim::OnReadComPort1Thread(void)
{
				////////////////////////////////
				///
				// Читаем 1-й Com порт
				if (hThread1)
				{
					if (::WaitForSingleObject(pThread1->m_hThread, 0) != WAIT_OBJECT_0)
						::ExitThread(0); //TerminateThread(hThread,0)
					//AfxMessageBox(_T("еще есть старый поток"));
				}
//					::TerminateThread(pThread->m_hThread,0);
				//CWinThread *
					pThread1 = ::AfxBeginThread (ThreadFuncRead, NULL);
				//HANDLE 
					hThread1 = pThread1->m_hThread;
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
				port1.SetTimeouts(timeouts);
				port1.Set0ReadTimeout();
				port1.ReadEx(&mStart,20);  // port.ClearReadBuffer();sRxBuf
				//AfxMessageBox(mStart);
			
			//mStart = sRxBuf;
		
			///
			//dwRead = 1;
			//port.Write(sRxBuf,38);
			//port.ClearWriteBuffer();
			//if (!dwRead)
			//{
				port1.ClearReadBuffer();
				// Приходит строка вида "$ASkkkk,mmm$AVsss,s"
				
//				int		pos;
				
	//			mStart = sRxBuf;
//				strPiket = sRxBuf;

	

				//return FALSE; 

				int ns = mStart.Find(_T("$AS"),0)+3;
				int nv = mStart.Find(_T("$AV"),0)+3;
				if (ns<nv)
				{
//					strPiket = mStart.Mid(ns, ns+5) + _T("км ") + //+8	// если приняли лишнее
//								mStart.Mid(nv, nv+2) + _T("км/ч");//+5

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
//		strPiket = _T("ОШИБКА");
		pEx->Delete();
	}

/// Конец процедуры чтения 1-го порта
	//////////////////////////////////////////////////////////////////////////////////////


	return FALSE;
} // END ThreadFuncRead
