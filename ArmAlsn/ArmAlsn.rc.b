// Microsoft Visual C++ generated resource script.
//
#include "resource.h"

#define APSTUDIO_READONLY_SYMBOLS
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 2 resource.
//
#ifndef APSTUDIO_INVOKED
#include "targetver.h"
#endif
#include "afxres.h"

/////////////////////////////////////////////////////////////////////////////
#undef APSTUDIO_READONLY_SYMBOLS

/////////////////////////////////////////////////////////////////////////////
// ������� resources

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_RUS)
#ifdef _WIN32
LANGUAGE LANG_RUSSIAN, SUBLANG_DEFAULT
#pragma code_page(1251)
#endif //_WIN32

#ifdef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// TEXTINCLUDE
//

1 TEXTINCLUDE 
BEGIN
    "resource.h\0"
END

2 TEXTINCLUDE 
BEGIN
    "#ifndef APSTUDIO_INVOKED\r\n"
    "#include ""targetver.h""\r\n"
    "#endif\r\n"
    "#include ""afxres.h""\r\n"
    "\0"
END

3 TEXTINCLUDE 
BEGIN
    "#define _AFX_NO_PROPERTY_RESOURCES\r\n"
    "\r\n"
    "#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_RUS)\r\n"
    "LANGUAGE 25, 1\r\n"
    "#pragma code_page(1251)\r\n"
    "#include ""res\\ArmAlsn.rc2""  // �������, �� ������������� � Microsoft Visual C++\r\n"
    "#include ""l.RUS\\afxres.rc""          // ����������� ����������\r\n"
    "#include ""l.RUS\\afxprint.rc""        // ������� ��� ������/���������������� ���������\r\n"
    "#include ""l.RUS\\afxolecl.rc""        // ������� ���������� OLE\r\n"
    "#include ""l.RUS\\afxolesv.rc""        // ������� ������� OLE\r\n"
    "#if !defined(_AFXDLL)\r\n"
    "#include ""l.RUS\\afxribbon.rc""               // ����� MFC � ������� ������ ����������\r\n"
    "#endif\r\n"
    "#endif\r\n"
    "1 TYPELIB ""ArmAlsn.tlb""\r\n"
    "\0"
END

#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// Icon
//

// Icon with lowest ID value placed first to ensure application icon
// remains consistent on all systems.
IDR_MAINFRAME           ICON                    "res\\ArmAlsn.ico"
IDR_ArmAlsnTYPE         ICON                    "res\\ArmAlsnDoc.ico"
IDI_OUTPUT_WND          ICON                    "res\\output_wnd.ico"
IDI_OUTPUT_WND_HC       ICON                    "res\\output_wnd_hc.ico"

/////////////////////////////////////////////////////////////////////////////
//
// Bitmap
//

IDR_MAINFRAME           BITMAP                  "res\\Toolbar.bmp"
IDR_MAINFRAME_256       BITMAP                  "res\\Toolbar256.bmp"
IDR_OSCILLOSCOPEFRAME   BITMAP                  "res\\OToolbar.bmp"
IDR_OSCILLOSCOPEFRAME_256 BITMAP                "res\\OToolbar256.bmp"
IDR_SRVR_INPLACE        BITMAP                  "res\\IToolbar.bmp"
IDR_SRVR_INPLACE_256    BITMAP                  "res\\IToolbar256.bmp"

/////////////////////////////////////////////////////////////////////////////
//
// Toolbar
//

IDR_MAINFRAME TOOLBAR  16, 16
BEGIN
    BUTTON      ID_FILE_NEW
    BUTTON      ID_FILE_OPEN
    BUTTON      ID_FILE_SAVE
    SEPARATOR
    BUTTON      ID_EDIT_CUT
    BUTTON      ID_EDIT_COPY
    BUTTON      ID_EDIT_PASTE
    SEPARATOR
    BUTTON      ID_FILE_PRINT
    BUTTON      ID_APP_ABOUT
    BUTTON      ID_CONTEXT_HELP
END

IDR_MAINFRAME_256 TOOLBAR  16, 16
BEGIN
    BUTTON      ID_FILE_NEW
    BUTTON      ID_FILE_OPEN
    BUTTON      ID_FILE_SAVE
    SEPARATOR
    BUTTON      ID_EDIT_CUT
    BUTTON      ID_EDIT_COPY
    BUTTON      ID_EDIT_PASTE
    SEPARATOR
    BUTTON      ID_FILE_PRINT
    BUTTON      ID_APP_ABOUT
    BUTTON      ID_CONTEXT_HELP
END

IDR_OSCILLOSCOPEFRAME TOOLBAR  16, 16
BEGIN
    BUTTON      ID_FILE_NEW
    BUTTON      ID_FILE_OPEN
    BUTTON      ID_FILE_SAVE
    SEPARATOR
    BUTTON      ID_EDIT_CUT
    BUTTON      ID_EDIT_COPY
    BUTTON      ID_EDIT_PASTE
    SEPARATOR
    BUTTON      ID_FILE_PRINT
    BUTTON      ID_APP_ABOUT
    BUTTON      ID_CONTEXT_HELP
END

IDR_OSCILLOSCOPEFRAME_256 TOOLBAR  16, 16
BEGIN
    BUTTON      ID_FILE_NEW
    BUTTON      ID_FILE_OPEN
    BUTTON      ID_FILE_SAVE
    SEPARATOR
    BUTTON      ID_EDIT_CUT
    BUTTON      ID_EDIT_COPY
    BUTTON      ID_EDIT_PASTE
    SEPARATOR
    BUTTON      ID_FILE_PRINT
    BUTTON      ID_APP_ABOUT
    BUTTON      ID_CONTEXT_HELP
