#pragma once
#include "afxwin.h"
#include "ConfigDat.h"



// диалоговое окно CConfigGPS

class CConfigGPS : public CDialog
{
	DECLARE_DYNAMIC(CConfigGPS)

public:
	CConfigGPS(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CConfigGPS();

// ƒанные диалогового окна
	enum { IDD = IDD_DIALOG_CONFIG_GPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CConfigDat m_configdat;  // сохран€ем наши m_
//	CString m_pCombo;
	virtual BOOL OnInitDialog();

	CComboBox m_ComboPort;
	CComboBox m_2_ComboPort;
	afx_msg void OnBnClickedConsave();
	bool CanSerialize(void);
	virtual void Serialize(CArchive& ar);
	afx_msg void OnBnClickedButton1com();
	afx_msg void OnBnClickedButton2com();
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// признак использовани€ OziExplorer
	BOOL m_OziExplorer_OnOff;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOzi();
	CButton m_ozi_offon;
	CButton m_map_onoff;
};
