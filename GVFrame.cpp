/// \file GVFrame.cpp
/// \brief class file for main window of GalaxyView

// GVFrame.cpp -- class file for main window of GalaxyView
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
#include <list>
using std::cerr;

#include "GVApp.h"
#include "GVFrame.h"
#define ENUM_ONLY
#include "GVGalaxyNGReport.h"
#undef ENUM_ONLY
#include "GVNewGameDialog.h"
#include "GVOpenGameDialog.h"
#include "GVAddBookmarkDialog.h"
#include "GVDeleteBookmarkDialog.h"
#include "preferences/GVPreferences.h"


GVFrame::GVFrame (const wxChar * title, int xpos, int ypos, int width, int height):wxFrame ((wxFrame *) NULL, -1, title, wxPoint (xpos, ypos),
		 wxSize (width,
				 height))
{
	// set help window to NULL
	m_help = NULL;

	// we need to instantiate handlers for PNG images and the compressed file system
	wxImage::AddHandler (new wxPNGHandler);
	wxImage::AddHandler (new wxJPEGHandler);
	wxFileSystem::AddHandler (new wxZipFSHandler);

	// the image for the splash screen 
#include "GalaxyViewPic.xpm"

	wxBitmap* splash_bm = new wxBitmap (GalaxyViewPic_xpm);
	wxSplashScreen*	splash = NULL;

	if (splash_bm) {
		splash = new wxSplashScreen (*splash_bm,
									 wxSPLASH_CENTRE_ON_SCREEN |
									 wxSPLASH_TIMEOUT, 1000, NULL, -1,
									 wxDefaultPosition, wxDefaultSize,
									 wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR);
	};
	wxYield ();
	// add the handlers for the XML resources, load the main menu

	wxFileConfig *
		cf = (wxFileConfig *)
		wxConfigBase::Get (false);

	wxString
		resourceFile;

	cf->Read (_T ("/GalaxyView/resources"), &resourceFile);
	wxString resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/menubar.xrc");
	wxXmlResource::Get ()->InitAllHandlers ();
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/opengamedialog.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/newgamedialog.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/addbookmarkdialog.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/deletebookmarkdialog.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/preferences/preferencesdialog.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/helpframe.xrc");
	wxXmlResource::Get ()->Load (resources);

	resources = _T ("file:") + resourceFile + _T ("#zip:resource/ui/toolbar.xrc");
	wxXmlResource::Get ()->Load (resources);

	// the menu and tool bar
	SetMenuBar (wxXmlResource::Get ()->LoadMenuBar (this, _("main_menubar")));

	// set up the main window layout. This consists of 3 panes, two
	// across the top - one for tool panes, the other for the map - and
	// one for tabular data tabular data across the bottom
	m_hsplit =
		new wxSplitterWindow (this, -1, wxPoint (0, 0), wxSize (1000, 700),
							  wxSP_3D);
	m_vsplit = new wxSplitterWindow (m_hsplit);

	// assign new elements to the panes they belong in
	m_tools = new GVTools (m_vsplit);
	m_tables = new GVInfoView (m_hsplit);
	m_map = new GVMapPanel (m_vsplit);

	// final layout details
	m_hsplit->SplitHorizontally (m_vsplit, m_tables);
	m_vsplit->SplitVertically (m_tools, m_map);

	// eliminate unsplit - ie, make it impossible to get rid of one of
	// them 
	m_hsplit->SetMinimumPaneSize (10);
	m_vsplit->SetMinimumPaneSize (10);

	// load icon
	wxZipInputStream
		iconstream (resourceFile, _T ("resource/icons/eye_in_32x32x16.png"));
	if (iconstream.CanRead ()) {
		wxImage *img = new wxImage (iconstream);
		if (img) {
			wxBitmap bmp (img);
			delete img;
			wxIcon icon;
			icon.CopyFromBitmap (bmp);
			this->SetIcon (icon);
		}
		else {
			wxLogMessage (_T ("could not load frame icon"));
		}
	}
	else {
		wxLogMessage (_T ("Unable to open resourcefile"));
	}

	m_toolbar = new GVToolBar(this);
	this->SetToolBar(m_toolbar);


	CreateStatusBar(3);
	m_status = GetStatusBar();

	// show all the details
	m_tools->Show (TRUE);
	m_map->Show (TRUE);
	m_tables->Show (TRUE);

	delete splash_bm;
	delete splash;
}