END

IDR_SRVR_INPLACE TOOLBAR  16, 16
BEGIN
    BUTTON      ID_EDIT_CUT
    BUTTON      ID_EDIT_COPY
    BUTTON      ID_EDIT_PASTE
    SEPARATOR
    BUTTON      ID_APP_ABOUT
    BUTTON      ID_CONTEXT_HELP
END


/////////////////////////////////////////////////////////////////////////////
//
// Menu
//

IDR_MAINFRAME MENU 
BEGIN
    POPUP "&����"
    BEGIN
        MENUITEM "����� ��&���",                ID_FILE_NEW_FRAME
        MENUITEM "����&���\tCtrl+N",            ID_FILE_NEW
        MENUITEM "&�������...\tCtrl+O",         ID_FILE_OPEN
        MENUITEM "��&�������\tCtrl+S",          ID_FILE_SAVE
        MENUITEM "��������� &���...",           ID_FILE_SAVE_AS
        MENUITEM SEPARATOR
        MENUITEM "&������...\tCtrl+P",          ID_FILE_PRINT
        MENUITEM "����&����������� ��������",   ID_FILE_PRINT_PREVIEW
        MENUITEM "���&������ ������...",        ID_FILE_PRINT_SETUP
        MENUITEM SEPARATOR
        MENUITEM "��������� ����",              ID_FILE_MRU_FILE1, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "�&����",                      ID_APP_EXIT
    END
    POPUP "&������"
    BEGIN
        MENUITEM "&��������\tCtrl+Z",           ID_EDIT_UNDO
        MENUITEM SEPARATOR
        MENUITEM "&��������\tCtrl+X",           ID_EDIT_CUT
        MENUITEM "&����������\tCtrl+C",         ID_EDIT_COPY
        MENUITEM "���&�����\tCtrl+V",           ID_EDIT_PASTE
        MENUITEM "&����������� �������...",     ID_EDIT_PASTE_SPECIAL
        MENUITEM SEPARATOR
        MENUITEM "�������� &����� ������...",   ID_OLE_INSERT_NEW
        MENUITEM "��&���...",                   ID_OLE_EDIT_LINKS
        MENUITEM "<<������� OLE>>",             ID_OLE_VERB_FIRST
    END
    POPUP "������"
    BEGIN
        MENUITEM "Disco",                       ID_DISCO
        MENUITEM "������������",                ID_CONFIG
    END
    POPUP "&���"
    BEGIN
        POPUP "&������ ������������ � ������������ ����"
        BEGIN
            MENUITEM "<����������������>",          ID_VIEW_TOOLBAR
        END
        MENUITEM "&������ ���������",           ID_VIEW_STATUS_BAR
        POPUP "&��� ����������"
        BEGIN
            MENUITEM "Windows &2000",               ID_VIEW_APPLOOK_WIN_2000
            MENUITEM "Office &XP",                  ID_VIEW_APPLOOK_OFF_XP
            MENUITEM "&Windows XP",                 ID_VIEW_APPLOOK_WIN_XP
            MENUITEM "Office 200&3",                ID_VIEW_APPLOOK_OFF_2003
            MENUITEM "Visual Studio.NET 200&5",     ID_VIEW_APPLOOK_VS_2005
            POPUP "Office 200&7"
            BEGIN
                MENUITEM "&������� �����",              ID_VIEW_APPLOOK_OFF_2007_BLUE
                MENUITEM "�&����� �����",               ID_VIEW_APPLOOK_OFF_2007_BLACK
                MENUITEM "&����������� �����",          ID_VIEW_APPLOOK_OFF_2007_SILVER
                MENUITEM "&����������-������� �����",   ID_VIEW_APPLOOK_OFF_2007_AQUA
            END
        END
        MENUITEM "&���������",                  ID_WINDOW_SPLIT
        MENUITEM SEPARATOR
        MENUITEM "����������",                  ID_MyBass
        MENUITEM SEPARATOR
        POPUP "����� �����"
        BEGIN
            MENUITEM "�� ���������",                ID_LANGUAGE_FIRST
        END
    END
    POPUP "&�������"
    BEGIN
        MENUITEM "&����� �������",              ID_HELP_FINDER
        MENUITEM SEPARATOR
        MENUITEM "&� ������� ArmAlsn...",       ID_APP_ABOUT
    END
END

IDR_CNTR_INPLACE MENU 
BEGIN
    POPUP "&����"
    BEGIN
        MENUITEM "����� ��&���",                ID_FILE_NEW_FRAME
        MENUITEM "����&���\tCtrl+N",            ID_FILE_NEW
        MENUITEM "&�������...\tCtrl+O",         ID_FILE_OPEN
        MENUITEM "��&�������\tCtrl+S",          ID_FILE_SAVE
        MENUITEM "��������� &���...",           ID_FILE_SAVE_AS
        MENUITEM SEPARATOR
        MENUITEM "&������...\tCtrl+P",          ID_FILE_PRINT
        MENUITEM "����&����������� ��������",   ID_FILE_PRINT_PREVIEW
        MENUITEM "���&������ ������...",        ID_FILE_PRINT_SETUP
        MENUITEM SEPARATOR
        MENUITEM "��������� ����",              ID_FILE_MRU_FILE1, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "�&����",                      ID_APP_EXIT
    END
    MENUITEM SEPARATOR
    MENUITEM SEPARATOR
