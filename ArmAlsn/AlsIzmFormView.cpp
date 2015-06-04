// AlsIzmFormView.cpp: ���� ����������
// ��������� ���������� �.�.

#include "stdafx.h"
#include "ArmAlsn.h"

#include "DataRowItinerary.h"
#include "DataRowCoupe.h"
#include "DataRowObject.h"

#include "MainFrm.h"
#include "ViewPut.h"

#include "AlsIzmFormView.h"

//#include "OziExplorerMap.h"
//#include "oziapi.h"
#include "OziExplorerApi.h"

//static UINT NEAR
//static		 UINT  WM_TOK=0;
static		 UINT  WM_TOK = ::RegisterWindowMessage((LPCWSTR) L"MyMessage_TOK");

// CAlsIzmFormView

IMPLEMENT_DYNCREATE(CAlsIzmFormView, CFormView)

	CDataObjectRowset	dataObject;



// Progress bar
#define BASE 2500	// for test 

#define PROGRESS 0
#define SNAKE 1

CAlsIzmFormView::CAlsIzmFormView()
	: CFormView(CAlsIzmFormView::IDD)
	, m_strPK_current(_T(""))
	, m_strPK_n(_T(""))
	, m_strPK_k(_T(""))
	, m_str_Latitude(_T(""))
	, m_str_Longitude(_T(""))
	, m_strStolbKm_current(_T(""))
	
{
	m_ozi = -1; // �������
	m_PK_obgect_start=0;
	m_TOK = 0;
	m_TOK1 = 0;
	// Progress bar
	//{{AFX_DATA_INIT(CAlsIzmFormView)
	m_fUseBrush = FALSE;
	m_fRubberBar = FALSE;
	m_fTiedText = FALSE;
	m_fVertText = TRUE;
	m_nBorder = 0;
	m_iTextMode = 0;
	m_iProgressMode = 0;
	m_nRange = 100;
	m_nStepSize = 1; //2
	m_nTailSize = 1;//40
	//}}AFX_DATA_INIT
	m_pos = 0;
	m_inc = TRUE;
	// Progress bar end
}

CAlsIzmFormView::~CAlsIzmFormView()
{
	// �������� ������ � ������� ������ CMainFrame ����� ���:
//	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
//	pMainFrame->m_ViewPut.DestroyWindow();
	//FileTok.Close();	// ������ 2015.05.13
	//dataObject.CloseAll();  //

	
}

void CAlsIzmFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUPE_IZM, m_Coupe);
	DDX_Control(pDX, IDC_ITINERARY_IZM, m_Itinerary);
	DDX_Control(pDX, IDC_OBGECT_IZM, m_Obgect);
	DDX_Control(pDX, IDC_OBGECT_OLD_IZM, m_Obgect_old);
	DDX_Text(pDX, IDC_PK_V_IZM, m_strPK_current);
	DDX_Control(pDX, IDC_PK_V_IZM, m_PK_current_Ctrl);
	DDX_Text(pDX, IDC_PK_V_N, m_strPK_n);
	DDX_Text(pDX, IDC_PK_V_K, m_strPK_k);
	DDX_Text(pDX, IDC_LATITUDE_IZM, m_str_Latitude);
	DDX_Text(pDX, IDC_LONGITUDE_IZM, m_str_Longitude);
	DDX_Text(pDX, IDC_TOK_IZM, m_strTOK_current); //Control
	DDX_Control(pDX, IDC_TOK_IZM, m_TOK_current_Ctrl);
	DDX_Text(pDX, IDC_STOLB_KM, m_strStolbKm_current);
	DDX_Control(pDX, IDC_START_IZM, StartIzm);
	DDX_Control(pDX, IDC_PROGRESS_H, m_progressH); // ProgressBar
}

//

