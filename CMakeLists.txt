CMAKE_MINIMUM_REQUIRED(VERSION 1.6)
INCLUDE (${CMAKE_ROOT}/Modules/CMakeDetermineSystem.cmake)

MACRO(BUILD_TEST_PGM classname)
  STRING(ASCII 35 POUND)
  WRITE_FILE("${CMAKE_CURRENT_BINARY_DIR}/test_${classname}.cpp" "${POUND}define ${classname}_MAIN_NEEDED\n${POUND}define ${classname}_Debug\n${POUND}include \"${classname}.cpp\" ")
  ADD_EXECUTABLE(test_${classname} ${CMAKE_CURRENT_BINARY_DIR}/test_${classname}.cpp ${test_${classname}_SRC_LIST})
ENDMACRO(BUILD_TEST_PGM)

MACRO(UPDATE_TEST_LIB classname libname)
  TARGET_LINK_LIBRARIES(test_${classname} ${libname})
ENDMACRO(UPDATE_TEST_LIB)

MACRO(UPDATE_TEST_SRC classname srcname)
  SET(test_${classname}_SRC_LIST ${test_${classname}_SRC_LIST} ${srcname})
ENDMACRO(UPDATE_TEST_SRC)

PROJECT(GalaxyView)

LINK_DIRECTORIES(/usr/local/wxwin241/lib /usr/local/lib)

ADD_EXECUTABLE(GalaxyView GVApp.cpp GVFrame.cpp GVdb.cpp
	tools/GVToolsBattleSimulator.cpp  tools/GVToolsMoveEditor.cpp
	tools/GVToolsCalculator.cpp       tools/GVToolsPlanetEditor.cpp
	tools/GVTools.cpp                 tools/GVToolsShipDesigner.cpp
	tools/GVToolsIntelligence.cpp     tools/GVToolsTextEditor.cpp
	tools/GVToolsMessageCenter.cpp    tools/GVToolsTreatyEditor.cpp
	GVOpenGameDialog.cpp GVNewGameDialog.cpp GVInfoView.cpp
	GVGalaxyNGReport.cpp GVStateLookup.cpp
	GVDBAliens.cpp    GVDBOptions.cpp  GVDBStatus.cpp
	GVDBBulletin.cpp  GVDBPlanets.cpp  GVGame.cpp
	XMLParser.cpp GVError.cpp GVHelpFrame.cpp
	GVGalaxy.cpp GVMapPanel.cpp GVPlanet.cpp bookmark.cpp
	GVToolBar.cpp
	preferences/GVPreferences.cpp sqlite++/Query.cpp
	sqlite++/SQLiteFile.cpp sqlite++/Result.cpp
	sqlite++/Row.cpp infoviews/GVInfoPlanets.cpp)

<<<<<<< CMakeLists.txt
INCLUDE_DIRECTORIES(/usr/local/wxwin241/lib/wx/include/gtk-2.4 preferences)
TARGET_LINK_LIBRARIES(GalaxyView wx_gtk-2.4 wx_gtk_xrc-2.4 sqlite )
=======
INCLUDE_DIRECTORIES(/usr/local/lib/wx/include/gtk2-2.4 preferences)
TARGET_LINK_LIBRARIES(GalaxyView wx_gtk2-2.4 wx_gtk2_xrc-2.4 sqlite )
>>>>>>> 1.30

ADD_DEFINITIONS(-g -Wall -D__STRICT_ANSI__ -DGTK_NO_CHECK_CASTS -D__WXGTK__ -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES)

BUILD_TEST_PGM(XMLParser)
UPDATE_TEST_LIB(XMLParser wx_gtk-2.4)
UPDATE_TEST_LIB(XMLParser expat)