END

IDR_SRVR_INPLACE MENU 
BEGIN
    POPUP "&������"
    BEGIN
        MENUITEM "&��������\tCtrl+Z",           ID_EDIT_UNDO
        MENUITEM SEPARATOR
        MENUITEM "&��������\tCtrl+X",           ID_EDIT_CUT
        MENUITEM "&����������\tCtrl+C",         ID_EDIT_COPY
        MENUITEM "���&�����\tCtrl+V",           ID_EDIT_PASTE
        MENUITEM "&����������� �������...",     ID_EDIT_PASTE_SPECIAL
        MENUITEM SEPARATOR
        MENUITEM "�������� &����� ������...",   ID_OLE_INSERT_NEW
        MENUITEM "��&���...",                   ID_OLE_EDIT_LINKS
        MENUITEM "<<������� OLE>>",             ID_OLE_VERB_FIRST
    END
    POPUP "&���"
    BEGIN
        POPUP "&������ ������������ � ������������ ����"
        BEGIN
            MENUITEM "<����������������>",          ID_VIEW_TOOLBAR
        END
    END
    MENUITEM SEPARATOR
    MENUITEM SEPARATOR
    POPUP "&�������"
    BEGIN
        MENUITEM "&����� �������",              ID_HELP_FINDER
        MENUITEM SEPARATOR
        MENUITEM "&� ������� ArmAlsn...",       ID_APP_ABOUT
    END
END

IDR_SRVR_EMBEDDED MENU 
BEGIN
    POPUP "&����"
    BEGIN
        MENUITEM "�&�������\tCtrl+S",           ID_FILE_UPDATE
        MENUITEM "��������� ����� &���...",     ID_FILE_SAVE_COPY_AS
        MENUITEM SEPARATOR
        MENUITEM "&������...\tCtrl+P",          ID_FILE_PRINT
        MENUITEM "����&����������� ��������",   ID_FILE_PRINT_PREVIEW
        MENUITEM "���&������ ������...",        ID_FILE_PRINT_SETUP
        MENUITEM SEPARATOR
        MENUITEM "�&����",                      ID_APP_EXIT
    END
    POPUP "&������"
    BEGIN
        MENUITEM "&��������\tCtrl+Z",           ID_EDIT_UNDO
        MENUITEM SEPARATOR
        MENUITEM "&��������\tCtrl+X",           ID_EDIT_CUT
        MENUITEM "&����������\tCtrl+C",         ID_EDIT_COPY
        MENUITEM "���&�����\tCtrl+V",           ID_EDIT_PASTE
        MENUITEM "&����������� �������...",     ID_EDIT_PASTE_SPECIAL
        MENUITEM SEPARATOR
        MENUITEM "�������� &����� ������...",   ID_OLE_INSERT_NEW
        MENUITEM "��&���...",                   ID_OLE_EDIT_LINKS
        MENUITEM "<<������� OLE>>",             ID_OLE_VERB_FIRST
    END
    POPUP "&���"
    BEGIN
        POPUP "&������ ������������ � ������������ ����"
        BEGIN
            MENUITEM "<����������������>",          ID_VIEW_TOOLBAR
        END
        MENUITEM "&������ ���������",           ID_VIEW_STATUS_BAR
        POPUP "&��� ����������"
        BEGIN
            MENUITEM "Windows &2000",               ID_VIEW_APPLOOK_WIN_2000
            MENUITEM "Office &XP",                  ID_VIEW_APPLOOK_OFF_XP
            MENUITEM "&Windows XP",                 ID_VIEW_APPLOOK_WIN_XP
            MENUITEM "Office 200&3",                ID_VIEW_APPLOOK_OFF_2003
            MENUITEM "Visual Studio.NET 200&5",     ID_VIEW_APPLOOK_VS_2005
            POPUP "Office 200&7"
            BEGIN
                MENUITEM "&������� �����",              ID_VIEW_APPLOOK_OFF_2007_BLUE
                MENUITEM "�&����� �����",               ID_VIEW_APPLOOK_OFF_2007_BLACK
                MENUITEM "&����������� �����",          ID_VIEW_APPLOOK_OFF_2007_SILVER
                MENUITEM "&����������-������� �����",   ID_VIEW_APPLOOK_OFF_2007_AQUA
            END
        END
        MENUITEM "&���������",                  ID_WINDOW_SPLIT
    END
    POPUP "&�������"
    BEGIN
        MENUITEM "&����� �������",              ID_HELP_FINDER
        MENUITEM SEPARATOR
        MENUITEM "&� ������� ArmAlsn...",       ID_APP_ABOUT
    END
END

IDR_POPUP_EDIT MENU 
BEGIN
    POPUP "�������������"
    BEGIN
        MENUITEM "&��������\tCtrl+X",           ID_EDIT_CUT
        MENUITEM "&����������\tCtrl+C",         ID_EDIT_COPY
        MENUITEM "���&�����\tCtrl+V",           ID_EDIT_PASTE
    END
END

IDR_OUTPUT_POPUP MENU 
BEGIN
    POPUP "����������� ����"
    BEGIN
        MENUITEM "&����������",                 ID_EDIT_COPY
        MENUITEM "&��������",                   ID_EDIT_CLEAR
        MENUITEM SEPARATOR
        MENUITEM "&������",                     ID_VIEW_OUTPUTWND
    END
END

