#if !defined(__GVDBPLANETS_H__)
#define __GVDBPLANETS_H__
/// \file GVDBPlanets.h
/// \brief header file for storing data into the database in GalaxyView

// GVDBPlanets.h -- header file for storing data into the database in GalaxyView
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

#include <iostream>
#include <map>
using namespace std;

#include "GVdb.h"
#include "GVDBObject.h"

struct GVDBPlanetData
{
	wxString m_name;

	float x;
	float y;

	bool m_identified;

	float m_resources;
	float m_size;
	float m_population;
	float m_industry;
	float m_capital;
	float m_material;
	float m_colonists;

  int m_owner_id;

	wxString m_owner;
	wxString m_production;
	wxString m_posture;
	wxString m_status;
};

class GVDBPlanets : public GVDBObject
{
public:

	GVDBPlanets();
	virtual ~GVDBPlanets();

	bool Store(GVdb* db, hDB handle);

	void Add(bool identified, wxString name);
	void Close();

	void SetOwner(wxString name, int id);
	void SetProduction(wxString p);
	void SetMaterial(float m);
	void SetCapital(float c);
	void SetIndustry(float i);
	void SetPopulation(float p);
	void SetResources(float r);
	void SetSize(float s);
	void SetColonists(float c);
	void SetX(float x);
	void SetY(float y);
	void SetPosture(wxString p) { m_curPlanet->m_posture = p; }
	void SetStatus(wxString s) { m_curPlanet->m_status = s; }

protected:
	int GetPlanet(SQLiteFile* sql, GVDBPlanetData* planet);

	wxString m_curOwner;
	int m_curOwner_id;
	GVDBPlanetData* m_curPlanet;
	list<GVDBPlanetData*> m_data;

};

#endif
