// DataRowsetALS.h: объявление CDataRowsetALS

#pragma once

// создаваемый код 2 мая 2010 г., 23:05

class CDataRowsetALSAccessor
{
public:
	double m_column0;
	TCHAR m_column1[256];
	TCHAR m_column2[256];
	double m_column3;
	LONG m_column4;
	TCHAR m_column5[256];
	TCHAR m_column6[256];
	double m_column7;

	// Следующие создаваемые мастером члены данных содержат значения 
	// состояния для соответствующих полей в сопоставлении столбцов. 
	// Эти значение можно использовать для сохранения значений NULL, возвращаемых
	// базой данных, или для сохранения сведений об ошибках, когда компилятор 
	// возвращает ошибки. См. описание членов данных состояния полей в создаваемых 
	// мастером методах доступа в документации Visual C++ 
	// и сведения об использовании полей.
	// Примечание. Перед заданием или вставкой данных эти поля необходимо инициализировать!

	DBSTATUS m_dwcolumn0Status;
	DBSTATUS m_dwcolumn1Status;
	DBSTATUS m_dwcolumn2Status;
	DBSTATUS m_dwcolumn3Status;
	DBSTATUS m_dwcolumn4Status;
	DBSTATUS m_dwcolumn5Status;
	DBSTATUS m_dwcolumn6Status;
	DBSTATUS m_dwcolumn7Status;

	// Следующие создаваемые мастером члены данных содержат значения 
	// длины для соответствующих полей в сопоставлении столбцов. 
	// Примечание. Для столбцов с переменной длиной значений необходимо
	//      инициализировать эти поля перед заданием или вставкой данных!

	DBLENGTH m_dwcolumn0Length;
	DBLENGTH m_dwcolumn1Length;
	DBLENGTH m_dwcolumn2Length;
	DBLENGTH m_dwcolumn3Length;
	DBLENGTH m_dwcolumn4Length;
	DBLENGTH m_dwcolumn5Length;
	DBLENGTH m_dwcolumn6Length;
	DBLENGTH m_dwcolumn7Length;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
#error Проблема безопасности: строка подключения может содержать пароль 
// Следующая строка подключения может содержать незашифрованные пароли или 
// другую конфиденциальную информацию. Удалите #error после просмотра строки подключения 
// в целях безопасности. Возможно, 
// потребуется сохранить пароль в другом виде или использовать другую проверку подлинности.
		hr = _db.OpenFromInitializationString(L"Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=\x0410\x043b\x0441\x043d.accdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=6;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	BEGIN_COLUMN_MAP(CDataRowsetALSAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_column0, m_dwcolumn0Length, m_dwcolumn0Status)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_column1, m_dwcolumn1Length, m_dwcolumn1Status)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_column2, m_dwcolumn2Length, m_dwcolumn2Status)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_column3, m_dwcolumn3Length, m_dwcolumn3Status)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_column4, m_dwcolumn4Length, m_dwcolumn4Status)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_column5, m_dwcolumn5Length, m_dwcolumn5Status)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_column6, m_dwcolumn6Length, m_dwcolumn6Status)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_column7, m_dwcolumn7Length, m_dwcolumn7Status)
	END_COLUMN_MAP()
};

class CDataRowsetALS : public CTable<CAccessor<CDataRowsetALSAccessor> >
{
public:
	HRESULT OpenAll()
	{
		HRESULT hr;
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
		__if_exists(GetRowsetProperties)
		{
			CDBPropSet propset(DBPROPSET_ROWSET);
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
					propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
			GetRowsetProperties(&propset);
			return OpenRowset(&propset);
		}
		__if_not_exists(GetRowsetProperties)
		{
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
				{
					CDBPropSet propset(DBPROPSET_ROWSET);
					propset.AddProperty(DBPROP_IRowsetLocate, true);
					return OpenRowset(&propset);
				}
			}
		}
		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET *pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, L"ЖД Объекты", pPropSet);
#ifdef _DEBUG
		if(FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		CloseDataSource();
	}
};


