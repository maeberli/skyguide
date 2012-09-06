;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Name and file
  Name "SkyGuide"
  OutFile "install.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES32\SkyGuide"
  
  ;Get installation folder from registry if available
  ; InstallDirRegKey HKCU "Software\Modern UI Test" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel user

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  
  !define MUI_WELCOMEFINISHPAGE_BITMAP "logo.bmp" 
  
  !define MUI_ICON "mainicon.ico"
	
  !define MUI_UNICON "mainicon.ico"

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "license.rtf"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------

;--------------------------------
;Installer Sections

Section "SkyGuide" main

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  
  File "SkyGuide.exe"
  File "SkyGuide.db"
  File "SkyGuide.ini"
  File "SkyGuide.log"
  File "mainicon.ico"
  File "libgcc_s_dw2-1.dll"
  File "mingwm10.dll"
  File "QtCore4.dll"
  File "QtGui4.dll"
  File "QtSql4.dll"
  File "GuideMode.exe"
  File "sqlite3.exe"
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\uninstall.exe"
  
  ;--------------------------------
  ;ShortCut
  CreateDirectory "$SMPROGRAMS\SkyGuide"
  CreateShortCut "$SMPROGRAMS\SkyGuide\SkyGuide.lnk" "$INSTDIR\SkyGuide.exe" "" "$INSTDIR\mainicon.ico"
  CreateShortCut "$SMPROGRAMS\SkyGuide\Guide Mode.lnk" "$INSTDIR\GuideMode.exe" "" "$INSTDIR\mainicon.ico"
  CreateShortCut "$SMPROGRAMS\SkyGuide\Uninstall SkyGuide.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\mainicon.ico"
  CreateShortCut "$DESKTOP\SkyGuide.lnk" "$INSTDIR\SkyGuide.exe" "" "$INSTDIR\mainicon.ico"
  CreateShortCut "$DESKTOP\Guide Mode.lnk" "$INSTDIR\GuideMode.exe" "" "$INSTDIR\mainicon.ico"
SectionEnd
;--------------------------------
;Descriptions

  ;Language strings
  LangString mainDescription ${LANG_ENGLISH} "Install files of application."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${main} $(mainDescription)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...
  
  Delete "$INSTDIR\SkyGuide.exe"
  Delete "$INSTDIR\SkyGuide.db"
  Delete "$INSTDIR\SkyGuide.ini"
  Delete "$INSTDIR\SkyGuide.log"
  Delete "$INSTDIR\mainicon.ico"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtSql4.dll"
  Delete "$INSTDIR\GuideMode.exe"
  Delete "$INSTDIR\sqlite3.exe"

  Delete "$INSTDIR\uninstall.exe"

  Delete "$DESKTOP\SkyGuide.lnk"
  Delete "$DESKTOP\Guide Mode.lnk"
  Delete "$SMPROGRAMS\SkyGuide\SkyGuide.lnk"
  Delete "$SMPROGRAMS\SkyGuide\Uninstall SkyGuide.lnk"
  Delete "$SMPROGRAMS\SkyGuide\Guide Mode.lnk"
  RMDir "$SMPROGRAMS\SkyGuide"
  
  RMDir "$INSTDIR"

  ; DeleteRegKey /ifempty HKCU "Software\Modern UI Test"

SectionEnd