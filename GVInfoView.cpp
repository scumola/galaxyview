/// \file GVInfoView.cpp
/// \brief Base Class for the table view

// GVInfoView.cpp
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

#include "GVInfoView.h"

GVInfoView::GVInfoView(wxWindow *parent)
: wxNotebook(parent, -1)
{
	LoadImages();
	SetImageList (m_imageList);

	wxNotebook::AddPage(new wxPanel(this), _T("Groups"), false, 0);
	wxNotebook::AddPage(new wxPanel(this), _T("Fleets"), false, 1);
	wxNotebook::AddPage(new wxPanel(this), _T("Incoming Groups"), false, 2);
	wxNotebook::AddPage(new wxPanel(this), _T("Ship Types"), false, 3);
	wxNotebook::AddPage(m_planets = new GVInfoPlanets(this), _T("Planets"), false, 4);
	wxNotebook::AddPage(new wxPanel(this), _T("Production"), false, 5);
	wxNotebook::AddPage(new wxPanel(this), _T("Stockpiles"), false, 6);
	wxNotebook::AddPage(new wxPanel(this), _T("Routes"), false, 7);
	wxNotebook::AddPage(new wxPanel(this), _T("Races"), false, 8);
	wxNotebook::AddPage(new wxPanel(this), _T("Battles"), false, 9);
	wxNotebook::AddPage(new wxPanel(this), _T("Bombings"), false, 10);
	UpdateChilds();
}


GVInfoView::~GVInfoView()
{
	delete m_imageList;
}

void
GVInfoView::LoadImages()
{
	m_imageList = new wxImageList(20, 20);

	wxString resourceFile;
	wxString resources;

	wxFileConfig *cf = (wxFileConfig *) wxConfigBase::Get (false);
	cf->Read (_T ("/GalaxyView/resources"), &resourceFile);

	AddIcon(resourceFile, "resource/buttons/groups_tbl.png");
	AddIcon(resourceFile, "resource/buttons/fleets_tbl.png");
	AddIcon(resourceFile, "resource/buttons/groups_incoming.png");
	AddIcon(resourceFile, "resource/buttons/ship_types_tbl.png");
	AddIcon(resourceFile, "resource/buttons/planets_tbl.png");
	AddIcon(resourceFile, "resource/buttons/production_tbl.png");
	AddIcon(resourceFile, "resource/buttons/stockpiles_tbl.png");
	AddIcon(resourceFile, "resource/buttons/routes_tbl.png");
	AddIcon(resourceFile, "resource/buttons/races_tbl.png");
	AddIcon(resourceFile, "resource/buttons/battles_tbl.png");
	AddIcon(resourceFile, "resource/buttons/bombings_tbl.png");

}

void GVInfoView::AddIcon(const char* resFile, const char* file)
{
	wxZipInputStream stream(resFile, file);
	wxImage* img = new wxImage (stream);

	if (img) {
		wxBitmap bmp (img);
		wxIcon icon;
		icon.CopyFromBitmap (bmp);
		m_imageList->Add (icon);
	}
	else {
		wxLogMessage (_T ("could not load Groups icon"));
	}
	delete img;
}

void
GVInfoView::UpdateChilds()
{
	m_planets->Update();
}


void 
GVInfoView::SwitchView(GVInfoView_Tables t)
{
	switch(t) {
		case GVInfoView_TblGroups: SetSelection(0); break;
		case GVInfoView_TblFleets: SetSelection(1); break;
		case GVInfoView_TblIncoming: SetSelection(2); break;
		case GVInfoView_TblShipTypes: SetSelection(3); break;
		case GVInfoView_TblPlanets: SetSelection(4); break;
		case GVInfoView_TblProduction: SetSelection(5); break;
		case GVInfoView_TblStockpiles: SetSelection(6); break;
		case GVInfoView_TblRoutes: SetSelection(7); break;
		case GVInfoView_TblRaces: SetSelection(8); break;
		case GVInfoView_TblBattles: SetSelection(9); break;
		case GVInfoView_TblBombings: SetSelection(10); break;
	};
}

