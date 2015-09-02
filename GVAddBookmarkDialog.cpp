/// \file GVAddBookmarkDialog.cpp
/// \brief class file for the add bookmark dialog in GalaxyView

// GVAddBookmarkDialog.cpp -- class file for the add bookmark dialog in GalaxyView
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

#include "GVAddBookmarkDialog.h"
#include "GVApp.h"
#include "GVGalaxy.h"
#include "bookmark.h"

GVAddBookmarkDialog::GVAddBookmarkDialog(wxWindow* parent)
{
	wxXmlResource::Get ()->LoadDialog (this, parent, wxT ("addbookmark_dialog"));

	LoadBookmarks();
}

void
GVAddBookmarkDialog::OnOK(wxCommandEvent& evt)
{
	wxComboBox* slots = XRCCTRL(*this, "addbookmark_slot", wxComboBox);
	wxTextCtrl* desc  = XRCCTRL(*this, "addbookmark_description", wxTextCtrl);

	m_slot = slots->GetValue().GetChar(0);
	m_description = desc->GetValue();
	EndModal(wxID_OK);
}

void
GVAddBookmarkDialog::OnCancel(wxCommandEvent& evt)
{
	EndModal(wxID_CANCEL);
}

void
GVAddBookmarkDialog::LoadBookmarks()
{
	GVBookmarkManager* bm = GVApp::GetGalaxy()->GetBookmarks();
	wxASSERT_MSG(bm,"BookmarkManager was NULL");

	wxComboBox* slots = XRCCTRL(*this, "addbookmark_slot", wxComboBox);

	// Load all bookmarks from A-Z
	for(char c='A';c<='Z';c++)
	{
		BookmarkData* data = bm->GetBookmark(c);
		if(data) {
			slots->Append(wxString(data->id));
		} else {
			char text[] = "  (Empty)";
			text[0] = c;
			slots->Append(text);
		}
	}
}

BEGIN_EVENT_TABLE(GVAddBookmarkDialog, wxDialog)
	EVT_BUTTON(XRCID ("addbookmark_ok"), GVAddBookmarkDialog::OnOK) 
	EVT_BUTTON(XRCID ("addbookmark_cancel"), GVAddBookmarkDialog::OnCancel)
END_EVENT_TABLE()
