// DataRowset.h: объявление CDataRowset

#pragma once

// создаваемый код 2 мая 2010 г., 22:27

class CDataRowsetAccessor
{
public:
	// ISequentialStream* m_column0;
	TCHAR m_column0[8000];
	DATE m_column1;
	DATE m_column2;
	LONG m_column3;
	LONG m_column4;
	TCHAR m_column5[51];
	LONG m_column6;
	TCHAR m_column7[51];
	TCHAR m_column8[51];
	// ISequentialStream* m_column9;
	TCHAR m_column9[8000];
	LONG m_column10;
	// ISequentialStream* m_column11;
	TCHAR m_column11[8000];
	TCHAR m_column12[51];
	CURRENCY m_column13;
	TCHAR m_column14[51];
	TCHAR m_column15[51];
	CURRENCY m_column16;
	LONG m_column17;

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
	DBSTATUS m_dwcolumn8Status;
	DBSTATUS m_dwcolumn9Status;
	DBSTATUS m_dwcolumn10Status;
	DBSTATUS m_dwcolumn11Status;
	DBSTATUS m_dwcolumn12Status;
	DBSTATUS m_dwcolumn13Status;
	DBSTATUS m_dwcolumn14Status;
	DBSTATUS m_dwcolumn15Status;
	DBSTATUS m_dwcolumn16Status;
	DBSTATUS m_dwcolumn17Status;

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
	DBLENGTH m_dwcolumn8Length;
	DBLENGTH m_dwcolumn9Length;
	DBLENGTH m_dwcolumn10Length;
	DBLENGTH m_dwcolumn11Length;
	DBLENGTH m_dwcolumn12Length;
	DBLENGTH m_dwcolumn13Length;
	DBLENGTH m_dwcolumn14Length;
	DBLENGTH m_dwcolumn15Length;
	DBLENGTH m_dwcolumn16Length;
	DBLENGTH m_dwcolumn17Length;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
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
		hr = _db.OpenFromInitializationString(L"Provider=Microsoft.ACE.OLEDB.12.0;User ID=Admin;Data Source=\x0410\x043b\x0441\x043d.accdb;Mode=ReadWrite;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=6;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Jet OLEDB:Support Complex Data=False");
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

// Эта таблица или команда содержит столбцы, доступные 
// через интерфейс ISequentialStream. Однако это средство поддерживают 
// не все поставщики, и даже те, кто поддерживает, 
// часто ограничиваются только одним ISequentialStream на набор строк. 
// Если требуется использовать потоки в этом методе доступа, используйте
// примеры строк кода ниже и задайте для свойства набора строк 
// DBPROP_ISequentialStream значение true. Затем с помощью метода Read() 
// можно прочитать данные или записать их с помощью метода Write(). 
// (Для этого требуется заменить свойство потока STGM_READ 
// на STGM_WRITE или STGM_READWRITE). Дополнительно о привязке 
// ISequentialStream см. в документации
	BEGIN_COLUMN_MAP(CDataRowsetAccessor)
		// BLOB_ENTRY_LENGTH_STATUS(16, IID_ISequentialStream, STGM_READ, m_column0, m_dwcolumn0Length, m_dwcolumn0Status)
		COLUMN_ENTRY_LENGTH_STATUS(16, m_column0, m_dwcolumn0Length, m_dwcolumn0Status)
		_COLUMN_ENTRY_CODE(9, DBTYPE_DATE, _SIZE_TYPE(m_column1), 0, 0, offsetbuf(m_column1), offsetbuf(m_dwcolumn1Length), offsetbuf(m_dwcolumn1Status))
		_COLUMN_ENTRY_CODE(17, DBTYPE_DATE, _SIZE_TYPE(m_column2), 0, 0, offsetbuf(m_column2), offsetbuf(m_dwcolumn2Length), offsetbuf(m_dwcolumn2Status))
		COLUMN_ENTRY_LENGTH_STATUS(5, m_column3, m_dwcolumn3Length, m_dwcolumn3Status)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_column4, m_dwcolumn4Length, m_dwcolumn4Status)
		COLUMN_ENTRY_LENGTH_STATUS(12, m_column5, m_dwcolumn5Length, m_dwcolumn5Status)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_column6, m_dwcolumn6Length, m_dwcolumn6Status)
		COLUMN_ENTRY_LENGTH_STATUS(13, m_column7, m_dwcolumn7Length, m_dwcolumn7Status)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_column8, m_dwcolumn8Length, m_dwcolumn8Status)
		// BLOB_ENTRY_LENGTH_STATUS(18, IID_ISequentialStream, STGM_READ, m_column9, m_dwcolumn9Length, m_dwcolumn9Status)
		COLUMN_ENTRY_LENGTH_STATUS(18, m_column9, m_dwcolumn9Length, m_dwcolumn9Status)
		COLUMN_ENTRY_LENGTH_STATUS(15, m_column10, m_dwcolumn10Length, m_dwcolumn10Status)
		// BLOB_ENTRY_LENGTH_STATUS(14, IID_ISequentialStream, STGM_READ, m_column11, m_dwcolumn11Length, m_dwcolumn11Status)
		COLUMN_ENTRY_LENGTH_STATUS(14, m_column11, m_dwcolumn11Length, m_dwcolumn11Status)
		COLUMN_ENTRY_LENGTH_STATUS(8, m_column12, m_dwcolumn12Length, m_dwcolumn12Status)
		_COLUMN_ENTRY_CODE(11, DBTYPE_CY, _SIZE_TYPE(m_column13), 0, 0, offsetbuf(m_column13), offsetbuf(m_dwcolumn13Length), offsetbuf(m_dwcolumn13Status))
		COLUMN_ENTRY_LENGTH_STATUS(6, m_column14, m_dwcolumn14Length, m_dwcolumn14Status)
		COLUMN_ENTRY_LENGTH_STATUS(7, m_column15, m_dwcolumn15Length, m_dwcolumn15Status)
		_COLUMN_ENTRY_CODE(10, DBTYPE_CY, _SIZE_TYPE(m_column16), 0, 0, offsetbuf(m_column16), offsetbuf(m_dwcolumn16Length), offsetbuf(m_dwcolumn16Status))
		COLUMN_ENTRY_LENGTH_STATUS(4, m_column17, m_dwcolumn17Length, m_dwcolumn17Status)
	END_COLUMN_MAP()
};

class CDataRowset : public CTable<CAccessor<CDataRowsetAccessor> >
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
		HRESULT hr = Open(m_session, L"Основные средства", pPropSet);
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


