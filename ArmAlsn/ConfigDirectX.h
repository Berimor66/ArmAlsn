#pragma once
#include "afxwin.h"
#include "ConfigDat.h"


// диалоговое окно CConfigDirectX

class CConfigDirectX : public CDialog
{
	DECLARE_DYNAMIC(CConfigDirectX)

public:
	CConfigDirectX(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CConfigDirectX();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CONFIG_DIRECTX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// Устройство воспроизведения
	CComboBox m_ComboDevice;
	// Устройство записи
	CComboBox m_ComboCaptureDevice;
	DWORD m_DeviceCount;
	LPGUID m_pDeviceIDs[20]; //LP
	CConfigDat m_configdat;  // сохраняем наши m_

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeSoundDeviceCombo();
	afx_msg void OnBnClickedConsave();
	bool CanSerialize(void);
	virtual void Serialize(CArchive& ar);
	CButton BConfigSave;

	afx_msg void OnBnClickedCancel();
	// признак использования Диско
	BOOL m_on_disko;
	afx_msg void OnBnClickedDisko();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};
	// Перечисление устройств воспроизведения
	int CALLBACK DSoundEnumCallback(GUID* pGUID, TCHAR* strDesc, 
										TCHAR* strDrvName, CConfigDirectX *pDlg); //CConfigDirectX CConfigAppDlg

	int CALLBACK DSoundCaptureEnumCallback(GUID* pGUID, TCHAR* strDesc,
										TCHAR* strDrvName, CConfigDirectX *pDlg);
