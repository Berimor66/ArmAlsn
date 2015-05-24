#pragma once
//p
#include "ConfigDat.h"
#include "bass.h"
#include "afxwin.h"
#include "SerialPort.h"

	void CALLBACK UpdateAsim(UINT uTimerID,	//  � ������������� �������.
								 UINT uMsg,		//  � �������������� ��������.
								 DWORD dwUser,	//  � 32-��������� ��������, ��������� ����������� ��� ������� ������� � ������� timeSetEvent.
							 	 DWORD dw1,		//  � �������������� ��������.
								 DWORD dw2);	//  � �������������� ��������.
	BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user);
	UINT ThreadFunc (LPVOID pParam);
	UINT ThreadFunc2 (LPVOID pParam);
	UINT ThreadFuncRead (LPVOID pParam);
	UINT ThreadFuncRead2 (LPVOID pParam);

// ���������� ���� ViewPut

class CViewPut : public CDialog
{
	DECLARE_DYNAMIC(CViewPut)

public:
	CViewPut(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CViewPut();

// ������ ����������� ����
	enum { IDD = IDD_VIEW_PUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV
	CSerialPort port01;
	CSerialPort port02;
//HANDLE hcomm01;
//HANDLE hcomm02;

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	virtual void Serialize(CArchive& ar);
	CConfigDat m_configdat;  // ������ � ������ 
	void OpenComPort(int nPort, CString strComPort);
	//�������������� ������
	UINT timer;
	// recording channel
	HRECORD chancap1;
//	afx_msg void OnEnChangeAschen1();
	CString m_strAsCen1;
	CString m_strAsCen2;
	CString m_strAsimetr;
	int     m_Asimetr;
	CString m_strPiket;
	// ���������� �� ���
	CString m_2_strPiket;
	CString sPort; // ��� ���� ������ (_T("\\\\.\\%s")
	CEdit m_chen1;
//	CStdioFile	asfile;
	CFile	asimfile;

	 // ��������� CBrush* ��� �������� ����� ����� ���� edit controls.
	CBrush* m_pEditBkBrush;

//	CSerialPort port;
	//CComPort	ComGps;
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedCancel();
	// ������
	CString m_str_Latitude;
	// �������
	CString m_str_Longitude;
	// �������� ������� �� ��� ������
	CString GetParametr(CString stroka, int np);
	// ��������� ��������� RMC �� GPS
	void OnGpsRmc(void);
	// ������������� ������
	double m_setpk;
	afx_msg void OnBnClickedPkok();
	// ���������� �� ����������
	int m_pkp;
	int m_ipiketkp;
	// ���������� �� ���������
	bool m_pkm;
	// ����������� �������� ����� � ��� �����
	int ComPortStrtoInt(CString strComPort);
	void OnReadComPort1(void);
	void OnReadComPort1Thread(void);
	void OnReadComPort2(void);
	void OnReadComPort2Thread(void);
	double TimeStrtoCount(CString strTime);
	double vTime1;
	double vTime2;
	double kmpk_tek;
	int m_iAnswer;
	afx_msg void OnBnClickedSchetm();
	afx_msg void OnBnClickedSchetp();
//	double primer;
//	double Kanal2;
	afx_msg void OnEnChangeKorect();
	CString m_strsetpk;
	// ���������������� ��������� �����
	VARIANT_BOOL OnInitOscilloscopeDisko(void);
	// �������� ���������� �� ����� �����
	HRESULT OnVoltageDisko(void);
	// ���������� ������� ������ �����
	double m_2_valueAsCen1;
	// ���������� ������� ������ �����
	double m_2_valueAsCen2;
	// ���������� �����
	double m_2_valueAsimetr;
	void OnCloseOscilloscopeDisko(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ���������� ���������� ������������� ������
	CEdit m_corect_pk;
	double OnPK_car(void);
	afx_msg void OnBnClickedAddPk();
	afx_msg void OnBnClickedIncPk();
	afx_msg void OnBnClickedAdd10m();
	afx_msg void OnBnClickedInc10m();
	CEdit m_2_Piket;
protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

public:
	CButton m_piketkp;
	CButton m_piketkm;
};

