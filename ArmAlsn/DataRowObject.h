// DataRowObject.h: объявление CDataObjectRowset

#pragma once

// создаваемый код 30 мая 2010 г., 23:16

class CDataObjectRowsetAccessor
{
public:
	TCHAR m_ChName[51];
	VARIANT_BOOL m_Coupe;
	TCHAR m_CoupeName[51];
	TCHAR m_ItineraryName[51];
	TCHAR m_LandName[51];
	LONG m_Latitude;
	LONG m_Longitude;
	TCHAR m_ObgectID[51];
	TCHAR m_ObgectName[51];
	double m_Pk;
	LONG m_Serialnumber;
	VARIANT_BOOL m_Type;

	// Следующие создаваемые мастером члены данных содержат значения 
	// состояния для соответствующих полей в сопоставлении столбцов. 
	// Эти значение можно использовать для сохранения значений NULL, возвращаемых
	// базой данных, или для сохранения сведений об ошибках, когда компилятор 
	// возвращает ошибки. См. описание членов данных состояния полей в создаваемых 
	// мастером методах доступа в документации Visual C++ 
	// и сведения об использовании полей.
	// Примечание. Перед заданием или вставкой данных эти поля необходимо инициализировать!

	DBSTATUS m_dwChNameStatus;
	DBSTATUS m_dwCoupeStatus;
	DBSTATUS m_dwCoupeNameStatus;
	DBSTATUS m_dwItineraryNameStatus;
	DBSTATUS m_dwLandNameStatus;
	DBSTATUS m_dwLatitudeStatus;
	DBSTATUS m_dwLongitudeStatus;
	DBSTATUS m_dwObgectIDStatus;
	DBSTATUS m_dwObgectNameStatus;
	DBSTATUS m_dwPkStatus;
	DBSTATUS m_dwSerialnumberStatus;
	DBSTATUS m_dwTypeStatus;

	// Следующие создаваемые мастером члены данных содержат значения 
	// длины для соответствующих полей в сопоставлении столбцов. 
	// Примечание. Для столбцов с переменной длиной значений необходимо
	//      инициализировать эти поля перед заданием или вставкой данных!

	DBLENGTH m_dwChNameLength;
	DBLENGTH m_dwCoupeLength;
	DBLENGTH m_dwCoupeNameLength;
	DBLENGTH m_dwItineraryNameLength;
	DBLENGTH m_dwLandNameLength;
	DBLENGTH m_dwLatitudeLength;
	DBLENGTH m_dwLongitudeLength;
	DBLENGTH m_dwObgectIDLength;
	DBLENGTH m_dwObgectNameLength;
	DBLENGTH m_dwPkLength;
	DBLENGTH m_dwSerialnumberLength;
	DBLENGTH m_dwTypeLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		ASSERT(pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT(pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT(pPropSet->AddProperty(DBPROP_IRowsetChange, true, DBPROPOPTIONS_OPTIONAL));
		ASSERT(pPropSet->AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE));
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
		//hr = _db.OpenFromInitializationString(L"Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=c:\\SAP_SAN\\ArmAlsn\\Alsn.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=4;Jet OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False");
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

	DEFINE_COMMAND_EX(CDataObjectRowsetAccessor, L" \
	SELECT \
		`Serial number`, \
		ObgectID, \
		Pk, \
		Latitude, \
		Longitude, \
		ObgectName, \
		Coupe, \
		Type, \
		CoupeName, \
		LandName, \
		ItineraryName, \
		ChName \
		FROM \x041e\x0431\x044a\x0435\x043a\x0442\x044b")
		
	// Для устранения некоторых проблем с поставщиками следующий код может 
	// привязывать столбцы в порядке, отличном от сообщаемого поставщиком

	BEGIN_COLUMN_MAP(CDataObjectRowsetAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_Serialnumber, m_dwSerialnumberLength, m_dwSerialnumberStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_ObgectID, m_dwObgectIDLength, m_dwObgectIDStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_Pk, m_dwPkLength, m_dwPkStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_Latitude, m_dwLatitudeLength, m_dwLatitudeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_Longitude, m_dwLongitudeLength, m_dwLongitudeStatus)
		COLUMN_ENTRY_LENGTH_STATUS(6, m_ObgectName, m_dwObgectNameLength, m_dwObgectNameStatus)
		_COLUMN_ENTRY_CODE(7, DBTYPE_BOOL, _SIZE_TYPE(m_Coupe), 0, 0, offsetbuf(m_Coupe), offsetbuf(m_dwCoupeLength), offsetbuf(m_dwCoupeStatus))
		_COLUMN_ENTRY_CODE(8, DBTYPE_BOOL, _SIZE_TYPE(m_Type), 0, 0, offsetbuf(m_Type), offsetbuf(m_dwTypeLength), offsetbuf(m_dwTypeStatus))
		COLUMN_ENTRY_LENGTH_STATUS(9, m_CoupeName, m_dwCoupeNameLength, m_dwCoupeNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(10, m_LandName, m_dwLandNameLength, m_dwLandNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(11, m_ItineraryName, m_dwItineraryNameLength, m_dwItineraryNameStatus)
		COLUMN_ENTRY_LENGTH_STATUS(12, m_ChName, m_dwChNameLength, m_dwChNameStatus)
	END_COLUMN_MAP()
};

class CDataObjectRowset : public CCommand<CAccessor<CDataObjectRowsetAccessor> >
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


