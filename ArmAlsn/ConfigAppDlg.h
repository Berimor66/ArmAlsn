#pragma once




// #include "MainFrm.h"
#include "stdafx.h"
#include "Resource.h"
#include "afxcmn.h"
#include "ConfigDirectX.h"
// #include "MainFrm.h"
// ���������� ���� CConfigAppDlg

class CConfigAppDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigAppDlg)

public:
	CConfigAppDlg(CWnd* pParent = NULL);   // ����������� �����������  = NULL - �.�. ������ ���������
	virtual ~CConfigAppDlg();

	virtual void OnFinalRelease();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

		
	CTabCtrl m_Tab_config_app; // �������� ������� ��������� 
	CDialog* m_pTabDialog; // ����������-��������� �� ������� ������


	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

private:
 	// ����������, ������������, ������������ �� �
 	// ������ ������ ������
 
 	//BOOL inUse;
 	//CMainFrame *pParent;

	 CRect l_Rect;

	
public:
	afx_msg void OnBnClickedCancel();


	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	// ���������� - ���� ������������ �������������
	CTreeCtrl m_treeDialogMessages;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveExit();
	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();

	// ���������� ���������������
//	CComboBox m_ComboDevice;

	afx_msg void OnBnClickedSave();


	 CConfigDirectX configdx ;
	 afx_msg void OnBnClickedNosave();
	 virtual BOOL PreTranslateMessage(MSG* pMsg);
};
