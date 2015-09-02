#if !defined(GVDB_H_)
#define GVDB_H_
/// \file GVdb.h
/// \brief header file for database interface in GalaxyView

// GVdb.h -- header file for database interface in GalaxyView
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

#include <map>
#include <vector>

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

#include "wx/string.h"
#include "wx/log.h"
#include "wx/config.h"
#include "wx/fileconf.h"

#include "sqlite++/sqlite++.h"

/// \var typedef int hDB
/// \brief type for sql database instance id
using namespace std;

typedef int hDB;


#define GVDB_ERROR -1

/// \brief this class is to abstract the database layer from the
/// code. 
///
/// Currently we see no need to change from an imbedded database,
/// nor do we see the need to go to a complete ODBC separation. Thus,
/// this class is meant to allow for the unlikely occasion when we
/// change from using sqlite to some other db - all changes will be
/// located in this code and not spread out through the program
///
/// the implementation will support multiple queries at once, along
/// with multiple database connections

class GVdb
{
  public:
	GVdb ();
	~GVdb ();

	/// opens a database, returns handle for further reference
	/// \param dbName wxString reference
	/// \return database handle to be used in future interactions
	hDB Open (wxString& gameName, wxString & dbName);

	/// closes an open database, handle is invalid after this returns
	/// \param db database handle, key to locate database instance to
	/// close
	/// \return no return values
	void Close (hDB db);

	/// does a single operation - like a row insert, delete, etc
	/// some SQL is only a single operation (ie, doesn't affect multiple
	/// rows that we want to iterate over.) For those functions (insert,
	/// delete, update) there is the single operation interface.
	/// \param db database handle
	/// \param sql SQL statement to be executed
	/// \return int an error indicator
	int Sql (hDB db, wxString & sql);

	/// Returns database handle by gamename
	/// \param gamename name of the game
	/// \return hDB handle to database
	hDB GetByGame (wxString gamename);

	/// Returns a SQLiteFile object to execute queries
	/// \param hDB handle of the database to use
	/// \return SQLiteFile* object to sqlite db
	SQLiteFile* GetSQL(hDB db);

	static void EscapeSQL(wxString& sql);

  private:
	/// per database unique key
	int m_dbIdx;

	/// for gamename to database handle 
	map< wxString,hDB > m_gamedb;

	/// hDB to SQLiteFile map
	map< hDB,SQLiteFile* > m_db;

};

#endif
