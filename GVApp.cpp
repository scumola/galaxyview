/// \file GVApp.cpp
/// \brief header file for PURPOSE in GalaxyView

// GVApp.cpp -- header file for PURPOSE in GalaxyView
//
// Copyright 2003, Quarterflash Design Group
//
// Licensed under GPL version 2 - see COPYING for details
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#include <iostream>

#if defined(__WIN32__)
#pragma warning(disable:4786)
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if !defined(WX_PRECOMP)
#include "wx/wx.h"
#endif

#include "wx/cmdline.h"
#include "wx/utils.h"
#include "wx/log.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/utils.h"

#include "GVApp.h"
#include "GVFrame.h"
#include "GVDialogs.h"

#if defined(WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#endif

// command line options
static const wxCmdLineEntryDesc cmdLineDesc[] = {
	{wxCMD_LINE_SWITCH, _T ("h"), _T ("help"), _T ("show help message"),
	 wxCMD_LINE_VAL_NONE,
	 wxCMD_LINE_OPTION_HELP},
	{wxCMD_LINE_SWITCH, _T ("v"), _T ("verbose"), _T ("be verbose")},
	{wxCMD_LINE_PARAM, NULL, NULL, _T ("game name"),
	 wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL},

	{wxCMD_LINE_NONE}
};


IMPLEMENT_APP (GVApp)
	 bool GVApp::OnInit ()
{
#if defined(WIN32) && defined(_DEBUG)
	// Set Breakpoint at memory allocation 
	//_CrtSetBreakAlloc(42034);
#endif

	bool retCode = true;
	
	wxChar pathSep;				// the path separator for the platform

	wxString rc_file;			// initialization info file name
	wxFileConfig *configFile;	// very minimal per game as most
	// options are stored in the database

	gameName.Clear ();			// ensure that we can tell if a name
	// is passed on the command line 

	GVdb *db = NULL;

	// command line parser
	wxCmdLineParser parser (cmdLineDesc, argc, argv);

	wxString defaultPath;		// where we'll put files if it's not specified
	// determine if we're on windows or linux
	rc_file = argv[0];
	if (rc_file.Find (_(".exe")) != -1) {
		// windows platform
		pathSep = '\\';
		defaultPath = rc_file.Left (rc_file.Find ('\\', true)) + _("\\");
		rc_file = defaultPath + _("galaxyviewrc");
	}
	else {
		if (!wxGetEnv (_("HOME"), &rc_file)) {
			wxLogWarning (_T
						  ("Could not find $HOME, options file set to /tmp/galaxyviewrc"));
			defaultPath = _("/tmp/");
			rc_file = _("/tmp/galaxyviewrc");
			pathSep = '/';
		}
		else {
			pathSep = '/';
			defaultPath = rc_file + _("/.galaxyview/");
			rc_file.Append (_("/.galaxyview/galaxyviewrc"));
			if (!::wxDirExists (defaultPath)) {
				::wxMkdir (defaultPath, 0700);
			}
		}
	}

	wxLogMessage (rc_file);

	// where to find the config info
	configFile = new wxFileConfig (_T ("GalaxyView"), _T ("QDG"), rc_file);
	wxConfigBase::Set (configFile);


	// process the command line, if any
	switch (parser.Parse ()) {
	case -1:
		retCode = false;
		break;

	case 0:
		retCode = true;
		ParseParams (parser);
	}

	configFile->Write (_T ("/GalaxyView/resources"),
					   defaultPath + _T ("GalaxyView.rfa"));
	configFile->Write (_T ("/GalaxyView/help"),
					   _T ("file:") + defaultPath +
					   _T ("GalaxyView.rfa#zip:") + _T ("help"));
	
	//check if the resourcefile exists
	wxString resourceFile;
	configFile->Read(_T ("/GalaxyView/resources"), &resourceFile);
	if (!(::wxFileExists(resourceFile))) {
		wxLogWarning (_T("Could not find resource file GalaxyView.rfa, GV will now exit"));
		return false;
	}
	
	// set default game directory 
	wxString gameDir;
	configFile->Read(_T("/GalaxyView/GameDirectory"), &gameDir, "");
	if(gameDir=="") {
		// Not Set Yet
		gameDir = ::wxGetHomeDir() + "/.galaxyview/";
		configFile->Write(_T("/GalaxyView/GameDirectory"), gameDir);
		wxLogMessage(gameDir);
	}

	db = new GVdb ();

	mainWindow = new GVFrame (_T ("GalaxyView"), 0, 0, 1024, 768);
	mainWindow->db (db);

	// was a game name specified on the command line?
	if (!gameName.IsEmpty ()) {
		bool dbInitNeeded = false;
		long game_init;
		wxString cfgPrefix = _T ("/") + gameName;
		wxString cfgKey = cfgPrefix + _T ("/Initialized");
		game_init = configFile->Read (cfgKey, 0L);


		if (!game_init) {
#if 0
			gvInitGameDialog *id = new gvInitGameDialog (gameName);
			id->ShowModal ();
			delete id;
#endif
			cfgKey = cfgPrefix + _T ("/Initialized");
			configFile->Write (cfgKey, 1);

			// show this as an active game
			cfgKey = cfgPrefix + _T ("/Active");
			configFile->Write (cfgKey, 1);

			// add this game to the list of games already known about
			wxString gameList;
			configFile->Read (_T ("/GalaxyView/Games"), &gameList);
			if (gameList.IsEmpty ()) {
				gameList = gameName;
			}
			else {
				gameList.Append (_(",") + gameName);
			}
			configFile->Write (_T ("/GalaxyView/Games"), gameList);
		}

		wxString gameDir = defaultPath;

		cfgKey = cfgPrefix + _T ("/GameDir");
		configFile->Read (cfgKey, &gameDir);
		configFile->Write (cfgKey, gameDir);
		wxString gameDBName = gameDir + pathSep + gameName + _T (".gdf");

		if (!::wxFileExists (gameDBName)) {
			wxLogMessage (_T ("dbInitNeeded set to true"));
			dbInitNeeded = true;
		}

		wxLogMessage (gameDBName);	// debugging statement

		// database for game related data
		hDB tdb = db->Open (gameName, gameDBName);
		// check to see if this is a newly created database
		if (dbInitNeeded) {
			// this should be a new database, do the initialization
			DBInit (db, tdb);
		}

		// Set new created game as our current game
		configFile->Write (_("/GalaxyView/CurrentGame"), gameName);

	}
	else {

		// No GameName specified - checking for default one
		configFile->Read (_("/GalaxyView/CurrentGame"), &gameName, "");
		if (gameName.IsEmpty ()) {
			// No Game?

			// Do we have other games?
			wxString gameList;
			configFile->Read (_("/GalaxyView/Games"), &gameList, "");
			if (gameList.IsEmpty ()) {
				wxMessageBox (_T ("No Games Found. Creating a new one"));
				mainWindow->ShowNewGameDialog ();
			}
			else {
				mainWindow->ShowOpenGameDialog (true);
			}

		}
		else {
			if (!mainWindow->LoadGame (gameName)) {
				// Failed to Load Current Game - Display Open Game Dialog With New Game Option
				wxLogMessage (_T ("LoadGame Failed"));

				// open loadgame/newgame dialog
				mainWindow->ShowOpenGameDialog (true);
			}
			else {
				mainWindow->UpdateApplication();
				wxLogMessage (_T ("Current Game Loaded: ") + gameName);
			}
		}

	}

	mainWindow->Show (TRUE);
	SetTopWindow (mainWindow);

	return retCode;
}

