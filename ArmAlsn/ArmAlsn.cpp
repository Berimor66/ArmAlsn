
// ArmAlsn.cpp : Определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "ArmAlsn.h"
#include "MainFrm.h"

#include "IpFrame.h"
#include "ArmAlsnDoc.h"
#include "ArmAlsnView.h"
#include "AlsIzmFormView.h"

#include "OscilloscopeFrm.h"
#include "OscilloscopeDoc.h"
#include "OscilloscopeView.h"

#include "AlsDbFrame.h"
#include "AlsDbDoc.h"
#include "AlsDbFormView.h"

#include "DBVListFrm.h"
#include "DBVListDoc.h"
#include "DBVListView.h"
#include "ConfigDat.h"

#include "StringFile.h"
#include "VersionNo.h"
#include "HyperLink.h"
#include "afxwin.h"
#include "afxcmn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "../MultiLangW/MultiLang.h"
///Автор: Vadun
//Чтобы CRT автоматически просматривала heap на неосвобожденные блоки памяти
//#include"crtdbg.h" 
   //INT_PTR res = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG |
			//		_CRTDBG_CHECK_ALWAYS_DF |
			//		_CRTDBG_DELAY_FREE_MEM_DF |
			//		_CRTDBG_LEAK_CHECK_DF |
			//		_CRTDBG_ALLOC_MEM_DF);  //_CRTDBG_ALLOC_MEM_DF);

//INT_PTR res = _CrtSetBreakAlloc(457); // где num - номер утечки
//TODO: Saving log here
//UNDONE: Test this value to be less, then 10
//HACK: Fix a problem.
 //// res = _CrtSetBreakAlloc(372); // где num - номер утечки
//Внимание - пример своих напоминаний
// Глобальные данные
CString	m_gstrPathSet;
//static		 
//	UINT  WM_TOK = ::RegisterWindowMessage((LPCWSTR) L"MyMessage_TOK");
LPDIRECTSOUND8        m_pDS        = NULL;
BYTE *specbuf_i;

// CArmAlsnApp

BEGIN_MESSAGE_MAP(CArmAlsnApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CArmAlsnApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW_FRAME, &CArmAlsnApp::OnFileNewFrame)
	ON_COMMAND(ID_FILE_NEW, &CArmAlsnApp::OnFileNew)
	// Стандартные команды по работе с файлами документов
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Стандартная команда настройки печати
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_OSCILLOSCOPE, &CArmAlsnApp::OnOscilloscope)
	ON_COMMAND(ID_DATABASE, &CArmAlsnApp::OnDatabase)
	ON_COMMAND(ID_IZMALSN, &CArmAlsnApp::OnIzmAlsn)
	//ON_REGISTERED_MESSAGE(WM_TOK, OnTok)
END_MESSAGE_MAP()


// создание CArmAlsnApp

