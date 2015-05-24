// ConfigAppDlg.cpp: файл реализации
//	  Главное окно настроек программы

#include "stdafx.h"
#include "ArmALSN.h"
#include "ConfigAppDlg.h"
#include "ConfigDirectX.h"
#include "ConfigGPS.h"
#include "ConfigSound.h"
#include "ConfigPath.h"
//#include "Config.h"


// диалоговое окно CConfigAppDlg

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
	// Когда будет освобождена последняя ссылка на объект автоматизации,
	// вызывается OnFinalRelease. Базовый класс автоматически
	// удалит объект. Перед вызовом базового класса добавьте
	// дополнительную очистку, необходимую вашему объекту.

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

// Примечание: мы добавили поддержку для IID_IConfigAppDlg, чтобы обеспечить безопасную с точки зрения типов привязку
//  из VBA. Этот IID должен соответствовать GUID, связанному с 
//  disp-интерфейсом в файле .IDL.

// {3DDAD29C-F07E-48BA-B50A-02E421529830}
static const IID IID_IConfigAppDlg =
{ 0x3DDAD29C, 0xF07E, 0x48BA, { 0xB5, 0xA, 0x2, 0xE4, 0x21, 0x52, 0x98, 0x30 } };

BEGIN_INTERFACE_MAP(CConfigAppDlg, CDialog)
	INTERFACE_PART(CConfigAppDlg, IID_IConfigAppDlg, Dispatch)
END_INTERFACE_MAP()


// обработчики сообщений CConfigAppDlg
// Выбрана вкладка
void CConfigAppDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений

 int id; // ID диалога

 // надо сначала удалить предыдущий диалог в Tab Control'е:
 if (m_pTabDialog)
 {
  m_pTabDialog->DestroyWindow();
  delete m_pTabDialog;
 }

 // теперь в зависимости от того, какая закладка выбрана, 
 // выбираем соотв. диалог
 switch( m_Tab_config_app.GetCurSel()+1 ) // +1 для того, чтобы порядковые номера закладок
                // и диалогов совпадали с номерами в case
 {
  // первая закладка
  case 1 :
     id = IDD_DIALOG_CONFIG_DIRECTX;
     m_pTabDialog = new CConfigDirectX;
      // тип указателя соответствует нужному диалогу,
      // иначе добавленный в диалог код не будет функционировать
  break;

  // вторая закладка
  case 2 :
     id = IDD_DIALOG_CONFIG_GPS;
     m_pTabDialog = new CConfigGPS;
  break;

  // третья закладка
	case 3 :
	  id = IDD_DIALOG_CONFIG_SOUND;
	  m_pTabDialog = new CConfigSound;
	break;
	  // 4 закладка
	case 4 :
	  id = IDD_DIALOG_CONFIG_PATH;
	  m_pTabDialog = new CConfigPath;
	break;



  // все остальные закладки, если они есть,
  // будут здесь тоже представлены, каждая - отдельным case

  // а если обработка такого номера не предусмотрена
  default:
    m_pTabDialog = new CDialog; // новый пустой диалог
    return;

  } // end switch

  // создаем диалог
 VERIFY(m_pTabDialog->Create (id, (CWnd*)&m_Tab_config_app)); //параметры: ресурс диалога и родитель

 CRect rc; 

 m_Tab_config_app.GetWindowRect (&rc); // получаем "рабочую область"
 m_Tab_config_app.ScreenToClient (&rc); // преобразуем в относительные координаты

 // исключаем область, где отображаются названия закладок:
 m_Tab_config_app.AdjustRect (FALSE, &rc); 

 // помещаем диалог на место..
 m_pTabDialog->MoveWindow (&rc);

 // и показываем:
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
	// TODO: добавьте свой код обработчика уведомлений
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

// Выбор  элемента дерева 
void CConfigAppDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	UNREFERENCED_PARAMETER(pNMTreeView);
	// TODO: добавьте свой код обработчика уведомлений

	HTREEITEM hitem = m_treeDialogMessages.GetSelectedItem();
	CRect rc; 

//  1-я № 0 т.к. нумерация c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="Устройства")
	{
				 // надо сначала удалить предыдущий диалог в Tab Control'е:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(0); // выбрали закладку
		m_pTabDialog = new CConfigDirectX;
		
	  // создаем диалог id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_DIRECTX, (CWnd*)&m_Tab_config_app)); //параметры: ресурс диалога и родитель

		
	}


////////////////////////////
//  2-я № 1 т.к. нумерация c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="GPS")
	{
				 // надо сначала удалить предыдущий диалог в Tab Control'е:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(1); // выбрали закладку
		m_pTabDialog = new CConfigGPS;
		
	  // создаем диалог id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_GPS, (CWnd*)&m_Tab_config_app)); //параметры: ресурс диалога и родитель


//		m_Tab_config_app.GetWindowRect (&rc); // получаем "рабочую область"
//		m_Tab_config_app.ScreenToClient (&rc); // преобразуем в относительные координаты

		// исключаем область, где отображаются названия закладок:
//		m_Tab_config_app.AdjustRect (FALSE, &rc); 

		// помещаем диалог на место..
//		m_pTabDialog->MoveWindow (&rc);

		// и показываем:
//		m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
//		m_pTabDialog->UpdateWindow();		

	}
	//
