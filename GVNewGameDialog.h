//-*- c++ -*-     so xemacs treats this as c++ code instead of C
#if !defined(GVNEWGAMEDIALOG_H_)
#define GVNEWGAMEDIALOG_H_
/// \file GVNewGameDialog.h
/// \brief header file for setting up new games in GalaxyView

// GVNewGameDialog.h -- header file for setting up new games in GalaxyView
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

#include "wx/xrc/xmlres.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "wx/tokenzr.h"

#include "tools/GVTools.h"
#include "GVdefines.h"

/*
	Defines of Position of GalaxyNG and Explorer in the 
	newgamedialog.xrc, game type combobox
*/

enum _GameIndex {
	GVNEWGAME_GALAXYNG_INDEX = 2,
	GVNEWGAME_GALAXYEXPLORER_INDEX = 3,
};

class GVNewGameDialog:public wxDialog
{
  public:
	/**
	 * Constructor: creates a new frame for GalaxyView new game dialog
	 */
	GVNewGameDialog (wxWindow * parent);

	/**
	 * Returns the name of the new game
	 * \return wxString name of new game
	 */
	wxString GetGamename ();
	
	/**
	 * Returns the path to the turnreports
	 * \return wxString path to turnreports
	 */
	wxString GetGameDirectory ();
	
	/**
	 * Returns path/filename to the first report
	 * \return wxString path to turn0.xml
	 */
	wxString GetTurn0();
	
	/**
	 * Returns game type 
	 * \return wxString gametype
	 */
	wxString GetGameType();
	
	
	// callbacks
	void OnBrowse (wxCommandEvent & event);
	void OnGameBrowse(wxCommandEvent& event);
	void OnOK (wxCommandEvent & event);
	void OnCancel(wxCommandEvent& event);
	void OnGameNameChanged (wxCommandEvent & event);
	void OnTurnDirChanged (wxCommandEvent & event);
	void OnGameTypeSelectionChanged (wxCommandEvent & event);
	void OnTurnChanged(wxCommandEvent& event);
	void OnTurnBrowse(wxCommandEvent& event);
	
  private:
	/** 
	 * activates the ok button if all needed information are filled in
	 */
	void CheckInformation();
	
	wxString m_baseDir;
	
	DECLARE_EVENT_TABLE ()
};

#endif