BEGIN_MESSAGE_MAP(CAlsIzmFormView, CFormView)
	ON_CBN_SELCHANGE(IDC_ITINERARY_IZM, &CAlsIzmFormView::OnCbnSelchangeItineraryIzm)
	ON_BN_CLICKED(IDC_START_IZM, &CAlsIzmFormView::OnBnClickedStartIzm)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STIK, &CAlsIzmFormView::OnBnClickedStik)
	//
	ON_REGISTERED_MESSAGE(WM_TOK, &CAlsIzmFormView::OnTok)
	ON_MESSAGE(WM_MYMESSAGE,&CAlsIzmFormView::OnMyMessage)

	//ON_MESSAGE(WM_TOK, &CAlsIzmFormView::OnTok)
	//ON_REGISTERED_MESSAGE(WM_TOK, &CAlsIzmFormView::OnBnClickedStik)
	//ON_EN_CHANGE(IDC_PK_V_IZM, &CAlsIzmFormView::OnEnChangePkVIzm)
	ON_COMMAND(ID_OziMap, &CAlsIzmFormView::OnOziMap)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS_H, &CAlsIzmFormView::OnNMCustomdrawProgressH)
END_MESSAGE_MAP()


// ����������� CAlsIzmFormView

#ifdef _DEBUG
void CAlsIzmFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAlsIzmFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ����������� ��������� CAlsIzmFormView


void CAlsIzmFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	
	// �������� �� ������� ����������
	//CMainFrame* mf;
	//mf->OnViewPut();
	// �������� ������ � ������� ������ CMainFrame ����� ���:
//	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
	//��������� ���� ����������
//	pMainFrame->OnViewPut();
//	// � �������������� ���
//	pMainFrame->m_ViewPut.ShowWindow(2); //3-���



	// ���������������� ����� ��������� ��� ������������� � ����
	// �����������. ��� ������ ������ ��������� � �����
	// �����������.
	//.................................................
	
	
	m_Itinerary.SetExtendedUI(1);
	m_Coupe.SetExtendedUI(1);
	m_Obgect.SetExtendedUI(1);
	m_Obgect_old.SetExtendedUI(1);
	

	CDataItineraryRowset dataItin; // = new CDataItineraryRowset ;
 
	if (SUCCEEDED(dataItin.OpenAll()))
	{
		m_Itinerary.ResetContent();
		while (dataItin.MoveNext() == S_OK)
		{
			//AfxMessageBox(dataItin->m_ItineraryName);
			m_Itinerary.AddString(dataItin.m_ItineraryName);
		}
		m_Itinerary.SetCurSel(0);	
		//dataItin.CloseAll();

		/////////////////////////////
		DWORD dwAttrs;
		LPCWSTR aa = L"Data\\";

		dwAttrs = GetFileAttributes(aa);   // 

		if (dwAttrs == INVALID_FILE_ATTRIBUTES)
		{
			//AfxMessageBox( L"��� ����� �����!!");
			if (!CreateDirectory(aa, NULL))
			{
				AfxMessageBox(L"�� ���� ������� �������� \"Data\" � ������� ��������");
			}
		}

		


		////////////////////////////////////////////

		OnCbnSelchangeItineraryIzm(); // ������� 1-� �������
		// ����� ���
		OpenFileTok	(L"Data\\tok.txt");

	}
	else
	{
		StartIzm.EnableWindow(false);
		AfxMessageBox(L"������ �������� ���� ���������");
	}

	// pb
	OnChangeRange(); //init
	OnChangeStepsize(); //init
	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));
	_tcscpy_s (lf.lfFaceName, _T("Arial")); // !!!!!!!! Only True-Type Fonts (TTF) can be rotated
	lf.lfWeight = 700;
	m_fontH.CreateFontIndirect(&lf);
	lf.lfOrientation = 900;
	lf.lfEscapement = 900;
	m_progressH.SetFont(&m_fontH);

	m_brBk.CreateHatchBrush(HS_DIAGCROSS, RGB(0,0,255));
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	m_brBar.CreatePatternBrush(&bmp);

	// pb end

	// ������������� ����� �����������
	m_pObjFont.CreateFont(23, 0, 0, 0, FW_EXTRABOLD, FALSE, FALSE, FALSE,  //FW_NORMAL FW_BOLD
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE, (LPCTSTR)"Verdana"); //Tahoma Arial   Times New Roman

	m_PK_current_Ctrl.SetFont(&m_pObjFont);
	m_PK_current_Ctrl.SetReadOnly();
	m_TOK_current_Ctrl.SetFont(&m_pObjFont);
	m_TOK_current_Ctrl.SetReadOnly();