GVFrame::~GVFrame ()
{
	UnloadGame();
	GVApp::GetGalaxy()->Save();
	delete m_db;
}

void
GVFrame::db (GVdb * _db)
{
	m_db = _db;
}

bool GVFrame::NewGame (wxString gamename, wxString turn0, wxString type)
{
	wxFileConfig *cf = (wxFileConfig *)wxConfigBase::Get (false);

	// create database
	wxString turnDir = cf->Read (_("/") + gamename + _("/GameDir"), "");
	if (turnDir.IsEmpty ()) {
		// GameDirectory is Empty
		return false;
	}

	// get game directory
	wxString gameDir = cf->Read(_T("/GalaxyView/GameDirectory"), "");
	if(gameDir.IsEmpty()) {
		return false;
	}

	// create turn directory if it doesnt exist
	if (!::wxDirExists (turnDir)) {
		::wxMkdir (turnDir);
	}

	// create game directory if it doesn't exist
	if(!::wxDirExists(gameDir)) {
		::wxMkdir(gameDir);
	}

	wxString dbfilename = gameDir + _("/") + gamename + _(".gdf"); 
	m_currentDB = m_db->Open (gamename, dbfilename);

	long game_init = cf->Read (_("/") + gamename + _("/Initialized"), 0L);
	if (!game_init) {
		// TODO: Database Init.
		GVApp::DBInit (m_db, m_currentDB);

		// Set initialized = 1
		cf->Write (_("/") + gamename + _("/Initialized"), 1L);

		// set show as active
		cf->Write (_("/") + gamename + _("/Active"), 1L);

		::wxSetCursor (*wxHOURGLASS_CURSOR);

		if(type=="GalaxyNG") {

			// Parse First Report - TODO: game types
			GVGalaxyNGReport* p = new GVGalaxyNGReport;

			if (p->ParseReport(m_db, m_currentDB, turn0)) {
				wxLogMessage (_T ("Turn Imported Into Database"));
			}
			else {
				wxLogMessage (_T ("Error Parsing"));
			}

			// Now Write additional data to the database (preferencesgame)
			SQLiteFile* sql = m_db->GetSQL(m_currentDB);
			if(!sql) return false;

			Query q = sql->GetQuery();

			// If there are already settings delete them
			q << "SELECT * FROM preferencesgame";
			Result res = q.Store();
			if(!res.Empty()) {
				q << "DELETE * FROM preferencesgame";
				q.Execute();
			}

			GVApp::GetGalaxy()->SetDatabase(m_db, m_currentDB);

			GVGalaxyNGFeatures* f = p->GetFeatures();

			GVGameData settings;
			settings.password = p->GetPassword();
			settings.gametype = "GalaxyNG";
			settings.gamename = p->GetGamename();
			settings.homeplanesnum = 0; /* TODO: Read from dialog */
			settings.homeplanetssize = ""; /* TODO: Read from dialog */
			settings.racename = p->GetPlayerRace();
			settings.size = f->size;

			GVApp::GetGalaxy()->GetGame()->Save(&settings);
			if(settings.valid) {
				wxLogMessage("Updated Preferences");
			} else {
				wxLogMessage("Failed to Update Preferences");
			}

			m_currentTurn = p->GetTurn();

			GVApp::GetGalaxy()->LoadTurn(m_currentTurn);
			m_map->SetMapSize(settings.size);
			m_map->SetTurn(m_currentTurn);

			delete p;

		} else {
			wxMessageBox("Gametype " + type + " not supported yet.", "Sorrry :(");
			return false;
		}

		::wxSetCursor (*wxSTANDARD_CURSOR);

	}	


	// setup ini file
	wxString gameList;
	cf->Read (_T ("/GalaxyView/Games"), &gameList);
	if (gameList.IsEmpty ()) {
		gameList = gamename;
	}
	else {
		gameList.Append (_(",") + gamename);
	}
	cf->Write (_T ("/GalaxyView/Games"), gameList);
	cf->Write (_T ("/GalaxyView/CurrentGame"), gamename);

	return true;
}

