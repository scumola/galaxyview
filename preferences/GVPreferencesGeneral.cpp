/// \file GVPreferencesGeneral.cpp
/// \brief class file for Preferences Dialog in GalaxyView

// GVPreferencesGeneral.cpp -- class file for Preferences Dialog in GalaxyView
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

#include "GVPreferencesGeneral.h"
#include "GVPreferences.h"

IMPLEMENT_DYNAMIC_CLASS(GVPreferencesGeneral, GVPreferencesPage)

GVPreferencesGeneral::GVPreferencesGeneral()
{
}

void
GVPreferencesGeneral::OnCreate()
{
	// Called after the Panel is created
	m_game =				XRCCTRL (*this, "general_gamedirectory", wxTextCtrl);
	m_calculator =				XRCCTRL (*this, "general_calculator_path", wxTextCtrl);
	m_texteditor =				XRCCTRL (*this, "general_texteditor_path", wxTextCtrl);
	m_turn =							XRCCTRL (*this, "general_turn_path", wxTextCtrl);
	m_cf = (wxFileConfig*) wxConfigBase::Get(false);
}

void
GVPreferencesGeneral::Save()
{
	// Do whatever you need to do to save things
	m_gamepath = m_game->GetValue();
	m_turnpath = m_turn->GetValue();
	m_texteditorpath = m_texteditor->GetValue();
	m_calculatorpath = m_calculator->GetValue();
	
	m_cf->Write(_T ("/GalaxyView/DefaultTurnDirectory"), m_turnpath);
	m_cf->Write(_T ("/GalaxyView/TextEditorPath"), m_texteditorpath);
	m_cf->Write(_T ("/GalaxyView/CalculatorPath"), m_calculatorpath);
	m_cf->Write(_T ("/GalaxyView/GameDirectory"), m_gamepath);
}

void
GVPreferencesGeneral::Load()
{
	// Do whatever you need to do to load things
	m_cf->Read(_T ("/GalaxyView/DefaultTurnDirectory"), &m_turnpath, "");
	m_cf->Read(_T ("/GalaxyView/TextEditorPath"), &m_texteditorpath, "");
	m_cf->Read(_T ("/GalaxyView/CalculatorPath"), &m_calculatorpath, "");
	m_cf->Read(_T ("/GalaxyView/GameDirectory"), &m_gamepath, "");

	m_turn->SetValue(m_turnpath);
	m_texteditor->SetValue(m_texteditorpath);
	m_calculator->SetValue(m_calculatorpath);
	m_game->SetValue(m_gamepath);
}

void
GVPreferencesGeneral::OnChangeGameDirectory(wxCommandEvent& event)
{
	if(m_gamepath != event.GetString()) addChange("gamedirectory");
	else delChange("gamedirectory");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGeneral::OnChangeCalculatorPath(wxCommandEvent& event)
{
	if(m_calculatorpath != event.GetString()) addChange("calculator");
	else delChange("calculator");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGeneral::OnChangeTextEditorPath(wxCommandEvent& event)
{
	if(m_texteditorpath != event.GetString()) addChange("texteditor");
	else delChange("texteditor");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGeneral::OnChangeTurnPath(wxCommandEvent& event)
{
	if(m_turnpath != event.GetString()) addChange("game");
	else delChange("game");

	if(isChanged()) m_pParent->EnableApply(true);
	else m_pParent->EnableApply(false);
}

void
GVPreferencesGeneral::OnButtonGameDirectory(wxCommandEvent& event)
{
	wxString path;

	if(!m_game->GetValue().IsEmpty()) {
		path = m_game->GetValue();
	} else {
		path = ::wxGetCwd();
	}

	wxDirDialog dlg(this);
	dlg.SetPath(path);

	if(dlg.ShowModal() == wxID_OK)
		m_game->SetValue(dlg.GetPath());

	dlg.Destroy();
}

void
GVPreferencesGeneral::OnButtonCalculatorPath(wxCommandEvent& event)
{
	wxString path;

	if(!m_calculator->GetValue().IsEmpty()) {
		path = m_calculator->GetValue();
	} else {
		path = ::wxGetCwd();
	}
	
#if defined(__WIN32__)
 	wxFileDialog* dlg = new wxFileDialog(this, "Choose the Calculator", path, "", "Executable files (*.exe)|*.exe");
#else
 	wxFileDialog* dlg = new wxFileDialog(this, "Choose the Calculator", path);
#endif

	if (dlg->ShowModal() == wxID_OK)
		m_calculator->SetValue(dlg->GetPath());

	dlg->Destroy();
}

void
GVPreferencesGeneral::OnButtonTextEditorPath(wxCommandEvent& event)
{
	wxString path;

	if(!m_texteditor->GetValue().IsEmpty()) {
		path = m_texteditor->GetValue();
	} else {
		path = ::wxGetCwd();
	}
	
#if defined(__WIN32__)
 	wxFileDialog* dlg = new wxFileDialog(this, "Choose the Text Editor", path, "", "Executable files (*.exe)|*.exe");
#else
 	wxFileDialog* dlg = new wxFileDialog(this, "Choose the Text Editor", path);
#endif

	if (dlg->ShowModal() == wxID_OK)
		m_texteditor->SetValue(dlg->GetPath());

	dlg->Destroy();
}

void
GVPreferencesGeneral::OnButtonTurnPath(wxCommandEvent& event)
{
	wxString path;

	if(!m_turn->GetValue().IsEmpty()) {
		path = m_turn->GetValue();
	} else {
		path = ::wxGetCwd();
	}
	
	wxDirDialog* dlg = new wxDirDialog(this, "Choose a directory", path);
	if (dlg->ShowModal() == wxID_OK)
		m_turn->SetValue(dlg->GetPath());

	dlg->Destroy();
}


BEGIN_EVENT_TABLE (GVPreferencesGeneral, GVPreferencesPage)
	EVT_TEXT(XRCID("general_gamedirectory"), GVPreferencesGeneral::OnChangeGameDirectory)
	EVT_TEXT(XRCID("general_calculator_path"), GVPreferencesGeneral::OnChangeCalculatorPath)
	EVT_TEXT(XRCID("general_texteditor_path"), GVPreferencesGeneral::OnChangeTextEditorPath)
	EVT_TEXT(XRCID("general_turn_path"), GVPreferencesGeneral::OnChangeTurnPath)
	EVT_BUTTON(XRCID("general_gamedirectory_button"), GVPreferencesGeneral::OnButtonGameDirectory)
	EVT_BUTTON(XRCID("general_calculator_path_button"), GVPreferencesGeneral::OnButtonCalculatorPath)
	EVT_BUTTON(XRCID("general_texteditor_path_button"), GVPreferencesGeneral::OnButtonTextEditorPath)
	EVT_BUTTON(XRCID("general_turn_path_button"), GVPreferencesGeneral::OnButtonTurnPath)
END_EVENT_TABLE()