//	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
	//��������� ���� ����������
//	pMainFrame->OnViewPut();
}
// END   OnInitialUpdate()

BOOL CAlsIzmFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
		if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	//BOOL bRes = CFormView::PreCreateWindow(cs);

	cs.style &= ~FWS_ADDTOTITLE;
	cs.x = 10;
	cs.y = 10;
	cs.cx=100;
	cs.cy=100;
	//return bRes;
	//return CFormView::PreCreateWindow(cs);
	return TRUE;
}
/////////////////////////////////
// ������� �������
void CAlsIzmFormView::OnCbnSelchangeItineraryIzm()
{
	// TODO: �������� ���� ��� ����������� �����������
	////////////////////////////////////////////////////////

	//AfxMessageBox(L"������ �������� ���� ���������");

	//CViewPut *wPut = new CViewPut;
//	CViewPut *wPut;
//	CString sPut = wPut->m_2_strPiket;
//	sPut =L"111";
//	AfxMessageBox(sPut);
//	m_PK_car = L"223355";
//	AfxMessageBox(m_PK_car);
//	m_strPiket.Format(_T(" %.3f "),wPut->OnPK_car());
	// �� ��������� � ����������
//	m_strPiket= wPut->m_2_strPiket;
//	double pelix;
	
	KillTimer(10);
	dataObject.CloseAll();
//	put = 0;
	m_PK_current=theApp.m_PK_current;
	m_strPK_current.Format(_T(" %.3f "),m_PK_current);
	//m_strPK_n.Format(_T(" %.3f "),m_PK_n);
	//m_strPK_k.Format(_T(" %.3f "),m_PK_k);
	m_str_Latitude=theApp.m_str_Latitude_current;
	m_str_Longitude=theApp.m_str_Longitude_current;
	UpdateData(FALSE);
//AfxMessageBox(L"��������� 3");
	CString  strQuery; // sss,
	//double pk=0;

//	int n_records;
	CSession session;
	// �������� �������
	m_Itinerary.GetLBText(m_Itinerary.GetCurSel(),sss);
	// �������� ����������
	m_Coupe.ResetContent();
	m_Obgect.ResetContent();
	m_Obgect_old.ResetContent();
	// ���� ��� ����������
	// AfxMessageBox(m_strPK_current);
	if (m_strPK_current.IsEmpty())   // ��������� �� ������� ���������
	{
		AfxMessageBox(L"��������� �� �������");
		CDataRowsetCoupe dataCoupe;

		strQuery.Format(L"SELECT * FROM [��������] WHERE [ItineraryName]=\"%s\"",sss); //CoupeName


		//m_Coupe.AddString(L"");

		if (SUCCEEDED(dataCoupe.OpenAll()))
		{
			session=dataCoupe.m_session;
			dataCoupe.CloseAll();

			if (SUCCEEDED(dataCoupe.Open(session, strQuery))) //'������� ����. - ������� ��.'ataCoupe.Open(dataCoupe.m_session,sss))
			{
				//dataCoupe.MoveFirst();
				while (dataCoupe.MoveNext() == S_OK)
				{
					m_Coupe.AddString(dataCoupe.m_CoupeName);
				}
				m_Coupe.SetCurSel(0);
				dataCoupe.CloseAll();
			}
			else AfxMessageBox(L"������ ������� � ���� ���������");
		}
		else AfxMessageBox(L"������ �������� ���� ���������");
	}
// ���� ����������
	else   //�����, �� ������� ��������
	{
	
		
		//dataObject.  END [Pk] > 10  [ItineraryName]=\"%s\"",sss,pk)
		// �������� ������� ��������� ��������, � ���������, ������� ������� � ����������� \"%f\"
		//AfxMessageBox(m_strPK_current);
		if (theApp.m_ipiketkp==1) 
			strQuery.Format(L"SELECT * FROM [�������] WHERE [ItineraryName]=\"%s\" AND [Pk] > %f ORDER BY Pk ASC",sss,m_PK_current);
		else                      
			strQuery.Format(L"SELECT * FROM [�������] WHERE [ItineraryName]=\"%s\" AND [Pk] < %f ORDER BY Pk DESC",sss,m_PK_current);

	//AfxMessageBox(strQuery);
		if (SUCCEEDED(dataObject.OpenAll()))
		{

			session=dataObject.m_session;
			dataObject.CloseAll();
			//AfxMessageBox(strQuery);
			if (SUCCEEDED(dataObject.Open(session, strQuery))) //'������� ����. - ������� ��.'ataCoupe.Open(dataCoupe.m_session,sss))
			{
	//			 AfxMessageBox(L"������ � ���� �������");
				//dataCoupe.MoveFirst();
				while (dataObject.MoveNext() == S_OK)
				{
//					CString ss;
//					ss.Format(L"It %s Coup %s",dataObject.m_ItineraryName, dataObject.m_CoupeName);
//					AfxMessageBox(dataObject.m_CoupeName);
					m_Coupe.AddString(dataObject.m_CoupeName);
					m_Obgect.AddString(dataObject.m_ObgectName);
					m_Obgect_old.AddString(dataObject.m_ObgectName);
/////////////////////////////////////////////////////////////////////////////////
					//m_Pk = dataObject.m_Pk;

/////////////////////////////////////////////////////////////////////////////////

				}
				m_Coupe.SetCurSel(0);
				m_Obgect.SetCurSel(0);
				m_Obgect_old.SetCurSel(-1);
				// � �������
				//OnBnClickedStartIzm();
				
			}
			else AfxMessageBox(L"������ ������� � ���� �������");
		}
		else AfxMessageBox(L"������ �������� ���� �������");
	}
	//AfxMessageBox(L"����� �������� ���� ���������");
			/////////////////////////////////////////////////////////////////////
}

