/// \file SQLiteFile.cpp
/// \brief class file for USED_FOR in GalaxyView

// SQLiteFile.cpp -- Part of C++ Wrapper for sqlite library in GalaxyView
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

#include <sqlite.h>

#include <string>
#include <sstream>
using namespace std;

#include "SQLiteFile.h"
#include "Query.h"

SQLiteFile::SQLiteFile()
{
	m_error = "";
	m_file = 0;
	m_sqlite = 0;
}


SQLiteFile::~SQLiteFile()
{	
	sqlite_close(m_sqlite);

	if(m_file) {
		delete[] m_file;
	}
}

bool
SQLiteFile::Open(const char* file)
{
	if(m_file) {
		m_error = "Database already open.";	
		return false;
	}
	m_file = new char[strlen(file)+1];
	strcpy(m_file, file);

	char* error = 0;
	m_sqlite = sqlite_open(m_file, 0, &error);

	if(error) {
		m_error = error;
		sqlite_freemem(error);
		return false;
	}

	return true;
};



const char*
SQLiteFile::GetLastError()
{
	return m_error.c_str();
}

void
SQLiteFile::SetLastError(const char* s)
{
	m_error = s;
}


Query
SQLiteFile::GetQuery()
{
	return Query(this);
}

bool
SQLiteFile::Execute(const char* sql)
{
	char* error;

	int retVal = sqlite_exec (m_sqlite, sql, NULL, NULL, &error);

	if(retVal!=SQLITE_OK) {
		SetLastError(error);
		sqlite_freemem(error);		
		return false;
	}
	return true;	
}

