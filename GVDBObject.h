#if !defined(GVDBOBJECT_H_)
#define GVDBOBJECT_H_
/// \file GVDBObject.h
/// \brief header file for database interface in GalaxyView

// GVDBObject.h -- header file for database interface in GalaxyView
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

#include <list>

#if defined(__WIN32__)
#pragma warning(disable:4786)
#endif

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

/// \brief this class is an abstract base class for all data that can be written to the database
class GVDBObject
{
  public:

	/// Stores saves this object into the database 
	/// \param db: GalaxyView database class
	/// \param handle: hDB handle to database
	/// \return boolean: true on success, false otherwise
	virtual bool Store (GVdb * db, hDB handle) = 0;
	virtual void SetTurn (long turn)
	{
		m_turn = turn;
	}

  protected:
	long m_turn;
};

#endif
