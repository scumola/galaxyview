#if !defined(GVFRAME_H)
#define GVFRAME_H
/// \file GVFrame.h
/// \brief header file for main window of GalaxyView

// GVFrame.h -- header file for main window of GalaxyView
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

#if defined(__WIN32__)
#pragma warning(disable:4786)
#endif

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if !defined(WX_PREC)
#include "wx/wx.h"
#endif

#include "wx/toolbar.h"
#include "wx/xrc/xmlres.h"
#include "wx/menuitem.h"
#include "wx/image.h"
#include "wx/fs_zip.h"
#include "wx/splash.h"
#include "wx/sizer.h"
#include "wx/splitter.h"
#include "wx/notebook.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/zipstrm.h"
#include "wx/tokenzr.h"
#include "wx/html/htmlwin.h"
#include "wx/html/helpctrl.h"

#include "tools/GVTools.h"
#include "GVdb.h"
#include "GVHelpFrame.h"
#include "GVMapPanel.h"
#include "GVInfoView.h"
#include "GVToolBar.h"

/**
 * Sorting Operator for STL 
 * Not Sure where i should put it - perhaps in defines
 */
class wxStringSorter
{
  public:
	bool operator       () (const wxString arg1, const wxString arg2) const
	{
		return arg1.Cmp (arg2) < 0;
	}
};

#define GVFRAME_BOOKMARKMENU 5
#define GVFRAME_FIRSTBOOKMARK 3

class GVFrame:public wxFrame
{
  public:
  /**
   * Constructor: creates a new frame for GalaxyView viewer
   */
	GVFrame (const wxChar * title, int xpos, int ypos, int width, int height);

  /**
   * Destructor
   */
	~GVFrame ();

	void db (GVdb * _db);

  /**
   * New Game
   * Creates a new database, ini file entries
   * \param gamename wxString - name of new game
   * \param turn0 wxString - turn0 report
   * \param type wxString - galaxy variant
   * \return bool - true on sucess
   */
	bool NewGame (wxString gamename, wxString turn0, wxString type);

  /**
   * Loads a Game
   * Refreshes all Tools, Subwindows, Map, etc
   * \param gamename wxString - name of the game to load
   * \return bool - true on success
   */
	bool LoadGame (wxString gamename);
	
	/** 
	 * unloads a game
	 * saves all game related resources
	 * \return bool - true on sucess
	 */
	bool UnloadGame();
	 

	void ShowNewGameDialog ();
	void ShowOpenGameDialog (bool withNew);

	// callbacks
	void OnHelp (wxCommandEvent & event);
	void OnNewGame (wxCommandEvent & event);
	void OnLoadGame (wxCommandEvent & event);
	void OnPreferences (wxCommandEvent & event);
	void OnQuit (wxCommandEvent & event);
	void OnAbout (wxCommandEvent & event);
	void OnReportLoad (wxCommandEvent & event);
	void OnSwitchTools (wxCommandEvent & event);
	void OnMapZoom(wxCommandEvent& event);
	void OnTablesMenu(wxCommandEvent& event);
	void OnBookmarkAdd(wxCommandEvent& event);
	void OnBookmarkLoad(wxCommandEvent& event);
	void OnBookmarkDelete(wxCommandEvent& event);

	/**
	 * updates all child windows
	 */
	void UpdateApplication();

	/**
	 * updates title bar with current game name
	 */
	void UpdateTitlebar ();

	/**
	 * updates status bar with gamename and turn
	 */
	void UpdateStatusBar();

	/**
	 * updates the bookmarks menu entries
	 */
	void UpdateBookmarks();

	wxSplitterWindow* GetHSplitter() { return m_hsplit; }
	wxSplitterWindow* GetVSplitter() { return m_vsplit; }
	GVMapPanel* GetMapPanel() { return m_map; };

  private:
	  GVHelpFrame * m_help;

	wxMenuBar *m_MenuBar;
	wxSplitterWindow *m_hsplit;	// first, the horizontal split
	wxSplitterWindow *m_vsplit;	// then the vertical split
	GVInfoView *m_tables;	// window for tables notebook
	GVTools *m_tools;			// window for tools
	GVdb *m_db;					// database interface
	hDB m_currentDB;			// handle to the currently active game
	GVMapPanel *m_map;
	GVToolBar* m_toolbar;
	long m_currentTurn;

	wxStatusBar*	m_status;

  DECLARE_EVENT_TABLE ()
};

#endif
