/// \file GVPreferencesGame.cpp
/// \brief class file for Preferences Dialog in GalaxyView

// GVPreferencesGame.cpp -- class file for Preferences Dialog in GalaxyView
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

#include "GVPreferencesGame.h"
#include "GVPreferences.h"

IMPLEMENT_DYNAMIC_CLASS(GVPreferencesGame, GVPreferencesPage)

GVPreferencesGame::GVPreferencesGame()
{
}

void
GVPreferencesGame::OnCreate()
{
	// Called after the Panel is created
	m_passwordctrl =					XRCCTRL (*this, "game_user_password", wxTextCtrl);
	m_racenamectrl =					XRCCTRL (*this, "game_user_racename", wxTextCtrl);
	m_homeplanetsnumctrl =		XRCCTRL (*this, "game_homeplanets_number", wxTextCtrl);
	m_homeplanetssizectrl =		XRCCTRL (*this, "game_homeplanets_sizes", wxTextCtrl);
	m_gametypectrl =					XRCCTRL (*this, "game_gametypes", wxComboBox);
	m_gamenamectrl =					XRCCTRL (*this, "game_gamename", wxTextCtrl);

	m_bookmark_activectrl = XRCCTRL(*this, "game_bookmark_defaultsave_active", wxCheckBox);
	m_bookmark_slotctrl = XRCCTRL(*this, "game_bookmark_defaultsave", wxComboBox);

	m_homeplanetsnumctrl->SetMaxLength(5);

	m_cf = (wxFileConfig*) wxConfigBase::Get(false);
}

void
GVPreferencesGame::Save()
{
	// Do whatever you need to do to save things
	m_password = m_passwordctrl->GetValue();
	m_racename = m_racenamectrl->GetValue();
	m_homeplanetsnum = m_homeplanetsnumctrl->GetValue();
	m_homeplanetssize = m_homeplanetssizectrl->GetValue();
	m_gametype = m_gametypectrl->GetValue();
	m_gamename = m_gamenamectrl->GetValue();

	m_bookmark_active = m_bookmark_activectrl->IsChecked();
	m_bookmark_slot = wxString(m_bookmark_slotctrl->GetValue())[size_t(0)];
	
	GVdb* db = m_pParent->GetDB();
	hDB currentDB = m_pParent->GetCurrentDB();

	wxString curGame = m_cf->Read(_T("/GalaxyView/CurrentGame"), "");
	wxASSERT_MSG(curGame!="", "PreferenceGame::Save - current game is empty");

	if(m_bookmark_active) {
		m_cf->Write("/" + curGame + "/" + _T("BookmarkAutoSaveSlot"), wxString(m_bookmark_slot));
	} else {
		m_cf->Write("/" + curGame + "/" + _T("BookmarkAutoSaveSlot"), "0");
	}

	wxString cmd = "UPDATE preferencesgame SET password=\'" + m_password + "\'";
	db->Sql(currentDB, cmd);

	cmd = "UPDATE preferencesgame SET racename=\'" + m_racename + "\'";
	db->Sql(currentDB, cmd);
	
	cmd = "UPDATE preferencesgame SET gametype=\'" + m_gametype + "\'";
	db->Sql(currentDB, cmd);

	cmd = "UPDATE preferencesgame SET gamename=\'" + m_gamename + "\'";
	db->Sql(currentDB, cmd);

	cmd = "UPDATE preferencesgame SET homeplanetsnum=\'" + m_homeplanetsnum + "\'";
	db->Sql(currentDB, cmd);

	cmd = "UPDATE preferencesgame SET homeplanetssize=\'" + m_homeplanetssize + "\'";
	db->Sql(currentDB, cmd);
}