// ������ �����
void CAlsIzmFormView::OnBnClickedStartIzm()
{
	// TODO: �������� ���� ��� ����������� �����������
	// setup update timer (25 - 4hz)2c 1c
/*	timer = timeSetEvent(950,	//  � �������� ������� �� ����������� ���������� ������� � �������������.
						50,	//  � ���������� ������� ��� ������� ���������, � �������������. ������� �������� ������� ����������� ���������� ���������� 
						0, //  � ��������� ������� �����������.
						0, //  � ������������ 32-��������� ��������, ������������ ������� ����������� ��� ������ � �������� ���������.
						TIME_PERIODIC); // ��� ���������� �������: TIME_ONESHOT � �����������, TIME_PERIODIC � �������������.
	*/





	dataObject.MoveFirst();
	/////
	// �������� ������ � ������� ������ CMainFrame ����� ���:
///	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
///	put = &pMainFrame->m_ViewPut;
	sss.Format(L"\xFEFF\r\n�������\t%s\r\n",dataObject.m_ItineraryName);
	//sss =  L'\xFEFF'+ ssf;
	//sss += dataObject.m_ItineraryName;
	//sss += L"\r\n"; //+L"�������\t"
	//sss += _T("\r\n" );
///	put->asimfile.SeekToEnd();
///	put->asimfile.Write(sss,sss.GetLength()*sizeof(TCHAR ));
	
//	dataObject.MoveNext();
	//AfxMessageBox(dataObject.m_ObgectName);
	//m_PK_obgect_start = m_PK_obgect;
	m_PK_obgect = dataObject.m_Pk;
	m_CurSel = 0;


	////
	   	if (FileTok.m_hFile!=(HANDLE)-1)
	{
		sss = L"\r\n";
		//
		CTime time = CTime::GetCurrentTime();
		sss += time.Format("%x %X\t");	   //%Y 
		//
		//sss += L"\t";
		sss += L"�������: ";
		//sss += L"\t";
		sss += dataObject.m_ItineraryName;
		sss += L"\r\n";
		FileTok.SeekToEnd();
		FileTok.Write(sss, sss.GetLength()*sizeof(TCHAR));
 	}



	//��������� ��������� OziExplorer
	if (m_gOziExplorer_OnOff)
	{
		COziExplorerApi OziExplorer; // ������ � �����
		if (!OziExplorer.OziExplorerIsRun) return ; // ���� ��� �� �������� - �����
		if (OziExplorer.CheckOziExplorerRunning() == -1)
		{
			AfxMessageBox(L" ������ OziExplorer �� ����� ��������������. \n  ��������� ������ ����� ��� �������������");

			////AfxMessageBox(L"OziExplorer �� �������",0,0);
			//::ShellExecute(NULL, L"Open", m_gstrPathOz,
			//			   NULL,
			//			   m_gstrPathOz.Left(m_gstrPathOz.ReverseFind(_T('\\'))+1),
			//			   SW_SHOWNORMAL);
			//////////////////////////////////////////////////////////////////////////////
			SHELLEXECUTEINFO se;
			se.cbSize =sizeof(se);
			se.fMask = NULL;
			//se.hwnd = GetDesktopWindow();
			se.lpVerb = L"runas";
			se.lpFile = m_gstrPathOz;
			se.lpDirectory = m_gstrPathOz.Left(m_gstrPathOz.ReverseFind(_T('\\'))+1);
			se.nShow = SW_NORMAL;
			//se.lpParameters = 
			::ShellExecuteEx(&se);
			/////////////////////////////////////////////////////////////////////////////
			//Sleep(2000);
			do {}
			while (OziExplorer.CheckOziExplorerRunning());
			Sleep(3000);
			///////////////////////////////////////////////////////////
		}
	   // �������� �������
		m_Itinerary.GetLBText(m_Itinerary.GetCurSel(),sss);
		// ������� ������ ������� �����
		OziExplorer.ClearAllWaypoints();
		// ��������� ������� �����
		if (OziExplorer.LoadWaypoint(&sss))  // 0 ��� ����� 
		{
			AfxMessageBox (L"������ �������� ������� �����  " + sss);
			return ;
		}
		// ��������� �������
		//AfxMessageBox (L"�������� ��������� �������" + sss);
		if (OziExplorer.LoadRoute(&sss))  // 0 ��� ����� 
		{
			AfxMessageBox (L"������ �������� ��������  " + sss);
			return ;
		}
		//else 

		if (OziExplorer.StartMovingMapSerial()) // ��������� ���������,����� ������� �� ��������
		{
			AfxMessageBox(L"�� �������� ��������� ����� � GPS",0,0);
			return ;
		}
		
		OziExplorer.ShowTrack(1); // �������� ����

		////��������� ������������ �1
		//////int res = oziOedometer1ON((int*)& Oedometer1);
		//////if (res)
		//////{
		//////	AfxMessageBox(L"������� �� �������",0,0);
		//////	return ;			
		//////}
		//double m_gPiket;
		//m_gPiket = NULL;
		//m_gPiket = 333,0;
		//double* m_Pk;
		//m_Pk = & m_gPiket;
		//int mp;
		//mp = NULL;
		//int* mpp;
		//mpp = & mp;
		////if (OziExplorer.OedometerON(1, &m_gPiket, &mp))  // theApp.m_PK_current theApp.m_ipiketkp
		////{
		////	AfxMessageBox(L"������� �� �������",0,0);
		////	return ;			
		////}
		////else AfxMessageBox(L"������� �������",0,0);
		//}
	}
		////
	
	SetTimer(10, 500, NULL); //1000
}


