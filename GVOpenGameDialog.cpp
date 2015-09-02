/// \file GVOpenGameDialog.cpp
/// \brief main framework implementation for the GalaxyView project

// GVOpenGameDialog.cpp main framework implementation for the GalaxyView project
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

#include "GVFrame.h"
#include "GVOpenGameDialog.h"
#include "tools/GVTools.h"

#include <typeinfo>

GVOpenGameDialog::GVOpenGameDialog (wxWindow * parent,
									bool withNew /* = false */ )
{
	wxXmlResource::Get ()->LoadDialog (this, parent, wxT ("opengame_dialog"));

	wxTreeCtrl *treectrl = XRCCTRL (*this, "loadgame_gamelist", wxTreeCtrl);
	m_treeroot = treectrl->AddRoot (_T ("Games"));
	m_activeroot = treectrl->AppendItem (m_treeroot, _("Active Games"));
	m_inactiveroot = treectrl->AppendItem (m_treeroot, _("Inactive Games"));

	treectrl->Expand (m_treeroot);
	treectrl->SelectItem (m_treeroot);
	XRCCTRL (*this, "loadgame_ok", wxButton)->Enable (false);

	XRCCTRL (*this, "loadgame_newgame", wxButton)->Show (withNew);
}

void
GVOpenGameDialog::OnOK (wxCommandEvent & evt)
{
	EndModal (wxID_OK);
}

void
GVOpenGameDialog::OnSelectionChanged (wxCommandEvent & event)
{
	wxTreeCtrl *treectrl = XRCCTRL (*this, "loadgame_gamelist", wxTreeCtrl);
	wxTreeItemId selItem = treectrl->GetSelection ();

	wxButton *button = XRCCTRL (*this, "loadgame_ok", wxButton);
	if (selItem == m_treeroot || selItem == m_activeroot
		|| selItem == m_inactiveroot) {
		button->Enable (false);
		m_selection = "";
	}
	else {
		button->Enable (true);
		m_selection = treectrl->GetItemText (selItem);
	}
}

void
GVOpenGameDialog::AddGame (wxString game, bool active)
{

	wxTreeCtrl *treectrl = XRCCTRL (*this, "loadgame_gamelist", wxTreeCtrl);
	if (active) {
		treectrl->AppendItem (m_activeroot, game);
	}
	else {
		treectrl->AppendItem (m_inactiveroot, game);
	}
}


void
GVOpenGameDialog::SortGames ()
{
	wxTreeCtrl *treectrl = XRCCTRL (*this, "loadgame_gamelist", wxTreeCtrl);

	treectrl->SortChildren (m_activeroot);
	treectrl->SortChildren (m_inactiveroot);
}

void
GVOpenGameDialog::OnNew (wxCommandEvent & evt)
{
	wxWindow *parent = this->GetParent ();

	GVFrame *frame = static_cast < GVFrame * >(parent);
	if (frame) {
		EndModal (wxID_CANCEL);
		frame->ShowNewGameDialog ();
	}
}

void
GVOpenGameDialog::OnCancel(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

BEGIN_EVENT_TABLE (GVOpenGameDialog, wxDialog)
	EVT_TREE_SEL_CHANGED (XRCID ("loadgame_gamelist"), GVOpenGameDialog::OnSelectionChanged)
	EVT_BUTTON (XRCID ("loadgame_ok"), GVOpenGameDialog::OnOK)
	EVT_BUTTON (XRCID ("loadgame_newgame"), GVOpenGameDialog::OnNew)
	EVT_BUTTON (XRCID ("loadgame_cancel"), GVOpenGameDialog::OnCancel)
END_EVENT_TABLE ()
