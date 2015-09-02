/// \file GVDBPlanet.cpp
/// \brief Database Object to store data

// GVDBPlanets.cpp - source file for storing data into the database in GalaxyView
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


#include "GVDBPlanets.h"

GVDBPlanets::GVDBPlanets()
{
	m_curPlanet = NULL;
	m_curOwner_id = -1;
}

GVDBPlanets::~GVDBPlanets()
{
	list<GVDBPlanetData*>::iterator i;
	for(i=m_data.begin();i!=m_data.end();i++) {
		GVDBPlanetData* planet = (*i);
		delete planet;
	}

	m_data.clear();
}

bool
GVDBPlanets::Store(GVdb* db, hDB handle)
{
  wxLogMessage("GVDBPlanets::Store()");
	SQLiteFile* sql = db->GetSQL(handle);
	if(!sql) {
	  wxLogMessage("sql not assigned");
		return false;
	}

	Query q = sql->GetQuery();

	list<GVDBPlanetData*>::iterator i;
	for(i=m_data.begin();i!=m_data.end();i++) {
		GVDBPlanetData* planet = (*i);

		int id = -1;
		if((id = GetPlanet(sql, planet))!=-1) {
			if(planet->m_identified) {
				q << "SELECT * FROM planets_turn WHERE turn=" << m_turn
					<< " AND id=" << id << " AND source=\'report\'";
				Result res = q.Store();

				// if an entry exist update it with new data
				if(res.Size()!=0) {
				  wxLogMessage("updating existing entry");
					q << "UPDATE planets_turn SET "
					  << "source=\'report\', "
					  << "sourceid=" << m_turn << ", "
					  << "name=\'" << planet->m_name.c_str() << "\', "
					  << "owner=" << planet->m_owner_id << ", "
					  << "size=" << planet->m_size << ", "
					  << "resources=" << planet->m_resources << ", "
					  << "population=" << planet->m_population << ", "
					  << "col=" << planet->m_population << ", "
					  << "mat=" << planet->m_material << ", "
					  << "cap=" << planet->m_capital << ", "
					  << "industry=" << planet->m_industry << ", "
					  << "posture=" << planet->m_posture.c_str() << " "
					  << "WHERE turn=" << m_turn
					  << " AND id=" << id << " AND source=\'report\'";
					
					if(!q.Execute()) {
					  wxLogMessage("update failed");
						return false;
					}

				} else {
				  wxLogMessage("inserting new entry");
					q << "INSERT INTO planets_turn VALUES("
					  << id << ", "
					  << m_turn << ", "
					  << "\'report\', "
					  << m_turn << ", "
					  << "\'" << planet->m_name.c_str() << "\', "
					  << planet->m_owner_id << ", " 
					  << planet->m_size << ", "
					  << planet->m_resources << ", "
					  << planet->m_population << ", "
					  << planet->m_colonists << ", "
					  << planet->m_material << ", "
					  << planet->m_capital << ", "
					  << planet->m_industry << ", "
					  << planet->m_posture.c_str()
					  << ")";

					if(!q.Execute()) {
					  wxLogMessage("insertion failed");
						return false;
					}
				}
			} else {
			  wxLogMessage("planet not identified");
				/* Planet Not Identified - Can't write it */
			}
		} else {
			wxString logMessage;
			logMessage.Printf("Inserting planets(%f, %f, %s)",
					planet->x, planet->y, planet->m_status.c_str());
			wxLogMessage(logMessage);
			q << "INSERT INTO planets(x,y,status) VALUES(" 
				<< planet->x << ", " << planet->y << ", "
				<< "\'" << planet->m_status.c_str() << "\')";
			if(!q.Execute()) {
			  wxLogMessage("insertion failed");
				return false ;
			}


			if(planet->m_identified) {

				int id = GetPlanet(sql, planet);
				wxASSERT_MSG(id!=-1, "Planet not found, but should have");
				wxLogMessage("planet identified, inserting into planets_turn");
				q << "INSERT INTO planets_turn VALUES("
					<< id << ", "
					<< m_turn << ", "
					<< "\'report\', "
					<< m_turn << ", "
					<< "\'" << planet->m_name.c_str() << "\', "
				  << planet->m_owner_id << ", "
					<< planet->m_size << ", "
					<< planet->m_resources << ", "
					<< planet->m_population << ", "
					<< planet->m_colonists << ", "
					<< planet->m_material << ", "
					<< planet->m_capital << ", "
					<< planet->m_industry << ", "
					<< "\'" << planet->m_posture.c_str() << "\')";

				if(!q.Execute()) {
				  wxLogMessage("insertion failed");
					return false;
				}

			}
		}
	}

	wxLogMessage("planets stored, leaving");

	return true;
}

int 
GVDBPlanets::GetPlanet(SQLiteFile* sql, GVDBPlanetData* planet)
{
    Query q = sql->GetQuery();
	q << "SELECT * from PLANETS WHERE x=" << planet->x 
		<< " AND y=" << planet->y;

	Result res = q.Store();

	if(res.Empty()) {
		return -1;
	} else {
	    wxASSERT_MSG(res.Size()==1,
					 _T("There is more than one planet with the same position."));
		Row r = res[0];
		return r.GetInteger(0);
	}
}

void
GVDBPlanets::Add(bool identified, wxString name)
{
	if(m_curPlanet) {
		Close();
	}

	wxLogMessage("Adding \"" + name + "\" to the list");
	m_curPlanet = new GVDBPlanetData;
	m_curPlanet->m_identified = identified;

	if(identified) {
		m_curPlanet->m_name = name;
		m_curPlanet->m_owner = m_curOwner;
		m_curPlanet->m_posture = "";
	}
}

void
GVDBPlanets::Close()
{
	if(m_curPlanet) {
	  wxLogMessage("Closing \"" + m_curPlanet->m_name + "\"");
		m_data.push_back(m_curPlanet);
		m_curPlanet = NULL;
	}
}

void
GVDBPlanets::SetProduction(wxString p)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_production = p;
}

void
GVDBPlanets::SetMaterial(float m)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_material = m;
}

void 
GVDBPlanets::SetCapital(float c)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_capital = c;
}

void
GVDBPlanets::SetIndustry(float i)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_industry = i;
}

void 
GVDBPlanets::SetPopulation(float p)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_population = p;
}

void
GVDBPlanets::SetResources(float r)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_resources = r;
}

void
GVDBPlanets::SetSize(float s)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_size = s;
}

void
GVDBPlanets::SetX(float x)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->x = x;
}

void 
GVDBPlanets::SetY(float y)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->y = y;
}

void  
GVDBPlanets::SetColonists(float c)
{
	wxASSERT_MSG(m_curPlanet, "No Current Planet");
	m_curPlanet->m_colonists = c;
}

void
GVDBPlanets::SetOwner(wxString name, int id)
{
  m_curOwner = name;
  m_curOwner_id = id;
}
