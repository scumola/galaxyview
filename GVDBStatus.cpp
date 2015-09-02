/// \file GVDBStatus.cpp
/// \brief Database Object to store data

// GVDBStatus.cpp - source file for storing data into the database in GalaxyView
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
#include "GVDBStatus.h"

GVDBStatus::GVDBStatus()
{

}

bool GVDBStatus::Store(GVdb* db, hDB handle)
{
	SQLiteFile* sql = db->GetSQL(handle);
	if(!sql) return false;

	Query q = sql->GetQuery();

	q << "SELECT * FROM status WHERE turn=" << m_turn;
	Result res = q.Store();

	if(!res.Empty()) {
		q << "DELETE FROM status WHERE turn=" << m_turn;
		q.Execute();
	};

	q << "INSERT INTO status VALUES(" << m_turn
		<< ", " << m_id 
		<< ", \'" << m_name.c_str() << "\'"
		<< ", \'" << m_password.c_str() << "\'"
		<< ", " << m_drive << ", " << m_weapons
		<< ", " << m_shields << ", " << m_cargo
		<< ", " << m_numPlanets << ", " << m_population
		<< ", " << m_industry << ", " << m_capital
		<< ", " << m_material << ", " << m_colonists << ")";

	if(!q.Execute()) {
		return false;
	}

	// Now Store yourself in the race table too
	q << "INSERT INTO races VALUES("
		<< m_turn << ", "
		<< m_id << ", "
		<< "\'" << m_name.c_str() << "\', "
		<< m_drive << ", "
		<< m_weapons << ", "
		<< m_shields << ", "
		<< m_cargo << ", "
		<< "\'N/A\')";

	if(!q.Execute()) {
		return false;
	}

	return true;
}
