/// \file GVDBAliens.cpp
/// \brief XML report parser, derived from XMLParser

// GVDBAliens.cpp - source file for storing data into the database in GalaxyView
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

#include "GVdb.h"
#include "GVDBObject.h"
#include "GVDBAliens.h"

GVDBAliens::GVDBAliens()
{
	m_curAlien = NULL;
}

GVDBAliens::~GVDBAliens()
{
	list<GVDBAlienData*>::iterator i;
	for(i=m_data.begin();i!=m_data.end();i++) {
		GVDBAlienData* alien = (*i);
		delete alien;
	}

	m_data.clear();
}

bool
GVDBAliens::Store(GVdb* db, hDB handle)
{
	SQLiteFile* sql = db->GetSQL(handle);
	if(!sql) {
		return false;
	}

	Query q = sql->GetQuery();

	q << "DELETE FROM races WHERE turn=" << m_turn;
	if(!q.Execute()) {
		return false;
	}

	list<GVDBAlienData*>::iterator i;
	int id = 0;
	for(i=m_data.begin();i!=m_data.end();i++) {
		GVDBAlienData* alien = (*i);

		q << "INSERT INTO races VALUES("
			<< m_turn << ", "
			<< alien->m_id << ", "
			<< "\'" << alien->m_name.c_str() << "\', "
			<< alien->m_drive << ", "
			<< alien->m_weapons << ", "
			<< alien->m_shields << ", "
			<< alien->m_cargo << ", "
			<< "\'" << alien->m_posture.c_str() << "\'"
			<< ")";

		if(!q.Execute()) {
			return false;
		}

		id++;
	}

	return true;
}

void
GVDBAliens::AddNew(wxString name, wxString id)
{
	if(m_curAlien) {
		Close();
	}
	m_curAlien = new GVDBAlienData;
	m_curAlien->m_name = name;
	m_curAlien->m_id = atoi(id.c_str());
}

void
GVDBAliens::Close()
{
	if(m_curAlien) {
		m_data.push_back(m_curAlien);
		m_curAlien = NULL;
	}
}

void
GVDBAliens::SetDrive(float d)
{
	wxASSERT_MSG(m_curAlien, "No Current Alien");
	m_curAlien->m_drive = d;
}

void
GVDBAliens::SetWeapons(float w)
{
	wxASSERT_MSG(m_curAlien, "No Current Alien");
	m_curAlien->m_weapons = w;
}

void
GVDBAliens::SetShields(float s)
{
	wxASSERT_MSG(m_curAlien, "No Current Alien");
	m_curAlien->m_shields = s;
}

void
GVDBAliens::SetCargo(float c)
{
	wxASSERT_MSG(m_curAlien, "No Current Alien");
	m_curAlien->m_cargo = c;
}

void
GVDBAliens::SetPosture(wxString& p)
{
	wxASSERT_MSG(m_curAlien, "No Current Alien");
	m_curAlien->m_posture = p;
}

int
GVDBAliens::GetId(wxString& name)
{
	list<GVDBAlienData*>::iterator i;

	for(i=m_data.begin();i!=m_data.end();i++) {
	  GVDBAlienData* alien = (*i);
		if (name == alien->m_name)
		  return alien->m_id;
	}

	return -1;
}
