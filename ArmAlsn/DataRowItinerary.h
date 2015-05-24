// DataRowItinerary.h: объявление CDataItineraryRowset

#pragma once

// создаваемый код 25 мая 2010 г., 22:45

class CDataItineraryRowsetAccessor
{
public:
	TCHAR m_ItineraryEND[51];
	TCHAR m_ItineraryHome[51];
	TCHAR m_ItineraryID[26];
	TCHAR m_ItineraryName[256];
	VARIANT_BOOL m_Negative;
	LONG m_Serialnumber;

	// Следующие создаваемые мастером члены данных содержат значения 
	// состояния для соответствующих полей в сопоставлении столбцов. 
	// Эти значение можно использовать для сохранения значений NULL, возвращаемых
	// базой данных, или для сохранения сведений об ошибках, когда компилятор 
	// возвращает ошибки. См. описание членов данных состояния полей в создаваемых 
	// мастером методах доступа в документации Visual C++ 
	// и сведения об использовании полей.
	// Примечание. Перед заданием или вставкой данных эти поля необходимо инициализировать!

	DBSTATUS m_dwItineraryENDStatus;
	DBSTATUS m_dwItineraryHomeStatus;
	DBSTATUS m_dwItineraryIDStatus;
	DBSTATUS m_dwItineraryNameStatus;
	DBSTATUS m_dwNegativeStatus;
	DBSTATUS m_dwSerialnumberStatus;

	// Следующие создаваемые мастером члены данных содержат значения 
	// длины для соответствующих полей в сопоставлении столбцов. 
	// Примечание. Для столбцов с переменной длиной значений необходимо
	//      инициализировать эти поля перед заданием или вставкой данных!

	DBLENGTH m_dwItineraryENDLength;
	DBLENGTH m_dwItineraryHomeLength;
	DBLENGTH m_dwItineraryIDLength;
	DBLENGTH m_dwItineraryNameLength;
	DBLENGTH m_dwNegativeLength;
	DBLENGTH m_dwSerialnumberLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		ASSERT (pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT (pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT (pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT (pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE));
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error Проблема безопасности: строка подключения может содержать пароль 
// Следующая строка подключения может содержать незашифрованные пароли или 
// другую конфиденциальную информацию. Удалите #error после просмотра строки подключения 
// в целях безопасности. Возможно, 
// потребуется сохранить пароль в другом виде или использовать другую проверку подлинности.
		//hr = _db.OpenFromInitializationString(L"Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=C:\\SAP_SAN\\ArmAlsn\\Alsn.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False");
		hr = _db.OpenFromInitializationString(_T(DATA_STRING_DB_ACC)); //DATA_STRING_DB_MDB
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

	BEGIN_COLUMN_MAP(CDataItineraryRowsetAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_ItineraryEND, m_dwItineraryENDLength, m_dwItineraryENDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_ItineraryHome, m_dwItineraryHomeLength, m_dwItineraryHomeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_ItineraryID, m_dwItineraryIDLength, m_dwItineraryIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_ItineraryName, m_dwItineraryNameLength, m_dwItineraryNameStatus)
		_COLUMN_ENTRY_CODE(4, DBTYPE_BOOL, _SIZE_TYPE(m_Negative), 0, 0, offsetbuf(m_Negative), offsetbuf(m_dwNegativeLength), offsetbuf(m_dwNegativeStatus))
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Serialnumber, m_dwSerialnumberLength, m_dwSerialnumberStatus)
	END_COLUMN_MAP()
};

class CDataItineraryRowset : public CTable<CAccessor<CDataItineraryRowsetAccessor> >
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
//		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET *pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, L"Маршруты", pPropSet);
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


