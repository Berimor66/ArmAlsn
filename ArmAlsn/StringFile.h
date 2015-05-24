// StringFile.h: interface for the CStringFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGFILE_H__A6247296_4E48_11D2_BF32_0040333952B6__INCLUDED_)
#define AFX_STRINGFILE_H__A6247296_4E48_11D2_BF32_0040333952B6__INCLUDED_


//#define SFBUF_SIZE	4096

#define SFBUF_SIZE	2048


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringFile  
{
public:
	CStringFile(int nBufSize = SFBUF_SIZE);
	virtual ~CStringFile();
	BOOL Open(LPCTSTR szFile, CFileException *feError=NULL, int Unicode=NULL);
	void Close();
	void Reset(void);
	void GetErrorText(CString &szMsg);

	//DWORD GetNextLine(LPWSTR szLine,int iLineSize); //T -> W

	DWORD GetNextLine(LPSTR szLine,int iLineSize);

	DWORD GetNextLine(CString &szLine);
	
protected:
	int m_nBufferSize;
	CString m_szError;
	ULONGLONG	m_nMaxSize; //DWORD
	DWORD	m_dwRead;
	DWORD	m_dwLine;
	ULONGLONG	m_dwMasterIndex; //DWORD
	DWORD	m_dwIndex;
	int		m_nSectionCount;
	BYTE	*m_pBuffer;
	CFile	m_fFile;
};

#endif // !defined(AFX_STRINGFILE_H__A6247296_4E48_11D2_BF32_0040333952B6__INCLUDED_)
