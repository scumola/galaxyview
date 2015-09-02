/// \file GVGalaxy.cpp
/// \brief class file to load turn data into memory in GalaxyView

// GVGalaxy.cpp -- class file to load turn data into memory in GalaxyView
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

#include "GVGalaxy.h"

GVGalaxy::GVGalaxy ()
{
	m_turn = 0;

	m_game = NULL;
	m_bookmarks = NULL;
}

GVGalaxy::~GVGalaxy ()
{
	list < GVGalaxyObject * >::iterator it;
	for (it = m_objects.begin (); it != m_objects.end (); it++) {
		GVGalaxyObject *obj = (*it);
		delete obj;
	}

	m_objects.erase (m_objects.begin (), m_objects.end ());

	if(m_game) delete m_game;
	if(m_bookmarks) delete m_bookmarks;
}

bool GVGalaxy::LoadTurn (long turnnumber)
{
 	FreeTurn (turnnumber);

	if (!LoadTurnPlanets (turnnumber))
		return false;

	return true;
}

bool
GVGalaxy::LoadTurnPlanets (long turnnumber)
{
	// Get SQLiteFile
	SQLiteFile* sql = m_db->GetSQL(m_handle);

	Query query = sql->GetQuery();
	query << "SELECT p.id, p.x, p.y, pt.* FROM planets p "
		<< "LEFT JOIN planets_turn pt ON p.id=pt.id WHERE turn="
		<< turnnumber; 

	// Execute Query - if bad return false
	Result result = query.Store();
	if(!result.Ok()) return false;

	for(unsigned int i=0;i<result.Size();i++) {
		Row r = result[i];
		GVPlanet* p = GVPlanet::LoadFromResult(r);
		m_objects.push_back(p);
	}

	return true;
}


#include <iostream>
void
GVGalaxy::FreeTurn (long turnnumber)
{
	list < GVGalaxyObject * >::iterator it;
	for (it = m_objects.begin (); it != m_objects.end (); it++) {
		GVGalaxyObject *obj = (*it);
		if (obj->turn () == turnnumber) {
			delete obj;
		}

		m_objects.erase (it);
	}
}

unsigned int
GVGalaxy::GetNumPlanets (long turnnumber)
{
	unsigned int num = 0;

	list < GVGalaxyObject * >::iterator it;
	for (it = m_objects.begin (); it != m_objects.end (); it++) {
		if (((*it)->type () == GVObj_Planet) &&
			(((*it)->turn () == turnnumber) || ((*it)->turn () == -1))) {
			num++;
		}
	}

	return num;
}


void
GVGalaxy::GetPlanets (GVPlanet ** ptr, long turnnumber)
{
	unsigned int i = 0;

	list < GVGalaxyObject * >::iterator it;
	for (it = m_objects.begin (); it != m_objects.end (); it++) {
		if (((*it)->type () == GVObj_Planet) &&
			(((*it)->turn () == turnnumber) || ((*it)->turn () == -1))) {
			ptr[i++] = (GVPlanet *) (*it);
		}
	}
}

void
GVGalaxy::SetDatabase(GVdb* db, hDB handle)
{
	m_db = db;
	m_handle = handle;

	if(m_game) {
		delete m_game;
	}
	m_game = new GVGame(db, handle);

	if(m_bookmarks) {
		delete m_bookmarks;
	}
	m_bookmarks = new GVBookmarkManager(db, handle);
}

void
GVGalaxy::Save()
{
	// If we have a database set save galaxy objects
	if(m_db) {
		m_bookmarks->SaveBookmarks();
	}
}
