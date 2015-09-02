//-*- c++ -*-
#if !defined(__GVDBSTATUS_H__)
#define __GVDBSTATUS_H__
/// \file GVDBStatus.h
/// \brief header file for storing data into the database in GalaxyView

// GVDBStatus.h -- header file for storing data into the database in GalaxyView
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

#include <map>
using namespace std;

#include "GVDBObject.h"

class GVDBStatus : public GVDBObject
{
public:

	GVDBStatus();

	bool Store(GVdb* db, hDB handle);

	wxString m_password;
	wxString m_name;
	int m_id;

	float m_drive;
	float m_weapons;
	float m_shields;
	float m_cargo;
	int m_numPlanets;
	int m_population;

	float m_industry;
	float m_capital;
	float m_material;
	float m_colonists;
};

#endif
