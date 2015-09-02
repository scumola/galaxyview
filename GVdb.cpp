/// \file GVdb.cpp
/// \brief implementation file for database interface in GalaxyView

// GVdb.cpp -- implementation file for database interface in GalaxyView
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

#include <iostream>

#include "GVdb.h"

GVdb::GVdb ()
{
	// initialize the data members
	m_dbIdx = 1;
}

GVdb::~GVdb ()
{
	map<hDB,SQLiteFile*>::iterator i;
	for(i=m_db.begin();i!=m_db.end();i++) {
		SQLiteFile* sql = (*i).second;
		delete sql;
	}
	m_db.clear();
	m_gamedb.clear();
}

hDB
GVdb::Open (wxString& gameName, wxString & dbName)
{
	SQLiteFile* sql = new SQLiteFile;

	if(sql->Open(dbName)) {
		m_db[m_dbIdx] = sql;
		m_gamedb[gameName] = m_dbIdx;
		return m_dbIdx++;

	} else {
		// Could not open database
		delete sql;
		return GVDB_ERROR;
	}
}

void
GVdb::Close (hDB db)
{
	map<hDB,SQLiteFile*>::iterator i = m_db.find(db);

	if(i!=m_db.end()) {
		// that hDB realy exists delete it then
		delete (*i).second;
	}
}

int
GVdb::Sql (hDB db, wxString & sql)
{
	map<hDB,SQLiteFile*>::iterator i = m_db.find(db);
	if(i!=m_db.end()) {
		// SQLiteFile found - execute query
		SQLiteFile* handle = (*i).second;

		return handle->Execute(sql.c_str());
	}
	return 0;
}


// [kenw]: if it exists, open it, return handle - if it doesnt' exist, return -1
hDB
GVdb::GetByGame (wxString gamename)
{
	map<wxString,hDB>::iterator entry = m_gamedb.find(gamename);

	if(entry==m_gamedb.end()) {
		// Game Database not open - open it now

		wxFileConfig* cf = (wxFileConfig *)wxConfigBase::Get (false);
		long game_init = cf->Read (_("/") + gamename + _("/Initialized"), 0L);
		if (!game_init) {
			// Game Was Not Correctly set up
			// TODO: fix this game here - for the moment return -1
			return -1;
		} else {
			wxString gamedir;
			cf->Read (_("/GalaxyView/GameDirectory"), &gamedir, "");

			wxString dbfilename = gamedir +	_("/") + gamename + _(".gdf");

			if (::wxFileExists (dbfilename)) {
				// file found - Open Database
				return Open (gamename, dbfilename);
			} else {
				// Database not found
				return -1;
			}
		}
	} else {
		return (*entry).second;
	}
}

SQLiteFile*
GVdb::GetSQL(hDB db)
{
	map<hDB,SQLiteFile*>::iterator i;

	i = m_db.find(db);
	if(i==m_db.end()) {
		return NULL;
	} else {
		return (*i).second;
	}
}

void
GVdb::EscapeSQL(wxString& sql)
{
/*
	wxString newSql = "";

	for(unsigned int i=0;i<sql.Length();i++) {
		if(sql[i]=='\'') {
			newSql += "\'\'";
		} else {
			newSql += sql[i];
		}
	}

	sql = newSql;
	
	sql.Replace("\"", "\\\"");
	*/
	sql.Replace("\'", "\'\'");
}

#if defined(GVDB_MAIN_NEEDED)
int
main (int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Usage: GVdb dbname" << endl;
		return 1;
	}

	GVdb* db = new GVdb ();
	hDB testDB;

	wxString
		dbName =
		argv[1];
	if ((testDB = db->Open (dbName)) == 0) {
		cerr << "Could not open \"" << dbName << "\" as a database" << endl;
		return 1;
	}

	wxString
		query;

	query = "create table test1 (rowid integer, name char(32))";
	int
		retVal;
	if ((retVal = db->Sql (testDB, query)) != 0) {
		wxString
			error;
		error.Printf ("error creating table: (%d)", retVal);
		wxLogError (error);
		return 1;
	}

	int
		looper;
	for (looper = 1; looper < 10; looper++) {
		query.Printf (_("insert into test1 values (%d, \"looper_%d\")"),
					  looper, looper);
		if (db->Sql (testDB, query) != 0) {
			wxLogError (_("error inserting test row"));
			return 1;
		}
	}

	hSql
		myquery;

	query = "select * from test1";
	myquery = db->QueryOpen (testDB, query);
	if (myquery == 0) {
		wxString
			error;
		error.Printf (_("invalid query \"%s\""), query.c_str ());
		wxLogError (error);
	}

	result_list
		results;
	while (db->NextRow (myquery, results) == SQLITE_OK) {
		int
			nbr_cols =
			results.
			size ();
		int
			i;
		for (i = 0; i < nbr_cols; i++) {
			cout << results[i] << "\t";
		}
		cout << endl;
	}

	wxArrayString
		colnames;
	db->ColumnNames (myquery, colnames);

	{
		int
			i;
		for (i = 0; i < colnames.GetCount (); i++)
			cerr << colnames[i] << endl;
	}

	db->QueryClose (myquery);

	db->Close (testDB);

	return 0;
}
#endif
