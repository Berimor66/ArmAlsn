// ConfigDat.cpp: файл реализации
//	 Сохранение / восстановление настроек программы

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigDat.h"
#include <io.h>
#include "Globals.h"

// CConfigDat
CString m_gstrPathDb=L"Алсн.accdb"; // Файл базы данных
CString m_gstrPathWp=L"OziExplorer\\Data"; // Путь к папке с путевыми точками
CString m_gstrPathOz=L"OziExplorer\\OziExp.exe"; // Путь к OziExplorer
int		m_gFreqRate = 0; //

CConfigDat::CConfigDat()
{
}

CConfigDat::~CConfigDat()
{
}


// функции-члены CConfigDat

void CConfigDat::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{	// код записи
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
	{	// кол чтения
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
	// сохраняем данные в dat
	BOOL bCanSave = FALSE;
	UINT nFlags = CFile::typeBinary | CFile::modeWrite;
	// Файл не существует - создаем
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
		// Файл с правами на чтение и запись
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
	// берем данные из dat
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
			//AfxMessageBox( _T("Ошибка 1 открытия файла данных .dat"));
			fe.ReportError();
		}
	}
	else AfxMessageBox( _T("Ошибка 2  файл данных .dat не найден"));

	return true;
}