///////////////////////////////////////////////////
	////////////////////////////
	//  3-я № 2 т.к. нумерация c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="Звук")
	{
		// надо сначала удалить предыдущий диалог в Tab Control'е:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(2); // выбрали закладку
		m_pTabDialog = new CConfigSound;

		// создаем диалог id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_SOUND, (CWnd*)&m_Tab_config_app)); //параметры: ресурс диалога и родитель
	}


	//
	///////////////////////////////////////////////////
///////////////////////////////////////////////////
	////////////////////////////
	//  4-я № 3 т.к. нумерация c 0
	if (m_treeDialogMessages.GetItemText(hitem)=="Каталоги")
	{
		// надо сначала удалить предыдущий диалог в Tab Control'е:
		if (m_pTabDialog)
		{
			m_pTabDialog->DestroyWindow();
			delete m_pTabDialog;
		}

		m_Tab_config_app.SetCurSel(3); // выбрали закладку
		m_pTabDialog = new CConfigPath;

		// создаем диалог id
		VERIFY(m_pTabDialog->Create (IDD_DIALOG_CONFIG_PATH, (CWnd*)&m_Tab_config_app)); //параметры: ресурс диалога и родитель
	}


	//
	///////////////////////////////////////////////////

	
	m_Tab_config_app.GetWindowRect (&rc); // получаем "рабочую область"
		m_Tab_config_app.ScreenToClient (&rc); // преобразуем в относительные координаты

		// исключаем область, где отображаются названия закладок:
		m_Tab_config_app.AdjustRect (FALSE, &rc); 

		// помещаем диалог на место..
		m_pTabDialog->MoveWindow (&rc);

		// и показываем:
		m_pTabDialog->ShowWindow ( SW_SHOWNORMAL );
		m_pTabDialog->UpdateWindow();


	*pResult = 0;
}




BOOL CConfigAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	//////////////////////////////////////////////////////////////////
	///



	HTREEITEM h1 = m_treeDialogMessages.InsertItem(_T("Ввод / Вывод"));
	HTREEITEM h2 = m_treeDialogMessages.InsertItem(_T("Аналоговые сигналы"),h1);
	HTREEITEM h3 = m_treeDialogMessages.InsertItem(_T("Цифровые сигналы"),h1);
	HTREEITEM h4 = m_treeDialogMessages.InsertItem(_T("Программы и базы"));
	
	m_treeDialogMessages.InsertItem(_T("Устройства"), h2);
	m_treeDialogMessages.InsertItem(_T("Звук"), h2);
	m_treeDialogMessages.InsertItem(_T("GPS"), h3);
	m_treeDialogMessages.InsertItem(_T("Каталоги"), h4);
	

	/////////////////////////////////////////////////////////////////

    //страница свойств
	//

////////////////////////////////////////////////////////////////////////////////
	//// Инициализация закладок

	TC_ITEM TabItem;	// в нее записываются параметры создаваемой закладки
 	memset(&TabItem,0,sizeof(TabItem));
	TabItem.mask = TCIF_TEXT;	// у закладки будет только текст

	TabItem.pszText = _T("Устройства");
  	m_Tab_config_app.InsertItem( 0, &TabItem ); // первая закладка имеет индекс 0
  	TabItem.pszText = _T("GPS");
  	m_Tab_config_app.InsertItem( 1, &TabItem );//  2-я
	TabItem.pszText = _T("Звук");
	m_Tab_config_app.InsertItem( 2, &TabItem );	// 3-я
	TabItem.pszText = _T("Пути");
	m_Tab_config_app.InsertItem( 3, &TabItem );	// 4-я
  	//TabItem.pszText = _T("Закладка3");
  	//m_config_app.InsertItem( 2, &TabItem );

	// отобразить самую первую закладку
	NMHDR hdr;

	hdr.code = TCN_SELCHANGE;
	hdr.hwndFrom = m_Tab_config_app.m_hWnd;

	SendMessage ( WM_NOTIFY, m_Tab_config_app.GetDlgCtrlID(), (LPARAM)&hdr );

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
void CConfigAppDlg::OnBnClickedSave()
{
	// Послать сообщение актвной Вкладке елемента Страницы свойств
	m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONDOWN,1,1);
	m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONUP,1,1);

}


void CConfigAppDlg::OnBnClickedSaveExit()
{
	// Послать сообщение актвной Вкладке елемента Страницы свойств
	//m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONDOWN,1,1);
	//m_pTabDialog->SendDlgItemMessageW(IDCONSAVE, WM_LBUTTONUP,1,1);
	OnBnClickedSave();
	DestroyWindow();
}
// Показывает, что выбор будет перенесен
void CConfigAppDlg::OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UNREFERENCED_PARAMETER(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
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
	// TODO: добавьте свой код обработчика сообщений
	
	/*
	// Удаление ресурса вкладок
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
	// TODO: добавьте свой код обработчика уведомлений
	m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONDOWN,1,1);
	m_pTabDialog->SendDlgItemMessageW(IDCANCEL, WM_LBUTTONUP,1,1);
}

// Обрабатываем клавишу ENTER
BOOL CConfigAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	//BOOL bHandledMsg = FALSE;

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		//OnBnClickedSaveExit();
		// Послать сообщение актвной Вкладке елемента Страницы свойств
		m_pTabDialog->SendDlgItemMessage(IDCONSAVE, WM_LBUTTONDOWN,1,1);
		m_pTabDialog->SendDlgItemMessage(IDCONSAVE, WM_LBUTTONUP,1,1);
		//pMsg->wParam = VK_TAB;
		//AfxMessageBox(L"Нажали ВВОД");
	}


	return CDialog::PreTranslateMessage(pMsg);
}
