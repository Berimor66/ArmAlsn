#pragma once
//p
#include "ConfigDat.h"
#include "bass.h"
#include "afxwin.h"
#include "SerialPort.h"

	void CALLBACK UpdateAsim(UINT uTimerID,	//  — идентификатор события.
								 UINT uMsg,		//  — неиспользуемый параметр.
								 DWORD dwUser,	//  — 32-разрядное значение, указанное приложением при запросе события в функции timeSetEvent.
							 	 DWORD dw1,		//  — неиспользуемый параметр.
								 DWORD dw2);	//  — неиспользуемый параметр.
	BOOL CALLBACK DuffRecording(HRECORD handle, const void *buffer, DWORD length, void *user);
	UINT ThreadFunc (LPVOID pParam);
	UINT ThreadFunc2 (LPVOID pParam);
	UINT ThreadFuncRead (LPVOID pParam);
	UINT ThreadFuncRead2 (LPVOID pParam);

// диалоговое окно ViewPut

class CViewPut : public CDialog
{
	DECLARE_DYNAMIC(CViewPut)

public:
	CViewPut(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CViewPut();

// Данные диалогового окна
	enum { IDD = IDD_VIEW_PUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	CSerialPort port01;
	CSerialPort port02;
//HANDLE hcomm01;
//HANDLE hcomm02;

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	virtual void Serialize(CArchive& ar);
	CConfigDat m_configdat;  // доступ к данным 
	void OpenComPort(int nPort, CString strComPort);
	//мультимедийный таймер
	UINT timer;
	// recording channel
	HRECORD chancap1;
//	afx_msg void OnEnChangeAschen1();
	CString m_strAsCen1;
	CString m_strAsCen2;
	CString m_strAsimetr;
	int     m_Asimetr;
	CString m_strPiket;
	// Километраж от ЖРС
	CString m_2_strPiket;
	CString sPort; // Для имен портов (_T("\\\\.\\%s")
	CEdit m_chen1;
//	CStdioFile	asfile;
	CFile	asimfile;

	 // Добавляем CBrush* для хранения новой кисти фона edit controls.
	CBrush* m_pEditBkBrush;

//	CSerialPort port;
	//CComPort	ComGps;
protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedCancel();
	// Широта
	CString m_str_Latitude;
	// Долгота
	CString m_str_Longitude;
	// Получить праметр по его номеру
	CString GetParametr(CString stroka, int np);
	// Обработка сообщения RMC от GPS
	void OnGpsRmc(void);
	// предустановка пикета
	double m_setpk;
	afx_msg void OnBnClickedPkok();
	// километраж на увеличение
	int m_pkp;
	int m_ipiketkp;
	// километраж на вычитание
	bool m_pkm;
	// Преобразует название порта в его номер
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
	// Инициализировать интерфейс Диско
	VARIANT_BOOL OnInitOscilloscopeDisko(void);
	// Измерить напряжение на входе Диско
	HRESULT OnVoltageDisko(void);
	// Напряжение первого канала Диско
	double m_2_valueAsCen1;
	// Напряжение второго канала Диско
	double m_2_valueAsCen2;
	// Асимметрия Диско
	double m_2_valueAsimetr;
	void OnCloseOscilloscopeDisko(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// управление переменной корректировки пикета
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

