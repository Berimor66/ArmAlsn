// ConfigSound.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ConfigSound.h"
#include "afxdialogex.h"
#include "ConfigDat.h"
#include <io.h> // для access


// диалоговое окно CConfigSound

IMPLEMENT_DYNAMIC(CConfigSound, CDialogEx)

CConfigSound::CConfigSound(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigSound::IDD, pParent)
//	, m_frec_rate(44100)
	, m_FreqRate(2)
{

}

CConfigSound::~CConfigSound()
{
}

void CConfigSound::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_OCFloat(pDX, IDC_FREC_RATE,0,m_frec_rate);
	//	DDX_Control(pDX, IDC_FREC_RATE,m_frec_rate);

	DDX_CBIndex(pDX, IDC_FREC_RATE, m_FreqRate);

	//DDV_MinMaxUInt(pDX, m_FreqRate, 100, 48200);
//p20130910	DDX_Control(pDX, IDC_FREC_RATE, m_cFreqRate);
}


BEGIN_MESSAGE_MAP(CConfigSound, CDialogEx)
	ON_BN_CLICKED(IDCONSAVE, &CConfigSound::OnBnClickedConsave)
	ON_CBN_SELCHANGE(IDC_FREC_RATE, &CConfigSound::OnCbnSelchangeFrecRate)
END_MESSAGE_MAP()


// обработчики сообщений CConfigSound


void CConfigSound::OnCbnSelchangeFrecRate()
{
	// TODO: добавьте свой код обработчика уведомлений
}


// Нажимаем применить
void CConfigSound::OnBnClickedConsave()
{
	UpdateData(1);  // Из элементов управления в компонентную переменную
	CString strsound;
	CString strs;
#pragma warning(push)
#pragma warning(disable:6203 6385)
	strs.SetString(_T(""), MAX_PATH+2); //pelix
#pragma warning(pop)
	char ss[MAX_PATH*2+2]; // + /0
	DWORD dd = GetCurrentDirectory(MAX_PATH, (LPWSTR)ss);
	if (dd == NULL)
	{
		strs.Format(_T("Ошибка в пути файла настроек %s, длина %i"), (LPWSTR)ss, dd);
		AfxMessageBox( (LPCTSTR)strs,0,0);
	}

	strsound = (LPCTSTR)ss;
	strs = L"\\ArmALSN.ini";
	strs  = strsound + strs;


	//m_ComboPort.GetWindowTextW(strsound); //
	// сохраняем данные в dat
	//m_configdat.m_strComPort1 = strsound;
//	DWORD Freq [] ={555,666,42200};
//	m_configdat.m_freq_rate = Freq[m_FreqRate];
	//
	
	//p20130910 m_gFreqRate = m_cFreqRate.GetCurSel();
	m_gFreqRate = m_FreqRate;

	// сохраняем данные в ini
	strsound.Format(L"%d",m_FreqRate);
	//AfxMessageBox(strsound);
	WritePrivateProfileStringW(L"Sound",L"FreqRate", strsound ,strs);

	///////////////////////////////////////////////////
	// Сохранить данные в файл dat
	if (UpdateData())
	{
		m_configdat.InSerialize();
	}
}

void CConfigSound::Serialize(CArchive& ar)
{
	m_configdat.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

bool CConfigSound::CanSerialize(void)
{
	return (0 == _access_s((const char*)m_gstrPathSet.GetBuffer(m_gstrPathSet.GetLength()),6)); //wchar_t
	
}


BOOL CConfigSound::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
		if (m_configdat.OutSerialize())
	{
		//m_FreqRate = m_configdat.m_freq_rate;
//p20130910		m_cFreqRate.SetCurSel(m_gFreqRate);
		m_FreqRate = m_gFreqRate;
		UpdateData(FALSE);
	}
	//DWORD Freq [] ={555,666,42200};
	//m_configdat.m_freq_rate = Freq[m_FreqRate];
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
