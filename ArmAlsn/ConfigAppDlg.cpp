// ConfigAppDlg.cpp: ���� ����������
//	  ������� ���� �������� ���������

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigAppDlg.h"
#include "ConfigDirectX.h"
#include "ConfigGPS.h"
#include "ConfigSound.h"
#include "ConfigPath.h"
//#include "Config.h"


// ���������� ���� CConfigAppDlg

IMPLEMENT_DYNAMIC(CConfigAppDlg, CDialog)

CConfigAppDlg::CConfigAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigAppDlg::IDD, pParent)
//	, m_DeviceCount(0)
{
	m_pTabDialog=0;
	EnableAutomation();

}

CConfigAppDlg::~CConfigAppDlg()
{
	//ASSERT (m_pTabDialog)
	delete m_pTabDialog;
	
}

void CConfigAppDlg::OnFinalRelease()
{
	// ����� ����� ����������� ��������� ������ �� ������ �������������,
	// ���������� OnFinalRelease. ������� ����� �������������
	// ������ ������. ����� ������� �������� ������ ��������
	// �������������� �������, ����������� ������ �������.

	CDialog::OnFinalRelease();
}

void CConfigAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeDialogMessages);
	DDX_Control(pDX, IDC_TAB1, m_Tab_config_app);
}


BEGIN_MESSAGE_MAP(CConfigAppDlg, CDialog)

	ON_BN_CLICKED(IDCANCEL, &CConfigAppDlg::OnBnClickedCancel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CConfigAppDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_SAVE_EXIT, &CConfigAppDlg::OnBnClickedSaveExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CConfigAppDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CConfigAppDlg::OnTcnSelchangingTab1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SAVECONFIG, &CConfigAppDlg::OnBnClickedSave)// CConfigDirectX::OnBnClickedConsave)  CConfigAppDlg::OnBnClickedButton2
	ON_BN_CLICKED(IDC_NOSAVE, &CConfigAppDlg::OnBnClickedNosave)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConfigAppDlg, CDialog)
END_DISPATCH_MAP()

// ����������: �� �������� ��������� ��� IID_IConfigAppDlg, ����� ���������� ���������� � ����� ������ ����� ��������
//  �� VBA. ���� IID ������ ��������������� GUID, ���������� � 
//  disp-����������� � ����� .IDL.

// {3DDAD29C-F07E-48BA-B50A-02E421529830}
static const IID IID_IConfigAppDlg =
{ 0x3DDAD29C, 0xF07E, 0x48BA, { 0xB5, 0xA, 0x2, 0xE4, 0x21, 0x52, 0x98, 0x30 } };

BEGIN_INTERFACE_MAP(CConfigAppDlg, CDialog)
	INTERFACE_PART(CConfigAppDlg, IID_IConfigAppDlg, Dispatch)
END_INTERFACE_MAP()


// ����������� ��������� CConfigAppDlg
// ������� �������
void CConfigAppDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������

 int id; // ID �������

 // ���� ������� ������� ���������� ������ � Tab Control'�:
 if (m_pTabDialog)
 {
  m_pTabDialog->DestroyWindow();
  delete m_pTabDialog;
 }

 // ������ � ����������� �� ����, ����� �������� �������, 
 // �������� �����. ������
 switch( m_Tab_config_app.GetCurSel()+1 ) // +1 ��� ����, ����� ���������� ������ ��������
                // � �������� ��������� � �������� � case
 {
  // ������ ��������
  case 1 :
     id = IDD_DIALOG_CONFIG_DIRECTX;
     m_pTabDialog = new CConfigDirectX;
      // ��� ��������� ������������� ������� �������,
      // ����� ����������� � ������ ��� �� ����� ���������������
  break;

  // ������ ��������
  case 2 :
     id = IDD_DIALOG_CONFIG_GPS;
     m_pTabDialog = new CConfigGPS;
  break;

  // ������ ��������
	case 3 :
	  id = IDD_DIALOG_CONFIG_SOUND;
	  m_pTabDialog = new CConfigSound;
	break;
	  // 4 ��������
	case 4 :
	  id = IDD_DIALOG_CONFIG_PATH;
	  m_pTabDialog = new CConfigPath;
	break;



  // ��� ��������� ��������, ���� ��� ����,
  // ����� ����� ���� ������������, ������ - ��������� case

  // � ���� ��������� ������ ������ �� �������������
  default:
    m_pTabDialog = new CDialog; // ����� ������ ������
    return;

  } // end switch

  // ������� ������
 VERIFY(m_pTabDialog->Create (id, (CWnd*)&m_Tab_config_app)); //���������: ������ ������� � ��������

 CRect rc; 

 m_Tab_config_app.GetWindowRect (&rc); // �������� "������� �������"
 m_Tab_config_app.ScreenToClient (&rc); // ����������� � ������������� ����������

 // ��������� �������, ��� ������������ �������� ��������:
 m_Tab_config_app.AdjustRect (FALSE, &rc); 

 // �������� ������ �� �����..
 m_pTabDialog->MoveWindow (&rc);

 // � ����������:
 m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
 m_pTabDialog->UpdateWindow();


