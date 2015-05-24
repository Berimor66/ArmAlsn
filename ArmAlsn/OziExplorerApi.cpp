#include "stdafx.h"
#include "OziExplorerApi.h"
#include <io.h>

///////////////////////////////////////////////////////////////////////
// contains the declarations for the OziExplorer API dll  (OziAPI.dll)
// call the function  LoadOziApiDll() from your own program
// returns  0 if successful
//         -1 if the OziAPI.dll was not found
//         -2 if a function inside the DLL could not be assigned
///////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "OziExplorerApi.h"

HINSTANCE oziApiDll;           // Handle to DLL

ToziCloseApi oziCloseApi;

ToziGetExePath oziGetExePath;

ToziCenterMapAtPosition oziCenterMapAtPosition;
ToziCenterMapAtPositionWithMark oziCenterMapAtPositionWithMark;
ToziCloseProgram oziCloseProgram;
ToziFindOzi oziFindOzi;
ToziGetMapDatum oziGetMapDatum;

ToziShowTrack oziShowTrack;
ToziShowAllTracks oziShowAllTracks;
ToziConvertDatum oziConvertDatum;

ToziClearWPs oziClearWPs;
ToziClearEVs oziClearEVs;
ToziClearRTEs oziClearRTEs;
ToziClearTRKs oziClearTRKs;
ToziClearTRK oziClearTRK;
ToziClearPTs oziClearPTs;
ToziClearMFs oziClearMFs;
ToziClearMCs oziClearMCs;

ToziCreateWP oziCreateWP;
ToziCreateMF oziCreateMF;
ToziCreateMC oziCreateMC;

ToziMapSingleClickON oziMapSingleClickON;
ToziMapSingleClickOFF oziMapSingleClickOFF ;
ToziMapDblClickON oziMapDblClickON;
ToziMapDblClickOFF oziMapDblClickOFF;
ToziObjectClickON oziObjectClickON;
ToziObjectClickOFF oziObjectClickOFF;

ToziLoadMap oziLoadMap;
ToziSaveMap oziSaveMap;

ToziLoadWPfile oziLoadWPfile;
ToziLoadRTEfile oziLoadRTEfile;
ToziLoadTRKfile oziLoadTRKfile;

ToziStartMMserial oziStartMMserial;


ToziChangeTRKcolor oziChangeTRKcolor;

ToziGps2NavWp oziGps2NavWp;

ToziOedometer1ON oziOedometer1ON;
	//ToziOedometer1OFF oziOedometer1OFF;	// Выключить
	//ToziOedometer1Reset oziOedometer1Reset;	// Сбросить на 0
	//ToziOedometer1Set oziOedometer1Set;// Установить
	//ToziOedometer1UP oziOedometer1UP;		// На увеличение
	//ToziOedometer1DOWN oziOedometer1DOWN;	// На Уменьшение

//these are for multi tracking
ToziMTStartMultiTrack oziMTStartMultiTrack;
ToziMTStopMultiTrack oziMTStopMultiTrack;
ToziMTSendPosition oziMTSendPosition;
ToziMTloadIDsON oziMTloadIDsON;
ToziMTloadIDsOFF oziMTloadIDsOFF;


////////////////////////////////////////////
// call this function to load the oziAPI.dll
// and set up the function calls
////////////////////////////////////////////

