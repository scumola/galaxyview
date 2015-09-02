/// \file GVDeleteBookmarkDialog.cpp
/// \brief class file for delete bookmarks dialog in GalaxyView

// GVDeleteBookmarkDialog.cpp -- class file for delete bookmarks dialog in GalaxyView
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

#include "GVApp.h"
#include "GVDeleteBookmarkDialog.h"

GVDeleteBookmarkDialog::GVDeleteBookmarkDialog(wxWindow* parent)
{
	wxXmlResource::Get ()->LoadDialog (this, parent, wxT ("deletebookmark_dialog"));

	wxListBox* list = XRCCTRL(*this, "deletebookmark_list", wxListBox);
	GVBookmarkManager* bm = GVApp::GetGalaxy()->GetBookmarks();

	int i = 0;
	for(char c='A';c<='Z';c++) {
		BookmarkData* bd = bm->GetBookmark(c);
		if(bd) {
			m_items[i++] = wxString(c) + " (" + bd->description + ")"; 
		}
	}
	list->InsertItems(i+1, m_items, 0);
}

void 
GVDeleteBookmarkDialog::OnOK(wxCommandEvent&)
{
	wxListBox* list = XRCCTRL(*this, "deletebookmark_list", wxListBox);
	GVBookmarkManager* bm = GVApp::GetGalaxy()->GetBookmarks();

	wxArrayInt selections;
	list->GetSelections(selections);

	for(unsigned int i=0;i<selections.GetCount();i++)
	{
		int id = selections[i];

		bm->DeleteBookmark((char)m_items[id][(size_t)0]);
	}

	EndModal(wxID_OK);
}

void 
GVDeleteBookmarkDialog::OnCancel(wxCommandEvent&)
{
	EndModal(wxID_CANCEL);
}

BEGIN_EVENT_TABLE(GVDeleteBookmarkDialog, wxDialog)
	EVT_BUTTON(XRCID ("deletebookmark_ok"), GVDeleteBookmarkDialog::OnOK) 
	EVT_BUTTON(XRCID ("deletebookmark_cancel"), GVDeleteBookmarkDialog::OnCancel)
END_EVENT_TABLE()
