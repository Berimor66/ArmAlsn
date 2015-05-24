#pragma once


// диалоговое окно СViewAsim

class СViewAsim : public CDialogEx
{
	DECLARE_DYNAMIC(СViewAsim)

public:
	СViewAsim(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~СViewAsim();

// Данные диалогового окна
	enum { IDD = IDD_VIEW_ASIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	CSerialPort port01;
	void OpenComPort(int nPort, CString strComPort);
	// Преобразует название порта в его номер
	int ComPortStrtoInt(CString strComPort);
	CString sPort; // Для имен портов (_T("\\\\.\\%s")
	// Километраж от ЖРС
	CString m_1_strPiket;
	CString m_strPiket1;
	CString m_strAsCen1;
	CString m_strAsCen2;
	CString m_strAsimetr;
	int     m_Asimetr;
	CFile	asimfile;
	void OnReadComPort1(void);
	void OnReadComPort1Thread(void);
	// Асимметрия Диско
	double m_2_valueAsimetr;
	CConfigDat m_configdat;  // доступ к данным 

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnCancel();
};