void CAlsIzmFormView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	//AfxMessageBox(L"Timer");

	m_str_Latitude=theApp.m_str_Latitude_current;
	m_str_Longitude=theApp.m_str_Longitude_current;
	/////
/*
	if (m_gOziExplorer_OnOff)
	{
		COziExplorerMap OziExplorer;
		// ��������� ���
		if (OziExplorer.LoadOziApiDll()==0)
		{
//			m_strStolbKm_current = OziExplorer.GetNavWp();
			
			m_PK_current = OziExplorer.Position.distance1;
			OziExplorer.ClosingAPI();
		}
	}
	else */
		m_PK_current = theApp.m_PK_current;

	m_strPK_current.Format(_T(" %.3f "),m_PK_current); 

	m_strPK_n.Format(_T(" %.3f "),m_PK_obgect_start); 
	m_strPK_k.Format(_T(" %.3f "),m_PK_obgect); 
	/////
	

#ifdef _DEBUG
	WriteFileTok(m_strPK_current + L"\t" + m_strTOK_current); // ����� ������
#endif

	
	///////////
	int res = 0;

	// ��� ��������
	if ((theApp.m_ipiketkp==1) & ((m_PK_current -0.05) > m_PK_obgect)) res = 1; //+0.03  ���� 20 ������
	if ((theApp.m_ipiketkp==0) & ((m_PK_current +0.05) < m_PK_obgect)) res = 1; //-0.030
	if (((m_TOK+m_TOK) < m_TOK1)) res = 1; // ��� ��������� � 2 ����
	m_TOK1 = m_TOK;
	if (res)
	{
		OnBnClickedStik();
		// ����� ���
		//OpenFileTok	(L"Data\\tok.txt");
		// ������������� ���� ���������
		UpdateData(FALSE);
		if (dataObject.m_Type)	 // ���� ��������� ������������ ���������
		{
			
			WriteFileTok(m_strPK_current + L"\t" + 	m_strTOK_current);
		}
		else  WriteFileTok(m_strPK_current + L"\t");

		//FileTok.Close();
	}
	UpdateData(FALSE);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///ProgressBar
	if(m_iProgressMode == PROGRESS)  //m_iProgressMode == PROGRESS
	{
		CString ssp1;
		//  �� ����������
		if (theApp.m_ipiketkp==1)  
		{
			m_nRange = (unsigned int)((m_PK_obgect - m_PK_obgect_start)*1000);
			m_pos = (unsigned int)((m_PK_current - m_PK_obgect_start)*100 / (m_PK_obgect - m_PK_obgect_start));
		}
		// �� ����������
		if (theApp.m_ipiketkp==0)  
		{
			m_nRange = (unsigned int)((m_PK_obgect_start - m_PK_obgect)*1000);
			m_pos = (unsigned int)((m_PK_obgect_start-m_PK_current)*100 / (m_PK_obgect_start-m_PK_obgect));
		}
		if (m_pos > m_nRange)	m_pos = m_nRange;
		if (m_pos < 0)	m_pos = 0;
		ssp1.Format(L" %d �", m_nRange); // %.3f
		m_progressH.SetTextFormat(ssp1);
		m_progressH.Invalidate();
		m_progressH.SetPos(BASE+m_pos);
	}
	else
	{
		m_progressH.StepIt();
	}
	///ProgressBar end
	//////////////////////////////////////////////////////////////////////////////////////////////////
	CFormView::OnTimer(nIDEvent);
}

