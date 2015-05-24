// ConfigPath.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ConfigPath.h"
#include "afxdialogex.h"

#include "Globals.h"
#include "ConfigDat.h"


// диалоговое окно CConfigPath

IMPLEMENT_DYNAMIC(CConfigPath, CDialogEx)

CConfigPath::CConfigPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigPath::IDD, pParent)
	, m_strPathDb(_T("Алсн.accdb"))
	, m_strPathWp(_T("OziExplorer\\Data"))
	, m_strPathOz(_T("OziExplorer\\OziExp.exe"))
{

}

CConfigPath::~CConfigPath()
{
}

void CConfigPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH_DB,m_strPathDb);
	DDX_Text(pDX, IDC_EDIT_PATH_WP,m_strPathWp);
	DDX_Text(pDX, IDC_EDIT_PATH_OZ,m_strPathOz);
}


BEGIN_MESSAGE_MAP(CConfigPath, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FILE_DB, &CConfigPath::OnBnClickedButtonFileDb)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER_WP, &CConfigPath::OnBnClickedButtonFolderWp)
	ON_BN_CLICKED(IDC_BUTTON_FILE_OZ, &CConfigPath::OnBnClickedButtonFileOz)
	ON_BN_CLICKED(IDCONSAVE, &CConfigPath::OnBnClickedConsave)
END_MESSAGE_MAP()


// обработчики сообщений CConfigPath

void CConfigPath::OnBnClickedButtonFileDb()
{
	// TODO: добавьте свой код обработчика уведомлений
	CFileDialog	fileDialog(TRUE,NULL,L"Алсн.accdb",NULL,
	L"Сжатая база данных MS Access(*.accdb)|*.accdb|База данных MS Access (*.mdb)|*.mdb|Все файлы (*.*)|*.*|",
							NULL,NULL,TRUE);
	INT_PTR result = fileDialog.DoModal();
	if (result==IDOK) 
	{
		m_strPathDb = fileDialog.GetPathName();
		if((m_strPathDb.Find(L".accdb") != -1) || (m_strPathDb.Find(L".mdb") != -1)) 
		{
			//здесь делаешь что-то, если был открыт файл с расширением .mdb
			//AfxMessageBox(fileName);
			UpdateData(false);
			//m_gstrPathDb = m_strPathDb;
		}
	else 
		{
			//здесь делаешь что-то, если был открыт файл с расширением .mdb
			AfxMessageBox(L"С данным типом баз пока не работаем");

		}
	}
		
}

// Папка - выбрать стандартно
void CConfigPath::OnBnClickedButtonFolderWp()
{
	// TODO: добавьте свой код обработчика уведомлений
#ifdef _v100
	CFolderPickerDialog folderDialog(NULL,NULL,NULL,NULL);
#else
	CFolderPickerDialog folderDialog(NULL,NULL,NULL,NULL,NULL);
#endif
	INT_PTR result = folderDialog.DoModal();
	if (result==IDOK) 
	{
		m_strPathWp = folderDialog.GetPathName();
		//AfxMessageBox(folderName);
		UpdateData(false);
		//m_gstrPathWp = m_strPathWp;
	}
}

void CConfigPath::OnBnClickedButtonFileOz()
{
	// TODO: добавьте свой код обработчика уведомлений

	CFileDialog	fileDialog(TRUE,NULL,L"OziExp.exe",NULL,
							L"Файлы программ(*.exe)|*.exe|",
							NULL,NULL,TRUE);
	INT_PTR result = fileDialog.DoModal();
	if (result==IDOK) 
	{
		m_strPathOz = fileDialog.GetPathName();
		if(m_strPathOz.Find(L".exe") != -1) 
		{
			//здесь делаешь что-то, если был открыт файл с расширением .mdb
			//AfxMessageBox(fileName);
			UpdateData(false);
			//m_gstrPathOz = m_strPathOz;
		}
	else 
		{
			//здесь делаешь что-то, если был открыт файл с расширением .mdb
			m_strPathOz = L"OziExp.exe";
			UpdateData(false);
			AfxMessageBox(L"Выбран не исполняемый файл");

		}
	}
		
}

/*
void CConfigPath::Serialize(CArchive& ar)
{
	m_configdat.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
*/

void CConfigPath::OnBnClickedConsave()
{ 
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);  // Из элементов управления в компонентную переменную
	m_gstrPathDb = m_strPathDb; // Если меняли не кнопкой, а прямым
	m_gstrPathWp = m_strPathWp; // редактированием edit control
	m_gstrPathOz = m_strPathOz;

	// Сохранить данные в файл dat
	if (UpdateData())
	{
		m_configdat.InSerialize();
	}
}


BOOL CConfigPath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	// берем данные из dat
	if (m_configdat.OutSerialize())
	{
		m_strPathDb = m_gstrPathDb;
		m_strPathWp = m_gstrPathWp;
		m_strPathOz = m_gstrPathOz;
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
