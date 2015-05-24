// ConfigGPS.cpp: ���� ����������
//

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigGPS.h"
// ����� ��� PORT_INFO_1 �������� MSDN �������  include Windows.h.
#include <Winspool.h>
#include "ConfigDat.h"
#include <io.h> // ��� access
#include "enumser.h"

// ���������� ���� CConfigGPS

IMPLEMENT_DYNAMIC(CConfigGPS, CDialog)

CConfigGPS::CConfigGPS(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigGPS::IDD, pParent)
//	, m_pCombo(_T(""))
{

}

CConfigGPS::~CConfigGPS()
{
}

void CConfigGPS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_CBString(pDX, IDC_COMBO_PORT, m_pCombo);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ComboPort);
	DDX_Control(pDX, IDC_2_COMBO_PORT, m_2_ComboPort);
	DDX_Check(pDX, IDC_OZI, m_OziExplorer_OnOff);
	DDX_Control(pDX, IDC_OZI, m_ozi_offon);
	DDX_Control(pDX, IDC_MAP, m_map_onoff);
}



BEGIN_MESSAGE_MAP(CConfigGPS, CDialog)
		ON_BN_CLICKED(IDCONSAVE, &CConfigGPS::OnBnClickedConsave)
		ON_BN_CLICKED(IDC_BUTTON_1COM, &CConfigGPS::OnBnClickedButton1com)
		ON_BN_CLICKED(IDC_2_BUTTON_1COM, &CConfigGPS::OnBnClickedButton2com)
		ON_BN_CLICKED(IDC_OZI, &CConfigGPS::OnBnClickedOzi)
END_MESSAGE_MAP()


// ����������� ��������� CConfigGPS

BOOL CConfigGPS::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������

	//////////////////////////////////////////////////////////////////
	//m_pCombo.SetExtendedUI(1);
	m_ComboPort.SetExtendedUI(1);
	m_2_ComboPort.SetExtendedUI(1);
	// �������������� ComboBox, ���������� ����� ������
	// � ���� �� ������ �������� � ������� ������ 9, �� ���� ����������� ������ 
	// ��������� � �������� �������� \\.\COM10
	//CComboBox* pCombo = (CComboBox*) GetDlgItem(IDC_COMBO_PORT);

	///////////////////////////////////////////////////
// ����� ������ �� dat
	m_configdat.OutSerialize();
	

		//////////////////////////////////////////////////////
		///
		// �������� ������ ���� ������
//////////////////////////////////////////////////////////
		////
		  //////////////////////	
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef _AFX
  CUIntArray ports;
  int k1; //INT_PTR
  CStringArray sFriendlyNames;
#else
  CSimpleArray<UINT> ports;
  int k1;
  CSimpleArray<CString> sFriendlyNames;
#endif
 
	CString sss;
//	int CurSel = 0, CurSel2 = 0;
	if (CEnumerateSerial::UsingSetupAPI2(ports, sFriendlyNames)) //UsingSetupAPI1 - � ��� ����� �������
	{
		// ������� ��� �������� �� combo
		m_ComboPort.ResetContent();
		m_2_ComboPort.ResetContent();
	
		m_ComboPort.AddString(L"�� ������������");
		m_2_ComboPort.AddString(L"�� ������������");
		//int k1;
		m_ComboPort.SetCurSel(0);
		m_2_ComboPort.SetCurSel(0);
		for ( k1=0; k1<ports.GetSize(); k1++)
		{
			sss.Format(_T("COM%d <%s>\n"), ports[k1], sFriendlyNames[k1].operator LPCTSTR());
			sss.TrimRight(); // ������� " "sss.Delete( .GetLength() - 1);
			m_ComboPort.AddString(sss);
			m_2_ComboPort.AddString(sss);
			
			if (!sss.Compare(m_configdat.m_strComPort1))	m_ComboPort.SetCurSel(k1+1);
			if (!sss.Compare(m_configdat.m_2_strComPort1))	m_2_ComboPort.SetCurSel(k1+1);
		}  //END for
		sss = L"COM66 <�����������>";
		m_ComboPort.AddString(sss);
		m_2_ComboPort.AddString(sss);
		if (!sss.Compare(m_configdat.m_strComPort1))	m_ComboPort.SetCurSel(m_ComboPort.GetCount()-1);
		if (!sss.Compare(m_configdat.m_2_strComPort1))	m_2_ComboPort.SetCurSel(m_2_ComboPort.GetCount()-1); //
		//sss += m_configdat.m_2_strComPort1;
		//AfxMessageBox(sss);
		//m_2_ComboPort.
	}
  	else
  	{
    	sss.Format(_T("CEnumerateSerial::UsingSetupAPI2 �������, ������:%d\n"), GetLastError());
  		AfxMessageBox(sss);
  	}

