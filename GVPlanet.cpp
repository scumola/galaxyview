/// \file GVPlanet.cpp
/// \brief class file for planet object in GalaxyView

// GVPlanet.cpp -- class file for planet object in GalaxyView
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

#include "GVPlanet.h"

enum _planet_radius {
	PLANET_RADIUS = 3,
	PLANET_RADIUS_HALF = (PLANET_RADIUS/2),
};

GVPlanet::GVPlanet (unsigned int id, unsigned int turn) :
		GVGalaxyObject (id, turn)
{
}


GVPlanet::~GVPlanet ()
{
}


void
GVPlanet::Draw (wxDC* dc, long ox, long oy, double size, double zoom,
					   bool center)
{
	int nX;
	int nY;

	if (center) {
		nX = int (float (x + (size / 2)) * zoom - PLANET_RADIUS_HALF);
		nY = int (float (y + (size / 2)) * zoom - PLANET_RADIUS_HALF);
	}
	else {
		nX = int (float (x) * zoom - PLANET_RADIUS_HALF);
		nY = int (float (y) * zoom - PLANET_RADIUS_HALF);
	}

	nX -= ox;
	nY -= oy;

	if (zoom < 1) {
		float radius = float (PLANET_RADIUS) * zoom;
		if (radius < 1.0f)
			radius = 1.0f;
		dc->DrawCircle (nX, nY, int (radius));
	}
	else {
		dc->DrawCircle (nX, nY, PLANET_RADIUS);
	}
}


GVPlanet*
GVPlanet::LoadFromResult (Row& row)
{
	unsigned int id = atoi (row[0]);
	long turn = 0;

	// if we have turn data set turn
	if(row[4]) {
		turn = atol (row[4]);
	}


	GVPlanet *p = new GVPlanet (id, turn);

	p->x = atof (row[1]);
	p->y = atof (row[2]);

	// row[3] is null if the join failed
	if (row[3]!=NULL) {
		p->m_turn = -1;
		p->m_name = row[5];

		//	unsigned int raceid = atoi (row[6]);
		//      p->m_lastOwner = GVApp::GetGalaxy()->GetRaceByID(raceid);

		p->m_size = atof (row[7]);
	}

	return p;
}