int LoadOziApiDll(void)
{

oziApiDll = LoadLibrary(L"oziapi.dll");
if (oziApiDll == NULL)  {return -1;}

oziCloseApi = (ToziCloseApi)GetProcAddress(oziApiDll,"oziCloseApi");
if (!oziCloseApi) 
{
	AfxMessageBox(L"Ошибка dll, не найдена функция oziCloseApi");
	FreeLibrary(oziApiDll);
	return -2;
}


oziGetExePath = (ToziGetExePath)GetProcAddress(oziApiDll,"oziGetExePath");
if (!oziGetExePath) { FreeLibrary(oziApiDll);return -2;}

oziCenterMapAtPosition = (ToziCenterMapAtPosition)GetProcAddress(oziApiDll,"oziCenterMapAtPosition");
if (!oziCenterMapAtPosition) { FreeLibrary(oziApiDll);return -2;}

oziCenterMapAtPositionWithMark = (ToziCenterMapAtPositionWithMark)GetProcAddress(oziApiDll,"oziCenterMapAtPositionWithMark");
if (!oziCenterMapAtPositionWithMark) { FreeLibrary(oziApiDll);return -2;}

oziCloseProgram = (ToziCloseProgram)GetProcAddress(oziApiDll,"oziCloseProgram");
if (!oziCloseProgram) { FreeLibrary(oziApiDll);return -2;}

oziFindOzi = (ToziFindOzi)GetProcAddress(oziApiDll,"oziFindOzi");
if (!oziFindOzi) { FreeLibrary(oziApiDll);return -2;}

oziShowTrack = (ToziShowTrack)GetProcAddress(oziApiDll,"oziShowTrack");
if (!oziShowTrack) { FreeLibrary(oziApiDll);return -2;}



oziShowAllTracks = (ToziShowAllTracks)GetProcAddress(oziApiDll,"oziShowAllTracks");
if (!oziShowAllTracks) { FreeLibrary(oziApiDll);return -2;}



oziGetMapDatum = (ToziGetMapDatum)GetProcAddress(oziApiDll,"oziGetMapDatum");
if (!oziGetMapDatum) { FreeLibrary(oziApiDll);return -2;}

oziConvertDatum = (ToziConvertDatum)GetProcAddress(oziApiDll,"oziConvertDatum");
if (!oziConvertDatum) { FreeLibrary(oziApiDll);return -2;}

oziClearWPs = (ToziClearWPs)GetProcAddress(oziApiDll,"oziClearWPs");
if (!oziClearWPs) { FreeLibrary(oziApiDll);return -2;}

oziClearEVs = (ToziClearEVs)GetProcAddress(oziApiDll,"oziClearEVs");
if (!oziClearEVs) { FreeLibrary(oziApiDll);return -2;}

oziClearRTEs = (ToziClearRTEs)GetProcAddress(oziApiDll,"oziClearRTEs");
if (!oziClearRTEs) { FreeLibrary(oziApiDll);return -2;}

oziClearTRKs = (ToziClearTRKs)GetProcAddress(oziApiDll,"oziClearTRKs");
if (!oziClearTRKs) { FreeLibrary(oziApiDll);return -2;}

oziClearTRK = (ToziClearTRK)GetProcAddress(oziApiDll,"oziClearTRK");
if (!oziClearTRK) { FreeLibrary(oziApiDll);return -2;}

oziClearPTs = (ToziClearPTs)GetProcAddress(oziApiDll,"oziClearPTs");
if (!oziClearPTs) { FreeLibrary(oziApiDll);return -2;}

oziClearMFs = (ToziClearMFs)GetProcAddress(oziApiDll,"oziClearMFs");
if (!oziClearMFs) { FreeLibrary(oziApiDll);return -2;}

oziClearMCs = (ToziClearMCs)GetProcAddress(oziApiDll,"oziClearMCs");
if (!oziClearMCs) { FreeLibrary(oziApiDll);return -2;}

oziCreateWP = (ToziCreateWP)GetProcAddress(oziApiDll,"oziCreateWP");
if (!oziCreateWP) { FreeLibrary(oziApiDll);return -2;}

oziCreateMF = (ToziCreateMF)GetProcAddress(oziApiDll,"oziCreateMF");
if (!oziCreateMF) { FreeLibrary(oziApiDll);return -2;}

oziCreateMC = (ToziCreateMC)GetProcAddress(oziApiDll,"oziCreateMC");
if (!oziCreateMC) { FreeLibrary(oziApiDll);return -2;}

oziMapSingleClickON = (ToziMapSingleClickON)GetProcAddress(oziApiDll,"oziMapSingleClickON");
if (!oziMapSingleClickON) { FreeLibrary(oziApiDll);return -2;}

oziMapSingleClickOFF = (ToziMapSingleClickOFF)GetProcAddress(oziApiDll,"oziMapSingleClickOFF");
if (!oziMapSingleClickOFF) { FreeLibrary(oziApiDll);return -2;}

oziMapDblClickON = (ToziMapDblClickON)GetProcAddress(oziApiDll,"oziMapDblClickON");
if (!oziMapDblClickON) { FreeLibrary(oziApiDll);return -2;}

oziMapDblClickOFF = (ToziMapDblClickOFF)GetProcAddress(oziApiDll,"oziMapDblClickOFF");
if (!oziMapDblClickOFF) { FreeLibrary(oziApiDll);return -2;}

oziObjectClickON = (ToziObjectClickON)GetProcAddress(oziApiDll,"oziObjectClickON");
if (!oziObjectClickON) { FreeLibrary(oziApiDll);return -2;}

oziObjectClickOFF = (ToziObjectClickOFF)GetProcAddress(oziApiDll,"oziObjectClickOFF");
if (!oziObjectClickOFF) { FreeLibrary(oziApiDll);return -2;}

oziLoadMap = (ToziLoadMap)GetProcAddress(oziApiDll,"oziLoadMap");
if (!oziLoadMap) { FreeLibrary(oziApiDll);return -2;}

oziSaveMap = (ToziSaveMap)GetProcAddress(oziApiDll,"oziSaveMap");
if (!oziSaveMap) { FreeLibrary(oziApiDll);return -2;}

oziLoadWPfile = (ToziLoadWPfile)GetProcAddress(oziApiDll,"oziLoadWPfile");
if (!oziLoadWPfile) { FreeLibrary(oziApiDll);return -2;}

oziLoadRTEfile = (ToziLoadRTEfile)GetProcAddress(oziApiDll,"oziLoadRTEfile");
if (!oziLoadRTEfile) { FreeLibrary(oziApiDll);return -2;}


oziLoadTRKfile = (ToziLoadTRKfile)GetProcAddress(oziApiDll,"oziLoadTRKfile");
if (!oziLoadTRKfile) { FreeLibrary(oziApiDll);return -2;}

	oziStartMMserial = (ToziStartMMserial)GetProcAddress(oziApiDll,"oziStartMMserial");
	if (!oziStartMMserial) { FreeLibrary(oziApiDll);return -2;}

oziChangeTRKcolor = (ToziChangeTRKcolor)GetProcAddress(oziApiDll,"oziChangeTRKcolor");
if (!oziChangeTRKcolor) { FreeLibrary(oziApiDll);return -2;}
//
oziGps2NavWp = (ToziGps2NavWp)GetProcAddress(oziApiDll,"oziGps2NavWp");
if (!oziGps2NavWp) { FreeLibrary(oziApiDll);return -2;}

//
oziMTStartMultiTrack = (ToziMTStartMultiTrack)GetProcAddress(oziApiDll,"oziMTStartMultiTrack");
if (!oziMTStartMultiTrack) { FreeLibrary(oziApiDll);return -2;}

oziMTStopMultiTrack = (ToziMTStopMultiTrack)GetProcAddress(oziApiDll,"oziMTStopMultiTrack");
if (!oziMTStopMultiTrack) { FreeLibrary(oziApiDll);return -2;}

oziMTSendPosition = (ToziMTSendPosition)GetProcAddress(oziApiDll,"oziMTSendPosition");
if (!oziMTSendPosition) { FreeLibrary(oziApiDll);return -2;}

oziMTloadIDsON = (ToziMTloadIDsON)GetProcAddress(oziApiDll,"oziMTloadIDsON");
if (!oziMTloadIDsON) { FreeLibrary(oziApiDll);return -2;}

oziMTloadIDsOFF = (ToziMTloadIDsOFF)GetProcAddress(oziApiDll,"oziMTloadIDsOFF");
if (!oziMTloadIDsOFF) { FreeLibrary(oziApiDll);return -2;}

	// Пройденный путь
	///
	oziOedometer1ON = (ToziOedometer1ON)GetProcAddress(oziApiDll,"oziOedometer1ON");
	if (!oziOedometer1ON) { FreeLibrary(oziApiDll);return -2;}
	//
	//oziOedometer1OFF = (ToziOedometer1OFF)GetProcAddress(oziApiDll,"oziOedometer1OFF");
	//if (!oziOedometer1OFF) { FreeLibrary(oziApiDll);return -2;}

	//oziOedometer1Reset = (ToziOedometer1Reset)GetProcAddress(oziApiDll,"oziOedometer1Reset");
	//if (!oziOedometer1Reset) { FreeLibrary(oziApiDll);return -2;}

	//oziOedometer1Set = (ToziOedometer1Set)GetProcAddress(oziApiDll,"oziOedometer1Set");
	//if (!oziOedometer1Set) { FreeLibrary(oziApiDll);return -2;}

	//oziOedometer1UP = (ToziOedometer1UP)GetProcAddress(oziApiDll,"oziOedometer1UP");
	//if (!oziOedometer1UP) { FreeLibrary(oziApiDll);return -2;}

	//oziOedometer1DOWN = (ToziOedometer1DOWN)GetProcAddress(oziApiDll,"oziOedometer1DOWN");
	//if (!oziOedometer1DOWN) { FreeLibrary(oziApiDll);return -2;}

return 0;

}




