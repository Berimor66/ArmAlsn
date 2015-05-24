#pragma once

// конечный объект команды CConfigDat

class CConfigDat : public CObject
{
public:
	CConfigDat();
	virtual ~CConfigDat();
	CString m_strDirectXSound;
	CString	m_strDirectXCapture;
	int		m_curDirectXSound1;
	int		m_curDirectXCapture1;
	CString	m_strComPort1;
	CString	m_2_strComPort1;
	BOOL	m_disko_onof;
	// частота дескретизации
//	DWORD	m_freq_rate;
	
	bool CanSerialize(void);
	bool InSerialize(void);
	bool OutSerialize(void);
	virtual void Serialize(CArchive& ar);
};


		