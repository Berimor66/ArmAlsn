// ConfigDirectX.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigDirectX.h"
#include "ArmALSNDoc.h"
#include <io.h>
#include "ConfigDat.h"


// Имя файла настроек
//#define DATA_FILE_DAT _T("Alsn.dat")

// диалоговое окно CConfigDirectX

IMPLEMENT_DYNAMIC(CConfigDirectX, CDialog)

CConfigDirectX::CConfigDirectX(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDirectX::IDD, pParent)
	, m_on_disko(FALSE)
{

}

CConfigDirectX::~CConfigDirectX()
{
}

void CConfigDirectX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOUND_DEVICE_COMBO, m_ComboDevice); // 
	DDX_Control(pDX, IDC_CAPTURE_DEVICE_COMBO, m_ComboCaptureDevice);
	DDX_Control(pDX, IDCONSAVE, BConfigSave);
	DDX_Check(pDX, IDC_DISKO, m_on_disko);
}


BEGIN_MESSAGE_MAP(CConfigDirectX, CDialog)
	ON_CBN_SELCHANGE(IDC_CAPTURE_DEVICE_COMBO, &CConfigDirectX::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_SOUND_DEVICE_COMBO, &CConfigDirectX::OnCbnSelchangeSoundDeviceCombo)
	ON_BN_CLICKED(IDCONSAVE, &CConfigDirectX::OnBnClickedConsave)
//	ON_BN_CLICKED(IDC_CONFSAVE, &CConfigDirectX::OnBnClickedConfsave)
//	ON_BN_CLICKED(IDCANCEL, &CConfigDirectX::OnBnClickedCancel)
ON_BN_CLICKED(IDC_DISKO, &CConfigDirectX::OnBnClickedDisko)
END_MESSAGE_MAP()


// обработчики сообщений CConfigDirectX
// Перечисление устройств воспроизведения
int CALLBACK DSoundEnumCallback(GUID* pGUID, TCHAR* strDesc, TCHAR* strDrvName, CConfigDirectX *pDlg) //  CConfigAppDlg
{
	UNREFERENCED_PARAMETER(strDrvName);
	pDlg->m_DeviceCount = 0;
    pDlg->m_ComboDevice.InsertString(-1,strDesc);
	pDlg->m_pDeviceIDs[pDlg->m_DeviceCount++] = pGUID;


return pDlg->m_DeviceCount<20;

}

int CALLBACK DSoundCaptureEnumCallback(GUID* pGUID, TCHAR* strDesc, TCHAR* strDrvName, CConfigDirectX *pDlg)
{
	UNREFERENCED_PARAMETER(strDrvName);
	pDlg->m_DeviceCount = 0;
    pDlg->m_ComboCaptureDevice.InsertString(-1,strDesc);
	pDlg->m_pDeviceIDs[pDlg->m_DeviceCount++] = pGUID;


return pDlg->m_DeviceCount<20;
	
}

BOOL CConfigDirectX::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
			
	m_ComboDevice.SetExtendedUI(1);
	m_ComboCaptureDevice.SetExtendedUI(1);

	///////////////////////////////////////////////////
// берем данные из dat
m_configdat.OutSerialize();
//
//////////////////////////////////////////////////

	m_on_disko = m_configdat.m_disko_onof;

	///////////////////////////

		if (	
			(FAILED( DirectSoundEnumerate( (LPDSENUMCALLBACKW)DSoundEnumCallback, 
											(VOID*)this)))
        	)
        AfxMessageBox( _T("Ошибка DirectSoundEnumerate"),0,0);

/////////////////////////////////////////////

	
		//m_ComboDevice.SetCurSel(0);
		//m_ComboDevice.GetWindowTextW(strsound);
		//m_ComboDevice.GetLBText(2,strsound);
		//AfxMessageBox(strsound);
		
		//strsound = m_configdat.m_strDirectXSound;
		//AfxMessageBox(m_configdat.m_strDirectXSound);

		CString strsound;
		for (int i=0; i<m_ComboDevice.GetCount();++i)
		{


			m_ComboDevice.GetLBText(i,strsound);


			if (m_configdat.m_strDirectXSound == strsound)
			{				
				m_ComboDevice.SetCurSel(i);
				//m_configdat.m_curDirectXSound1 = i;
				break;
			}
			m_ComboDevice.SetCurSel(0);
		}




		if	
		( 
		FAILED( DirectSoundCaptureEnumerate( (LPDSENUMCALLBACKW)DSoundCaptureEnumCallback,
                   (VOID*)this ) ) 
		
		)

        AfxMessageBox( _T("Ошибка DirectSoundCaptureEnumerate"),0,0);
			m_ComboCaptureDevice.SetCurSel(0);
	
		for (int i=0; i<m_ComboCaptureDevice.GetCount();++i)
		{
			
			m_ComboCaptureDevice.GetLBText(i,strsound);
	

			if (m_configdat.m_strDirectXCapture == strsound)
			{				
				m_ComboCaptureDevice.SetCurSel(i);
				//m_configdat.m_curDirectXCapture1 = i;
				break;
			}
			m_ComboCaptureDevice.SetCurSel(0);
		}

UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CConfigDirectX::OnCbnSelchangeCombo2()
{
	// TODO: добавьте свой код обработчика уведомлений
}

