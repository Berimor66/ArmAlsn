
// MainFrm.cpp : реализация класса CMainFrame
//

#include "stdafx.h"
#include "ArmAlsn.h"

#include "MainFrm.h"

//#include "../MultiLangW/MultiLang.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//p
#include "MainFrm.h"
//#include "../MultiLangW/MultiLang.h"
// CMainFrame


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

static		 UINT  WM_TOK1 = ::RegisterWindowMessage((LPCWSTR) L"MyMessage_TOK");
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_CLOSE, &CMainFrame::OnFileClose)
	// Команды глобальной справки
	ON_COMMAND(ID_HELP_FINDER, &CFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_HELP, &CFrameWndEx::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, &CFrameWndEx::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, &CFrameWndEx::OnHelpFinder)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)

	ON_REGISTERED_MESSAGE(WM_TOK1, &CMainFrame::OnTok)

	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	//p

	ON_COMMAND_RANGE(ID_LANGUAGE_FIRST,ID_LANGUAGE_FIRST+MAX_LANGUAGES, 
														OnLanguageFirst)
	ON_UPDATE_COMMAND_UI_RANGE(ID_LANGUAGE_FIRST, ID_LANGUAGE_FIRST+MAX_LANGUAGES, OnUpdateLanguageFirst)

	ON_COMMAND(ID_CONFIG, &CMainFrame::OnConfigApp)
	ON_MESSAGE(WM_DIALOG_CNF_CLOSE, OnDialogCnfClose)
	ON_MESSAGE(WM_MYICONNOTIFY,OnIcon)
	ON_COMMAND(ID_HIDE, &CMainFrame::OnHide)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_APP_UP, &CMainFrame::OnAppUp)
	// Обработка меню Асимметрия
	ON_COMMAND(ID_MyBass, &CMainFrame::OnViewPut)
	ON_COMMAND(ID_DISCO, &CMainFrame::OnDisco)

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)

//	ON_WM_USERCHANGED()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // индикатор строки состояния
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_TIME,
};

// создание/уничтожение CMainFrame

CMainFrame::CMainFrame()
{
	// TODO: добавьте код инициализации члена
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);

}

CMainFrame::~CMainFrame()
{
//	m_ViewPut.DestroyWindow();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// установите наглядный диспетчер и стиль на основе постоянного значения
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Не удалось создать строку меню\n");
		return -1;      // не удалось создать
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// предотвращение фокусировки строки меню на активации 
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Не удалось создать панель инструментов\n");
		AfxMessageBox(L"Не удалось создать панель инструментов");
		return -1;      // не удалось создать
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Разрешить операции с пользовательскими панелями инструментов:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Не удалось создать строку состояния\n");
		return -1;      // не удалось создать
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// Действие: удалите эти пять строк, если панель инструментов и строка меню не должны быть закрепляемыми
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// включить режим работы закрепляемых окон стилей Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// включить режим работы автоматического скрытия закрепляемых окон стилей Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// создать закрепляемые окна
	if (!CreateDockingWindows())
	{
		TRACE0("Не удалось создать закрепляемые окна\n");
		return -1;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	// Включить функцию замены меню панелей инструментов и закрепляемых окон 
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// включить быструю (Alt+перетаскивание) настройку панелей инструментов
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// загрузить изображения пользовательских панелей инструментов
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// включить персонализацию меню (последние использованные команды)
	// Действие: определите свои основные команды так, чтобы каждое раскрывающееся меню содержало по крайней мере одну основную команду.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_FILE_NEW_FRAME);
	lstBasicCommands.AddTail(ID_FILE_CLOSE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	m_wndStatusBar.SetTimer(1, 1000, NULL); // таймер для времени 

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,               // TODO: измените число строк, столбцов
		CSize(10, 10),      // TODO: измените минимальный размер области
		pContext);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	cs.cx=300;
	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// Создать окно вывода
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Не удалось создать окно \"Вывод\"\n");
		return FALSE; // не удалось создать
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

}

// диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// обработчики сообщений CMainFrame

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* сканировать меню*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// базовый класс не работает

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	CWinApp* pApp = AfxGetApp();
	if (pApp->m_pMainWnd == NULL)
		pApp->m_pMainWnd = this;

	// включить кнопку настройки для всех пользовательских панелей инструментов
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}

void CMainFrame::OnFileClose()
{
	DestroyWindow();
}

void CMainFrame::OnConfigApp()
{
	// TODO: добавьте свой код обработчика команд
	//CConfigAppDlg DlgChf;
	//DlgChf.DoModal();
	// AfxMessageBox(_T("Dialog"),1,0);
	if (!m_ConfigAppDlg.GetSafeHwnd())
	{
		m_ConfigAppDlg.Create(IDD_DIALOG_CONFIG, this); 
		m_ConfigAppDlg.ShowWindow(SW_SHOW);
	}
	else
	{
		if (!m_ConfigAppDlg.IsWindowVisible())
			m_ConfigAppDlg.ShowWindow(SW_SHOW);
		
		m_ConfigAppDlg.SetFocus();
		AfxMessageBox(_T("Dialog ЕСТЬ - ДАЛИ ФОКУС"),0,0); // 0 0 внимание, ОК
	}

}


LRESULT CMainFrame::OnDialogCnfClose(WPARAM wParam, LRESULT lParam) // UINT
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	//int res = AfxMessageBox(_T("Данные не сохранены!! /n Сохранить?"),MB_YESNOCANCEL | MB_ICONSTOP | MB_DEFBUTTON1,0); //Вопрос, ОК, НЕТ, СЕСЕЛ
	int res = MessageBox(_T("       Сохранить изменения?"),
				_T("                Данные не сохранены!!!"),	
				MB_YESNOCANCEL | MB_ICONSTOP | MB_DEFBUTTON1); //Вопрос, ОК, НЕТ, СЕСЕЛ
  
	switch (res)
  {
  case IDYES:
		AfxMessageBox(_T("Выбрано YES"),MB_OK | MB_ICONINFORMATION,0);
		break;
  case IDNO:
		AfxMessageBox(_T("Выбрано NO"),MB_OK | MB_ICONINFORMATION,(UINT)-1);
		ASSERT(m_ConfigAppDlg.GetSafeHwnd());
		m_ConfigAppDlg.DestroyWindow();
		break;
  case IDCANCEL:
	AfxMessageBox(_T("Выбрано IDCANCEL"),MB_OK | MB_ICONINFORMATION,(UINT)-1);
		break;
  }
	
  return 0L;
}

// Спрятать в Трей
void CMainFrame::OnHide()
{
	// TODO: добавьте свой код обработчика команд

	NOTIFYICONDATA nf;
	nf.hWnd = m_hWnd;
	nf.uID = NULL;
	
	nf.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nf.uCallbackMessage = WM_MYICONNOTIFY;
	
	//strcpy((char*)nf.szTip,(const char*)_T("АрмоператораАЛСН"));
	//nf.szTip[32] = (TCHAR)'\0'; 
	
	// Use resource string as tip if there is one
	//Под ХР дает длину в 2 раза больше
   LoadString(0,IDS_STRING_TREY101, nf.szTip, sizeof(nf.szTip)/2);
	
	//AfxLoadString
	//CString cs;
	//cs = _T("Арм оператора АЛСН")+ '\0';
	//nf.szTip[0] = (TCHAR) _T("Арм оператора АЛСН"); //+ '\0';

/*	//
	LPSTR lpszTip = (LPSTR)_T("Арм оператора АЛСН");
    if (lpszTip) 
        // hr = 
		StringCbCopyN(nf.szTip, sizeof(nf.szTip), lpszTip, 
                           sizeof(nf.szTip));
        // TODO: Add error handling for the HRESULT.
    else 
        nf.szTip[0] = (TCHAR)'\0'; 
*/


	HICON hIcon;
	hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nf.hIcon = hIcon;
	Shell_NotifyIcon(NIM_ADD,&nf);


ShowWindow(SW_HIDE);	

}