bool GVFrame::LoadGame (wxString gamename)
{
	wxFileConfig* cf = (wxFileConfig *)wxConfigBase::Get (false);

	// Check if a game with name 'gamename' exists
	if (!cf->HasGroup (gamename)) {
		// This Game has no entry
		return false;
	}

	// load game database
	hDB database = m_db->GetByGame(gamename);
	if (database == -1) {
		wxLogMessage (_T ("Unable to get database by gamename: ") + gamename);
		return false;
	}
	m_currentDB = database;

	cf->Read ("/" + gamename + "/LastTurn", &m_currentTurn, 0);

	GVApp::GetGalaxy()->SetDatabase(m_db, m_currentDB);

	if (!GVApp::GetGalaxy ()->LoadTurn (m_currentTurn)) {
		wxLogMessage (_T("Unable to load galaxy turn for game: " + gamename));
		return false;
	}

	m_map->SetTurn (m_currentTurn);
	m_map->SetMapSize (GVApp::GetGalaxy()->GetGame()->GetSize(), false);	// create a centered map

	// set current game
	cf->Write (_("/GalaxyView/CurrentGame"), gamename);

	// Load Default Bookmark
	wxString defaultBookmark = cf->Read("/" + gamename + _T("/BookmarkAutoSaveSlot"));
	if(defaultBookmark!="0") {
		GVApp::GetGalaxy()->GetBookmarks()->LoadBookmark(this, defaultBookmark[(size_t)0]);	
	}
	
	return true;
}

bool
GVFrame::UnloadGame()
{
	wxFileConfig *cf = (wxFileConfig*)wxConfigBase::Get(false);
	
	wxString currentGame = cf->Read(_T("/GalaxyView/CurrentGame"), "");
	wxASSERT_MSG(currentGame!="", "Unload Game, currentGame was empty");
	
	// Save Default Bookmark
	wxString defaultBookmark = cf->Read("/" + currentGame + _T("/BookmarkAutoSaveSlot"));
	if(defaultBookmark!="0") {
		GVApp::GetGalaxy()->GetBookmarks()->SaveBookmark(this, defaultBookmark[(size_t)0]);	
	}
	
	return true;
}

void
GVFrame::ShowNewGameDialog ()
{
	GVNewGameDialog dlg (this);
	if (dlg.ShowModal () == wxID_OK) {
		// User clicked ok - create the new game

		wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
		wxString cfgPrefix = _("/") + dlg.GetGamename () + _("/");

		// Write Active/Gamedir
		cf->Write (cfgPrefix + _("GameDir"), dlg.GetGameDirectory ());
		cf->Write (cfgPrefix + _("Active"), 1L);

		if (!NewGame (dlg.GetGamename (), dlg.GetTurn0(), dlg.GetGameType())) {
			wxMessageBox (_("Unable To Create New Game"), _("Error"),
						  wxID_OK);
		}

	} else {
		// User Pressed Cancel
	}
	UpdateApplication();
}

void
GVFrame::ShowOpenGameDialog (bool withNew)
{
	GVOpenGameDialog dlg (this, withNew);

	// Add Games

	// Read [GalaxyView] games 
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	wxString games;
	cf->Read (_("/GalaxyView/Games"), &games);

	wxStringTokenizer st (games, _(","));


	while (st.HasMoreTokens ()) {
		wxString game = st.NextToken ();
		bool active;
		cf->Read (_("/") + game + _("/Active"), &active);

		dlg.AddGame (game, active);
	}

	dlg.SortGames ();

	// Do Modal
	if (dlg.ShowModal () == wxID_OK) {
		// Open 
		wxLogMessage (_T ("Load Game: ") + dlg.GetSelection ());

		LoadGame (dlg.GetSelection ());

	}
	else {
		// User Clicked Cancel
	}
	UpdateApplication();
}

