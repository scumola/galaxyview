/// \file GVNewGameDialog.cpp
/// \brief Set up a new game for GalaxyView 

// GVNewGameDialog.cpp Set up a new game for GalaxyView 
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

#include "GVNewGameDialog.h"

/// Constructor for the new game dialog

/// The constructor reads the dialog from the resources file

GVNewGameDialog::GVNewGameDialog (wxWindow * parent)
{
	wxXmlResource::Get ()->LoadDialog (this, parent, wxT ("newgame_dialog"));
	XRCCTRL (*this, "newgame_samehomes", wxCheckBox)->Enable (false);
	XRCCTRL (*this, "newgame_ok", wxButton)->Enable (false);

	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);

	wxString defaultDir;
	cf->Read (_T ("/GalaxyView/DefaultTurnDirectory"), &defaultDir, "");
	m_baseDir = defaultDir;

	XRCCTRL (*this, "newgame_turndirectory",
			 wxTextCtrl)->SetValue (defaultDir);
	
	wxString gameDir;
	cf->Read(_T("/GalaxyView/GameDirectory"), &gameDir, "");
	XRCCTRL(*this, "newgame_gamedirectory", wxTextCtrl)->SetValue(gameDir);
}

void
GVNewGameDialog::OnGameBrowse(wxCommandEvent&)
{
	wxDirDialog dlg(this);
	wxTextCtrl *t = XRCCTRL(*this, "newgame_gamedirectory", wxTextCtrl);

	dlg.SetPath(t->GetValue());

	if(wxID_OK == dlg.ShowModal()) {
		wxString path = dlg.GetPath();
		t->SetValue(path);
	}
}

void
GVNewGameDialog::OnBrowse (wxCommandEvent &)
{
	wxDirDialog dlg (this);
	wxTextCtrl *t = XRCCTRL (*this, "newgame_turndirectory", wxTextCtrl);
//	wxTextCtrl *game = XRCCTRL (*this, "newgame_name", wxTextCtrl);

	dlg.SetPath (t->GetValue ());

	if (wxID_OK == dlg.ShowModal ()) {
		// User Selected a directory
		m_baseDir = dlg.GetPath ();

		t->SetValue (m_baseDir);

		/* Don't Overwrite DefaultTurnDirectory on Change
		wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
		cf->Write (_T ("/GalaxyView/DefaultTurnDirectory"), m_baseDir);
		*/
	}
}

void
GVNewGameDialog::OnGameTypeSelectionChanged (wxCommandEvent & event)
{
	//enable same planet size box for GalaxyNG and Explorer
	wxComboBox *comboctrl = XRCCTRL (*this, "newgame_type", wxComboBox);
	wxCheckBox *checkctrl = XRCCTRL (*this, "newgame_samehomes", wxCheckBox);

	if (comboctrl->GetSelection () == GVNEWGAME_GALAXYNG_INDEX) {
		checkctrl->Enable (true);
	}
	else if (comboctrl->GetSelection () == GVNEWGAME_GALAXYEXPLORER_INDEX) {
		checkctrl->Enable (true);
	}
	else {
		checkctrl->Enable (false);
	}
}

void
GVNewGameDialog::OnOK (wxCommandEvent & evt)
{
	// Check if already a game with this name exists

	// get game in textctrl
	wxTextCtrl *gamenamectrl = XRCCTRL (*this, "newgame_name", wxTextCtrl);
	wxString currentgame = gamenamectrl->GetValue ();

        wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);

	// update default game dir
	wxTextCtrl* gamedir = XRCCTRL(*this, "newgame_gamedirectory", wxTextCtrl);
	cf->Write(_T("/GalaxyView/GameDirectory"), gamedir->GetValue());

	// load games list from config file
	wxString gamesList;
	cf->Read (_("/GalaxyView/Games"), &gamesList);

	// check if we have a match
	wxStringTokenizer st (gamesList, _(","));
	while (st.HasMoreTokens ()) {
		wxString game = st.NextToken ();

		if (game == currentgame) {
			// We have a match
			wxMessageBox (_T ("A game with name ") + currentgame +
						  _T (" already exists."), _T ("Create Game"),
						  wxID_OK | wxICON_WARNING);
			return;
		}
	}
	EndModal (wxID_OK);
}


void
GVNewGameDialog::OnGameNameChanged (wxCommandEvent & event)
{
	CheckInformation();
}