IDR_HELP_MENU MENU 
BEGIN
    MENUITEM "&����� �������",              ID_HELP_FINDER
    MENUITEM SEPARATOR
    MENUITEM "&� ������� ArmAlsn...",       ID_APP_ABOUT
END

IDR_THEME_MENU MENU 
BEGIN
    MENUITEM "Office 2007 (&������� �����)", ID_VIEW_APPLOOK_OFF_2007_BLUE
    MENUITEM "Office 2007 (�&����� �����)", ID_VIEW_APPLOOK_OFF_2007_BLACK
    MENUITEM "Office 2007 (&����������� �����)", ID_VIEW_APPLOOK_OFF_2007_SILVER
    MENUITEM "Office 2007 (&����������-������� �����)", ID_VIEW_APPLOOK_OFF_2007_AQUA
END

IDR_OSCILLOSCOPEFRAME MENU 
BEGIN
    POPUP "&����"
    BEGIN
        MENUITEM "����� ��&���",                ID_FILE_NEW_FRAME
        MENUITEM "����&���\tCtrl+N",            ID_FILE_NEW
        MENUITEM "&�������...\tCtrl+O",         ID_FILE_OPEN
        MENUITEM "��&�������\tCtrl+S",          ID_FILE_SAVE
        MENUITEM "��������� &���...",           ID_FILE_SAVE_AS
        MENUITEM SEPARATOR
        MENUITEM "&������...\tCtrl+P",          ID_FILE_PRINT
        MENUITEM "����&����������� ��������",   ID_FILE_PRINT_PREVIEW
        MENUITEM "���&������ ������...",        ID_FILE_PRINT_SETUP
        MENUITEM SEPARATOR
        MENUITEM "��������� ����",              ID_FILE_MRU_FILE1, GRAYED
        MENUITEM SEPARATOR
        MENUITEM "�&����",                      ID_APP_EXIT
    END
    POPUP "&������"
    BEGIN
        MENUITEM "&��������\tCtrl+Z",           ID_EDIT_UNDO
        MENUITEM SEPARATOR
        MENUITEM "&��������\tCtrl+X",           ID_EDIT_CUT
        MENUITEM "&����������\tCtrl+C",         ID_EDIT_COPY
        MENUITEM "���&�����\tCtrl+V",           ID_EDIT_PASTE
        MENUITEM "&����������� �������...",     ID_EDIT_PASTE_SPECIAL
        MENUITEM SEPARATOR
        MENUITEM "�������� &����� ������...",   ID_OLE_INSERT_NEW
        MENUITEM "��&���...",                   ID_OLE_EDIT_LINKS
        MENUITEM "<<������� OLE>>",             ID_OLE_VERB_FIRST
    END
    POPUP "������"
    BEGIN
        MENUITEM "������������",                ID_CONFIG
    END
    POPUP "&���"
    BEGIN
        POPUP "&������ ������������ � ������������ ����"
        BEGIN
            MENUITEM "<����������������>",          ID_VIEW_TOOLBAR
        END
        MENUITEM "&������ ���������",           ID_VIEW_STATUS_BAR
        POPUP "&��� ����������"
        BEGIN
            MENUITEM "Windows &2000",               ID_VIEW_APPLOOK_WIN_2000
            MENUITEM "Office &XP",                  ID_VIEW_APPLOOK_OFF_XP
            MENUITEM "&Windows XP",                 ID_VIEW_APPLOOK_WIN_XP
            MENUITEM "Office 200&3",                ID_VIEW_APPLOOK_OFF_2003
            MENUITEM "Visual Studio.NET 200&5",     ID_VIEW_APPLOOK_VS_2005
            POPUP "Office 200&7"
            BEGIN
                MENUITEM "&������� �����",              ID_VIEW_APPLOOK_OFF_2007_BLUE
                MENUITEM "�&����� �����",               ID_VIEW_APPLOOK_OFF_2007_BLACK
                MENUITEM "&����������� �����",          ID_VIEW_APPLOOK_OFF_2007_SILVER
                MENUITEM "&����������-������� �����",   ID_VIEW_APPLOOK_OFF_2007_AQUA
            END
        END
        MENUITEM "&���������",                  ID_WINDOW_SPLIT
        MENUITEM SEPARATOR
        MENUITEM "����������",                  ID_MyBass
        MENUITEM SEPARATOR
        POPUP "����� �����"
        BEGIN
            MENUITEM "�� ���������",                ID_LANGUAGE_FIRST
        END
    END
    POPUP "&�������"
    BEGIN
        MENUITEM "&����� �������",              ID_HELP_FINDER
        MENUITEM SEPARATOR
        MENUITEM "&� ������� ArmAlsn...",       ID_APP_ABOUT
    END
END


/////////////////////////////////////////////////////////////////////////////
//
// Accelerator
//

