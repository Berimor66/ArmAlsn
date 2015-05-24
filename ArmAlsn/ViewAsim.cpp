// ViewAsim.cpp: ���� ����������
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ViewAsim.h"
#include "afxdialogex.h"

///////////
CSerialPort port1;  // ��� ��������� �������
HANDLE hcomm01 = 0; // ��� ��������� �������
CWinThread *pThread1;
HANDLE hThread1 = NULL;






//////////////




// ���������� ���� �ViewAsim

IMPLEMENT_DYNAMIC(�ViewAsim, CDialogEx)

�ViewAsim::�ViewAsim(CWnd* pParent /*=NULL*/)
	: CDialogEx(�ViewAsim::IDD, pParent)
		, m_1_strPiket(_T(""))
		, m_strAsCen1(_T(""))
		, m_strAsCen2(_T(""))
		, m_strAsimetr(_T(""))
		, m_2_valueAsimetr(0)
{

}

�ViewAsim::~�ViewAsim()
{
}

void �ViewAsim::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_1_PK_V, m_1_strPiket);
	DDX_Text(pDX, IDC_ASCHEN1, m_strAsCen1);
	DDX_Text(pDX, IDC_ASCHEN2, m_strAsCen2);
	DDX_Text(pDX, IDC_ASIMETR, m_strAsimetr);
	DDX_Text(pDX, IDC_2_ASIMETR, m_2_valueAsimetr);
}


BEGIN_MESSAGE_MAP(�ViewAsim, CDialogEx)
END_MESSAGE_MAP()


// ����������� ��������� �ViewAsim


BOOL �ViewAsim::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �������� �������������� �������������
	// ����� ������ �� dat
	//CConfigDat dat;
	//CConfigDat m_configdat;
	m_configdat.OutSerialize();

	m_strPiket1.SetString(L"��� �� ������");
	m_strAsCen1.SetString(_T("���.1"));
	m_strAsCen2.SetString(_T("���.2"));
	m_strAsimetr.SetString(_T("�����."));
	UpdateData(false); //����� ��� �������� � �������� ����

	// ���������� 1 �����
	int pr;
	pr = m_configdat.m_strComPort1.Compare(L"�� ������������");
	//���������� ������ ����
	if (pr) 
	{
		CFileStatus status;
		CString ssport;
		ssport.Format(L"\\\\.\\%s",m_configdat.m_strComPort1.Left(5));

		if (CFile::GetStatus(ssport, status))
		{
			port01.Open(ComPortStrtoInt(m_configdat.m_strComPort1));
			port01.Set0ReadTimeout();  // ��� ����� ���������
		}
		else
		{
			CString sss;
			sss.Format(L"���� %s �� ������ ��� �� ��������, \r\n \r\n      �������� ���������",m_configdat.m_strComPort1);
			AfxMessageBox(sss);
		}
	}

	CFileException fe;
	if (!asimfile.Open(_T("Data\\asim.txt"), // &fe
					CFile::modeCreate |
					CFile::modeNoTruncate |	// ���� ���������� - ��������
					CFile::modeReadWrite, &fe))
	{
			fe.ReportError();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

// ����������� �������� ����� � ��� �����
int �ViewAsim::ComPortStrtoInt(CString strComPort)
{
	//CString sss;
	strComPort.Delete(strComPort.Find(L"<")-1,50); //�� ����� ������
	int n_port = _ttoi(strComPort.Mid(3,3));

	return n_port;
}

BOOL �ViewAsim::DestroyWindow()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	port01.Close();

	return CDialogEx::DestroyWindow();
}


