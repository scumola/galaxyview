/// \file GVDBBulletin.cpp
/// \brief class file for bulletin db object in GalaxyView

// GVDBOptions.cpp -- class file  for bulletin db object in GalaxyView
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
#include "GVDBBulletin.h"


GVDBBulletin::GVDBBulletin ()
{
	m_bulletins.Clear ();
	m_turn = -1;
}

GVDBBulletin::~GVDBBulletin ()
{

}

void
GVDBBulletin::Add (wxString line)
{
	m_bulletins.Add (line);
}

bool GVDBBulletin::Store (GVdb * db, hDB handle)
{
	wxASSERT (m_turn != -1);

	SQLiteFile* sql = db->GetSQL(handle);
	if(!sql) {
		return false;
	}

	Query q = sql->GetQuery();

	q << "DELETE FROM bulletins WHERE turn=" << m_turn;
	if (!q.Execute()) {
		return false;
	}

	for (unsigned int i = 0; i < m_bulletins.GetCount (); i++) {
		wxString bulletin = m_bulletins[i];
		GVdb::EscapeSQL(bulletin);
		q << "INSERT INTO bulletins VALUES(" << m_turn << ", " << i
			<< ", \'" << bulletin.c_str() << "\')";

		if (!q.Execute()) {
			return false;
		}

	}
	return true;
}
