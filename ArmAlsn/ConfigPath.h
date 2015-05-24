#pragma once


// диалоговое окно CConfigPath

class CConfigPath : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigPath)

public:
	CConfigPath(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CConfigPath();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG_CONFIG_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFileDb(); //
	afx_msg void OnBnClickedButtonFolderWp(); //
	afx_msg void OnBnClickedButtonFileOz(); //

	CString m_strPathDb; // Файл базы данных
	CString m_strPathWp; // Путь к папке с путевыми точками
	CString m_strPathOz; // Путь к OziExplorer

//	virtual void Serialize(CArchive& ar);
	CConfigDat m_configdat;  // сохраняем наши m_
	afx_msg void OnBnClickedConsave();
	virtual BOOL OnInitDialog();
};