//	ssr.Format(L"%i    %i",cc, CurSel);
//	AfxMessageBox(sss + L"\n" + m_configdat.m_strComPort1 + L"\n"+ ssr);

	//CString ssr;
	//	ssr.Format(L"%i",cc);
//	AfxMessageBox(sss + L"\n" + m_configdat.m_strComPort1 + L"\n"+ ssr);
///////////////////////
#ifdef _WIN64
	m_OziExplorer_OnOff = 0;
	m_ozi_offon.EnableWindow(false);
	m_ozi_offon.SetNote(L"� 64-�� ��������� �������� OziApi ����������");
#else
	m_OziExplorer_OnOff = m_gOziExplorer_OnOff;
	UpdateData(false); // ��  ������������ ����������  � ������� ���������� 
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

// �������� ���������
void CConfigGPS::OnBnClickedConsave()
{
	//AfxMessageBox(_T("SAVEGPS"));
	
	UpdateData(true);  // �� ��������� ���������� � ������������ ����������
	//m_ComboDevice.UpdateData(1);
	
	CString strsound;
	CString strs;
	
	//strs.SetLength(270);
	#pragma warning(push)
    #pragma warning(disable:6385 6203)
	strs.SetString(_T(""), MAX_PATH+2); //pelix
	#pragma warning(pop)
	//strs.ReleaseBufferSetLength(MAX_PATH+2);

	char ss[MAX_PATH*2+2]; // + /0
	DWORD dd = GetCurrentDirectoryW(MAX_PATH, (LPWSTR)ss);
	if (dd == NULL)
	{
		strs.Format(_T("������ � ���� ����� �������� %s, ����� %i"), (LPWSTR)ss, dd);
		AfxMessageBox( (LPCTSTR)strs,0,0);
	}
	
	strsound = (LPCTSTR)ss;
	strs = L"\\ArmALSN.ini";
	strs  = strsound + strs;
	 
	//m_pCombo.Get

	m_ComboPort.GetWindowTextW(strsound); //
	// ��������� ������ � dat
	m_configdat.m_strComPort1 = strsound;
	// ��������� ������ � ini
	WritePrivateProfileStringW(L"Port",L"1COM", strsound ,strs);

	//	m_configdat.m_strDirectXSound = strsound;

	m_2_ComboPort.GetWindowTextW(strsound);
	// ��������� ������ � dat
	m_configdat.m_2_strComPort1 = strsound;
	// ��������� ������ � ini
	WritePrivateProfileStringW(L"Port",L"2COM", strsound ,strs);
	

///////////////////////////////////////////////////
	// ��������� ������ � ���� dat
	if (UpdateData())
	{
		m_configdat.InSerialize();
	}
}


void CConfigGPS::Serialize(CArchive& ar)
{
	m_configdat.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

bool CConfigGPS::CanSerialize(void)
{
	return (0 == _access((const char*)m_gstrPathSet.GetBuffer(m_gstrPathSet.GetLength()),6));
}
// ������ ��������� 1-�� �����
void CConfigGPS::OnBnClickedButton1com()
{
	// TODO: �������� ���� ��� ����������� �����������
	COMMCONFIG comm;
	CString sPort;
	m_ComboPort.GetWindowTextW(sPort);
	sPort.Delete(sPort.Find(L"<")-1,50); //�� ����� ������
	//sPort.Left(sPort.Find(L"<"));
	//AfxMessageBox(sPort);
	CommConfigDialog(sPort,NULL,&comm);
}
void CConfigGPS::OnBnClickedButton2com()
{
	// TODO: �������� ���� ��� ����������� �����������
	COMMCONFIG comm;
	CString sPort;
	m_2_ComboPort.GetWindowTextW(sPort);
	sPort.Delete(sPort.Find(L"<")-1,50); //�� ����� ������
	//sPort.Left(sPort.Find(L"<"));
	//AfxMessageBox(sPort);
	CommConfigDialog(sPort,NULL,&comm);
}

//BOOL CConfigGPS::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: �������� ������������������ ��� ��� ����� �������� ������
//
//	return CDialog::PreCreateWindow(cs);
//}

BOOL CConfigGPS::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

		BOOL bHandledMsg = FALSE;

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		bHandledMsg =  TRUE;

		//AfxMessageBox(L"������ ����");
	}

	return ( bHandledMsg ? bHandledMsg
			: CDialog::PreTranslateMessage(pMsg));
}


void CConfigGPS::OnBnClickedOzi()
{
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(true);	
	m_gOziExplorer_OnOff = m_OziExplorer_OnOff; //������� ������������� OziExplorer
}