// ����������� ����������� ����� ���������� ������� ������ �� ������ //������������ �������� ������
///
#pragma data_seg ("MY_DATA") 
TCHAR cSharedData[100] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#pragma data_seg () 
///


void CAlsIzmFormView::OnBnClickedStik()
{
	sss.Format(L"\xFEFF \r\n%s\t%s ��\t(���� %.3f ��)\t%s\r\n", 
												dataObject.m_ObgectName,
												m_strPK_current,
												dataObject.m_Pk,
												dataObject.m_CoupeName);
//sss = L'\xFEFF'+dataObject.m_ObgectName;
//sss = ssf; //+dataObject.m_CoupeName+L"\r\n";
//	put->asimfile.SeekToEnd();
//	put->asimfile.Write(sss,sss.GetLength()*sizeof(TCHAR ));

	KillTimer(10); // �� ����� �������� �� ���� ����������
	if (dataObject.MoveNext() == S_OK)
	{
		//AfxMessageBox(dataObject.m_ObgectName);
		m_PK_obgect_start = m_PK_obgect;
		m_PK_obgect = dataObject.m_Pk;
		m_CurSel ++;
		m_Coupe.SetCurSel(m_CurSel);
		m_Obgect.SetCurSel(m_CurSel);
		m_Obgect_old.SetCurSel(m_CurSel-1);
		SetTimer(10, 500, NULL);
		//UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(L"������� ��������");
		dataObject.CloseAll();
	}
}

afx_msg LRESULT CAlsIzmFormView::OnTok(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
   //AfxMessageBox(L"Tok �� AlsIzmFormView");
	m_TOK = wParam;

	UINT_PTR s3 = wParam/10;
	m_strTOK_current.Format(L"%d.%d A",wParam/10,wParam-s3*10);
	UpdateData(FALSE);
	return 0;
}


