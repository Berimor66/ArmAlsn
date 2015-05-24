// ConfigDat.cpp: ���� ����������
//	 ���������� / �������������� �������� ���������

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigDat.h"
#include <io.h>
#include "Globals.h"

// CConfigDat
CString m_gstrPathDb=L"����.accdb"; // ���� ���� ������
CString m_gstrPathWp=L"OziExplorer\\Data"; // ���� � ����� � �������� �������
CString m_gstrPathOz=L"OziExplorer\\OziExp.exe"; // ���� � OziExplorer
int		m_gFreqRate = 0; //

CConfigDat::CConfigDat()
{
}

CConfigDat::~CConfigDat()
{
}


// �������-����� CConfigDat

void CConfigDat::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{	// ��� ������
		ar << m_curDirectXSound1;
		ar << m_strDirectXSound;
		ar << m_curDirectXCapture1;
		ar << m_strDirectXCapture;
		ar << m_strComPort1;
		ar << m_2_strComPort1;
		ar << m_disko_onof;
//		ar << m_freq_rate;
		ar << m_gFreqRate;
		ar << m_gstrPathDb;
		ar << m_gstrPathWp;
		ar << m_gstrPathOz;
		ar << m_gOziExplorer_OnOff;


	}
	else
	{	// ��� ������
		ar >> m_curDirectXSound1;
		ar >> m_strDirectXSound;
		ar >> m_curDirectXCapture1;
		ar >> m_strDirectXCapture;
		ar >> m_strComPort1;
		ar >> m_2_strComPort1;
		ar >> m_disko_onof;
//		ar >> m_freq_rate;
		ar >> m_gFreqRate;
		ar >> m_gstrPathDb;
		ar >> m_gstrPathWp;
		ar >> m_gstrPathOz;
		ar >> m_gOziExplorer_OnOff;

	}
}

bool CConfigDat::CanSerialize(void)
{
	return (0 == _access_s((char*)m_gstrPathSet.GetBuffer(m_gstrPathSet.GetLength()),6)); // (char*) DATA_FILE_DAT
}

bool CConfigDat::InSerialize()
{
	// ��������� ������ � dat
	BOOL bCanSave = FALSE;
	UINT nFlags = CFile::typeBinary | CFile::modeWrite;
	// ���� �� ���������� - �������
	if (_access_s((char*)m_gstrPathSet.GetBuffer(m_gstrPathSet.GetLength()),0)) // const  ,,  (char*)DATA_FILE_DAT
	{
		nFlags |= CFile::modeCreate;
		bCanSave = TRUE;
	}
	else
	{
		bCanSave = CanSerialize();
	}
	if (bCanSave)
	{
		CFile file;
		CFileException fe;
		// ���� � ������� �� ������ � ������
		if (file.Open(m_gstrPathSet, nFlags, &fe)) // DATA_FILE_DAT
		{
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
		}
			else fe.ReportError();
	}
	return 0;
}

bool CConfigDat::OutSerialize()
{
	// ����� ������ �� dat
	if (!CanSerialize())
	{
		CFile file;
		CFileException fe;
	
		if (file.Open(m_gstrPathSet, CFile::typeBinary | CFile::modeRead, &fe))
		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
			//AfxMessageBox(_T("DATA_FILE_DAT"));
			
		}
		else 
		{
			//AfxMessageBox( _T("������ 1 �������� ����� ������ .dat"));
			fe.ReportError();
		}
	}
	else AfxMessageBox( _T("������ 2  ���� ������ .dat �� ������"));

	return true;
}