// 	int nTab = m_Tab_config_app.GetCurSel();
//    TC_ITEM tci;
//    tci.mask = TCIF_PARAM;
// 	m_Tab_config_app.GetItem(nTab, &tci);
//    ASSERT(tci.lParam);
// 	CWnd* pWnd = (CWnd *)tci.lParam;
//    pWnd->ShowWindow(SW_SHOW);

	*pResult = 0;
}

void CConfigAppDlg::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������
	//m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONDOWN,1,1);
	//m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONUP,1,1);


/*
	CWnd* pParent = GetParent();
	ASSERT (pParent);
	{
		pParent->PostMessageW (WM_DIALOG_CNF_CLOSE, 0, 0);
	}
*/
	//
	OnBnClickedNosave();
	OnCancel();
	DestroyWindow();
}

// �����  �������� ������ 
void CConfigAppDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	UNREFERENCED_PARAMETER(pNMTreeView);
	// TODO: �������� ���� ��� ����������� �����������

	HTREEITEM hitem = m_treeDialogMessages.GetSelectedItem();
	CRect rc; 

//  1-� � 0 �.�. ��������� c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="����������")
	{
				 // ���� ������� ������� ���������� ������ � Tab Control'�:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(0); // ������� ��������
		m_pTabDialog = new CConfigDirectX;
		
	  // ������� ������ id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_DIRECTX, (CWnd*)&m_Tab_config_app)); //���������: ������ ������� � ��������

		
	}


////////////////////////////
//  2-� � 1 �.�. ��������� c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="GPS")
	{
				 // ���� ������� ������� ���������� ������ � Tab Control'�:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(1); // ������� ��������
		m_pTabDialog = new CConfigGPS;
		
	  // ������� ������ id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_GPS, (CWnd*)&m_Tab_config_app)); //���������: ������ ������� � ��������


//		m_Tab_config_app.GetWindowRect (&rc); // �������� "������� �������"
//		m_Tab_config_app.ScreenToClient (&rc); // ����������� � ������������� ����������

		// ��������� �������, ��� ������������ �������� ��������:
//		m_Tab_config_app.AdjustRect (FALSE, &rc); 

		// �������� ������ �� �����..
//		m_pTabDialog->MoveWindow (&rc);

		// � ����������:
//		m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
//		m_pTabDialog->UpdateWindow();		

	}
	//
///////////////////////////////////////////////////
	////////////////////////////
	//  3-� � 2 �.�. ��������� c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="����")
	{
		// ���� ������� ������� ���������� ������ � Tab Control'�:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(2); // ������� ��������
		m_pTabDialog = new CConfigSound;

		// ������� ������ id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_SOUND, (CWnd*)&m_Tab_config_app)); //���������: ������ ������� � ��������
	}


	//
	///////////////////////////////////////////////////
///////////////////////////////////////////////////
	////////////////////////////
	//  4-� � 3 �.�. ��������� c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="��������")
	{
		// ���� ������� ������� ���������� ������ � Tab Control'�:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(3); // ������� ��������
		m_pTabDialog = new CConfigPath;

		// ������� ������ id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_PATH, (CWnd*)&m_Tab_config_app)); //���������: ������ ������� � ��������
	}


	//
	///////////////////////////////////////////////////

	
	m_Tab_config_app.GetWindowRect (&rc); // �������� "������� �������"
		m_Tab_config_app.ScreenToClient (&rc); // ����������� � ������������� ����������

		// ��������� �������, ��� ������������ �������� ��������:
		m_Tab_config_app.AdjustRect (FALSE, &rc); 

		// �������� ������ �� �����..
		m_pTabDialog->MoveWindow (&rc);

		// � ����������:
		m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
		m_pTabDialog->UpdateWindow();


	*pResult = 0;
}




