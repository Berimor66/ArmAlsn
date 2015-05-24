// AlsDbFormView.cpp: ���� ����������
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


// ����������� CAlsDbFormView

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

CAlsDbDoc* CAlsDbFormView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlsDbDoc)));
	return (CAlsDbDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CAlsDbFormView

void CAlsDbFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_Itinerary.SetExtendedUI(1);
	m_Coupe.SetExtendedUI(1);
	
	CDataItineraryRowset dataItin; // = new CDataItineraryRowset ;
 
	if (SUCCEEDED (dataItin.OpenAll())) //SUCCEEDED ��� FAILED
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
	else AfxMessageBox(L"������ �������� ���� ���������");
 /**/
		
	///dataItin->Delete();

	// TODO: ������� ���� ���, ����� ��������� ��� ������ ������ ����� �������
//	m_pSelection = NULL;    // ������������� ���������

}

	
//����� �������
void CAlsDbFormView::OnCbnSelchangeItinerary()
{
	// TODO: �������� ���� ��� ����������� �����������
	///////////////////////////////////////////////////////////////////
	//UpdateData(1);  // �� �������a ���������� �  ���������� m_strItinerary

	CDataRowsetCoupe dataCoupe;
	CSession session;
	CString sss, strQuery;

	m_Itinerary.GetLBText(m_Itinerary.GetCurSel(),sss);
	//sss.Trim();
	strQuery.Format(L"SELECT * FROM [��������] WHERE [ItineraryName]=\"%s\"",sss); //CoupeName

	if (SUCCEEDED  (dataCoupe.OpenAll()))  // SUCCEEDED ��� FAILED
	{
		session=dataCoupe.m_session;
		dataCoupe.CloseAll();
/**/ // SUCCEEDED ��� FAILED
		if (SUCCEEDED (dataCoupe.Open(session, strQuery))) //'������� ����. - ������� ��.'ataCoupe.Open(dataCoupe.m_session,sss))
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
		else AfxMessageBox(L"������ ������� � ���� ���������");
	}
	else AfxMessageBox(L"������ �������� ���� ���������");
		/**/	/////////////////////////////////////////////////////////////////////
	//dataCoupe.Delete();
}


void CAlsDbFormView::OnCbnKillfocusItinerary()
{
	// TODO: �������� ���� ��� ����������� �����������
//	UpdateData(1);  // �� ��������� ���������� � ������������ ����������
//	AfxMessageBox(m_strItinerary);
}