BOOL �ViewAsim::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
		CString str;
	switch (message)
	{
		case WM_TIMER:
//			AfxMessageBox (_T("������ on"), NULL, 0);
			// ������ ��� ������
			ASSERT (m_gtimer);
		if (wParam == m_gtimer)
		{
			if (port01.IsOpen())    // ������ 1-� Com ����
			{

				OnReadComPort1();
				m_strPiket1.SetString(m_gstrPiket);
				UpdateData(false);
					//	AfxMessageBox (_T("������"), NULL, 0);
			}
			///////////////////////////////////////////////////////////////////////////////
			// ������������� ���� ���������
			if (asimfile.m_hFile!=(HANDLE)-1)
			{
				CString strif, strf;
				//////m_strAsimetr =L"33";
				strif = m_strAsimetr;//.GetString();
		
				if (m_Asimetr > 4)        //    strif !=_T("0 %"))// ������ = A
				{
					CString srtutf(L'\xFEFF');
					strif = srtutf+ strif;			// ������ = xFEFF A
					strif += _T("\t" );
					
					if (m_configdat.m_strComPort1.Compare(L"�� ������������"))
					{
						strif += m_gstrPiket.Trim(L" ");		// ������ = xFEFF A ������
						strif += _T("\t" );
					}
					
					strif += m_gstrPiket;			// ������ = xFEFF A ������ ������
					strif += _T("\t" );
					
					strif += m_gstr_Latitude; 
					strif += _T("\t" );
					strif += m_gstr_Longitude;
					strif += _T("\r\n");            // ������ = xFEFF A ������ ������ ������ �������
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


void �ViewAsim::OnCancel()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	if (port01.IsOpen()) // try �� �������������   && m_configdat.m_strComPort1.Compare(L"�� ������������")
	{
		port01.CancelIo();
		port01.Close();                      // try �� �������������
		//AfxMessageBox(_T("����1 ������"));
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
		
		//  - ������� � ���� �� ��������
		CString str(L"�������� - ");
		str += time.Format("%Y %x %X\r\n"); //\n
		//  CStdioFile - ������� � ������
		
		// str = L"\�\�\�\�\�\�\�\� - " + str + L"\�\�\�\�\� \n";
		//////////////// SaveFile.Write(m_text ,m_text.GetLength()*sizeof(TCHAR) );
		// str = L"�������� - " + str + L"\r\n";
		 //str += L"����� \r\n";
		 // _T("\r\n");
		//str.OemToCharA();
		asimfile.SeekToEnd();
		asimfile.Write(str,str.GetLength()*sizeof(TCHAR)); // (LPCTSTR)
		asimfile.Close();
	}

	CDialogEx::OnCancel();
}



void �ViewAsim::OnReadComPort1(void)
{
#ifdef _DEBUG
		�ViewAsim::SetWindowTextW(L"Start OnReadComPort1");
#endif
		////////////////////////////////
	///
	// ������ Com ����
	//ComGps.WriteString((LPCTSTR)str);
	//ComGps.ReadString(str);

			//char WCHAR
/////////////////////////////////////////////////////////////////////////////////////////////////
	//// ��������� ������ 1-�� �����  //AfxMessageBox(mStart);
//AfxMessageBox(L"������0");
			CString mStart;
			mStart	= L"$AS  ����   $AV��. "; //_T("$AS������!!$AVerror") ;


			////

		 //mStart1.GetBufferSetLength(400);
		// char* mStart2[400];
		 //port01.ReadEx(mStart1.GetBuffer(), 20);  // (void*)(LPCTSTR)mStart1
			////

				//COMMTIMEOUTS timeouts;
				//timeouts.ReadTotalTimeoutMultiplier = 1000; // 100000
				//port01.SetTimeouts(timeouts);

				//port01.Set0ReadTimeout();  // ��� ����� ��������� // ��������� � InitInstance
				
//AfxMessageBox(L"������1");

				port01.ReadEx(mStart.GetBuffer(), 20);  // (void*)(LPCTSTR)mStart1 - �� �� ��������
				// port.ClearReadBuffer();sRxBuf
				//port01.
				//port01.ClearReadBuffer(); // ������-�� ������
				
				int ns = mStart.Find(_T("$AS"),0)+3;
				int nv = mStart.Find(_T("$AV"),0)+3;
				if (ns<nv)
				{
					m_strPiket1 = mStart.Mid(ns, ns+5) + _T("�� ") + //+8	// ���� ������� ������
								mStart.Mid(nv, nv+2) + _T("��/�");//+5

				}
#ifdef _DEBUG
	�ViewAsim::SetWindowTextW(L"Stop OnReadComPort1");
#endif
/// ����� ��������� ������ 1-�� �����
	//////////////////////////////////////////////////////////////////////////////////////

}  //// CViewPut::OnReadComPort1 END

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////// ������� �������
void �ViewAsim::OpenComPort(int nPort, CString strComPort)
{
			/// ������� � ��������� ������
	//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	//	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	//	pStatus->SetPaneText(0, strComPort);


	sPort.Format(_T("\\\\.\\%s"), strComPort);
	sPort.Delete(sPort.Find(L"<")-1,50); //�� ����� ������

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


// �����, ����������� ���� �1
UINT ThreadFunc (LPVOID pParam)
{	
	CString* nPort = static_cast<CString*>(pParam);
	CString strPort;
	// ��������� �������� ����� � ����� �����
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
	soob.Format(_T("������ �������� ����� �1 %s:\n %s\n"),
				strPort.Mid(4,6),
				pEx->GetErrorMessage().operator LPCTSTR());
	AfxMessageBox(soob);
    pEx->Delete();
  }

	return FALSE;
} // END ThreadFunc 1

void �ViewAsim::OnReadComPort1Thread(void)
{
				////////////////////////////////
				///
				// ������ 1-� Com ����
				if (hThread1)
				{
					if (::WaitForSingleObject(pThread1->m_hThread, 0) != WAIT_OBJECT_0)
						::ExitThread(0); //TerminateThread(hThread,0)
					//AfxMessageBox(_T("��� ���� ������ �����"));
				}
//					::TerminateThread(pThread->m_hThread,0);
				//CWinThread *
					pThread1 = ::AfxBeginThread (ThreadFuncRead, NULL);
				//HANDLE 
					hThread1 = pThread1->m_hThread;
								//Sleep(1);
}

// ����� � ������� ������ �� ����� 1
UINT ThreadFuncRead (LPVOID pParam)
{
	UNREFERENCED_PARAMETER(pParam);
	////////////////////////////////
	///
	// ������ Com ����
	//ComGps.WriteString((LPCTSTR)str);
	//ComGps.ReadString(str);

			//char WCHAR
/////////////////////////////////////////////////////////////////////////////////////////////////
	//// ��������� ������ 1-�� �����
//			unsigned char	sRxBuf[] =  "$AS������!!$AVerror";
			CString mStart;
			mStart	= _T("$AS  ����   $AV��. "); //_T("$AS������!!$AVerror") ;
	//		strPiket = _T("����� ����������");
//			DWORD dwRead;
	//		*sRxBuf = *mStart;

	try
	{
// 		if (port.IsOpen())
//		{
			//char sRxBuf[38]; // 19 ��������  Unicode ?
			//_T("$AS1234,567�� $AV123,4");
			

			//AfxMessageBox(_T("������"));
			//dwRead = 
		// ��������� &mStart
				
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
				// �������� ������ ���� "$ASkkkk,mmm$AVsss,s"
				
//				int		pos;
				
	//			mStart = sRxBuf;
//				strPiket = sRxBuf;

	

				//return FALSE; 

				int ns = mStart.Find(_T("$AS"),0)+3;
				int nv = mStart.Find(_T("$AV"),0)+3;
				if (ns<nv)
				{
//					strPiket = mStart.Mid(ns, ns+5) + _T("�� ") + //+8	// ���� ������� ������
//								mStart.Mid(nv, nv+2) + _T("��/�");//+5

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
//				strPiket = mStart.Mid(ns, ns+5) + _T("�� ") + //+8	// ���� ������� ������
//							mStart.Mid(nv, nv+2) + _T("��/�");//+5
//				}
//				else strPiket = _T("������ ������");

				
				//strPiket.Format(_T("%X%X%X %X "), 
				//sRxBuf[1], sRxBuf[2], sRxBuf[3], sRxBuf[4] );
				//m_strPiket.SetString(str);
			//}
			//strPiket = _T("��� ������");
//		}
//		strPiket = _T("���� �� ������");
	}
	catch (CSerialException* pEx)
	{
		TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
		CString soob;
		soob.Format(_T("������ ������ ������� ��� �����:\n %s\n"),
		pEx->GetErrorMessage().operator LPCTSTR());
		//AfxMessageBox(soob);
		///
//st		CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//st		CStatusBar* pStatus = &pFrame->m_wndStatusBar;
//st		pStatus->SetPaneText(0, soob);
		///
//		strPiket = _T("������");
		pEx->Delete();
	}

/// ����� ��������� ������ 1-�� �����
	//////////////////////////////////////////////////////////////////////////////////////


	return FALSE;
} // END ThreadFuncRead
