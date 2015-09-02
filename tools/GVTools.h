#if !defined(GVTOOLS_H)
#define GVTOOLS_H
/// \file GVTools.h
/// \brief header file for tools window in GalaxyView

// GVTools.h -- header file for tools window in GalaxyView
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

#include <wx/xrc/xmlres.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/listctrl.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/image.h>
#include <wx/zipstrm.h>

#include <list>

using namespace std;

// TABS DEFINES

#define GVTAB_MESSAGES						0
#define GVTAB_MOVE_EDITOR					1
#define GVTAB_PLANET_EDITOR					2
#define GVTAB_SHIP_DESIGNER					3
#define GVTAB_BATTLE_SIMULATOR				4
#define GVTAB_TREATY_EDITOR					5
#define GVTAB_INTELLIGENCE					6
#define GVTAB_TEXT_EDITOR					7
#define GVTAB_CALCULATOR					8

class GVToolsPage;

class GVTools:public wxNotebook
{
public:
	GVTools (wxWindow * parent, const wxPoint & pos = wxDefaultPosition,
			 const wxSize & size = wxDefaultSize, long style = 0,
			 const wxString & name = _("GalaxyView Tools"));

	~GVTools ();

	void CreatePages (void);
	int GetIconIndex (void) const;

	bool AddPage(const wxString& text, const wxString& classname, const wxString& resource, const wxString& resourcefile="", int pic=-1);
	GVToolsPage* CreatePage(const wxString& classname);
	void SaveAll();

private:
	void LoadImages ();

	wxImageList*				m_imageList;
	wxIcon*							m_icons;
	list<GVToolsPage*>	m_pagelist;
	wxNotebookSizer*		m_notebooksizer;
};

class GVToolsPage : public wxPanel
{
	DECLARE_ABSTRACT_CLASS(GVToolsPage)
public:
	void Create(const wxString& resource, wxWindow* parent);

	virtual void OnCreate()=0;

	virtual void Save()=0;
	virtual void Load()=0;
	GVTools* GetParent() { return m_pParent; };
	
	int isChanged() { return !m_changed.empty(); };
	void addChange(const wxString& chg);
	void delChange(const wxString& chg);
	void delAllChange();
protected:
	list<wxString> m_changed;
	GVTools* m_pParent;
	DECLARE_EVENT_TABLE ()
};

#endif