void
GVFrame::OnNewGame (wxCommandEvent &)
{
	ShowNewGameDialog ();
}

void
GVFrame::OnLoadGame (wxCommandEvent &)
{
	ShowOpenGameDialog (false);
}

void
GVFrame::OnQuit (wxCommandEvent &)
{
	Close (TRUE);
}

void
GVFrame::OnAbout (wxCommandEvent &)
{
	wxString about_info =
		_T ("GalaxyView\n© 2003 Quarterflash Design Group\n");
	about_info += _T ("Licensed under the GPL\n\n");
	about_info += _T ("Developers:\n");
	about_info +=
		_T ("  Ken Weinert (madcoder42)\n  Chris Shaffer (christhecat)\n");
	about_info += _T ("  James Thorpe (jamesthorpe)\n");
	about_info +=
		_T ("  Fabio Rossetto (redhook)\n  Raphael Juchli (hellcat0)\n");

	wxMessageBox (about_info, _T ("About"), wxICON_INFORMATION | wxOK);
}

void
GVFrame::OnSwitchTools (wxCommandEvent & event)
{
	int evt = event.GetId ();

	if (evt == XRCID ("move_editor")) {
		m_tools->SetSelection (GVTAB_MOVE_EDITOR);
	}
	else if (evt == XRCID ("planet_developer")) {
		m_tools->SetSelection (GVTAB_PLANET_EDITOR);
	}
	else if (evt == XRCID ("ship_designer")) {
		m_tools->SetSelection (GVTAB_SHIP_DESIGNER);
	}
	else if (evt == XRCID ("battle_simulator")) {
		m_tools->SetSelection (GVTAB_BATTLE_SIMULATOR);
	}
	else if (evt == XRCID ("intel_center")) {
		m_tools->SetSelection (GVTAB_INTELLIGENCE);
	}
	else if (evt == XRCID ("message_center")) {
		m_tools->SetSelection (GVTAB_MESSAGES);
	}
	else if (evt == XRCID ("treaty_editor")) {
		m_tools->SetSelection (GVTAB_TREATY_EDITOR);
	}
	else if (evt == XRCID ("text_editor")) {
		m_tools->SetSelection (GVTAB_TEXT_EDITOR);
	}
	else if (evt == XRCID ("calculator")) {
		m_tools->SetSelection (GVTAB_CALCULATOR);
	}
}

void
GVFrame::OnReportLoad (wxCommandEvent & event)
{
	// For Now Just a simple method to test the report parser
	wxFileDialog dlg (this, _("Load Report"), "", "", _("*.xml"));

	if (dlg.ShowModal () == wxID_OK) {
		wxString filename = dlg.GetPath ();
		wxLogMessage (filename);

		GVParseReport* p = new GVGalaxyNGReport;

		::wxSetCursor (*wxHOURGLASS_CURSOR);

		if (p->ParseReport(m_db, m_currentDB, filename)) {
			wxLogMessage (_T ("Turn Imported Into Database"));
		}
		else {
			wxLogMessage (_T ("Error Parsing"));
		}

		delete p;

		::wxSetCursor (*wxSTANDARD_CURSOR);
	}
}

void
GVFrame::OnHelp (wxCommandEvent & event)
{
	if (m_help) {
		m_help->Show (true);
		m_help->Raise ();
	}
	else {
		m_help = new GVHelpFrame (this);
	}
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	wxString index;
	if (!cf->Exists (_("GalaxyView/help"))) {
		wxLogMessage (_T ("Help Path Not Set"));
		return;
	}

	cf->Read (_("/GalaxyView/help"), &index);
	index += _("/index.html");

	if (!m_help->SetIndex (index)) {
		wxLogMessage (_T ("Unable to load index page"));
	}
}

void
GVFrame::OnPreferences (wxCommandEvent &)
{
	GVPreferences dlg(this, m_db, m_currentDB);
	dlg.ShowModal();
}