BOOL CConfigAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �������� �������������� �������������
	//////////////////////////////////////////////////////////////////
	///



	HTREEITEM h1 = m_treeDialogMessages.InsertItem(_T("���� / �����"));
	HTREEITEM h2 = m_treeDialogMessages.InsertItem(_T("���������� �������"),h1);
	HTREEITEM h3 = m_treeDialogMessages.InsertItem(_T("�������� �������"),h1);
	HTREEITEM h4 = m_treeDialogMessages.InsertItem(_T("��������� � ����"));
	
	m_treeDialogMessages.InsertItem(_T("����������"), h2);
	m_treeDialogMessages.InsertItem(_T("����"), h2);
	m_treeDialogMessages.InsertItem(_T("GPS"), h3);
	m_treeDialogMessages.InsertItem(_T("��������"), h4);
	

	/////////////////////////////////////////////////////////////////

    //�������� �������
	//

////////////////////////////////////////////////////////////////////////////////
	//// ������������� ��������

	TC_ITEM TabItem;	// � ��� ������������ ��������� ����������� ��������
 	memset(&TabItem,0,sizeof(TabItem));
	TabItem.mask = TCIF_TEXT;	// � �������� ����� ������ �����

	TabItem.pszText = _T("����������");
  	m_Tab_config_app.InsertItem( 0, &TabItem ); // ������ �������� ����� ������ 0
  	TabItem.pszText = _T("GPS");
  	m_Tab_config_app.InsertItem( 1, &TabItem );//  2-�
	TabItem.pszText = _T("����");
	m_Tab_config_app.InsertItem( 2, &TabItem );	// 3-�
	TabItem.pszText = _T("����");
	m_Tab_config_app.InsertItem( 3, &TabItem );	// 4-�
  	//TabItem.pszText = _T("��������3");
  	//m_config_app.InsertItem( 2, &TabItem );

	// ���������� ����� ������ ��������
	NMHDR hdr;

	hdr.code = TCN_SELCHANGE;
	hdr.hwndFrom = m_Tab_config_app.m_hWnd;

	SendMessage ( WM_NOTIFY, m_Tab_config_app.GetDlgCtrlID(), (LPARAM)&hdr );

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
void CConfigAppDlg::OnBnClickedSave()
{
	// ������� ��������� ������� ������� �������� �������� �������
	m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONDOWN,1,1);
	m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONUP,1,1);

}


void CConfigAppDlg::OnBnClickedSaveExit()
{
	// ������� ��������� ������� ������� �������� �������� �������
	//m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONDOWN,1,1);
	//m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONUP,1,1);
	OnBnClickedSave();
	DestroyWindow();
}
// ����������, ��� ����� ����� ���������
void CConfigAppDlg::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	// TODO: �������� ���� ��� ����������� �����������
/*
	int nTab = m_Tab_config_app.GetCurSel();
    TC_ITEM tci;
    tci.mask = TCIF_PARAM;
 	m_Tab_config_app.GetItem(nTab, &tci);
    ASSERT(tci.lParam);
 	CWnd* pWnd = (CWnd *)tci.lParam;
    pWnd->ShowWindow(SW_HIDE);

*/
	OnBnClickedSave();
	*pResult = 0;
}

void CConfigAppDlg::OnDestroy()
{
	CDialog::OnDestroy();
	//delete CConfigDirectX;
	ASSERT (m_pTabDialog);
	// TODO: �������� ���� ��� ����������� ���������
	
	/*
	// �������� ������� �������
	CWnd* pWnd; 
	TC_ITEM tci; 
	tci.mask = TCIF_PARAM; 

	for ( int i = 2 ; i>= 0 ; i--) 
	{ 
		m_config_app.GetItem(i, &tci); 
		ASSERT(tci.lParam); 

		pWnd = (CWnd *)tci.lParam; 
		pWnd->DestroyWindow(); 
		delete pWnd; 
	}
	*/




}




void CConfigAppDlg::OnBnClickedNosave()
{
	// TODO: �������� ���� ��� ����������� �����������
	m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONDOWN,1,1);
	m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONUP,1,1);
}

// ������������ ������� ENTER
BOOL CConfigAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	//BOOL bHandledMsg = FALSE;

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		//OnBnClickedSaveExit();
		// ������� ��������� ������� ������� �������� �������� �������
		m_pTabDialog->SendDlgItemMessage(IDCONSAVE, WM_LBUTTONDOWN,1,1);
		m_pTabDialog->SendDlgItemMessage(IDCONSAVE, WM_LBUTTONUP,1,1);
		//pMsg->wParam = VK_TAB;
		//AfxMessageBox(L"������ ����");
	}


	return CDialog::PreTranslateMessage(pMsg);
}
