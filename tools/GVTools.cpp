/// \file GVTools.cpp
/// \brief class file for tools window in GalaxyView

// GVTools.cpp -- class file for tools window in GalaxyView
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

#include "GVTools.h"

static const char* tool_titles[] =
{
#ifdef WIN32
	_T("Message Center"),
	_T("Move Editor"),
	_T("Planet Editor"),
	_T("Ship Designer"),
	_T("Battle Simulator"),
	_T("Treaty Editor"),
	_T("Intelligence"),
	_T("Text Editor"),
	_T("Calculator")
#else
	_T("Message\nCenter"),
	_T("Move\nEditor"),
	_T("Planet\nEditor"),
	_T("Ship\nDesigner"),
	_T("Battle\nSimulator"),
	_T("Treaty\nEditor"),
	_T("Intelligence"),
	_T("Text\nEditor"),
	_T("Calculator")
#endif
};

GVTools::GVTools (wxWindow * parent, const wxPoint & pos, const wxSize & size, long style, const wxString & name):
wxNotebook (parent, -1, pos, size, style, name)
{
	m_imageList = new wxImageList (20, 20);

	LoadImages ();

	this->SetImageList (m_imageList);

	m_notebooksizer = new wxNotebookSizer(this);

	CreatePages ();

};

GVTools::~GVTools ()
{
	// Empty
	if (m_imageList) delete m_imageList;
	if (m_notebooksizer) delete m_notebooksizer;
	m_pagelist.clear();
};


void
GVTools::LoadImages ()
{
	// We have 8 Icons
	/*
	   I hope there is a better way to load icons from a resource file,
	   because this looks ugly and complicated.
	 */

	wxString resourceFile;
	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	cf->Read (_T ("/GalaxyView/resources"), &resourceFile);
	wxString resources;

	// Messages
	wxImage *img;


	wxZipInputStream msg_stream (resourceFile, 
								 "resource/buttons/message_center.png");
	img = new wxImage (msg_stream);

	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Message Center icon"));
	}
	delete img;
	
	// Move
	wxZipInputStream move_stream (resourceFile,
								  "resource/buttons/move_editor.png");
	img = new wxImage (move_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Move Editor icon"));
	}
	delete img;

	// Planet
	wxZipInputStream planet_stream (resourceFile,
									"resource/buttons/planeteditor.png");
	img = new wxImage (planet_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Planet Editor icon"));
	}
	delete img;


	// Shipdesign
	wxZipInputStream ship_stream(resourceFile,
								 "resource/buttons/ship_designer.png");
	
	img = new wxImage(ship_stream);
	if(img) {
		wxBitmap bmp(img);
		wxIcon icon;
		icon.CopyFromBitmap(bmp);
		m_imageList->Add(icon);
	} else {
		wxLogMessage(_T("could not load Ship Designer icon"));
	}
	delete img;

	// Battle
	wxZipInputStream battle_stream (resourceFile,
									"resource/buttons/battle_simulator.png");
	img = new wxImage (battle_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Battle Simulator icon"));
	}
	delete img;

	// Threaty
	wxZipInputStream threaty_stream (resourceFile,
									 "resource/buttons/treaty_editor.png");
	img = new wxImage (threaty_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Treaty Editor icon"));
	}
	delete img;

	// int
	wxZipInputStream intel_stream (resourceFile,
								   "resource/buttons/intel_center.png");
	img = new wxImage (intel_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Intelligence Center icon"));
	}
	delete img;

	// text ed
	wxZipInputStream text_stream (resourceFile,
								  "resource/buttons/text_editor.png");
	img = new wxImage (text_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Text Editor icon"));
	}
	delete img;

	// calc
	wxZipInputStream calc_stream (resourceFile,
								  "resource/buttons/calculator.png");
	img = new wxImage (calc_stream);
	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Calculator icon"));
	}
	delete img;
}

static wxFont panel_font;

void
GVTools::SaveAll()
{
	list<GVToolsPage*>::iterator it;

	for(it=m_pagelist.begin();it!=m_pagelist.end();it++) {
		if ((*it)->isChanged()) {
			(*it)->Save();
			(*it)->delAllChange();
		}
	}
}