void 
GVFrame::OnTablesMenu(wxCommandEvent& event)
{
	int evt = event.GetId ();

	if(evt==XRCID("groups_tbl")) {
		m_tables->SwitchView(GVInfoView_TblGroups);
	} else if(evt==XRCID("fleets_tbl")) {
		m_tables->SwitchView(GVInfoView_TblFleets);
	} else if(evt==XRCID("incoming_tbl")) {
		m_tables->SwitchView(GVInfoView_TblIncoming);
	} else if(evt==XRCID("ship_types_tbl")) {
		m_tables->SwitchView(GVInfoView_TblShipTypes);
	} else if(evt==XRCID("planets_tbl")) {
		m_tables->SwitchView(GVInfoView_TblPlanets);
	} else if(evt==XRCID("production_tbl")) {
		m_tables->SwitchView(GVInfoView_TblProduction);
	} else if(evt==XRCID("stockpiles_tbl")) {
		m_tables->SwitchView(GVInfoView_TblStockpiles);
	} else if(evt==XRCID("routes_tbl")) {
		m_tables->SwitchView(GVInfoView_TblRoutes);
	} else if(evt==XRCID("races_tbl")) {
		m_tables->SwitchView(GVInfoView_TblRaces);
	} else if(evt==XRCID("battles_tbl")) {
		m_tables->SwitchView(GVInfoView_TblBattles);
	} else if(evt==XRCID("bombings_tbl")) {
		m_tables->SwitchView(GVInfoView_TblBombings);
	} else {
		wxASSERT_MSG(false, "Tables Menu Handler handled non Tables Menu Item :P");
	};
}

void
GVFrame::OnMapZoom(wxCommandEvent& event)
{
	int evt = event.GetId ();

	if (evt == XRCID ("zoom_in")) {
		m_map->DoZoom(MAP_ZOOM_IN);
	}
	else if (evt == XRCID ("zoom_out")) {
		m_map->DoZoom(MAP_ZOOM_OUT);
	}
	else {
		wxLogMessage("Wrong Event to wrong method");
	}
}

void
GVFrame::OnBookmarkAdd(wxCommandEvent& event)
{
	GVAddBookmarkDialog dlg(this);
	if(dlg.ShowModal()==wxID_OK) {
		wxString tmp = dlg.GetDescription();
		GVApp::GetGalaxy()->GetBookmarks()->CreateBookmark(this, dlg.GetSlot(), tmp);
	} 
	UpdateBookmarks();
}

void
GVFrame::OnBookmarkLoad(wxCommandEvent& event)
{
	int evt = event.GetId();
	if( (evt>=XRCID("bookmark_A")) &&
		(evt<=XRCID("bookmark_Z")) )
	{
		char c = 'A' + (event.GetId()-XRCID("bookmark_A"));
		GVApp::GetGalaxy()->GetBookmarks()->LoadBookmark(this, c);
	};
}

void
GVFrame::OnBookmarkDelete(wxCommandEvent& event)
{
	GVDeleteBookmarkDialog dlg(this);
	if(dlg.ShowModal()==wxID_OK) 
	{
		UpdateBookmarks();
	}
}


void
GVFrame::UpdateApplication()
{
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	wxString gameName;
	cf->Read (_("/GalaxyView/CurrentGame"), &gameName, "");

	UpdateTitlebar();
	UpdateStatusBar();
	UpdateBookmarks();

	if(gameName=="") {
		// If no Game loaded disable some stuff
		m_map->Enable(false);
	} else {
		// if game loaded enable some stuff
		m_map->Enable(true);
	}
}

void
GVFrame::UpdateStatusBar()
{
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	wxString gameName;
	wxString turn;
	cf->Read (_("/GalaxyView/CurrentGame"), &gameName, "");

	turn.Printf(_T("Turn %ld"), m_currentTurn);

	if(gameName=="") {
		m_status->SetStatusText("<No Game>", 1);
		m_status->SetStatusText("", 2);
	} else {
		m_status->SetStatusText(gameName, 1);
		m_status->SetStatusText(turn, 2);
		SetTitle (_T ("GalaxyView - Current Game: ") + gameName);
	}
}

