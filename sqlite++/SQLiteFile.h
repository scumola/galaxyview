#ifndef __SQLITEFILE_H__
#define __SQLITEFILE_H__
/// \file SQLiteFile.h
/// \brief header file for USED_FOR in GalaxyView

// SQLiteFile.h -- header file of C++ Wrapper for sqlite library in GalaxyView
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

class Query;

class SQLiteFile
{
public:
	SQLiteFile();
	~SQLiteFile();

	/// Opens Database file, if it doesn't exist it is created
	/// \param const char* file - filename
	/// \return bool - true on success
	bool Open(const char* file);

	/// Executes sql query 
	/// \param const char* sql - sql query to execute
	/// \return bool - true on sucess
	bool Execute(const char* sql);

	/// Get Last Error (Not Fully Implemented)
	/// \return const char* - last error 
	const char* GetLastError();

	/// Set Last Error (Not Fully Implemented)
	/// \param const char* s - new error message
	void SetLastError(const char* s);

	/// Creates a new Query for this database
	/// \return Query - new query object
	Query GetQuery();

	/// Get sqlite handle
	/// \return sqlite* - sqlite handle
	sqlite* GetDB() { return m_sqlite; }

protected:
	/// sqlite handle of this database
	sqlite* m_sqlite;

	/// last error
	string m_error;

	/// filename
	char* m_file;
};

#endif