IDR_MAINFRAME ACCELERATORS 
BEGIN
    "N",            ID_FILE_NEW,            VIRTKEY, CONTROL
    "O",            ID_FILE_OPEN,           VIRTKEY, CONTROL
    "S",            ID_FILE_SAVE,           VIRTKEY, CONTROL
    "P",            ID_FILE_PRINT,          VIRTKEY, CONTROL
    "Z",            ID_EDIT_UNDO,           VIRTKEY, CONTROL
    "X",            ID_EDIT_CUT,            VIRTKEY, CONTROL
    "C",            ID_EDIT_COPY,           VIRTKEY, CONTROL
    "V",            ID_EDIT_PASTE,          VIRTKEY, CONTROL
    VK_BACK,        ID_EDIT_UNDO,           VIRTKEY, ALT
    VK_DELETE,      ID_EDIT_CUT,            VIRTKEY, SHIFT
    VK_INSERT,      ID_EDIT_COPY,           VIRTKEY, CONTROL
    VK_INSERT,      ID_EDIT_PASTE,          VIRTKEY, SHIFT
    VK_F6,          ID_NEXT_PANE,           VIRTKEY 
    VK_F6,          ID_PREV_PANE,           VIRTKEY, SHIFT
    VK_F1,          ID_CONTEXT_HELP,        VIRTKEY, SHIFT
    VK_F1,          ID_HELP,                VIRTKEY 
    VK_ESCAPE,      ID_CANCEL_EDIT_CNTR,    VIRTKEY, NOINVERT
END

IDR_CNTR_INPLACE ACCELERATORS 
BEGIN
    "N",            ID_FILE_NEW,            VIRTKEY, CONTROL
    "O",            ID_FILE_OPEN,           VIRTKEY, CONTROL
    "S",            ID_FILE_SAVE,           VIRTKEY, CONTROL
    "P",            ID_FILE_PRINT,          VIRTKEY, CONTROL
    VK_F6,          ID_NEXT_PANE,           VIRTKEY 
    VK_F6,          ID_PREV_PANE,           VIRTKEY, SHIFT
    VK_F1,          ID_CONTEXT_HELP,        VIRTKEY, SHIFT
    VK_F1,          ID_HELP,                VIRTKEY 
    VK_ESCAPE,      ID_CANCEL_EDIT_CNTR,    VIRTKEY, NOINVERT
END

IDR_SRVR_INPLACE ACCELERATORS 
BEGIN
    "Z",            ID_EDIT_UNDO,           VIRTKEY, CONTROL
    "X",            ID_EDIT_CUT,            VIRTKEY, CONTROL
    "C",            ID_EDIT_COPY,           VIRTKEY, CONTROL
    "V",            ID_EDIT_PASTE,          VIRTKEY, CONTROL
    VK_BACK,        ID_EDIT_UNDO,           VIRTKEY, ALT
    VK_DELETE,      ID_EDIT_CUT,            VIRTKEY, SHIFT
    VK_INSERT,      ID_EDIT_COPY,           VIRTKEY, CONTROL
    VK_INSERT,      ID_EDIT_PASTE,          VIRTKEY, SHIFT
    VK_F1,          ID_CONTEXT_HELP,        VIRTKEY, SHIFT
    VK_F1,          ID_HELP,                VIRTKEY 
    VK_ESCAPE,      ID_CANCEL_EDIT_SRVR,    VIRTKEY, NOINVERT
END

IDR_SRVR_EMBEDDED ACCELERATORS 
BEGIN
    "S",            ID_FILE_UPDATE,         VIRTKEY, CONTROL
    "P",            ID_FILE_PRINT,          VIRTKEY, CONTROL
    "Z",            ID_EDIT_UNDO,           VIRTKEY, CONTROL
    "X",            ID_EDIT_CUT,            VIRTKEY, CONTROL
    "C",            ID_EDIT_COPY,           VIRTKEY, CONTROL
    "V",            ID_EDIT_PASTE,          VIRTKEY, CONTROL
    VK_BACK,        ID_EDIT_UNDO,           VIRTKEY, ALT
    VK_DELETE,      ID_EDIT_CUT,            VIRTKEY, SHIFT
    VK_INSERT,      ID_EDIT_COPY,           VIRTKEY, CONTROL
    VK_INSERT,      ID_EDIT_PASTE,          VIRTKEY, SHIFT
    VK_F6,          ID_NEXT_PANE,           VIRTKEY 
    VK_F6,          ID_PREV_PANE,           VIRTKEY, SHIFT
    VK_F1,          ID_CONTEXT_HELP,        VIRTKEY, SHIFT
    VK_F1,          ID_HELP,                VIRTKEY 
    VK_ESCAPE,      ID_CANCEL_EDIT_CNTR,    VIRTKEY, NOINVERT
END


/////////////////////////////////////////////////////////////////////////////
//
// Dialog
//

IDD_ABOUTBOX DIALOGEX 0, 0, 170, 62
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "� ������� ArmAlsn"
FONT 8, "MS Shell Dlg", 0, 0, 0x1
BEGIN
    ICON            IDR_MAINFRAME,IDC_STATIC,14,14,21,20
    LTEXT           "ArmAlsn, ������ 0.51",IDC_STATIC,42,14,114,8,SS_NOPREFIX
    LTEXT           "Copyright (C) 2010",IDC_STATIC,42,26,114,8
    DEFPUSHBUTTON   "��",IDOK,113,41,50,14,WS_GROUP
END

IDD_DIALOG_CONFIG DIALOGEX 0, 0, 495, 273
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_MAXIMIZEBOX | WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU
EXSTYLE WS_EX_OVERLAPPEDWINDOW
CAPTION "������������"
FONT 8, "MS Shell Dlg", 400, 0, 0x1
BEGIN
    PUSHBUTTON      "����� ��� ����������",IDCANCEL,184,253,96,14
    CONTROL         "",IDC_TREE1,"SysTreeView32",TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | WS_BORDER | WS_HSCROLL | WS_TABSTOP,11,24,136,207
    PUSHBUTTON      "��������� � �����",IDC_SAVE_EXIT,79,252,86,14
    CONTROL         "",IDC_TAB1,"SysTabControl32",TCS_BUTTONS | TCS_FIXEDWIDTH,147,24,310,207
    PUSHBUTTON      "���������",IDC_SAVECONFIG,14,252,50,14
    PUSHBUTTON      "��������",IDC_NOSAVE,423,252,50,14
