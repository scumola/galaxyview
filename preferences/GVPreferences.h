#if !defined(GVPREFERENCES_H_)
#define GVPREFERENCES_H_
/// \file GVPreferences.h
/// \brief header file for the Preferences Dialog in GalaxyView

// GVPreferences.h -- header file for the Preferences Dialog in GalaxyView
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
#include "wx/treectrl.h"
#include "wx/notebook.h"
#include "wx/panel.h"
#include "wx/confbase.h"
#include "wx/fileconf.h"

#include "../GVdb.h"

#include <list>

using namespace std;

class GVPreferencesPage;

class GVPreferences : public wxDialog
{
public:
	GVPreferences (wxWindow* parent, GVdb* _db, hDB currentDB, int page=0);
	virtual ~GVPreferences();

	void OnSize(wxSizeEvent& event);
	void OnOk(wxCommandEvent& event);
	void OnApply(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);

	GVdb* GetDB() { return m_db; };
	hDB GetCurrentDB() { return m_currentDB; };

	void SetDB(GVdb* _db) { m_db = _db; };
	void SetCurrentDB(hDB _db) { m_currentDB = _db; };
	void SaveAll();
	void EnableApply(bool enable);
	bool AddPage(const wxString& text, const wxString& classname, const wxString& resource, const wxString& resourcefile="", int pic=-1);
	GVPreferencesPage* CreatePage(const wxString& classname);
protected:
	GVdb*											m_db;
	hDB												m_currentDB;

	wxButton*									m_ok;
	wxButton*									m_cancel;
	wxButton*									m_apply;
	wxNotebook*								m_notebook;
	wxNotebookSizer*					m_notebooksizer;
	list<GVPreferencesPage*>	m_pagelist;

  DECLARE_EVENT_TABLE ()
};

class GVPreferencesPage : public wxPanel
{
	DECLARE_ABSTRACT_CLASS(GVPreferencesPage)
public:
	void Create(const wxString& resource, wxWindow* parent);

	virtual void OnCreate()=0;

	virtual void Save()=0;
	virtual void Load()=0;
	GVPreferences* GetDialogParent() { return m_pParent; };
	void SetDialogParent(GVPreferences* dlg) { m_pParent = dlg; };
	
	int isChanged() { return !m_changed.empty(); };
	void addChange(const wxString& chg);
	void delChange(const wxString& chg);
	void delAllChange();
protected:
	list<wxString> m_changed;
	GVPreferences* m_pParent;
	DECLARE_EVENT_TABLE ()
};


#endif
