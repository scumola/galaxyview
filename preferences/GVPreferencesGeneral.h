#if !defined(GVPREFERENCESGENERAL_H_)
#define GVPREFERENCESGENERAL_H_
/// \file GVPreferencesGeneral.h
/// \brief header file for Preferences Dialog in GalaxyView

// GVPreferencesGeneral.h -- header file for Preferences Dialog in GalaxyView
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

#include "wx/dirdlg.h"
#include "wx/generic/dirdlgg.h"
#include "wx/textctrl.h"
#include "wx/checkbox.h"
#include "wx/filedlg.h"
#include "wx/confbase.h"
#include "wx/fileconf.h"

#include "GVPreferences.h"

class GVPreferencesGeneral : public GVPreferencesPage
{
	DECLARE_DYNAMIC_CLASS(GVPreferencesGeneral)
public:
	GVPreferencesGeneral ();

	void OnCreate();
	void OnChangeGameDirectory(wxCommandEvent& event);
	void OnChangeCalculatorPath(wxCommandEvent& event);
	void OnChangeTextEditorPath(wxCommandEvent& event);
	void OnChangeTurnPath(wxCommandEvent& event);
	void OnButtonGameDirectory(wxCommandEvent& event);
	void OnButtonCalculatorPath(wxCommandEvent& event);
	void OnButtonTextEditorPath(wxCommandEvent& event);
	void OnButtonTurnPath(wxCommandEvent& event);

	void Save();
	void Load();

protected:
	wxString			m_gamepath;
	wxString			m_calculatorpath;
	wxString			m_texteditorpath;
	wxString			m_turnpath;
	bool					m_bookmarksave;

	wxTextCtrl*		m_game;
	wxTextCtrl*		m_calculator;
	wxTextCtrl*		m_texteditor;
	wxTextCtrl*		m_turn;

	wxFileConfig* m_cf;

	DECLARE_EVENT_TABLE ()
};

#endif
