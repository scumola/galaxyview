#ifndef __QUERY_H__
#define __QUERY_H__
/// \file Query.h
/// \brief header file for USED_FOR in GalaxyView

// Query.h -- header file of C++ Wrapper for sqlite library in GalaxyView
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

class SQLiteFile;
class Result;

/**
	The class Query represents a sql command interface.
*/
class Query
{
friend class SQLiteFile;
public:
	Query(const Query& q);
	~Query();

	/// Execute current sql command (INSERT, UPDATE, DELETE, commands without a result set)
	/// \return bool - true on success
	bool Execute();

	/// Execute current sql command (SELECT, commands with result set)
	/// \return Result - resultset object
	Result Store();

	/// \return const char* - returns currently stored sql string
	const char* Preview() { return m_sql.str().c_str(); }

	// Operators
	void operator=(const Query& q);
	Query& operator<<(const string& s);
	Query& operator<<(int i);
	Query& operator<<(long l);
	Query& operator<<(float f);
	Query& operator<<(double d);
	Query& operator<<(char c);
	Query& operator <<(unsigned int i);

protected:
	/// Protected Constructor so you can't create a Query without a SQLLiteFile attached
	Query(SQLiteFile* s);

	/// pointer to parent SQLiteFile
	SQLiteFile* m_sqlite;

	/// sql command buffer
	ostringstream m_sql;

};

#endif

