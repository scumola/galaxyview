# Microsoft Developer Studio Project File - Name="galaxyview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=galaxyview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "galaxyview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "galaxyview.mak" CFG="galaxyview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "galaxyview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "galaxyview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "galaxyview - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "__WIN32__" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDOWS_" /D "_WXMSW__WIN95_" /D "_WIN32_" /D WINVER=0x0400 /D "STRICT" /YX /FD /c
# ADD BASE RSC /l 0x807 /d "NDEBUG"
# ADD RSC /l 0x807 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 png.lib zlib.lib jpeg.lib tiff.lib wxxrc.lib sqlite.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib rpcrt4.lib comctl32.lib regex.lib wxmsw.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "galaxyview - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "__WIN32__" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDOWS_" /D "_WXMSW_" /D "_WXDEBUG_" /D WXDEBUG=1 /D "_WIN95_" /D "_WIN32_" /D WINVER=0x0400 /D "STRICT" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wxxrcd.lib zlibd.lib regexd.lib pngd.lib jpegd.lib tiffd.lib wxmswd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib sqlite.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /verbose /pdb:none

!ENDIF 

# Begin Target

# Name "galaxyview - Win32 Release"
# Name "galaxyview - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\GVApp.cpp
# End Source File
# Begin Source File

SOURCE=.\GVdb.cpp
# End Source File
# Begin Source File

SOURCE=.\GVDBAliens.cpp
# End Source File
# Begin Source File

SOURCE=.\GVDBBulletin.cpp
# End Source File
# Begin Source File

SOURCE=.\GVDBOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\GVDBPlanets.cpp
# End Source File
# Begin Source File

SOURCE=.\GVDBStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\GVError.cpp
# End Source File
# Begin Source File

SOURCE=.\GVFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GVGalaxy.cpp
# End Source File
# Begin Source File

SOURCE=.\GVGalaxyNGReport.cpp
# End Source File
# Begin Source File

SOURCE=.\GVHelpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\GVMapPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GVNewGameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GVOpenGameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GVOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\GVParseReport.cpp
# End Source File
# Begin Source File

SOURCE=.\GVPlanet.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLParser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bookmark.h
# End Source File
# Begin Source File

SOURCE=.\GVApp.h
# End Source File
# Begin Source File

SOURCE=.\GVdb.h
# End Source File
# Begin Source File

SOURCE=.\GVDBAliens.h
# End Source File
# Begin Source File

SOURCE=.\GVDBBulletin.h
# End Source File
# Begin Source File

SOURCE=.\GVDBGeneral.h
# End Source File
# Begin Source File

SOURCE=.\GVDBObject.h
# End Source File
# Begin Source File

SOURCE=.\GVDBOptions.h
# End Source File
# Begin Source File

SOURCE=.\GVDBPlanets.h
# End Source File
# Begin Source File

SOURCE=.\GVDBStatus.h
# End Source File
# Begin Source File

SOURCE=.\GVdefines.h
# End Source File
# Begin Source File

SOURCE=.\GVDialogs.h
# End Source File
# Begin Source File

SOURCE=.\GVError.h
# End Source File
# Begin Source File

SOURCE=.\GVFrame.h
# End Source File
# Begin Source File

SOURCE=.\GVGalaxy.h
# End Source File
# Begin Source File

SOURCE=.\GVGalaxyNGReport.h
# End Source File
# Begin Source File

SOURCE=.\GVGalaxyObject.h
# End Source File
# Begin Source File

SOURCE=.\GVGroup.h
# End Source File
# Begin Source File

SOURCE=.\GVHelpFrame.h
# End Source File
# Begin Source File

SOURCE=.\GVMapPanel.h
# End Source File
# Begin Source File

SOURCE=.\GVNewGameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GVOpenGameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GVOptions.h
# End Source File
# Begin Source File

SOURCE=.\GVparser.h
# End Source File
# Begin Source File

SOURCE=.\GVParseReport.h
# End Source File
# Begin Source File

SOURCE=.\GVPlanet.h
# End Source File
# Begin Source File

SOURCE=.\GVRace.h
# End Source File
# Begin Source File

SOURCE=.\GVShipDesign.h
# End Source File
# Begin Source File

SOURCE=.\system.h
# End Source File
# Begin Source File

SOURCE=.\XMLParser.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\colours.bmp
# End Source File
# Begin Source File

SOURCE=.\galaxyview.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Preferences"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\preferences\GVPreferences.cpp
# End Source File
# Begin Source File

SOURCE=.\preferences\GVPreferences.h
# End Source File
# Begin Source File

SOURCE=.\preferences\GVPreferencesGame.cpp
# End Source File
# Begin Source File

SOURCE=.\preferences\GVPreferencesGame.h
# End Source File
# Begin Source File

SOURCE=.\preferences\GVPreferencesGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\preferences\GVPreferencesGeneral.h
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tools\GVTools.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVTools.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsBattleSimulator.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsBattleSimulator.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsCalculator.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsIntelligence.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsIntelligence.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsMessageCenter.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsMessageCenter.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsMoveEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsMoveEditor.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsPlanetEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsPlanetEditor.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsShipDesigner.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsShipDesigner.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsTextEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsTextEditor.h
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsTreatyEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\tools\GVToolsTreatyEditor.h
# End Source File
# End Group
# Begin Group "SQLLite++"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\sqlite++\Query.cpp"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\Query.h"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\Result.cpp"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\Result.h"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\Row.cpp"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\Row.h"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\sqlite++.h"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\SQLiteFile.cpp"
# End Source File
# Begin Source File

SOURCE=".\sqlite++\SQLiteFile.h"
# End Source File
# End Group
# End Target
# End Project