void CConfigDirectX::OnCbnSelchangeSoundDeviceCombo()
{
	// TODO: добавьте свой код обработчика уведомлений
}


// Нажимаем применить
void CConfigDirectX::OnBnClickedConsave()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(1);  // Из элементов управления в компонентную переменную
	//m_ComboDevice.UpdateData(1);
	
	CString strsound;
	CString strs;
	
	//strs.SetLength(270);
	#pragma warning(push)
    #pragma warning(disable:6385 6203)  // Переполнение буфера """" вне стека при вызове
	strs.SetString(_T(""), MAX_PATH+2);  // Set так работает
	#pragma warning(pop)
	//strs.SetLength(270);
	//strs.ReleaseBufferSetLength(MAX_PATH+2);

	//pelix
	wchar_t ss[MAX_PATH*sizeof(wchar_t)+sizeof(wchar_t)]; // + /0
	DWORD_PTR dd = GetCurrentDirectory(MAX_PATH, (LPWSTR)ss);
	if (dd == NULL)
	{
		strs.Format(_T("Ошибка пути  ини файла %s, длина %i"), (LPWSTR)ss, dd);
		AfxMessageBox( (LPCTSTR)strs,0,0);
	}
	
	strsound = (LPCTSTR)ss;
	strs = L"\\ArmALSN.ini";
	strs  = strsound + strs;
	 

	m_ComboDevice.GetWindowTextW(strsound); //
	// сохраняем данные в ini
	WritePrivateProfileStringW(L"Sound",L"Play", strsound ,strs);
	// сохраняем данные в dat
	m_configdat.m_curDirectXSound1 = m_ComboDevice.GetCurSel();
	m_configdat.m_strDirectXSound = strsound;
	m_configdat.m_disko_onof = m_on_disko;

	m_ComboCaptureDevice.GetWindowTextW(strsound);
	// сохраняем данные в ini
	WritePrivateProfileStringW(L"Sound",L"Capture",	strsound , strs);

	// сохраняем данные в dat
	m_configdat.m_curDirectXCapture1 = m_ComboCaptureDevice.GetCurSel();
	m_configdat.m_strDirectXCapture = strsound;
///////////////////////////////////////////////////
	// Сохранить данные в файл dat
	if (UpdateData())
	{
		m_configdat.InSerialize();
	}
///////////////////////////////////////////////

	

	// m_ComboDevice.GetWindowTextW(strsound);
//	CArmALSNDoc* ms;
//	ms new CArmALSNDoc;
	//ms->m_name_sound = strsound;
//	m_ComboDevice.GetWindowTextW(ms->m_name_sound);
//	m_ComboCaptureDevice.GetWindowTextW(ms->m_name_capture);
		

//	CString strsound;
//	CString str;
//	char s[100];
//	
//	int n;
//	strsound = _T("Инициализация");
//	n = m_ComboDevice.GetCurSel();
//	int res = 0;

	//CArmALSNDoc::OnSaveNameSound(strsound);

	//m_ComboDevice.GetWindowTextW(CArmALSNDoc::m_name_sound);
	//	m_ComboDevice.GetLBText(1,strsound);
	//CArmALSNDoc- ms.m_name_sound = strsound;
	//str.Format(_T("Выбран  %s с индексом %i"), strsound, n);	
	//AfxMessageBox( ms->m_name_capture,0,0);

}

bool CConfigDirectX::CanSerialize(void)
{
	return (0 == _access_s((char*)m_gstrPathSet.GetBuffer(m_gstrPathSet.GetLength()),6)); // const 
}

void CConfigDirectX::Serialize(CArchive& ar)
{
	m_configdat.Serialize(ar);
	if (ar.IsStoring())
	{	// код записи
	}
	else
	{	// код чтения
	}
}

/*
void CConfigDirectX::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений

	//Очистить списки с конца, стоб не изменялись индексы
	for (int i=m_ComboDevice.GetCount(); i>=0;i--)
		{
			m_ComboDevice.DeleteString(i);
			//m_ComboCaptureDevice.DeleteString(i);
		}
	for (int i=m_ComboCaptureDevice.GetCount(); i>=0;i--)
		{
			//m_ComboDevice.DeleteString(i);
			m_ComboCaptureDevice.DeleteString(i);
		}

	
	OnInitDialog();
	//OnCancel();
}
*/
void CConfigDirectX::OnBnClickedDisko()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);	
}

BOOL CConfigDirectX::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	BOOL bHandledMsg = FALSE;

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		//OnBnClickedSaveExit();
		// Послать сообщение актвной Вкладке елемента Страницы свойств
		//HWND phWnd;
		//GetDlgItem(IDD_DIALOG_CONFIG, &phWnd);

		//::SendDlgItemMessageW((HWND)GetParent(), IDC_SAVE_EXIT, WM_LBUTTONDOWN,1,1); // phWnd
		//::SendDlgItemMessageW((HWND)GetParent(), IDC_SAVE_EXIT, WM_LBUTTONUP,1,1);
		//OnBnClickedConsave();
		
		pMsg->wParam = VK_TAB;
		bHandledMsg =  TRUE;

		//AfxMessageBox(L"Нажали ВВОД");
	}

	return ( bHandledMsg ? bHandledMsg
			: CDialog::PreTranslateMessage(pMsg));
}