void
GVFrame::UpdateTitlebar ()
{
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	wxString gameName;
	cf->Read (_("/GalaxyView/CurrentGame"), &gameName, "");

	if(gameName=="") {
		SetTitle(_T("GalaxyView - No Game"));
	} else {
		SetTitle (_T ("GalaxyView - Current Game: ") + gameName);
	}
}

void
GVFrame::UpdateBookmarks()
{
	GVBookmarkManager* bm = GVApp::GetGalaxy()->GetBookmarks();

	wxMenuBar* menubar = GetMenuBar();
	wxMenu* bookmarks = menubar->GetMenu(GVFRAME_BOOKMARKMENU); 

	// Remove all existing bookmarks
	while(wxMenuItem* item=bookmarks->FindItemByPosition(GVFRAME_FIRSTBOOKMARK)) {
		bookmarks->Remove(item);
		delete item;
	}

	if(!bm) {
		// Bookmark manager is NULL
		// -> no game/database loaded, abort
		return;
	}
	
	char id_str[] = "bookmark_?";
	for(char c = 'A' ; c<='Z' ; c++) {
		BookmarkData* bd = bm->GetBookmark(c);
		if(bd) {
			// replace the ? with the real character
			id_str[9] = c;
			wxString label;
			label.sprintf("&%c:%s\tAlt+%c", c, (const char*)bd->description, c);			
			wxMenuItem* item = new wxMenuItem(bookmarks, XRCID(id_str), label);
			bookmarks->Append(item);
		}
	}
}


// --------------------------------
// event tables
// --------------------------------

BEGIN_EVENT_TABLE (GVFrame, wxFrame)
	EVT_MENU (XRCID ("game_new"), GVFrame::OnNewGame)
	EVT_MENU (XRCID ("game_load"), GVFrame::OnLoadGame)
	EVT_MENU (XRCID ("preferences"), GVFrame::OnPreferences)
	EVT_MENU (XRCID ("exit"), GVFrame::OnQuit)
	EVT_MENU (XRCID ("help_about"), GVFrame::OnAbout)
	EVT_MENU (XRCID ("report_loadfile"), GVFrame::OnReportLoad)
	//*** Help
	EVT_MENU (XRCID ("help_contents"), GVFrame::OnHelp)
	//*** Pane Switch Menu items
	EVT_MENU (XRCID ("move_editor"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("planet_developer"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("ship_designer"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("battle_simulator"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("intel_center"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("message_center"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("treaty_editor"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("text_editor"), GVFrame::OnSwitchTools)
	EVT_MENU (XRCID ("calculator"), GVFrame::OnSwitchTools)

	//*** Map Menu
	EVT_MENU (XRCID ("zoom_in"), GVFrame::OnMapZoom)
	EVT_MENU (XRCID ("zoom_out"), GVFrame::OnMapZoom)

	//*** Tables Menu
	EVT_MENU (XRCID ("groups_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("fleets_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("incoming_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("ship_types_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("planets_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("production_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("stockpiles_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("routes_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("races_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("battles_tbl"), GVFrame::OnTablesMenu)
	EVT_MENU (XRCID ("bombings_tbl"), GVFrame::OnTablesMenu)

	//*** Bookmarks Menu
	EVT_MENU (XRCID ("bookmark_add"), GVFrame::OnBookmarkAdd)
	EVT_MENU (XRCID ("bookmark_delete"), GVFrame::OnBookmarkDelete)
	EVT_MENU (XRCID ("bookmark_A"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_B"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_C"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_D"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_E"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_F"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_G"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_H"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_I"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_J"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_K"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_L"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_M"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_N"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_O"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_P"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_Q"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_R"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_S"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_T"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_U"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_V"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_W"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_X"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_Y"), GVFrame::OnBookmarkLoad)
	EVT_MENU (XRCID ("bookmark_Z"), GVFrame::OnBookmarkLoad)

END_EVENT_TABLE ()
