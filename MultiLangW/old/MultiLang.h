//////////////////////////////////////////////////////
// Copyright Lingobit Technologies                  // 
// Use it at your own risk                          //
//////////////////////////////////////////////////////

#ifndef _MULTILANG_LIBRARY_
#define _MULTILANG_LIBRARY_

#ifndef _MULTILANGDLL

// #pragma comment(lib, "../DEBUG/MultiLang.lib")

//////////////////////////////////////////////////////
///

//#pragma comment(lib, "../Lib/MultiLang.lib")
#pragma comment(lib, "../../../MyLib/32/Multilang.lib")
//#pragma comment(lib, "../../../MyLib/64/Multilang.lib")

//////////////////////////////////////////////////////
///
#pragma message("Automatically linking with MultiLang.lib")
#endif

# if defined(_MULTILANGDLL)
#  define MULTILANG_DECL __declspec ( dllexport )
# else
#  define MULTILANG_DECL __declspec ( dllimport )
# endif

//EXE Localization
MULTILANG_DECL BOOL MultiLangInitLocalization(
                               UINT nStart, //command id of first menu entry
                               UINT nMaxLangs, //maximum number of languages
                               HKEY hkey,
                               LPCTSTR lpszSection,
                               LPCTSTR lpszEntry
                               );

// menu
MULTILANG_DECL void MultiLangUpdateMenu(CCmdUI* pCmdUI);
MULTILANG_DECL bool MultiLangOnClickMenu(UINT nID);

MULTILANG_DECL bool MultiLangIsSingleLanguageMode();

// combo
MULTILANG_DECL void MultiLangInitCombo(CComboBox & combo );
MULTILANG_DECL bool MultiLangOnComboApply(CComboBox & combo );

MULTILANG_DECL  BOOL MultiLangLoadLocalization();


// DLL Localization
MULTILANG_DECL HINSTANCE MultiLangLoadLibrary(
                          HINSTANCE hDllInstance,
                          HKEY hkey,
                          LPCTSTR lpszSection,
                          LPCTSTR lpszEntry
                          );

MULTILANG_DECL CString MultiLangGetCurLanguage();

#endif