// Восстановить из трея
LRESULT CMainFrame::OnIcon(WPARAM wp, LPARAM lp)
{
	UNREFERENCED_PARAMETER(wp);
//		if (lp==512)	AfxMessageBox(_T("512")); //наведение курсора
//		if (lp==513)	AfxMessageBox(_T("513")); // левый клик 
//		if (lp==514)	AfxMessageBox(_T("514")); // левый клик WM_LBUTTONUP
//		if (lp==515)	AfxMessageBox(_T("515")); // 2-й левый клик 
//		if (lp==516)	AfxMessageBox(_T("516")); //  правый клик
//		if (lp==517)	AfxMessageBox(_T("517")); // правыый клик
//		if (lp==518)	AfxMessageBox(_T("518")); // 2-й правый клик



	// А вот 512 - это двойной щелчок.
	if (lp==515) 
	{
		ShowWindow(SW_RESTORE);
		NOTIFYICONDATA nf;
		nf.hWnd = m_hWnd;
		nf.uID = NULL;
		nf.uFlags = NIF_ICON;
		nf.uCallbackMessage = NULL;
		nf.hIcon = NULL;
		Shell_NotifyIcon(NIM_DELETE,&nf);
	}
	
	if (lp==516) 
	{
		//Загрузить контекстное меню
		CMenu ConMenu;
		if (ConMenu.LoadMenu(IDR_CONTEXT_MENU_MAIN))
		{
			CMenu* pSubMenu = ConMenu.GetSubMenu(0);
			if (pSubMenu!=NULL)
			{
				CPoint point;
				GetCursorPos(&point);
				
				//ClientToScreen(&point);
				// Отобразить контекстное меню
				//pSubMenu->TrackPopupMenu		
				pSubMenu->TrackPopupMenu(TPM_LEFTALIGN |
					TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd(),0); // point.x, point.y
			}
			else AfxMessageBox(_T("ContexMenu НЕ загружено"));
		}

	}
	return 0L;

}

void CMainFrame::OnAppUp()
{
	// TODO: добавьте свой код обработчика команд

			ShowWindow(SW_RESTORE);
		NOTIFYICONDATA nf;
		nf.hWnd = m_hWnd;
		nf.uID = NULL;
		nf.uFlags = NIF_ICON;
		nf.uCallbackMessage = NULL;
		nf.hIcon = NULL;
		Shell_NotifyIcon(NIM_DELETE,&nf);

}




void CMainFrame::OnDisco()
{
	// TODO: добавьте свой код обработчика команд
		// Доступ к функциям осциллографа с помощью DiSco API
//	DiscoAPILib ddd = new DiscoAPILib;
//	IDevice::Status(1);

//IUnknown * objfact;
//CoInitialize(NULL);
//DiscoAPILib::CoDiscoAPI;
	//const GUID CLSID_oTerminal = DiscoAPILib::CoDiscoAPI;
	//CoCreateInstance(DiscoAPILib::CoDiscoAPI,
                //0,
				//CLSCTX_INPROC_SERVER,
				//IID_IDevice,
				//IDev);
	//CoInitialize(NULL);
IDevice* device = NULL;
IOscilloscope* osc = NULL ;   //  - интерфейс осциллографа

													//IDevicePtr dev (CLSID_CoDiscoAPI);
	CoInitialize(NULL);
  // создать COM-объект и получить интерфейс устройства
 HRESULT hr = CoCreateInstance( CLSID_CoDiscoAPI,
                  NULL,
                  CLSCTX_INPROC_SERVER,
                  IID_IDevice,
                  (LPVOID*) &device );  //(void**)

 if (FAILED(hr)) AfxMessageBox(L"Ошибка создания сервера\n");
 
  // запросить интерфейс осциллографа
	hr = device->QueryInterface(IID_IOscilloscope, (LPVOID*) &osc);
	if (FAILED(hr)) AfxMessageBox(L"Ошибка создания Oscilloscope\n");
//	   dev->QueryInterface(IID_IOscilloscope, (void**) &osc);
	// проинициализировать устройство
	//dev->Init(0); //0
	BOOL res;
		res = device->Init(-1,NormalAutoUpdate);
		if (!res) 
		{
			MessageBox(L"Не удалось проинициализировать устройство",L"Диско Осциллограф",0);
			device->Release();
			CoUninitialize();
		}
		else 
		{
			
  			 // получить номер версии устройства и отобразить его в окне
			CComBSTR v;
	//		_bstr_t ver;
			//ver ver =
			v.m_str = device->GetFirmwareVersion();

//			CString ss;
//			ss.Format(L"%i",v.m_str);
			AfxMessageBox(v.m_str);
			  // Задать параметры осциллографа
  //osc->SetSamplingFrequency(100000);  // частота дискретизации в Гц

  osc->SetChannelOnOff(A, On);      // включить канал A
  osc->SetChannelOnOff(B, On);      // включить канал B
  osc->SetChannelMaxGain(A, 2);     // установить шкалу канала A 2В
  osc->SetChannelMaxGain(B, 2);     // установить шкалу канала B 2В
	
//	try
//	{
//		IDevicePtr dev (LIBID_DiscoAPILib); // CLSID_HobbyLabDiSco
//	}
//	catch (_com_error& e)
//	{
//		MessageBox(e.ErrorMessage(),0,0);
//	}
//                     device->Release();
//                     CoUninitialize();
		}
}