bool GVApp::DBInit (GVdb * db, hDB tdb)
{
	wxFileSystem fs;
	wxFSFile* sqlFile = NULL;

	wxFileConfig* cf = (wxFileConfig *)wxConfigBase::Get (false);

	wxString resourceFile;
	cf->Read (_T ("/GalaxyView/resources"), &resourceFile);

	wxString wildcard = _T ("file:") + resourceFile + _T ("#zip:sql/*.sql");
	wxString sql;
	wxZipInputStream* sqlStream;

	wxLogMessage (_T ("wildcard: ") + wildcard);
	wxString sqlName = fs.FindFirst (wildcard, wxFILE);

	wxLogMessage (_T ("sqlName: ") + sqlName);
	while (!sqlName.IsEmpty ()) {
		sql.Clear ();
		sqlFile = fs.OpenFile (sqlName);
		sqlStream = (wxZipInputStream *) sqlFile->GetStream ();

		char c;
		while (true) {
			c = sqlStream->GetC ();
			if (sqlStream->Eof ()) {
				if(c==';') {
					// we have a completed sql
					wxLogMessage(sql);
					db->Sql(tdb, sql);
					sql.Clear();
				}
				break;
			}
			switch (c) {
			case ';':
				sql.Append (c);
				wxLogMessage (sql);
				// here's where we execute the sql
				db->Sql (tdb, sql);
				sql.Clear ();
				break;

			default:
				sql.Append (c);
				break;
			}
		}

		if (sqlFile) {
			delete sqlFile;
		}

		sqlName = fs.FindNext ();
		wxLogMessage (_T ("sqlName: ") + sqlName);
	}

	return true;
}


GVGalaxy GVApp::galaxy;
GVFrame* GVApp::mainWindow = NULL;

void
GVApp::ParseParams (const wxCmdLineParser & cmdline)
{
	if (cmdline.GetParamCount () > 0)
		gameName = cmdline.GetParam (0);
}
