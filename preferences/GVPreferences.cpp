/// \file GVPreferences.cpp
/// \brief class file for the Preferences Dialog in GalaxyView

// GVPreferences.cpp -- class file for the Preferences Dialog in GalaxyView
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


#include "GVPreferences.h"

GVPreferences::GVPreferences(wxWindow* parent, GVdb* _db, hDB currentDB, int page)
{
	m_ok = NULL;
	m_cancel = NULL;
	m_apply = NULL;
	m_notebook = NULL;

	wxXmlResource::Get ()->LoadDialog (this, parent, wxT ("preferences_dialog"));
	
	m_ok =				XRCCTRL (*this, "wxID_OK", wxButton);
	m_cancel =		XRCCTRL (*this, "wxID_CANCEL", wxButton);
	m_apply =			XRCCTRL (*this, "preferences_apply", wxButton);
	m_notebook =	XRCCTRL (*this, "preferences_notebook", wxNotebook);
	
	m_notebooksizer = new wxNotebookSizer(m_notebook);

	SetCurrentDB(currentDB);
	SetDB(_db);
	
	EnableApply(false);
	AddPage(wxT("GalaxyView"), wxT("GVPreferencesGeneral"), wxT("preferences_general_panel"), wxT("resource/ui/preferences/preferencesgeneral.xrc"));


	wxFileConfig* cf = (wxFileConfig*)wxConfigBase::Get(false);
	if(cf->Read(_T("/GalaxyView/CurrentGame"), "")!="") {
		AddPage(wxT("Game"), wxT("GVPreferencesGame"), wxT("preferences_game_panel"), wxT("resource/ui/preferences/preferencesgame.xrc"));

	}

	m_notebook->SetSelection(page);
	SetSize(400,300);
}

GVPreferences::~GVPreferences()
{
	if(m_notebooksizer) delete m_notebooksizer;
}

void
GVPreferences::OnSize(wxSizeEvent& event)
{
	wxSize size = GetClientSize();
	
	if (m_notebook) m_notebook->SetSize(4, 4, size.GetWidth()-10, size.GetHeight()-45);
	if (m_ok) m_ok->SetSize((size.GetWidth()-256)/2,size.GetHeight()-34, 72, -1);
	if (m_cancel) m_cancel->SetSize(((size.GetWidth()-256)/2)+92,size.GetHeight()-34, 72, -1);
	if (m_apply) m_apply->SetSize(((size.GetWidth()-256)/2)+184,size.GetHeight()-34, 72, -1);
}

void 
GVPreferences::OnOk(wxCommandEvent& event)
{
	SaveAll();
	wxDialog::OnOK(event);
}

void
GVPreferences::OnApply(wxCommandEvent& event)
{
	SaveAll();
	EnableApply(false);
}

void
GVPreferences::OnCancel(wxCommandEvent& event)
{
	wxDialog::OnCancel(event);	
}

void
GVPreferences::EnableApply(bool enable)
{
	m_apply->Enable(enable);
}

void
GVPreferences::SaveAll()
{
	list<GVPreferencesPage*>::iterator it;

	for(it=m_pagelist.begin();it!=m_pagelist.end();it++) {
		if ((*it)->isChanged()) {
			(*it)->Save();
			(*it)->delAllChange();
		}
	}
}

GVPreferencesPage*
GVPreferences::CreatePage(const wxString& classname)
{
	if (classname.IsEmpty()) return NULL;
	return (GVPreferencesPage*)::wxCreateDynamicObject(classname);
}

bool
GVPreferences::AddPage(const wxString& text, const wxString& classname, const wxString& resource, const wxString& resourcefile, int pic)
{
	
	if (!resourcefile.IsEmpty()) {
		wxFileConfig*	cf = (wxFileConfig*) wxConfigBase::Get(false);
		wxString resFile;

		cf->Read (_T ("/GalaxyView/resources"), &resFile);
	
		wxString res = _T ("file:") + resFile +
			_T ("#zip:") + resourcefile;
		wxXmlResource::Get ()->Load (res);
	}
	
	GVPreferencesPage* page = CreatePage(classname);
	if (!page) return false;
	page->Create(resource, m_notebook);

	if(!m_notebook->AddPage(page, text, false, pic)) return false;
	page->SetAutoLayout(true);
	page->SetDialogParent(this);
	page->Load();

	m_pagelist.push_back(page);
	return true;
}

BEGIN_EVENT_TABLE (GVPreferences, wxDialog)
	EVT_SIZE(GVPreferences::OnSize)
	EVT_BUTTON(XRCID("wxID_OK"), GVPreferences::OnOk)
	EVT_BUTTON(XRCID("preferences_apply"), GVPreferences::OnApply)
	EVT_BUTTON(XRCID("wxID_CANCEL"), GVPreferences::OnCancel)
END_EVENT_TABLE ()

//*** GVPreferencesPage ***
IMPLEMENT_ABSTRACT_CLASS(GVPreferencesPage, wxPanel)

void
GVPreferencesPage::Create(const wxString& resource, wxWindow* parent)
{
	m_changed.clear();
	wxXmlResource::Get ()->LoadPanel (this, parent, resource);
	OnCreate();
}

void
GVPreferencesPage::addChange(const wxString& chg)
{
	list<wxString>::iterator it;

	for (it=m_changed.begin();it!=m_changed.end();it++)
		if (*it == chg) return;
	
	m_changed.push_back(chg);
}

void
GVPreferencesPage::delChange(const wxString& chg)
{
	list<wxString>::iterator it;

	for (it=m_changed.begin();it!=m_changed.end();it++) {
		if (*it == chg) {
			m_changed.erase(it);
			return;
		}
	}
}

void
GVPreferencesPage::delAllChange()
{
	m_changed.clear();
}

BEGIN_EVENT_TABLE (GVPreferencesPage, wxPanel)
END_EVENT_TABLE()

