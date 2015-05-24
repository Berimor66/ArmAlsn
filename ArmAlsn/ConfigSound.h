#pragma once
#include "afxwin.h"


// диалоговое окно CConfigSound

class CConfigSound : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigSound)

public:
	CConfigSound(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CConfigSound();

// ƒанные диалогового окна
	enum { IDD = IDD_DIALOG_CONFIG_SOUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	bool CanSerialize(void);
	virtual void Serialize(CArchive& ar);
	afx_msg void OnCbnSelchangeFrecRate();
	afx_msg void OnBnClickedConsave();
	// выбор частоты дискретизации
	DWORD m_frec_rate;
	CConfigDat m_configdat;  // сохран€ем наши m_
	int m_FreqRate;
	virtual BOOL OnInitDialog();
//p20130910	CComboBox m_cFreqRate;
};