GVToolsPage*
GVTools::CreatePage(const wxString& classname)
{
	if (classname.IsEmpty()) return NULL;
	return (GVToolsPage*)::wxCreateDynamicObject(classname);
}

bool
GVTools::AddPage(const wxString& text, const wxString& classname, const wxString& resource, const wxString& resourcefile, int pic)
{
	
	if (!resourcefile.IsEmpty()) {
		wxFileConfig*	cf = (wxFileConfig*) wxConfigBase::Get(false);
		wxString resFile;

		cf->Read (_T ("/GalaxyView/resources"), &resFile);
	
		wxString res = "file:" + resFile + "#zip:" + resourcefile;
		wxXmlResource::Get ()->Load (res);
	}
	
	GVToolsPage* page = CreatePage(classname);
	if (!page) return false;
	page->Create(resource, this);

	if(!wxNotebook::AddPage(page, text, false, pic)) return false;
	page->SetAutoLayout(true);
	page->Load();

	m_pagelist.push_back(page);
	return true;
}

void
GVTools::CreatePages ()
{
	// create each of the pages and insert them

	panel_font = wxFont::wxFont (8, wxSWISS, wxNORMAL, wxNORMAL, FALSE,
								 "", wxFONTENCODING_SYSTEM);

	AddPage(tool_titles[0], "GVToolsMessageCenter",
			"tools_messagecenter", "resource/ui/tools/toolsmessagecenter.xrc",
			GetIconIndex());
	
	AddPage(tool_titles[1], "GVToolsMoveEditor",
			"tools_moveeditor", "resource/ui/tools/toolsmoveeditor.xrc",
			GetIconIndex());

	AddPage(tool_titles[2], "GVToolsPlanetEditor",
			"tools_planeteditor", "resource/ui/tools/toolsplaneteditor.xrc",
			GetIconIndex());

	AddPage(tool_titles[3], "GVToolsShipDesigner",
			"tools_shipdesigner", "resource/ui/tools/toolsshipdesigner.xrc",
			GetIconIndex());

	AddPage(tool_titles[4], "GVToolsBattleSimulator",
			"tools_battlesimulator",
			"resource/ui/tools/toolsbattlesimulator.xrc", GetIconIndex());

	AddPage(tool_titles[5], "GVToolsTreatyEditor",
			"tools_treatyeditor", "resource/ui/tools/toolstreatyeditor.xrc",
			GetIconIndex());

	AddPage(tool_titles[6], "GVToolsIntelligence",
			"tools_intelligence", "resource/ui/tools/toolsintelligence.xrc",
			GetIconIndex());

	AddPage(tool_titles[7], "GVToolsTextEditor",
			"tools_texteditor", "resource/ui/tools/toolstexteditor.xrc",
			GetIconIndex());

	AddPage(tool_titles[8], "GVToolsCalculator",
			"tools_calculator", "resource/ui/tools/toolscalculator.xrc",
			GetIconIndex());

	SetSelection (0);

}

int
GVTools::GetIconIndex () const
{
	if (m_imageList) {
		int nImages = m_imageList->GetImageCount ();
		if (nImages > 0)
			return GetPageCount () % nImages;
	}

	return -1;
}

//*** GVToolsPage ***
IMPLEMENT_ABSTRACT_CLASS(GVToolsPage, wxPanel)

void
GVToolsPage::Create(const wxString& resource, wxWindow* parent)
{
	m_changed.clear();
	wxXmlResource::Get ()->LoadPanel (this, parent, resource);
	m_pParent = (GVTools*)parent;
	OnCreate();
}

void
GVToolsPage::addChange(const wxString& chg)
{
	list<wxString>::iterator it;

	for (it=m_changed.begin();it!=m_changed.end();it++)
		if (*it == chg) return;
	
	m_changed.push_back(chg);
}

void
GVToolsPage::delChange(const wxString& chg)
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
GVToolsPage::delAllChange()
{
	m_changed.clear();
}

BEGIN_EVENT_TABLE (GVToolsPage, wxPanel)
END_EVENT_TABLE()
