#pragma once
#include "afxwin.h"
#include "ConfigDat.h"


// ���������� ���� CConfigDirectX

class CConfigDirectX : public CDialog
{
	DECLARE_DYNAMIC(CConfigDirectX)

public:
	CConfigDirectX(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CConfigDirectX();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_CONFIG_DIRECTX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// ���������� ���������������
	CComboBox m_ComboDevice;
	// ���������� ������
	CComboBox m_ComboCaptureDevice;
	DWORD m_DeviceCount;
	LPGUID m_pDeviceIDs[20]; //LP
	CConfigDat m_configdat;  // ��������� ���� m_

	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeSoundDeviceCombo();
	afx_msg void OnBnClickedConsave();
	bool CanSerialize(void);
	virtual void Serialize(CArchive& ar);
	CButton BConfigSave;

	afx_msg void OnBnClickedCancel();
	// ������� ������������� �����
	BOOL m_on_disko;
	afx_msg void OnBnClickedDisko();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};
	// ������������ ��������� ���������������
	int CALLBACK DSoundEnumCallback(GUID* pGUID, TCHAR* strDesc, 
										TCHAR* strDrvName, CConfigDirectX *pDlg); //CConfigDirectX CConfigAppDlg

	int CALLBACK DSoundCaptureEnumCallback(GUID* pGUID, TCHAR* strDesc,
										TCHAR* strDrvName, CConfigDirectX *pDlg);
