bin_PROGRAMS		=	GalaxyView

INFOVIEW_SOURCES 	= \
infoviews/GVInfoPlanets.cpp  infoviews/GVInfoPlanets.h

SQLITEPLUSPLUS_SOURCES	= \
sqlite++/Query.cpp   sqlite++/Result.h  sqlite++/SQLiteFile.cpp \
sqlite++/Query.h     sqlite++/Row.cpp   sqlite++/SQLiteFile.h \
sqlite++/Result.cpp  sqlite++/Row.h     sqlite++/sqlite++.h


PREFERENCES_SOURCES	= \
preferences/GVPreferences.cpp      preferences/GVPreferencesGeneral.cpp \
preferences/GVPreferencesGame.cpp  preferences/GVPreferencesGeneral.h \
preferences/GVPreferencesGame.h    preferences/GVPreferences.h 


TOOLS_SOURCES		= \
tools/GVToolsBattleSimulator.cpp  tools/GVToolsIntelligence.h     tools/GVToolsShipDesigner.cpp \
tools/GVToolsBattleSimulator.h    tools/GVToolsMessageCenter.cpp  tools/GVToolsShipDesigner.h \
tools/GVToolsCalculator.cpp       tools/GVToolsMessageCenter.h    tools/GVToolsTextEditor.cpp \
tools/GVToolsCalculator.h         tools/GVToolsMoveEditor.cpp     tools/GVToolsTextEditor.h \
tools/GVTools.cpp                 tools/GVToolsMoveEditor.h       tools/GVToolsTreatyEditor.cpp \
tools/GVTools.h                   tools/GVToolsPlanetEditor.cpp   tools/GVToolsTreatyEditor.h \
tools/GVToolsIntelligence.cpp     tools/GVToolsPlanetEditor.h


GalaxyView_SOURCES	= \
bookmark.cpp      GVDBOptions.h    GVGalaxyNGReport.cpp  GVNewGameDialog.h     GVStateLookup.cpp \
bookmark.h        GVDBPlanets.cpp  GVGalaxyNGReport.h    GVOpenGameDialog.cpp  GVStateLookup.h   \
GVApp.cpp         GVDBPlanets.h    GVGalaxyObject.h      GVOpenGameDialog.h    GVToolBar.cpp \
GVApp.h           GVDBStatus.cpp   GVGame.cpp            GVOptions.cpp 	       GVToolBar.h \
GVDBAliens.cpp    GVDBStatus.h     GVGame.h              GVOptions.h  \
GVDBAliens.h      GVdefines.h      GVGroup.h             GVParseReport.cpp \
GVDBBulletin.cpp  GVDialogs.h      GVHelpFrame.cpp       GVParseReport.h \
GVDBBulletin.h    GVError.cpp      GVHelpFrame.h         GVparser.h            XMLParser.cpp    \
GVdb.cpp          GVError.h        GVInfoView.cpp        GVPlanet.cpp          XMLParser.h      \
GVDBGeneral.h     GVFrame.cpp      GVInfoView.h          GVPlanet.h \
GVdb.h            GVFrame.h        GVMapPanel.cpp        GVRace.h \
GVDBObject.h      GVGalaxy.cpp     GVMapPanel.h          GVShipDesign.h \
GVDBOptions.cpp   GVGalaxy.h       GVNewGameDialog.cpp   GVStateDefs.h \
GVAddBookmarkDialog.cpp GVAddBookmarkDialog.h \
GVDeleteBookmarkDialog.cpp GVDeleteBookmarkDialog.h \
$(INFOVIEW_SOURCES) $(SQLITEPLUSPLUS_SOURCES) $(PREFERENCES_SOURCES) $(TOOLS_SOURCES)
	
EXTRA_DIST		= GalaxyViewPic.xpm resources.lst resource xtd doc makegvres