COziExplorerApi::COziExplorerApi(void)
{
	//LoadOziApiDll();
	if (LoadOziApiDll()!=0) 
	{
		OziExplorerIsRun = false;
		AfxMessageBox(L"OziAPI.dll не загружена");
	}
	else
	{
		OziExplorerIsRun = true;
	}
}


COziExplorerApi::~COziExplorerApi(void)
{
	oziCloseApi();
	FreeLibrary(oziApiDll);
}

int COziExplorerApi::CheckOziExplorerRunning(void)
{

	return oziFindOzi();
}

int COziExplorerApi::StartMovingMapSerial()
{
		return oziStartMMserial();
}

int COziExplorerApi::ClearAllWaypoints(void)
{
	return oziClearWPs();
}
// Загрузить пуевые точки
int COziExplorerApi::LoadWaypoint(CString* sss)
{
	CString wpfileW = *sss;  
	LPSTR WpFileName = (LPSTR) malloc(100);
	int res=0;
	wpfileW = m_gstrPathWp + L"\\км столбы " + wpfileW + L".wpt"; // полный путь файла
	strcpy_s(WpFileName,(rsize_t)100,(CStringA) wpfileW);
	
	if (_access_s(WpFileName,0)) // если файла нет - проверяем обратный маршрут
	{
		AfxMessageBox (L"Файл путевых точек: " + wpfileW  + L" не найден");
		// Переворачиваем маршрут
		wpfileW = *sss;
		wpfileW = wpfileW.Right(wpfileW.Find(L'-')-1) + L" - "+ wpfileW.Left(wpfileW.Find(L'-'));
		wpfileW.Trim(_T(' '));
		wpfileW = m_gstrPathWp + L"\\км столбы " + wpfileW + L".wpt";
		strcpy_s(WpFileName,(rsize_t)100,(CStringA) wpfileW);
		if (_access_s(WpFileName,0)) // если файла нет - выходим
		{
			free(WpFileName);
			AfxMessageBox (L"Файл путевых точек: " + wpfileW  + L" не найден");
			return -1;
		}
	}
	res = oziLoadWPfile(&WpFileName); //&WpFileName
	free(WpFileName);
	return res;  // 0 при удаче
}

