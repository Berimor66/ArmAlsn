// AlsDbFormView.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "AlsDbDoc.h"
#include "DataRowItinerary.h"
#include "DataRowCoupe.h"

#include "AlsDbFormView.h"


// CAlsDbFormView

IMPLEMENT_DYNCREATE(CAlsDbFormView, CFormView)

CAlsDbFormView::CAlsDbFormView()
	: CFormView(CAlsDbFormView::IDD)
	, m_strItinerary(_T(""))
{

}

CAlsDbFormView::~CAlsDbFormView()
{
}

void CAlsDbFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUPE, m_Coupe);
	DDX_Control(pDX, IDC_ITINERARY, m_Itinerary);
	DDX_CBString(pDX, IDC_ITINERARY, m_strItinerary);
}

BEGIN_MESSAGE_MAP(CAlsDbFormView, CFormView)
	ON_CBN_SELCHANGE(IDC_ITINERARY, &CAlsDbFormView::OnCbnSelchangeItinerary)
	ON_CBN_KILLFOCUS(IDC_ITINERARY, &CAlsDbFormView::OnCbnKillfocusItinerary)
END_MESSAGE_MAP()


// диагностика CAlsDbFormView

#ifdef _DEBUG
void CAlsDbFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAlsDbFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif

CAlsDbDoc* CAlsDbFormView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlsDbDoc)));
	return (CAlsDbDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CAlsDbFormView

void CAlsDbFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_Itinerary.SetExtendedUI(1);
	m_Coupe.SetExtendedUI(1);
	
	CDataItineraryRowset dataItin; // = new CDataItineraryRowset ;
 
	if (SUCCEEDED (dataItin.OpenAll())) //SUCCEEDED или FAILED
	{
			m_Itinerary.ResetContent();
			while (dataItin.MoveNext() == S_OK)
			{
				//AfxMessageBox(dataItin->m_ItineraryName);
				m_Itinerary.AddString(dataItin.m_ItineraryName);
			}
			m_Itinerary.SetCurSel(0);	
			dataItin.CloseAll();
	}
	else AfxMessageBox(L"Ошибка открытия базы маршрутов");
 /**/
		
	///dataItin->Delete();

	// TODO: удалите этот код, когда финальный код модели выбора будет написан
//	m_pSelection = NULL;    // инициализация выделения

}

	
//Выбор изменен
void CAlsDbFormView::OnCbnSelchangeItinerary()
{
	// TODO: добавьте свой код обработчика уведомлений
	///////////////////////////////////////////////////////////////////
	//UpdateData(1);  // Из элементa управления в  переменную m_strItinerary

	CDataRowsetCoupe dataCoupe;
	CSession session;
	CString sss, strQuery;

	m_Itinerary.GetLBText(m_Itinerary.GetCurSel(),sss);
	//sss.Trim();
	strQuery.Format(L"SELECT * FROM [Перегоны] WHERE [ItineraryName]=\"%s\"",sss); //CoupeName

	if (SUCCEEDED  (dataCoupe.OpenAll()))  // SUCCEEDED или FAILED
	{
		session=dataCoupe.m_session;
		dataCoupe.CloseAll();
/**/ // SUCCEEDED или FAILED
		if (SUCCEEDED (dataCoupe.Open(session, strQuery))) //'Харьков пасс. - Полтава Юж.'ataCoupe.Open(dataCoupe.m_session,sss))
		{
//			dataCoupe->MoveFirst();
			m_Coupe.ResetContent();
			while (dataCoupe.MoveNext() == S_OK)
			{
				m_Coupe.AddString(dataCoupe.m_CoupeName);
			}
			m_Coupe.SetCurSel(0);
			dataCoupe.CloseAll();

		}
		else AfxMessageBox(L"Ошибка запроса к базе перегонов");
	}
	else AfxMessageBox(L"Ошибка открытия базы перегонов");
		/**/	/////////////////////////////////////////////////////////////////////
	//dataCoupe.Delete();
}


void CAlsDbFormView::OnCbnKillfocusItinerary()
{
	// TODO: добавьте свой код обработчика уведомлений
//	UpdateData(1);  // Из элементов управления в компонентную переменную
//	AfxMessageBox(m_strItinerary);
}
