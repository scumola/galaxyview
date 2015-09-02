#if !defined(GVINFOPLANETS_H_)
#define GVINFOPLANETS_H_
/// \file GVInfoPlanets.h
/// \brief header file Child Class for the table view in GalaxyView

// GVInfoPlanets.h -- header file for the table view in GalaxyView
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

#include <wx/grid.h>

#define GVINFOPLANETS_NUM_COLS 12

class GVInfoPlanets : public wxPanel
{
public:
	GVInfoPlanets(wxWindow* parent);
	~GVInfoPlanets();

	void Update();

protected:
	void SetupGrid();
	void SetupCols();

	enum {
		PlanetsNULL = -1,
		PlanetsID = 0,
		PlanetsName,
		PlanetsOwner,
		PlanetsSize,
		PlanetsResources,
		PlanetsPopulation,
		PlanetsColonists,
		PlanetsMaterial,
		PlanetsCapital,
		PlanetsIndustry,
		PlanetsPosture,
		PlanetsSource
	} m_cols[GVINFOPLANETS_NUM_COLS];

	wxPanel* m_options;
	wxGrid*	m_planets;
};

#endif