void
GVPreferencesGame::Load()
{
	wxString curGame = m_cf->Read(_T("/GalaxyView/CurrentGame"), "");
	
	char slot = m_cf->Read("/" + curGame + "/" + _T("BookmarkAutoSaveSlot"), "0")[(size_t)0];
	if(slot=='0') {
		m_bookmark_activectrl->SetValue(false);
		m_bookmark_active = false;
		m_bookmark_slotctrl->Enable(false);
		m_bookmark_slot = 'A';
	} else {
		m_bookmark_activectrl->SetValue(true);
		m_bookmark_active = true;
		m_bookmark_slotctrl->SetValue(wxString(slot));
		m_bookmark_slot = slot;
	}

	// Do whatever you need to do to load things
	wxString cmd = "SELECT * FROM preferencesgame";

	GVdb* db = m_pParent->GetDB();
	hDB currentDB = m_pParent->GetCurrentDB();

	// Get SQLiteFile and get Query
	SQLiteFile* sql = db->GetSQL(currentDB);
	Query q = sql->GetQuery();

	// Execute the Query
	q << cmd.c_str();
	Result res = q.Store();

	// Did we get a valid result?
	if (!res.Ok()) return;

	if(res.Empty()) {
		// Table wasnt created yet - Creating the table with some Default values
		m_password = "";
		m_gametype = "Galaxy Standard";
		m_gamename = "";
		m_homeplanetsnum = "3";
		m_homeplanetssize = "100,200,500";
		m_racename = "";
		
		cmd = "INSERT INTO preferencesgame values(\'" + m_password + "\',\'"
																									+ m_gametype + "\',\'"
																									+ m_gamename + "\',\'"
																									+ m_homeplanetsnum + "\',\'"
																									+ m_homeplanetssize + "\',\'"
																									+ m_racename + "\')";
		sql->Execute(cmd);
																							
	} else {
		Row oneRow = res[0];

		m_password = oneRow["password"];
		m_gametype = oneRow["gametype"];
		m_gamename = oneRow["gamename"];
		m_homeplanetsnum = oneRow["homeplanetsnum"];
		m_homeplanetssize = oneRow["homeplanetssize"];
		m_racename = oneRow["racename"];
	}

	m_passwordctrl->SetValue(m_password);
	m_gamenamectrl->SetValue(m_gamename);
	m_homeplanetsnumctrl->SetValue(m_homeplanetsnum);
	m_homeplanetssizectrl->SetValue(m_homeplanetssize);
	m_racenamectrl->SetValue(m_racename);
	m_gametypectrl->SetValue(m_gametype);
	
}

void
GVPreferencesGame::OnUserPasswordChange(wxCommandEvent& event)
{
	if(m_password != event.GetString()) addChange("game_password");
	else delChange("game_password");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnUserRaceNameChange(wxCommandEvent& event)
{
	if(m_racename != event.GetString()) addChange("game_racename");
	else delChange("game_racename");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnHomePlanetsNumberChange(wxCommandEvent& event)
{
	int ipoint = m_homeplanetsnumctrl->GetInsertionPoint();
	if(!event.GetString().IsNumber() && !event.GetString().IsEmpty()) {
		wxLogWarning (_T("Please insert a number and not a string, please"));
		m_homeplanetsnumctrl->SetValue(event.GetString().Remove(ipoint-1, 1));
		m_homeplanetsnumctrl->SetInsertionPoint(ipoint-1);
	}

	if(m_homeplanetsnum != event.GetString()) addChange("game_homeplanets_num");
	else delChange("game_homeplanets_num");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnHomePlanetsSizesChange(wxCommandEvent& event)
{
	if(m_homeplanetssize != event.GetString()) addChange("game_homeplanets_size");
	else delChange("game_homeplanets_size");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnGameTypesChange(wxCommandEvent& event)
{
	if(m_gametype != event.GetString()) addChange("game_gametype");
	else delChange("game_gametype");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnGameNameChange(wxCommandEvent& event)
{
	if(m_gamename != event.GetString()) addChange("game_gamename");
	else delChange("game_gamename");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnSlotChange(wxCommandEvent& event)
{
	if(m_bookmark_slot != event.GetString()) addChange("game_slot");
	else delChange("game_slot");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGame::OnBookmarkActive(wxCommandEvent& event)
{
	if(m_bookmark_active != event.IsChecked()) addChange("game_bookmark");
	else delChange("game_bookmark");

	if(m_bookmark_activectrl->IsChecked()) {
		m_bookmark_slotctrl->Enable(true);
	} else {
		m_bookmark_slotctrl->Enable(false);
	}

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

BEGIN_EVENT_TABLE (GVPreferencesGame, GVPreferencesPage)
	EVT_TEXT(XRCID("game_user_password"), GVPreferencesGame::OnUserPasswordChange)
	EVT_TEXT(XRCID("game_user_racename"), GVPreferencesGame::OnUserRaceNameChange)
	EVT_TEXT(XRCID("game_homeplanets_number"), GVPreferencesGame::OnHomePlanetsNumberChange)
	EVT_TEXT(XRCID("game_homeplanets_sizes"), GVPreferencesGame::OnHomePlanetsSizesChange)
	EVT_COMBOBOX(XRCID("game_gametypes"), GVPreferencesGame::OnGameTypesChange)
	EVT_TEXT(XRCID("game_gamename"), GVPreferencesGame::OnGameNameChange)
	EVT_COMBOBOX(XRCID("game_bookmark_defaultsave"), GVPreferencesGame::OnSlotChange)
	EVT_CHECKBOX(XRCID("game_bookmark_defaultsave_active"), GVPreferencesGame::OnBookmarkActive)
END_EVENT_TABLE()