END

IDD_DIALOG_CONFIG_DIRECTX DIALOGEX 0, 0, 309, 182
STYLE DS_SETFONT | DS_FIXEDSYS | WS_CHILD | WS_SYSMENU
FONT 8, "MS Shell Dlg", 400, 0, 0x1
BEGIN
    COMBOBOX        IDC_SOUND_DEVICE_COMBO,119,17,165,30,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | WS_TABSTOP
    COMBOBOX        IDC_CAPTURE_DEVICE_COMBO,119,34,165,30,CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | WS_TABSTOP
    LTEXT           "���������� ���������������",IDC_STATIC,14,17,102,8
    LTEXT           "���������� ������",IDC_STATIC,14,36,65,8
    PUSHBUTTON      "Button1",IDCONSAVE,19,157,50,14,NOT WS_VISIBLE
    CONTROL         "����������� ����� ",IDC_DISKO,"Button",BS_AUTOCHECKBOX | BS_CENTER | WS_TABSTOP,10,71,97,10,WS_EX_RIGHT
END

IDD_DIALOG_CONFIG_GPS DIALOGEX 0, 0, 271, 182
STYLE DS_SETFONT | DS_FIXEDSYS | WS_CHILD | WS_SYSMENU
FONT 8, "MS Shell Dlg", 400, 0, 0x1
BEGIN
    COMBOBOX        IDC_COMBO_PORT,67,18,155,30,CBS_DROPDOWN | WS_VSCROLL | WS_TABSTOP
    LTEXT           "1-� COM ����",IDC_STATIC,8,18,55,8
    PUSHBUTTON      "���������",IDC_BUTTON_1COM,223,18,50,14
    PUSHBUTTON      "Button2",IDCONSAVE,17,159,50,14,NOT WS_VISIBLE
    LTEXT           "2-� COM ����",IDC_STATIC,10,52,47,8
    COMBOBOX        IDC_2_COMBO_PORT,66,47,156,30,CBS_DROPDOWN | WS_VSCROLL | WS_TABSTOP
    PUSHBUTTON      "���������",IDC_2_BUTTON_1COM,221,47,50,14
END

IDD_VIEW_PUT DIALOGEX 0, 0, 366, 102
STYLE DS_SETFONT | DS_SETFOREGROUND | DS_FIXEDSYS | WS_MINIMIZEBOX | WS_POPUP | WS_CLIPSIBLINGS | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME
EXSTYLE WS_EX_TOPMOST | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW
CAPTION "���� � �����������"
FONT 10, "MS Shell Dlg", 400, 0, 0xCC
BEGIN
    EDITTEXT        IDC_ASIMETR,64,20,33,14,ES_AUTOHSCROLL
    PUSHBUTTON      "�����",IDCANCEL,3,86,114,14
    EDITTEXT        IDC_ASCHEN1,64,37,33,14,ES_AUTOHSCROLL
    LTEXT           "����������",IDC_STATIC,3,6,42,8
    EDITTEXT        IDC_ASCHEN2,64,54,33,14,ES_AUTOHSCROLL
    LTEXT           "����� 1",IDC_STATIC,3,37,28,8
    LTEXT           "����� 2",IDC_STATIC,3,57,28,8
    LTEXT           "�����������",IDC_STATIC,3,20,48,8
    EDITTEXT        IDC_1_PK_V,63,4,68,12,ES_AUTOHSCROLL
    EDITTEXT        IDC_2_PK_V,140,4,203,14,ES_AUTOHSCROLL
    EDITTEXT        IDC_2_ASIMETR,140,21,40,14,ES_AUTOHSCROLL
    EDITTEXT        IDC_2_ASCHEN1,140,38,40,14,ES_AUTOHSCROLL
    EDITTEXT        IDC_2_ASCHEN2,140,55,40,14,ES_AUTOHSCROLL
    LTEXT           "������",IDC_STATIC,194,24,27,8
    LTEXT           "�������",IDC_STATIC,194,42,29,8
    EDITTEXT        IDC_LONGITUDE,238,40,84,14,ES_AUTOHSCROLL | ES_READONLY
    EDITTEXT        IDC_LATITUDE,238,22,84,14,ES_AUTOHSCROLL | ES_READONLY
    EDITTEXT        IDC_KORECT,239,64,40,14,ES_AUTOHSCROLL | ES_NOHIDESEL
    LTEXT           "�������������",IDC_STATIC,182,63,53,8
    PUSHBUTTON      "ok",IDC_PKOK,282,64,16,14
    GROUPBOX        "�����������",IDC_STATIC,303,55,46,24,BS_CENTER,WS_EX_RIGHT
    CONTROL         "+",IDC_SCHETP,"Button",BS_AUTORADIOBUTTON | BS_PUSHLIKE | WS_GROUP,310,65,12,10
    CONTROL         "-",IDC_SCHETM,"Button",BS_AUTORADIOBUTTON | BS_PUSHLIKE,327,65,12,10
END


/////////////////////////////////////////////////////////////////////////////
//
// Version
//

VS_VERSION_INFO VERSIONINFO
 FILEVERSION 0,5,1,1
 PRODUCTVERSION 0,5,1,1
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS 0x1L
#else
 FILEFLAGS 0x0L
