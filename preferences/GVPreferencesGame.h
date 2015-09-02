#if !defined(GVPREFERENCESGAME_H_)
#define GVPREFERENCESGAME_H_
/// \file GVPreferencesGame.h
/// \brief header file for Preferences Dialog in GalaxyView

// GVPreferencesGame.h -- header file for Preferences Dialog in GalaxyView
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

#include "wx/textctrl.h"
#include "wx/statbox.h"
#include "wx/combobox.h"
#include "wx/log.h"

#include "GVPreferences.h"

class GVPreferencesGame : public GVPreferencesPage
{
	DECLARE_DYNAMIC_CLASS(GVPreferencesGame)
public:
	GVPreferencesGame ();

	void OnUserPasswordChange(wxCommandEvent& event);
	void OnUserRaceNameChange(wxCommandEvent& event);
	void OnHomePlanetsNumberChange(wxCommandEvent& event);
	void OnHomePlanetsSizesChange(wxCommandEvent& event);
	void OnGameTypesChange(wxCommandEvent& event);
	void OnGameNameChange(wxCommandEvent& event);
	void OnSlotChange(wxCommandEvent& event);
	void OnBookmarkActive(wxCommandEvent& event);

	void OnCreate();

	void Save();
	void Load();
protected:
	wxString			m_password;
	wxString			m_racename;
	wxString			m_homeplanetsnum;
	wxString			m_homeplanetssize;
	wxString			m_gametype;
	wxString			m_gamename;

	char			m_bookmark_slot;
	bool			m_bookmark_active;
	
	wxFileConfig*		m_cf;

	wxTextCtrl*		m_passwordctrl;
	wxTextCtrl*		m_racenamectrl;
	wxTextCtrl*		m_homeplanetsnumctrl;
	wxTextCtrl*		m_homeplanetssizectrl;
	wxComboBox*		m_gametypectrl;
	wxTextCtrl*		m_gamenamectrl;
	wxCheckBox*		m_bookmark_activectrl;
	wxComboBox*		m_bookmark_slotctrl;

	DECLARE_EVENT_TABLE ()
};

#endif