afx_msg LRESULT  CAlsIzmFormView::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	MessageBeep(MB_SERVICE_NOTIFICATION);   //-1
	AfxMessageBox(L"Tok �� OnMyMessage");
	return 0;
}


bool CAlsIzmFormView::OpenFileTok(CString filename)
{				  //CFileException fe;
	if (!FileTok.Open(filename, // &fe
		CFile::modeCreate |
		CFile::modeNoTruncate |	// ���� ���������� - ��������
		CFile::modeReadWrite, &fe))
	{
		fe.ReportError();
		return false;
	}
	return true;
}

bool CAlsIzmFormView::WriteFileTok(CString filename)
{
	if (FileTok.m_hFile!=(HANDLE)-1)
	{
//		filename += L"\r\n";
		filename += L"\t";
		filename += dataObject.m_ObgectName;
		filename += L"\t";
		filename += dataObject.m_CoupeName;
		filename += L"\r\n";
		FileTok.SeekToEnd();
		FileTok.Write(filename, filename.GetLength()*sizeof(TCHAR));
		return true;
 	}
	return false;
}
// ��������� ������� ����
void CAlsIzmFormView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �������� ���� ��� ����������� ���������
	// AfxMessageBox(L"���� ����� �������");

	//
	//OziExplorer.ClosingAPI();
	//
	FileTok.Close();
	KillTimer(10);

	//CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
	//pMainFrame->m_ViewPut.DestroyWindow();

	dataObject.CloseAll();
//	if (!m_ozi) OziExplorer.ClosingAPI();
}
/*
BOOL CAlsIzmFormView::DestroyWindow()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	AfxMessageBox(L"��������� �������");
	//COziExplorerMap OziExplorer;
	if (OziExplorer.CheckOziExplorerRunning() == 0)
		{			
			OziExplorer.CloseOziExplorer();
		}
		FileTok.Close();

		dataObject.CloseAll();
	return CFormView::DestroyWindow();
}
*/

void CAlsIzmFormView::OnOziMap()
{
	// TODO: �������� ���� ��� ����������� ������


 // ������ � �����
	//		AfxMessageBox(OziExplorer.GetOziExePath(),0,0);
	//OziExplorer1.LoadOziApiDll();
//	if (OziExplorer.LoadOziApiDll()!=0) 
//	{
//		return;
//	}
//	else
//	{
	////if (m_gOziExplorer_OnOff)
	////{			
	////	CString NavWp;
	////		//NavWp =
	////	OziExplorer.GetNavWp();
	////}
	COziExplorerApi OziExplorer;
	if (!OziExplorer.OziExplorerIsRun) return ;
//p20150524	CString sss;
	if (OziExplorer.GetNavWp(&sss))
	{
		AfxMessageBox(sss);
	}

	
					//res = (LPSTR)malloc(200);
                   // strcpy(res,wp);
				
					//AfxMessageBox(wp,0,0);
					//AfxMessageBox(ss);
			//AfxMessageBox(OziExplorer.wname,0,0);
			//AfxMessageBox(OziExplorer.wdescription,0,0);
//			AfxMessageBox(NavWp,0,0);
//		OziExplorer.ClosingAPI();
//	}

}




BOOL CAlsIzmFormView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	AfxMessageBox(L"���� ����� �������");

	return CFormView::OnDrop(pDataObject, dropEffect, point);
}





void CAlsIzmFormView::OnNMCustomdrawProgressH(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UNREFERENCED_PARAMETER(pNMCD);
	// TODO: �������� ���� ��� ����������� �����������
	*pResult = 0;
}
///////////////////////////////////////
// PBar
void CAlsIzmFormView::OnChangeRange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(!UpdateData())
		return;
	
	m_progressH.SetRange32(BASE, BASE+ (int)m_nRange);

	m_progressH.SetPos(BASE+m_pos);

	m_progressH.Invalidate();


}

void CAlsIzmFormView::OnChangeStepsize() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(!UpdateData())
		return;
	
	m_progressH.SetStep(m_nStepSize);
	m_progressH.Invalidate();
	
}