#endif
 FILEOS 0x4L
 FILETYPE 0x1L
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "041904e3"
        BEGIN
            VALUE "CompanyName", "�������� ����������� �. �. � �. ����� �.�."
            VALUE "FileDescription", "TODO: <�������� �����>"
            VALUE "FileVersion", "0.7.1.20100227"
            VALUE "InternalName", "ArmAlsn.exe"
            VALUE "LegalCopyright", "TODO: (c) <�������� �����������>. ��� ����� ��������."
            VALUE "OriginalFilename", "ArmAlsn.exe"
            VALUE "ProductName", "TODO: <�������� ��������>"
            VALUE "ProductVersion", "0.7.1.20100227"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x419, 1251
    END
END


/////////////////////////////////////////////////////////////////////////////
//
// DESIGNINFO
//

#ifdef APSTUDIO_INVOKED
GUIDELINES DESIGNINFO 
BEGIN
    IDD_ABOUTBOX, DIALOG
    BEGIN
        LEFTMARGIN, 7
        RIGHTMARGIN, 163
        TOPMARGIN, 7
        BOTTOMMARGIN, 55
    END
END
#endif    // APSTUDIO_INVOKED


/////////////////////////////////////////////////////////////////////////////
//
// String Table
//

STRINGTABLE 
BEGIN
    IDP_OLE_INIT_FAILED     "�� ������� ��������� ������������� OLE. ��������� � ���, ��� ������������ ���������� ������ ��������� OLE."
    IDP_FAILED_TO_CREATE    "�� ������� ������� ������. ��������� � ���, ��� �� ������� � ��������� ������."
END

STRINGTABLE 
BEGIN
    IDR_MAINFRAME           "ArmAlsn\n\nArmAlsn\nArmAlsn Files (*.alsn)\n.alsn\nArmAlsn.Document\nArmAlsn.Document"
END

STRINGTABLE 
BEGIN
    AFX_IDS_APP_TITLE       "ArmAlsn"
    AFX_IDS_IDLEMESSAGE     "��� ��������� ������� ������� ������� F1"
    AFX_IDS_HELPMODEMESSAGE "�������� ������, ��� �������� ��������� �������"
END

STRINGTABLE 
BEGIN
    ID_INDICATOR_EXT        "EXT"
    ID_INDICATOR_CAPS       "CAP"
    ID_INDICATOR_NUM        "NUM"
    ID_INDICATOR_SCRL       "SCRL"
    ID_INDICATOR_OVR        "OVR"
    ID_INDICATOR_REC        "REC"
END

STRINGTABLE 
BEGIN
    ID_FILE_NEW             "�������� ������ ���������\n�������"
    ID_FILE_OPEN            "�������� ������������� ���������\n�������"
    ID_FILE_CLOSE           "�������� ��������� ���������\n�������"
    ID_FILE_SAVE            "���������� ��������� ���������\n���������"
    ID_FILE_SAVE_AS         "���������� ��������� ��������� ��� ����� ������\n��������� ���"
    ID_FILE_PAGE_SETUP      "��������� ���������� ������\n��������� ��������"
    ID_FILE_PRINT_SETUP     "��������� �������� � ���������� ������\n��������� ������"
    ID_FILE_PRINT           "������ ��������� ���������\n������"
    ID_FILE_PRINT_DIRECT    "������ ��������� ��������� � �������������� ������� ����������\n������� ������"
    ID_FILE_PRINT_PREVIEW   "�������� ��������� � ��������������� ������\n��������������� ��������"
    ID_FILE_UPDATE          "���������� ���������� ��� ����������� ���� ���������\n��������"
    ID_FILE_SAVE_COPY_AS    "���������� ����� ��������� ��������� ��� ����� ������\n��������� �����"
    ID_FILE_NEW_FRAME       "�������� ����� �����\n����� �����"
END

STRINGTABLE 
BEGIN
    IDS_CLOSE               "�������"
END

STRINGTABLE 
BEGIN
    ID_APP_ABOUT            "����� �������� � ���������, �� ������ � ��������� ������\n� ���������"
    ID_APP_EXIT             "���������� ������ ���������� � �������� �� ���������� ����������\n�����"
    ID_HELP_INDEX           "�������� ���������� �������\n����� �������"
    ID_HELP_FINDER          "����� ���������� ���������� �������\n����� �������"
    ID_HELP_USING           "����� ���������� �� ������ �� ���������� ��������\n�������"
    ID_CONTEXT_HELP         "����������� ���������� �������� ��� ��������� ������, ���� � ����\n�������"
    ID_HELP                 "����������� ���������� �������� ��� ������� ������ ��� �������\n�������"
END

STRINGTABLE 
BEGIN
    ID_FILE_MRU_FILE1       "�������� ������� ���������"
    ID_FILE_MRU_FILE2       "�������� ������� ���������"
    ID_FILE_MRU_FILE3       "�������� ������� ���������"
    ID_FILE_MRU_FILE4       "�������� ������� ���������"
    ID_FILE_MRU_FILE5       "�������� ������� ���������"
    ID_FILE_MRU_FILE6       "�������� ������� ���������"
    ID_FILE_MRU_FILE7       "�������� ������� ���������"
    ID_FILE_MRU_FILE8       "�������� ������� ���������"
    ID_FILE_MRU_FILE9       "�������� ������� ���������"
    ID_FILE_MRU_FILE10      "�������� ������� ���������"
    ID_FILE_MRU_FILE11      "�������� ������� ���������"
    ID_FILE_MRU_FILE12      "�������� ������� ���������"
    ID_FILE_MRU_FILE13      "�������� ������� ���������"
    ID_FILE_MRU_FILE14      "�������� ������� ���������"
    ID_FILE_MRU_FILE15      "�������� ������� ���������"
    ID_FILE_MRU_FILE16      "�������� ������� ���������"
