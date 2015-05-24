#pragma once
#include "afxwin.h"
#include "ConfigDat.h"



// ���������� ���� CConfigGPS

class CConfigGPS : public CDialog
{
	DECLARE_DYNAMIC(CConfigGPS)

public:
	CConfigGPS(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CConfigGPS();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_CONFIG_GPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CConfigDat m_configdat;  // ��������� ���� m_
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
	// ������� ������������� OziExplorer
	BOOL m_OziExplorer_OnOff;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOzi();
	CButton m_ozi_offon;
	CButton m_map_onoff;
};