CArmAlsnApp::CArmAlsnApp()
{
	EnableHtmlHelp();

	
	m_bHiColorIcons = TRUE;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CArmAlsnApp

CArmAlsnApp theApp;
// Этот идентификатор создан уникальным для вашего приложения
// Его можно изменить, если вы предпочитаете использовать какой-то определенный идентификатор

// {D77DB3AB-0C61-4008-9B42-C36AEB57B303}
static const CLSID clsid =
{ 0xD77DB3AB, 0xC61, 0x4008, { 0x9B, 0x42, 0xC3, 0x6A, 0xEB, 0x57, 0xB3, 0x3 } };

const GUID CDECL BASED_CODE _tlid =
		{ 0x90F77436, 0x35E4, 0x4994, { 0xBA, 0x97, 0xD5, 0x89, 0x73, 0x41, 0x79, 0xC3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// Глобальные переменные
BOOL		m_gOziExplorer_OnOff=0; //Признак использования OziExplorer

// инициализация CArmAlsnApp
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
BOOL CArmAlsnApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	//Чтобы CRT автоматически просматривала heap на неосвобожденные блоки памяти
	//#include"crtdbg.h" 
	//INT_PTR rs = 

	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения. В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Приложение АРМ АЛСН"));
	LoadStdProfileSettings(8);  // Загрузите стандартные параметры INI-файла (включая MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Зарегистрируйте шаблоны документов приложения. Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CMultiDocTemplate* pDocMainTemplate;
	pDocMainTemplate = new CMultiDocTemplate(
		IDR_MAINFRAME, //IDR_OSCILLOSCOPEFRAME,     //IDR_MAINFRAME,
		RUNTIME_CLASS(CArmAlsnDoc),
		RUNTIME_CLASS(CMainFrame),       // основное окно рамки SDI
		RUNTIME_CLASS(CArmAlsnView)); //CArmAlsnView  COscilloscopeView
	if (!pDocMainTemplate)
		return FALSE;
	pDocMainTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	pDocMainTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(CInPlaceFrame));
//p	m_pDocTemplate = pDocMainTemplate;
	AddDocTemplate(pDocMainTemplate);
	
	////////////////////////////////
	// Vall
	CMultiDocTemplate* pDocIzmTemplate = new CMultiDocTemplate(
		IDR_ALSIZMFRAME,
		RUNTIME_CLASS(CAlsDbDoc),  //CAlsDbDoc
		RUNTIME_CLASS(CMainFrame),       // основное окно рамки SDI  CMainFrame
		RUNTIME_CLASS(CAlsIzmFormView));
	if (!pDocIzmTemplate)
		return FALSE;
//	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
//	pDocTemplate->SetServerInfo(
//		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
//		RUNTIME_CLASS(CInPlaceFrame));
//p	m_pDocTemplate = pDocIzmTemplate;
	AddDocTemplate(pDocIzmTemplate);
	
	////////////////////////////////
	//// Базы данных
	CMultiDocTemplate* pDocDbTemplate = new CMultiDocTemplate(
		IDR_ALSDBFRAME,    //IDR_MAINFRAME,	IDR_DBVLISTFRAME		   
		RUNTIME_CLASS(CAlsDbDoc),			// 
		RUNTIME_CLASS(CAlsDbFrame),       // 
		RUNTIME_CLASS(CAlsDbFormView)); //
	if (!pDocDbTemplate)
		return FALSE;
	//	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	//	pDocTemplate->SetServerInfo(
	//		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
	//		RUNTIME_CLASS(CInPlaceFrame));
//p	m_pDocTemplate = pDocDbTemplate;
	AddDocTemplate(pDocDbTemplate);

	CMultiDocTemplate* pDocOsTemplate = new CMultiDocTemplate(
	IDR_OSCILLOSCOPEFRAME, //IDR_ALSIZMFRAME,    //IDR_MAINFRAME,	IDR_OSCILLOSCOPEFRAME
		RUNTIME_CLASS(COscilloscopeDoc),			// COscilloscopeDoc	  
		RUNTIME_CLASS(COscilloscopeFrm),			//CMainFrame COscilloscopeFrm основное окно рамки SDI CMainFrame
		RUNTIME_CLASS(COscilloscopeView));			// COscilloscopeView CArmAlsnView
	if (!pDocOsTemplate)
		return FALSE;
//	pDocOsTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
//	pDocDbTemplate->SetServerInfo(
//		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
//		RUNTIME_CLASS(CInPlaceFrame));
//p	m_pDocTemplate = pDocTemplate;
	AddDocTemplate(pDocOsTemplate);

	m_pDocTemplate = pDocMainTemplate;

// - установить главныйм фреймом 1-й фрейм
	m_pDocManager->GetFirstDocTemplatePosition();
	m_pDocManager->GetOpenDocumentCount();

	//
	//////////////////////////////
	// Подключите COleTemplateServer к шаблону документа
	//  COleTemplateServer создает новые документы от имени
	//  контейнеров OLE, выполняющих запрос с помощью информации,
	//  указанной в шаблоне документа
	m_server.ConnectTemplate(clsid, pDocMainTemplate, FALSE);
	// Зарегистрируйте все фабрики сервера OLE как работающие. Это позволит
	//  библиотекам OLE создавать объекты из других приложений
	COleTemplateServer::RegisterAll();
		// Примечание. Приложения MDI регистрируют все объекты сервера вне зависимости от наличия параметра
		//  /Embedding или /Automation в командной строке
	
	// Включить открытие исполнения DDE
	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);  // Ошибка ??????

		// получаем пути
#ifdef _v100
	m_gstrPathSet = DATA_FILE_DAT;
	m_gstrPathSet = m_gstrPathSet.Right(8);
#else
	size_t len;
	wchar_t *pValue;//
	errno_t err = _wdupenv_s(&pValue, &len,L"ProgramData"); //m_gstrPathSet =getenv("ProgramData") p20150524
	if (err) m_gstrPathSet = L"Config\\Alsn.dat";
	else
	{
		m_gstrPathSet = pValue;
		m_gstrPathSet = m_gstrPathSet + DATA_FILE_DAT;
		free(pValue); // It's OK to call free with NULL
	}
#endif
	
	//AfxMessageBox(m_gstrPathSet);

	// Читаем настройки программы
	// берем данные из dat
	CConfigDat m_configdat;
	m_configdat.OutSerialize();



	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Приложение было запущено с параметром /Embedding или /Automation.
	// Запуск приложения как сервера автоматизации.
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Не показывать главное окно
		return TRUE;
	}
	// Приложение было запущено с параметром /Register или /Unregister. Отключите
	// библиотеку типов. Иначе произойдет отмена регистрации в ProcessShellCommand().
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		UnregisterShellFileTypes();
		m_server.UpdateRegistry(OAT_INPLACE_SERVER, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// Приложение было запущено отдельно или с другими параметрами (например, /Register
	// или /Regserver). Обновите записи реестра, включая библиотеку типов.
	else
	{
		m_server.UpdateRegistry(OAT_INPLACE_SERVER);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}

	// Команды диспетчеризации, указанные в командной строке. Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	//p
	
	//////////////////////////////////////////////////
	/////////////////////
	// подключения библиотеки Multilingual к приложению
	//MultiLangInitLocalization(ID_LANGUAGE_FIRST,MAX_LANGUAGES, HKEY_CURRENT_USER, L"Software/Дор. Лаборатория А.Т.С. ЮЖД/АРМ АЛСН", L"GUILanguage");

	// Direct Sound
	// Initialize COM 	 нужен для Диско, Direct Sound
    CoInitialize( NULL );

	HRESULT	hr;
	if( FAILED( hr = DirectSoundCreate8 (NULL, &m_pDS, NULL)) )
       // return DXUT_ERR( L"DirectSoundCreate8", hr );
	AfxMessageBox(_T("Ошибка инициализации DirectX"),0,0);
	//else AfxMessageBox(_T("Инициализироавн DirectX"),0,0);


	//
	///////////////////////////////////////////////////
	//////////////////////////////////////////////////


	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// вызов DragAcceptFiles только при наличии суффикса
	//  В приложении SDI это должно произойти после ProcessShellCommand
	// Включить открытие перетаскивания
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_MailLink;
	CRichEditCtrl m_str_AboutLib; //CRichEditCtrl CEditView CEdit


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// Используемые библиотеки и компоненты	CEdit m_str_AboutLib;
	//CRichEditCtrl m_str_AboutLib2;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIL_LINK, m_MailLink);
	DDX_Control(pDX, IDC_EDIT_ABOUT, m_str_AboutLib);
//	DDX_Control(pDX, IDC_RICHEDIT21, m_str_AboutLib2);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_BN_CLICKED(IDC_MFCLINK1, &CAboutDlg::OnBnClickedMfclink1)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CArmAlsnApp::OnAppAbout()
{
	AfxInitRichEdit2();
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CArmAlsnApp настройка методов загрузки и сохранения

void CArmAlsnApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CArmAlsnApp::LoadCustomState()
{
}

void CArmAlsnApp::SaveCustomState()
{
}

// обработчики сообщений CArmAlsnApp

void CArmAlsnApp::OnFileNewFrame() 
{
	ASSERT(m_pDocTemplate != NULL);

	CDocument* pDoc = NULL;
	CFrameWnd* pFrame = NULL;

	// Создайте новый экземпляр документа, на который ссылается
	// член m_pDocTemplate.
	if (m_pDocTemplate != NULL)
		pDoc = m_pDocTemplate->CreateNewDocument();

	if (pDoc != NULL)
	{
		// если процедура создания работает, используйте ее для создания новой рамки
		// этого документа.
		pFrame = m_pDocTemplate->CreateNewFrame(pDoc, NULL);
		if (pFrame != NULL)
		{
			// Укажите заголовок и инициализируйте документ.
			// Если при инициализации документа произойдет сбой, очистите
			// окно рамки и документа.

			m_pDocTemplate->SetDefaultTitle(pDoc);
			if (!pDoc->OnNewDocument())
			{
				pFrame->DestroyWindow();
				pFrame = NULL;
			}
			else
			{
				// В противном случае обновите рамку
				m_pDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
			}
		}
	}

	// В случае сбоя очистите документ и выведите
	// пользователю сообщение.

	if (pFrame == NULL || pDoc == NULL)
	{
		delete pDoc;
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
	}
}

void CArmAlsnApp::OnFileNew() 
{

	CDocument* pDoc = NULL;
	CFrameWnd* pFrame;
	pFrame = DYNAMIC_DOWNCAST(CFrameWnd, CWnd::GetActiveWindow());
	
	if (pFrame != NULL)
		pDoc = pFrame->GetActiveDocument();

	if (pFrame == NULL || pDoc == NULL)
	{
		// Vall
		POSITION curTemplatePos = GetFirstDocTemplatePosition(); 
		while(curTemplatePos != NULL)
		{
			CDocTemplate* pTemplate = GetNextDocTemplate(curTemplatePos); 
			CString str;
			pTemplate->GetDocString(str, CDocTemplate::docName);
			//AfxMessageBox(str);
			if(str == _T("АЛСН "))
			{	
				pDoc = pTemplate->OpenDocumentFile(NULL);
				return;
			}
		}
		//AfxMessageBox(L"Why are we here ??");
		// Vall endpTemplate


		// если это первый документ, создайте его как обычный
		CWinApp::OnFileNew();
	}
	else
	{
		// В противном случае проверьте, необходимо ли сохранить изменения, а затем
		// обратитесь к документу за его повторной инициализацией.
		if (!pDoc->SaveModified())
			return;

		CDocTemplate* pTemplate = pDoc->GetDocTemplate();
		
		ASSERT(pTemplate != NULL);

		if (pTemplate != NULL)
			pTemplate->SetDefaultTitle(pDoc);
		pDoc->OnNewDocument();
	}
}



void CArmAlsnApp::OnOscilloscope()
{
	// TODO: добавьте свой код обработчика команд
	
	OnSelectTemplate( _T("Осциллограф"));

	//	==
//				POSITION curTemplatePos = GetFirstDocTemplatePosition(); 
//		CMultiDocTemplate* pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos); 
//		pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos); 
//		pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos);
//		pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos);
//		m_pDocTemplate = pDocTemplate;	
//		pDocTemplate->OpenDocumentFile(NULL);
	//		===


		//отобразить вьюху
//CMDIFrameWnd* pFrame=(CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd);
//pFrame->GetActiveFrame();
//pChild->GetActiveView();
//CPrice_exDoc* pDoc=(CPrice_exDoc*)(pChild->GetActiveDocument());



/*
	ASSERT(m_pDocTemplate != NULL);
  	CDocument* pDoc = NULL;
	CFrameWnd* pFrame = NULL;
	// Создайте новый экземпляр документа, на который ссылается
	// член m_pDocTemplate.
	if (m_pDocTemplate != NULL)
		pDoc = m_pDocTemplate->CreateNewDocument();

	// Vall

	CMultiDocTemplate*	pDocTemplate;
	POSITION curTemplatePos = GetFirstDocTemplatePosition(); 
	while(curTemplatePos != NULL)
	{
		pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos); 
		CString str;
		pDocTemplate->GetDocString(str, CDocTemplate::docName);
		//AfxMessageBox(str);
		if(str == _T("Осциллограф"))
		{
			// Создайте новый экземпляр документа, на который ссылается
			// член m_pDocTemplate.
			if (m_pDocTemplate != NULL)
				pDoc = m_pDocTemplate->CreateNewDocument();
	//////////////////////////////////////////////////////////////////////////


			if (pDoc != NULL)
			{
				// если процедура создания работает, используйте ее для создания новой рамки
				// этого документа.
				pFrame = m_pDocTemplate->CreateNewFrame(pDoc, NULL);
				if (pFrame != NULL)
				{
					// Укажите заголовок и инициализируйте документ.
					// Если при инициализации документа произойдет сбой, очистите
					// окно рамки и документа.

					m_pDocTemplate->SetDefaultTitle(pDoc);
					if (!pDoc->OnNewDocument())
					{
						pFrame->DestroyWindow();
						pFrame = NULL;
					}
					else
					{
						// В противном случае обновите рамку
						m_pDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
					}
				}
			}

			// В случае сбоя очистите документ и выведите
			// пользователю сообщение.

			if (pFrame == NULL || pDoc == NULL)
			{
				delete pDoc;
				AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
			}
   /////////////////////////////////////////////////////////////////////////
			//pDoc = pDocTemplate->OpenDocumentFile(NULL);
			//pDocTemplate->SetDefaultTitle(pDoc);
			return;
		}
	}
	//AfxMessageBox(L"Why are we here ??");
	// Vall endpTemplate
		

	//CDocument* pDoc = NULL;
	
	if (pDoc != NULL)
	{
		// если процедура создания работает, используйте ее для создания новой рамки
		// этого документа.
		pFrame = m_pDocTemplate->CreateNewFrame(pDoc, NULL);
		if (pFrame != NULL)
		{
			// Укажите заголовок и инициализируйте документ.
			// Если при инициализации документа произойдет сбой, очистите
			// окно рамки и документа.

			m_pDocTemplate->SetDefaultTitle(pDoc);
			if (!pDoc->OnNewDocument())
			{
				pFrame->DestroyWindow();
				pFrame = NULL;
			}
			else
			{
				// В противном случае обновите рамку
				m_pDocTemplate->InitialUpdateFrame(pFrame, pDoc, TRUE);
			}
		}
	}

	// В случае сбоя очистите документ и выведите
	// пользователю сообщение.

	if (pFrame == NULL || pDoc == NULL)
	{
		delete pDoc;
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
	}
*/
}

void CArmAlsnApp::OnDatabase()
{
	OnSelectTemplate( _T("База"));
	// TODO: добавьте свой код обработчика команд
/*
	CMultiDocTemplate* pDocTemplate;
	
	// Vall
//	CMultiDocTemplate*	pTemplate;
	POSITION curTemplatePos = GetFirstDocTemplatePosition(); 
	while(curTemplatePos != NULL)
	{
		pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos); 
		CString str;
		pDocTemplate->GetDocString(str, CDocTemplate::docName);
		//AfxMessageBox(str);
		if(str == _T("База"))
		{	
			pDocTemplate->OpenDocumentFile(NULL);
			return;
		}
	}
	//AfxMessageBox(L"Why are we here ??");
	// Vall endpTemplate
///=====
	 //получаем первый шаблон-->>делай приведение типов чтобы не злить компилер :))
	pDocTemplate = (CMultiDocTemplate*) m_pDocManager->GetNextDocTemplate(pos);
	pDocTemplate = (CMultiDocTemplate*) m_pDocManager->GetNextDocTemplate(pos);
	pDocTemplate = (CMultiDocTemplate*) m_pDocManager->GetNextDocTemplate(pos);
//	m_pDocTemplate = pDocTemplate;
//	m_pDocManager->GetOpenDocumentCount();
	pDocTemplate->OpenDocumentFile(NULL);
//	pView->GetParentFrame()->ActivateFrame();
//	AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
*/
	
}


//CFrameWnd* pOther;
void CArmAlsnApp::OnSelectTemplate(CString TemplateName)
{
		//CMultiDocTemplate* pDocTemplate;
	
	// Vall
//	CMultiDocTemplate*	pTemplate;
	POSITION curTemplatePos = GetFirstDocTemplatePosition(); 
	while(curTemplatePos != NULL)
	{
		CMultiDocTemplate* pDocTemplate = (CMultiDocTemplate*) GetNextDocTemplate(curTemplatePos); 
	//	pDocTemplate->OpenDocumentFile(NULL);
		CString str;
		pDocTemplate->GetDocString(str, CDocTemplate::docName);
		//AfxMessageBox(str);
		if(str == TemplateName)
		{	
//				m_pDocTemplate = pDocTemplate;
	//			m_pDocManager->GetOpenDocumentCount();
	/////////////////////////////////////////////////////////
//					POSITION posDoc = NULL, posView = NULL;
//	CDocument *pDoc = NULL;
		//posDoc = pDocTemplate->GetFirstDocPosition();  GetFirstViewPosition();

	//posView = pDocTemplate->GetFirstDocPosition();
//	posView = pDoc->GetFirstViewPosition();
/* pelix
				//////////////////
			CDocument *pDoc = pDocTemplate->OpenDocumentFile(NULL);
	posView =		pDoc->GetFirstViewPosition();
	//pView->GetParentFrame()->ActivateFrame(SW_SHOW);
		CView* pView =	pDoc->GetNextView(posView);
///		pView->GetParentFrame()->ActivateFrame(SW_SHOW);
///		pView->GetParent()->ActivateTopParent();
		HWND hWnd = pView->GetSafeHwnd();
		SetWindowText(hWnd, L"TEST");
		SetWindowText(GetParent(hWnd), L"TEST1"); 
		BringWindowToTop(GetParent(hWnd));
	//	if(pView != NULL) (pView->GetParentFrame())->ActivateFrame(SW_SHOW);
		//	pDoc->GetNextView(posView);
		//			if(pView != NULL) (pView->GetParentFrame())->ActivateFrame(SW_SHOW);
	//		pDoc->GetNextView(posView);
		//			if(pView != NULL) (pView->GetParentFrame())->ActivateFrame(SW_SHOW);
//	CView* pView;
//	pView->GetParentFrame()->ActivateFrame();
*/			m_pDocTemplate = pDocTemplate;	
			CDocument *pDoc = pDocTemplate->OpenDocumentFile(NULL);
	UNREFERENCED_PARAMETER(pDoc);
			//pDoc->SetTitle(L"8999999999");
			return;
		}
	}

}


void CArmAlsnApp::OnIzmAlsn()
{
	// TODO: добавьте свой код обработчика команд

		// получить доступ к объекту класса CMainFrame можно так:
	CMainFrame *pMainFrame = (CMainFrame*)(::AfxGetMainWnd()); 
	//Запустить окно ассиметрии
	pMainFrame->OnViewPut();
	// и минимизировать его
//	pMainFrame->m_ViewPut.ShowWindow(SW_MINIMIZE); //3-мах

	OnSelectTemplate( _T("Измерение"));
		
}
//---------------------------------------------------------------------
time_t gettimespan(LONG lDays, int nHours, int nMins, int nSecs) throw()
{
 	time_t tm;
	tm = nSecs + 60* (nMins + 60* (nHours + __int64(24) * lDays));
	return tm;
}
struct tm getdatebyspan(int Year,int lDays)
{
	struct tm tmbase ={0,};
	struct tm tmdate;
	time_t tibase;
	time_t timespan;
	UNREFERENCED_PARAMETER(timespan);

	//Make Year/01/01 base date
	tmbase.tm_year = Year - 1900;
	tmbase.tm_mon = 0;//0 to 11
	tmbase.tm_mday = 1;// 1 to 31
	tibase = mktime(&tmbase);
	timespan =  gettimespan(lDays,0,0,0);
	tibase += timespan;

	localtime_s(&tmdate,&tibase);
	return tmdate;
}


char * getdatetime(int which,tm *dtinfo)
{
	static char szdatetime[80]={0,};

	time_t ltm;
	time_t timespan;
	UNREFERENCED_PARAMETER(timespan);
	struct tm psttm;
	ltm = time(NULL);//їАґГіЇВҐё¦ ±ёЗСґЩ.
	localtime_s(&psttm,&ltm);
	*dtinfo = psttm;
	dtinfo->tm_year += 1900;
	dtinfo->tm_mon  += 1;

	//struct tm t2;
	//t2 = getdatebyspan(2007,302);//Get Date by Daily Offset from start of Year.(01/01)

	if(which == -1)
		wsprintf((LPWSTR)szdatetime,_T("%04d-%02d-%02d %02d:%02d:%02d"),
		psttm.tm_year+1900,psttm.tm_mon+1,psttm.tm_mday,
		psttm.tm_hour,psttm.tm_min,psttm.tm_sec);
	else if(which == 0)
		wsprintf((LPWSTR)szdatetime,_T("%04d-%02d-%02d"),psttm.tm_year+1900,psttm.tm_mon+1,psttm.tm_mday);
	else if(which == 1)
		wsprintf((LPWSTR)szdatetime,_T("%02d:%02d:%02d"),psttm.tm_hour,psttm.tm_min,psttm.tm_sec);

	return szdatetime;
}

//static DWORD_PTR CALLBACK 
//				MyStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
//{
//   CFile* pFile = (CFile*) dwCookie;
//
//   *pcb = pFile->Read(pbBuff, cb);
//
//   return 0;
//}
#include <Richedit.h>
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	char verfile[160];
//	char verprdt[80];
	//char baseyear[80];
#ifdef _WIN64
	_stprintf_s((LPWSTR)verfile, 160, L"АРМ АЛСН 64 бит, версии:\nфайла - %s,\nпродукта - %s",_T(VERSION_FILESTR),_T(VERSION_PRODUCTSTR));
#else
	_stprintf_s((LPWSTR)verfile, 160, L"АРМ АЛСН, версии:\nфайла - %s,\nпродукта - %s",_T(VERSION_FILESTR),_T(VERSION_PRODUCTSTR));
	//wsprintf((LPWSTR)verprdt, L"Версия продукта: %s",_T(VERSION_PRODUCTSTR));
#endif
	SetDlgItemText(IDC_VERFILE,(LPCTSTR)verfile);
	//SetDlgItemText(IDC_VERPRDT,(LPCTSTR)verprdt);
	#ifdef VERSION_BASEYEAR
	if(VERSION_BASEYEAR != 0)
	{
		char buff[160];
		char yearindex[3];
		char dayindex[4];
		int yi,di,year ;

		sprintf_s(buff,"%05d",VERSION_BUILDNO); // sprintf(buff,"%05d",VERSION_BUILDNO);
		strncpy_s(dayindex,buff+2,3);
		yi = atoi(yearindex);
		di = atoi(dayindex);

		struct tm today;
		getdatetime(0,&today);

		struct tm t2;
		t2 = getdatebyspan(today.tm_year,di);//Get Date by Daily Offset from start of Year.(01/01)
		year = VERSION_BASEYEAR + yi;

		wsprintf((LPWSTR)buff,L"(C)  Дорожная лаборатория \nА.Т. и С.  Южной ж.д. \n%5dг. - %02d-%02d-%04dг.",VERSION_BASEYEAR,t2.tm_mday,t2.tm_mon + 1,year); 
		SetDlgItemText(IDC_DAILYBASIS,(LPCTSTR)buff);

		//wsprintf((LPWSTR)baseyear,L" %d",VERSION_BASEYEAR);
		//SetDlgItemText(IDC_BASEYEAR,(LPCTSTR)baseyear);
	}
	#endif

	///////////
	m_MailLink.SetURL(_T("mailto:pelix66@mail.ru"));

	///////
	// Ввыводим текст в окошко
	//Вариант 1
#ifdef _v100
	CFile file(L"КомпонентыU.txt", CFile::modeRead | CFile::typeText); //typeUnicode typeText typeBinary
#else
	CFile file(L"КомпонентыU.txt", CFile::modeRead | CFile::typeUnicode); //typeUnicode typeText typeBinary
#endif
	int n = (int)file.GetLength();
	unsigned char *p = (unsigned char *)malloc(n+1); //unsigned char  TBYTE +1
	//memchr(p,_T('\0'),n);
	if (p)
	{
		file.Read(p, n);
		p[n] =  TEXT('\0');
		m_str_AboutLib.SetWindowText((LPCTSTR)p);
//???		
		free(p); 
	}
	file.Close();


	
	//Вариант 2 (не работает с Unicode)
	//CFileException* feError;
	//CString sss, sss1;
	//CStringFile strFile;
	//strFile.Open(L"Компоненты.txt",feError,0);

	//for (INT_PTR i=0; strFile.GetNextLine(sss)>0;i++) 
	//{
	//	int ndx = m_str_AboutLib.GetWindowTextLength();
	//	m_str_AboutLib.SetFocus();
	//	m_str_AboutLib.SendMessage(EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
	//	m_str_AboutLib.SendMessage(EM_REPLACESEL, 0, (LPARAM) ((LPSTR) sss.GetBuffer()));
	//	m_str_AboutLib.SendMessage(EM_REPLACESEL, 0, (LPARAM) ((LPSTR) L"\n\n"));
	//}
	//strFile.Close();
	
//	m_str_AboutLib.SetBackgroundColor(FALSE, RGB(255,0, 0));  // Use red as the background color. 
//	m_str_AboutLib.AnimateWindow(400 ,AW_SLIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


//void CAboutDlg::OnBnClickedMfclink1()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}


BOOL CAboutDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: добавьте специализированный код или вызов базового класса
	int nn = m_str_AboutLib.GetWindowTextLength();
	m_str_AboutLib.SetSel(nn-30,nn);
	m_str_AboutLib.ReplaceSel(L"Пелых",0);

	return CDialog::PreCreateWindow(cs);
}