int COziExplorerApi::LoadRoute(CString* sss)
{
	CString rfileW = *sss;
	LPSTR WpFileName = (LPSTR) malloc((rsize_t)100);  // (rsize_t) не нужно, но в следующем
	int res=0;
	rfileW =  m_gstrPathWp + L"\\" + rfileW + L".rte"; // полный путь файла
	strcpy_s(WpFileName,(rsize_t)100,(CStringA) rfileW);
	if (_access_s(WpFileName,0)) // если файла нет - выходим
	{
		free(WpFileName);
		AfxMessageBox (L"Файлы путевых точек: " + rfileW + L" или " + rfileW + L" не найдены");
		return -1;
	}
	res = oziLoadRTEfile(&WpFileName);
	free(WpFileName);
	return res; // 0 при удаче
}

int COziExplorerApi::GetNavWp(CString* sss)
{
	LPSTR wp, wpn;
	double mm, vv;
	CString ss1, ss2;
	if (OziExplorerIsRun)
	{
		int	return1 = oziGps2NavWp(&wp,&wpn,&mm,&vv);
		ss1 = wp; // ANSI -> Unicode
		ss2 = wpn;
		sss->Format(L"%s %s %.3f км",ss1,ss2,mm/1000); //mm в км
		return return1;
	}
	return -1;
}

int COziExplorerApi::ShowTrack(int n)
{
		return oziShowTrack(&n);
}

