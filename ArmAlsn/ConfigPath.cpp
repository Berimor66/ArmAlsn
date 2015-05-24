// ConfigPath.cpp: ���� ����������
//

#include "stdafx.h"
#include "ArmAlsn.h"
#include "ConfigPath.h"
#include "afxdialogex.h"

#include "Globals.h"
#include "ConfigDat.h"


// ���������� ���� CConfigPath

IMPLEMENT_DYNAMIC(CConfigPath, CDialogEx)

CConfigPath::CConfigPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigPath::IDD, pParent)
	, m_strPathDb(_T("����.accdb"))
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


// ����������� ��������� CConfigPath

void CConfigPath::OnBnClickedButtonFileDb()
{
	// TODO: �������� ���� ��� ����������� �����������
	CFileDialog	fileDialog(TRUE,NULL,L"����.accdb",NULL,
	L"������ ���� ������ MS Access(*.accdb)|*.accdb|���� ������ MS Access (*.mdb)|*.mdb|��� ����� (*.*)|*.*|",
							NULL,NULL,TRUE);
	INT_PTR result = fileDialog.DoModal();
	if (result==IDOK) 
	{
		m_strPathDb = fileDialog.GetPathName();
		if((m_strPathDb.Find(L".accdb") != -1) || (m_strPathDb.Find(L".mdb") != -1)) 
		{
			//����� ������� ���-��, ���� ��� ������ ���� � ����������� .mdb
			//AfxMessageBox(fileName);
			UpdateData(false);
			//m_gstrPathDb = m_strPathDb;
		}
	else 
		{
			//����� ������� ���-��, ���� ��� ������ ���� � ����������� .mdb
			AfxMessageBox(L"� ������ ����� ��� ���� �� ��������");

		}
	}
		
}

// ����� - ������� ����������
void CConfigPath::OnBnClickedButtonFolderWp()
{
	// TODO: �������� ���� ��� ����������� �����������
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
	// TODO: �������� ���� ��� ����������� �����������

	CFileDialog	fileDialog(TRUE,NULL,L"OziExp.exe",NULL,
							L"����� ��������(*.exe)|*.exe|",
							NULL,NULL,TRUE);
	INT_PTR result = fileDialog.DoModal();
	if (result==IDOK) 
	{
		m_strPathOz = fileDialog.GetPathName();
		if(m_strPathOz.Find(L".exe") != -1) 
		{
			//����� ������� ���-��, ���� ��� ������ ���� � ����������� .mdb
			//AfxMessageBox(fileName);
			UpdateData(false);
			//m_gstrPathOz = m_strPathOz;
		}
	else 
		{
			//����� ������� ���-��, ���� ��� ������ ���� � ����������� .mdb
			m_strPathOz = L"OziExp.exe";
			UpdateData(false);
			AfxMessageBox(L"������ �� ����������� ����");

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
	// TODO: �������� ���� ��� ����������� �����������
	UpdateData(true);  // �� ��������� ���������� � ������������ ����������
	m_gstrPathDb = m_strPathDb; // ���� ������ �� �������, � ������
	m_gstrPathWp = m_strPathWp; // ��������������� edit control
	m_gstrPathOz = m_strPathOz;

	// ��������� ������ � ���� dat
	if (UpdateData())
	{
		m_configdat.InSerialize();
	}
}


BOOL CConfigPath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �������� �������������� �������������
	// ����� ������ �� dat
	if (m_configdat.OutSerialize())
	{
		m_strPathDb = m_gstrPathDb;
		m_strPathWp = m_gstrPathWp;
		m_strPathOz = m_gstrPathOz;
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}
