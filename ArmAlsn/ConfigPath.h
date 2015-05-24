#pragma once


// ���������� ���� CConfigPath

class CConfigPath : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigPath)

public:
	CConfigPath(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CConfigPath();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG_CONFIG_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFileDb(); //
	afx_msg void OnBnClickedButtonFolderWp(); //
	afx_msg void OnBnClickedButtonFileOz(); //

	CString m_strPathDb; // ���� ���� ������
	CString m_strPathWp; // ���� � ����� � �������� �������
	CString m_strPathOz; // ���� � OziExplorer

//	virtual void Serialize(CArchive& ar);
	CConfigDat m_configdat;  // ��������� ���� m_
	afx_msg void OnBnClickedConsave();
	virtual BOOL OnInitDialog();
};