void CMainFrame::OnViewPut()
{
	// TODO: добавьте свой код обработчика команд

		
		if (!m_ViewPut.GetSafeHwnd())
	{
		
		m_ViewPut.Create(IDD_VIEW_PUT, &pParent); //this
		m_ViewPut.ShowWindow(SW_SHOW);
		//ShowWindow(SW_HIDE);
		ShowWindow(SW_MINIMIZE); //min 2
	}
	else
	{
		if (!m_ViewPut.IsWindowVisible()) m_ViewPut.ShowWindow(SW_SHOW);
		if (m_ViewPut.IsIconic())m_ViewPut.ShowWindow(SW_RESTORE);
		m_ViewPut.SetFocus();
		//AfxMessageBox(_T("Dialog Уже есть - Перешли"),0,0); // 0 0
		
	}


}


// Вывести текст в строке состояния
void CMainFrame::OnSetPaneText(CString txtstr)
{
	m_wndStatusBar.SetPaneText(0,txtstr,1);
	//m_wndOutput.m_wndOutputDebug.AddString(_T("Здесь отображается вывод отладки."));
}

// Выводим в вывод - отладка
void CMainFrame::OnOutputDebugAddString(CString outputstr)
{
	m_wndOutput.OnOutputDebugAddString(outputstr);
}

void CMainFrame :: OnLanguageFirst ( UINT nID ) 
{ 
	UNREFERENCED_PARAMETER(nID);
	
	//MultiLangOnClickMenu ( nID ); 
	//AfxMessageBox ( _T ("Please restart application for changes to take effect")); 
}

void CMainFrame :: OnUpdateLanguageFirst ( CCmdUI * pCmdUI ) 
{ 
	UNREFERENCED_PARAMETER(pCmdUI);
	//MultiLangUpdateMenu ( pCmdUI ); 
}

LRESULT CMainFrame :: OnTok(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	AfxMessageBox(L"Tok MainFrame");
	return 0;
}



//void CMainFrame::OnUserChanged()
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//
//	CFrameWndEx::OnUserChanged();
//}

void CMainFrame::OnUpdateTime(CCmdUI *pCmdUI)
{
	CTime t = CTime::GetCurrentTime();
	LPWSTR szTime[6]; //LPWSTR char
	int nHour = t.GetHour();
	int nMinute = t.GetMinute(); 
	// Часы считаются до 12 вместо 24
//	if (nHour > 12) nHour = nHour - 12;
	wsprintf((LPWSTR)szTime, L"%i:%02i", nHour, nMinute); // спецификатор размера "I"
	// Устанавливаем текст в панели.
	m_wndStatusBar.SetPaneText(
				m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME),
				LPCTSTR(szTime));
	pCmdUI->Enable();
}