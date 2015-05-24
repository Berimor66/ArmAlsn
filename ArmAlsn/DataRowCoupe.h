// DataRowCoupe.h: объявление CDataRowsetCoupe

#pragma once

// создаваемый код 26 мая 2010 г., 7:41

class CDataRowsetCoupeAccessor
{
public:
	LONG m_Serialnumber;
	LONG m_CoupeID;
	TCHAR m_Coupe[51];
	TCHAR m_CoupeEND[51];
	TCHAR m_CoupeName[51];
	TCHAR m_LandName[51];
	TCHAR m_ItineraryName[51];


	// Следующие создаваемые мастером члены данных содержат значения 
	// состояния для соответствующих полей в сопоставлении столбцов. 
	// Эти значение можно использовать для сохранения значений NULL, возвращаемых
	// базой данных, или для сохранения сведений об ошибках, когда компилятор 
	// возвращает ошибки. См. описание членов данных состояния полей в создаваемых 
	// мастером методах доступа в документации Visual C++ 
	// и сведения об использовании полей.
	// Примечание. Перед заданием или вставкой данных эти поля необходимо инициализировать!

	DBSTATUS m_dwCoupeStatus;
	DBSTATUS m_dwCoupeENDStatus;
	DBSTATUS m_dwCoupeIDStatus;
	DBSTATUS m_dwCoupeNameStatus;
	DBSTATUS m_dwLandNameStatus;
	DBSTATUS m_dwSerialnumberStatus;
	DBSTATUS m_dwItineraryNameStatus;

	// Следующие создаваемые мастером члены данных содержат значения 
	// длины для соответствующих полей в сопоставлении столбцов. 
	// Примечание. Для столбцов с переменной длиной значений необходимо
	//      инициализировать эти поля перед заданием или вставкой данных!

	DBLENGTH m_dwCoupeLength;
	DBLENGTH m_dwCoupeENDLength;
	DBLENGTH m_dwCoupeIDLength;
	DBLENGTH m_dwCoupeNameLength;
	DBLENGTH m_dwLandNameLength;
	DBLENGTH m_dwSerialnumberLength;
	DBLENGTH m_dwItineraryNameLength;


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
		if
			(FAILED(hr))
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

	DEFINE_COMMAND_EX(CDataRowsetCoupeAccessor, L" \
	SELECT \
		`Serial number`, \
		CoupeID, \
		Coupe, \
		CoupeEND, \
		CoupeName, \
		LandName, \
		ItineraryName \
		FROM \x041f\x0435\x0440\x0435\x0433\x043e\x043d\x044b")


	// Для устранения некоторых проблем с поставщиками следующий код может 
	// привязывать столбцы в порядке, отличном от сообщаемого поставщиком

	BEGIN_COLUMN_MAP(CDataRowsetCoupeAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Serialnumber, m_dwSerialnumberLength, m_dwSerialnumberStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Coupe, m_dwCoupeLength, m_dwCoupeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_CoupeEND, m_dwCoupeENDLength, m_dwCoupeENDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_CoupeID, m_dwCoupeIDLength, m_dwCoupeIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_CoupeName, m_dwCoupeNameLength, m_dwCoupeNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_LandName, m_dwLandNameLength, m_dwLandNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_ItineraryName, m_dwItineraryNameLength, m_dwItineraryNameStatus)
	END_COLUMN_MAP()
};

class CDataRowsetCoupe : public CCommand<CAccessor<CDataRowsetCoupeAccessor> >
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
		HRESULT hr = Open(m_session, NULL, pPropSet);
#ifdef _DEBUG
		if(FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		ReleaseCommand();
		CloseDataSource();
	}
};


