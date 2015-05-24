#pragma once


// ���������� ���� �ViewAsim

class �ViewAsim : public CDialogEx
{
	DECLARE_DYNAMIC(�ViewAsim)

public:
	�ViewAsim(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~�ViewAsim();

// ������ ����������� ����
	enum { IDD = IDD_VIEW_ASIM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
	CSerialPort port01;
	void OpenComPort(int nPort, CString strComPort);
	// ����������� �������� ����� � ��� �����
	int ComPortStrtoInt(CString strComPort);
	CString sPort; // ��� ���� ������ (_T("\\\\.\\%s")
	// ���������� �� ���
	CString m_1_strPiket;
	CString m_strPiket1;
	CString m_strAsCen1;
	CString m_strAsCen2;
	CString m_strAsimetr;
	int     m_Asimetr;
	CFile	asimfile;
	void OnReadComPort1(void);
	void OnReadComPort1Thread(void);
	// ���������� �����
	double m_2_valueAsimetr;
	CConfigDat m_configdat;  // ������ � ������ 

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnCancel();
};