END

STRINGTABLE 
BEGIN
    ID_NEXT_PANE            "������� � ��������� ������� ����\n��������� �������"
    ID_PREV_PANE            "������� � ���������� ������� ����\n���������� �������"
END

STRINGTABLE 
BEGIN
    ID_WINDOW_SPLIT         "���������� ��������� ���� �� �������\n���������"
END

STRINGTABLE 
BEGIN
    ID_EDIT_CLEAR           "�������� ����������� ���������\n�������"
    ID_EDIT_CLEAR_ALL       "������ �������� ����������� ���������\n������� ���"
    ID_EDIT_COPY            "����������� ����������� ��������� � ����� ������\n����������"
    ID_EDIT_CUT             "�������� ����������� ��������� � ����� ������\n��������"
    ID_EDIT_FIND            "����� ���������� ������\n�����"
    ID_EDIT_PASTE           "������� ����������� ������ ������\n��������"
    ID_EDIT_PASTE_LINK      "������� ����������� ������ ������ � �������� ����� � ��� ����������\n�������� �����"
    ID_EDIT_PASTE_SPECIAL   "������� ����������� ������ ������ � ������������ ������ �������\n����������� �������"
    ID_EDIT_REPEAT          "���������� ���������� ��������\n���������"
    ID_EDIT_REPLACE         "������ ��������� ������ ������ �������\n��������"
    ID_EDIT_SELECT_ALL      "��������� ����� ���������\n�������� ���"
    ID_EDIT_UNDO            "������ ���������� ��������\n��������"
    ID_EDIT_REDO            "��������� ���������� ���������� ����������� ��������\n�������"
END

STRINGTABLE 
BEGIN
    ID_VIEW_STATUS_BAR      "�������� ��� ������ ������ ���������\n ������������ ������ ���������"
END

STRINGTABLE 
BEGIN
    ID_OLE_INSERT_NEW       "������� ������ ����������� �������\n����� ������"
    ID_OLE_EDIT_LINKS       "��������� ��������� ��������\n�������� �����"
    ID_OLE_EDIT_CONVERT     "�������������� ������� � ������� ����\n������������� ������"
END

STRINGTABLE 
BEGIN
    ID_OLE_VERB_FIRST       "��������� ����������� ��� ���������� �������"
    57873                   "��������� ����������� ��� ���������� �������"
    57874                   "��������� ����������� ��� ���������� �������"
    57875                   "��������� ����������� ��� ���������� �������"
END

STRINGTABLE 
BEGIN
    AFX_IDS_SCSIZE          "��������� ������� ����"
    AFX_IDS_SCMOVE          "��������� ��������� ����"
    AFX_IDS_SCMINIMIZE      "����������� ���� � ������"
    AFX_IDS_SCMAXIMIZE      "������������� ���� �� ������� �������"
    AFX_IDS_SCNEXTWINDOW    "������� � ���������� ���� ���������"
    AFX_IDS_SCPREVWINDOW    "������� � ����������� ���� ���������"
    AFX_IDS_SCCLOSE         "�������� ��������� ���� � �������� �� ���������� ����������"
END

STRINGTABLE 
BEGIN
    AFX_IDS_SCRESTORE       "�������������� �������� �������� ����"
    AFX_IDS_SCTASKLIST      "������� � ������ �����"
END

STRINGTABLE 
BEGIN
    AFX_IDS_PREVIEW_CLOSE   "����� �� ������ ���������������� ���������\n�������� ��������"
END

STRINGTABLE 
BEGIN
    IDS_STATUS_PANE1        "������ 1"
    IDS_STATUS_PANE2        "������ 2"
    IDS_TOOLBAR_STANDARD    "�����������"
    IDS_TOOLBAR_CUSTOMIZE   "���������..."
END

STRINGTABLE 
BEGIN
    IDS_OUTPUT_WND          "������"
END

STRINGTABLE 
BEGIN
    IDS_BUILD_TAB           "������"
    IDS_DEBUG_TAB           "�������"
    IDS_FIND_TAB            "�����"
END

STRINGTABLE 
BEGIN
    IDS_EDIT_MENU           "�������������"
END

#endif    // ������� resources
/////////////////////////////////////////////////////////////////////////////



#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//
#define _AFX_NO_PROPERTY_RESOURCES

#if !defined(AFX_RESOURCE_DLL) || defined(AFX_TARG_RUS)
LANGUAGE 25, 1
#pragma code_page(1251)
#include "res\ArmAlsn.rc2"  // �������, �� ������������� � Microsoft Visual C++
#include "l.RUS\afxres.rc"          // ����������� ����������
#include "l.RUS\afxprint.rc"        // ������� ��� ������/���������������� ���������
#include "l.RUS\afxolecl.rc"        // ������� ���������� OLE
#include "l.RUS\afxolesv.rc"        // ������� ������� OLE
#if !defined(_AFXDLL)
#include "l.RUS\afxribbon.rc"               // ����� MFC � ������� ������ ����������
#endif
#endif
1 TYPELIB "ArmAlsn.tlb"

/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