//////////////////////////////////////////////////////////////////////////////////////
/////
//int COziExplorerApi::OedometerON(int n, double* meter, int* Up)
//{
//	typedef int (CALLBACK* ToziOedometerSet)(int *);
//	typedef int (CALLBACK* ToziOedometerInc)(void);		// На увеличение/Уменьшение
//	ToziOedometerSet oziOedometerSet;
//	ToziOedometerInc oziOedometerInc;
//
//	int res=-1;
//	switch(n)
//	{
//		case 1 :
//			oziOedometerSet = (ToziOedometerSet)GetProcAddress(oziApiDll,"oziOedometer1Set");
//			if (*Up==1) 
//			{
//				oziOedometerInc = (ToziOedometerInc)GetProcAddress(oziApiDll,"oziOedometer1UP");
//			}
//			else oziOedometerInc = (ToziOedometerInc)GetProcAddress(oziApiDll,"oziOedometer1DOWN");
//			res = oziOedometer1ON((int*)& Oedometer1);
//			res;
//
//			break;
//		case 2 :
//			oziOedometerSet = (ToziOedometerSet)GetProcAddress(oziApiDll,"oziOedometer2Set");
//			if (*Up==1) 
//			{
//				oziOedometerInc = (ToziOedometerInc)GetProcAddress(oziApiDll,"oziOedometer2UP");
//			}
//			else oziOedometerInc = (ToziOedometerInc)GetProcAddress(oziApiDll,"oziOedometer2DOWN");
////			res = oziOedometer2ON((int*)& Oedometer2);
//			break;
//		default:
//			return res; // -1 Ошибка выбора  путимера
//	}
//
//	if (res) return res;
//	res = oziOedometerInc();
//	if (res) return res;
////	res = oziOedometerSet(meter);
////	if (res) return res;
//	double ds = 300;
//	double *dis = &ds;
//	oziOedometer1Set(dis);
//	return 0;
//}
//
//int COziExplorerApi::OedometerOFF(int n)
//{
//	typedef int (CALLBACK* ToziOedometerOFF)(void);
//	ToziOedometerOFF oziOedometerOFF;
//	switch(n)
//	{
//		case 1 :
//			oziOedometerOFF = (ToziOedometerOFF)GetProcAddress(oziApiDll,"oziOedometer1OFF");
//			break;
//		case 2 :
//			oziOedometerOFF = (ToziOedometerOFF)GetProcAddress(oziApiDll,"oziOedometer2OFF");
//			break;
//		default:
//			return -1;
//	}
//	return oziOedometerOFF();
//}
//double dd1;
//double distance;
//
////void Oedometer1(double* distance)
////{
////	double dd;
////	dd = * distance;
////	//dd1 = *distance;
////	CString ss;
////	ss.Format(L"прошли %d", dd);
////	AfxMessageBox(dd);
////}
//
//void Oedometer2(double* distance)
//{
//	//COziExplorerMap::OziPosition op;
//	//op.distance2 = * distance;
//}
//
//int COziExplorerApi::OedometerReset(int n)
//{
//	typedef int (CALLBACK* ToziOedometerReset)(void);
//	ToziOedometerReset oziOedometerReset;
//	switch(n)
//	{
//		case 1 :
//			oziOedometerReset = (ToziOedometerReset)GetProcAddress(oziApiDll,"oziOedometer1Reset");
//			break;
//		case 2 :
//			oziOedometerReset = (ToziOedometerReset)GetProcAddress(oziApiDll,"oziOedometer2Reset");
//			break;
//		default:
//			return -1;
//	}
//	return oziOedometerReset();
//}
//
//int COziExplorerApi::OedometerSet(int n, double * meter)
//{
//	typedef int (CALLBACK* ToziOedometerSet)(double *);
//	ToziOedometerSet oziOedometerSet;
//	switch(n)
//	{
//		case 1 :
//			oziOedometerSet = (ToziOedometerSet)GetProcAddress(oziApiDll,"oziOedometer1Set");
//			break;
//		case 2 :
//			oziOedometerSet = (ToziOedometerSet)GetProcAddress(oziApiDll,"oziOedometer2Set");
//			break;
//		default:
//			return -1;
//	}
//	return oziOedometerSet(meter);
//}

