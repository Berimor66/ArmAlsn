#pragma once

#include "windows.h"

typedef int (CALLBACK* ToziCloseApi)(void);

typedef int (CALLBACK* ToziGetExePath)(char **, int *);

typedef int (CALLBACK* ToziCenterMapAtPosition)(double, double);
typedef int (CALLBACK* ToziCenterMapAtPositionWithMark)(double, double);
typedef int (CALLBACK* ToziCloseProgram)(void);
typedef int (CALLBACK* ToziFindOzi)(void);
typedef int (CALLBACK* ToziGetMapDatum)(char **, int *);

typedef int (CALLBACK* ToziShowTrack)(int *);
typedef int (CALLBACK* ToziShowAllTracks)(void);


typedef int (CALLBACK* ToziConvertDatum)(char **, char **, double *, double *);

typedef int (CALLBACK* ToziClearWPs)(void);
typedef int (CALLBACK* ToziClearEVs)(void);
typedef int (CALLBACK* ToziClearRTEs)(void);
typedef int (CALLBACK* ToziClearTRKs)(void);
typedef int (CALLBACK* ToziClearTRK)(int);
typedef int (CALLBACK* ToziClearPTs)(void);
typedef int (CALLBACK* ToziClearMFs)(void);
typedef int (CALLBACK* ToziClearMCs)(void);


typedef int (CALLBACK* ToziCreateWP)(char **, int ,double, double, double, double, int, int, int, int, int, int,
                                     char **, int, int, int);

typedef int (CALLBACK* ToziCreateMF)(char **, double, double, char **, char **, char **, int, char **);

typedef int (CALLBACK* ToziCreateMC)(char **, double, double, int, int, int, int , int, int);


typedef int (CALLBACK* ToziMapSingleClickON)(int *);
typedef int (CALLBACK* ToziMapSingleClickOFF)(void);
typedef int (CALLBACK* ToziMapDblClickON)(int *);
typedef int (CALLBACK* ToziMapDblClickOFF)(void);
typedef int (CALLBACK* ToziObjectClickON)(int *);
typedef int (CALLBACK* ToziObjectClickOFF)(void);

typedef int (CALLBACK* ToziLoadMap)(char **);
typedef int (CALLBACK* ToziSaveMap)(char **);
typedef int (CALLBACK* ToziLoadWPfile)(char **);
typedef int (CALLBACK* ToziLoadRTEfile)(char **);
typedef int (CALLBACK* ToziLoadTRKfile)(int, char **);

typedef int (CALLBACK* ToziStartMMserial)(void);

typedef int (CALLBACK* ToziChangeTRKcolor)(int, int);

typedef int (CALLBACK* ToziGps2NavWp)(char **, char **, double *, double *);

// Пройденный путь
typedef int (CALLBACK* ToziOedometer1ON)(int*);// Включить
//typedef int (CALLBACK* ToziOedometer1OFF)(void);	// Выключить
//typedef int (CALLBACK* ToziOedometer1Reset)(void);	// Сбросить на 0
//typedef int (CALLBACK* ToziOedometer1Set)(double *);// Установить
//typedef int (CALLBACK* ToziOedometer1UP)(void);		// На увеличение
//typedef int (CALLBACK* ToziOedometer1DOWN)(void);	// На Уменьшение


//void CALLBACK Oedometer2(double* distance);


// multi tracking
typedef int (CALLBACK* ToziMTStartMultiTrack)(void);
typedef int (CALLBACK* ToziMTStopMultiTrack)(void);
typedef int (CALLBACK* ToziMTSendPosition)(char **);
typedef int (CALLBACK* ToziMTloadIDsON)(void);
typedef int (CALLBACK* ToziMTloadIDsOFF)(void);


//============================================================================
extern HINSTANCE oziApiDll;           // Handle to DLL

extern ToziCloseApi oziCloseApi; 

extern ToziGetExePath oziGetExePath;

extern ToziCenterMapAtPosition oziCenterMapAtPosition;
extern ToziCenterMapAtPositionWithMark oziCenterMapAtPositionWithMark;
extern ToziCloseProgram oziCloseProgram;
extern ToziFindOzi oziFindOzi;
extern ToziGetMapDatum oziGetMapDatum;
extern ToziShowTrack oziShowTrack;
extern ToziShowAllTracks oziShowAllTracks;
extern ToziConvertDatum oziConvertDatum;

extern ToziClearWPs oziClearWPs;
extern ToziClearEVs oziClearEVs;
extern ToziClearRTEs oziClearRTEs;
extern ToziClearTRKs oziClearTRKs;
extern ToziClearTRK oziClearTRK;
extern ToziClearPTs oziClearPTs;
extern ToziClearMFs oziClearMFs;
extern ToziClearMCs oziClearMCs;


extern ToziCreateWP oziCreateWP;
extern ToziCreateMF oziCreateMF;
extern ToziCreateMC oziCreateMC;

extern ToziMapSingleClickON oziMapSingleClickON;
extern ToziMapSingleClickOFF oziMapSingleClickOFF ;
extern ToziMapDblClickON oziMapDblClickON;
extern ToziMapDblClickOFF oziMapDblClickOFF;
extern ToziObjectClickON oziObjectClickON;
extern ToziObjectClickOFF oziObjectClickOFF;

extern ToziLoadMap oziLoadMap;
extern ToziSaveMap oziSaveMap;
extern ToziLoadWPfile oziLoadWPfile;
extern ToziLoadRTEfile oziLoadRTEfile;
extern ToziLoadTRKfile oziLoadTRKfile;

extern ToziStartMMserial oziStartMMserial;

extern ToziChangeTRKcolor oziChangeTRKcolor;

extern ToziGps2NavWp oziGps2NavWp;
//
extern ToziOedometer1ON oziOedometer1ON;
//extern	ToziOedometer1OFF oziOedometer1OFF;	// Выключить
//extern	ToziOedometer1Reset oziOedometer1Reset;	// Сбросить на 0
//extern	ToziOedometer1Set oziOedometer1Set;// Установить
//extern	ToziOedometer1UP oziOedometer1UP;		// На увеличение
//extern	ToziOedometer1DOWN oziOedometer1DOWN;	// На Уменьшение



//these are for multi tracking
extern ToziMTStartMultiTrack oziMTStartMultiTrack;
extern ToziMTStopMultiTrack oziMTStopMultiTrack;
extern ToziMTSendPosition oziMTSendPosition;
extern ToziMTloadIDsON oziMTloadIDsON;
extern ToziMTloadIDsOFF oziMTloadIDsOFF;

int LoadOziApiDll(void);
//void Oedometer1(double* distance);

class COziExplorerApi
{
public:
	COziExplorerApi(void);
	~COziExplorerApi(void);
	int CheckOziExplorerRunning(void);
	int StartMovingMapSerial(void);
	int GetNavWp(CString* sss);
	int LoadWaypoint(CString* sss);
	int LoadRoute(CString* sss);

	int ClearAllWaypoints(void);
	int ShowTrack(int n);
	// Пройденный путь
	//int OedometerON(int n, double* meter, int* Up);
	//int OedometerOFF(int n);
	//int OedometerReset(int n);
	//int OedometerSet(int n, double * meter);

	bool OziExplorerIsRun;
};

