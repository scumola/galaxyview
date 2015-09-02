#if !defined(GVPLANET_H_)
#define GVPLANET_H_
/// \file GVPlanet.h
/// \brief header file for planet object in GalaxyView

// GVPlanet.h -- header file for planet object in GalaxyView
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

#include "GVGalaxyObject.h"
#include "GVRace.h"

/**
	This class stores data for one specific planet in
	the galaxy universe
*/
class GVPlanet:public GVGalaxyObject
{
  public:
	GVPlanet (unsigned int id, unsigned int turn);

	 ~GVPlanet ();

	wxRealPoint position (void)
	{
		return wxRealPoint (x, y);
	};

	wxString name (void)
	{
		return m_name;
	}
	int id (void)
	{
		return m_id;
	};
	float size (void)
	{
		return m_size;
	};
	float population (void)
	{
		return m_population;
	};
	float industry (void)
	{
		return m_industry;
	};
	float resources (void)
	{
		return m_resources;
	};
	GVRace *lastOwner (void)
	{
		return m_lastOwner;
	};

	GVObjectType type ()
	{
		return GVObj_Planet;
	}

	// draw planet to map
	virtual void Draw (wxDC* dc, long ox, long oy, double size, double zoom,
					   bool center);

	double x;
	double y;

	// Load this planet with data from row 
	static GVPlanet *LoadFromResult (Row& row);

  private:
	wxString m_name;
	float m_size;
	float m_population;
	float m_industry;
	float m_resources;

	GVRace *m_lastOwner;
};

// initially the planet name will be a string version of the id
// (1 == "1"). The player can rename the planet at any time, but we
// will maintain the original id for ease of tracking and to make sure
// orders/predictions are consistent.
//
// m_lastowner will be who owned the planet last we knew. we will use
// the value of -1.0 for size, population, industry, and resources
// when we don't know what the value is, and -1 for the last turn seen
// if we've never seen it.

#endif
