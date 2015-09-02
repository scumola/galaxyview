#if !defined(GVINFOVIEW_H_)
#define GVINFOVIEW_H_
/// \file GVInfoView.h
/// \brief header file for Base Class for the table view in GalaxyView

// GVInfoView.h -- header file for the table view in GalaxyView
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

#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/image.h>
#include <wx/zipstrm.h>
#include <wx/notebook.h>

#include "infoviews/GVInfoPlanets.h"

enum GVInfoView_Tables {
	GVInfoView_TblGroups,
	GVInfoView_TblFleets,
	GVInfoView_TblIncoming,
	GVInfoView_TblShipTypes,
	GVInfoView_TblPlanets,
	GVInfoView_TblProduction,
	GVInfoView_TblStockpiles,
	GVInfoView_TblRoutes,
	GVInfoView_TblRaces,
	GVInfoView_TblBattles,
	GVInfoView_TblBombings
};


class GVInfoView : public wxNotebook
{
public:
	GVInfoView(wxWindow *parent);
	~GVInfoView();

	void UpdateChilds();
	void SwitchView(GVInfoView_Tables t);

protected:
	void LoadImages();

	void AddIcon(const char* res, const char* file);

	wxImageList* m_imageList;

	GVInfoPlanets*	m_planets;

};

#endif