void
GVNewGameDialog::OnTurnDirChanged (wxCommandEvent & event)
{
/* Not Used At The Moment 

	wxTextCtrl* namectrl = XRCCTRL(*this, "newgame_name", wxTextCtrl);
	wxTextCtrl* dirctrl = XRCCTRL(*this, "newgame_turndirectory", wxTextCtrl);
	wxButton* button = XRCCTRL(*this, "newgame_ok", wxButton);
*/
}

wxString
GVNewGameDialog::GetGamename ()
{
	wxTextCtrl*	textctrl = XRCCTRL (*this, "newgame_name", wxTextCtrl);
	return textctrl->GetValue ();
}

wxString
GVNewGameDialog::GetTurn0()
{
	wxTextCtrl* textctrl = XRCCTRL(*this, "newgame_turn0", wxTextCtrl);
	return textctrl->GetValue();
}

wxString
GVNewGameDialog::GetGameDirectory ()
{
	wxTextCtrl*	path = XRCCTRL (*this, "newgame_turndirectory", wxTextCtrl);
	return path->GetValue ();
}

wxString
GVNewGameDialog::GetGameType()
{
	wxComboBox *comboctrl = XRCCTRL (*this, "newgame_type", wxComboBox);

	return comboctrl->GetValue();
}

void
GVNewGameDialog::OnCancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

void
GVNewGameDialog::OnTurnChanged(wxCommandEvent& event)
{
	CheckInformation();
}

void
GVNewGameDialog::OnTurnBrowse(wxCommandEvent& event)
{
	wxTextCtrl* turnDir = XRCCTRL(*this, "newgame_turndirectory", wxTextCtrl);

	// For Now Just a simple method to test the report parser
	wxFileDialog dlg (this, _("Load Report"), "", "", _("*.xml"));
	dlg.SetDirectory(turnDir->GetValue());

	if (dlg.ShowModal () == wxID_OK) {
		wxString filename = dlg.GetPath ();

		wxTextCtrl* turn0 = XRCCTRL(*this, "newgame_turn0", wxTextCtrl);
		turn0->SetValue(filename);
	}
}

void
GVNewGameDialog::CheckInformation()
{
	wxTextCtrl *turn0ctrl = XRCCTRL (*this, "newgame_turn0", wxTextCtrl);
	wxTextCtrl *namectrl = XRCCTRL (*this, "newgame_name", wxTextCtrl);
	wxTextCtrl *dirctrl = XRCCTRL (*this, "newgame_turndirectory", wxTextCtrl);
	wxButton *button = XRCCTRL (*this, "newgame_ok", wxButton);

	if (namectrl->GetValue ().IsEmpty ()) {
		button->Enable (false);
	}
	else if (dirctrl->GetValue ().IsEmpty ()) {
		button->Enable (false);
	}
	else if (turn0ctrl->GetValue().IsEmpty()) {
		button->Enable (false);
	}
	else {
		// Does the turn report exist?
		if(::wxFileExists(turn0ctrl->GetValue())) {
			button->Enable (true);
		} else {
			button->Enable (false);
		}
	}	
}

BEGIN_EVENT_TABLE(GVNewGameDialog, wxDialog)
	EVT_TEXT(XRCID ("newgame_name"), GVNewGameDialog::OnGameNameChanged)
	EVT_COMBOBOX(XRCID ("newgame_type"), GVNewGameDialog::OnGameTypeSelectionChanged)
	EVT_TEXT(XRCID ("newgame_turndirectory"), GVNewGameDialog::OnTurnDirChanged)
	EVT_BUTTON(XRCID ("newgame_turndirectory_browse"),	GVNewGameDialog::OnBrowse) 
	EVT_TEXT(XRCID ("newgame_turn0"), GVNewGameDialog::OnTurnChanged)
	EVT_BUTTON(XRCID ("newgame_turn0_browse"), GVNewGameDialog::OnTurnBrowse)
	EVT_BUTTON(XRCID ("newgame_ok"), GVNewGameDialog::OnOK) 
	EVT_BUTTON(XRCID ("newgame_cancel"), GVNewGameDialog::OnCancel)
	EVT_BUTTON(XRCID ("newgame_gamedirectory_browse"), GVNewGameDialog::OnGameBrowse)
END_EVENT_TABLE()
