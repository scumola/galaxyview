/// \file Query.cpp
/// \brief class file for USED_FOR in GalaxyView

// Query.cpp -- Part of C++ Wrapper for sqlite library in GalaxyView
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
#include <vector>
#include <map>
using namespace std;

#include "SQLiteFile.h"
#include "Row.h"
#include "Query.h"
#include "Result.h"

Query::Query(const Query& q)
{
	m_sql.str(q.m_sql.str());
	this->m_sqlite = q.m_sqlite;
}

void Query::operator=(const Query& q)
{

	this->m_sqlite = q.m_sqlite;
}

Query::Query(SQLiteFile* s)
{
	m_sql.str("");
	m_sqlite = s;
}

Query::~Query()
{

}

bool
Query::Execute()
{
	char* error;
	int retVal = sqlite_exec (m_sqlite->GetDB(), m_sql.str().c_str(), NULL, NULL, &error);

	if(retVal!=SQLITE_OK) {
		m_sqlite->SetLastError(error);
		sqlite_freemem(error);
		m_sql.str("");
		return false;
	}

	m_sql.str("");

	return true;
}

Result
Query::Store()
{
	sqlite_vm* vm;
	char* error;

	const char *statement_end;
	int retVal = sqlite_compile(m_sqlite->GetDB(), m_sql.str().c_str(), &statement_end, &vm, &error);

	if(retVal!=SQLITE_OK) {
		m_sqlite->SetLastError(error);
		sqlite_freemem(error);
		m_sql.str("");
		return Result(0);
	}

	m_sql.str("");
	return Result(vm);
}

Query&
Query::operator<<(const string& s)
{
	m_sql << s;
	return *this;
}

Query&
Query::operator<<(int i)
{
	m_sql << i;
	return *this;
}

Query&
Query::operator <<(unsigned int i)
{
	m_sql << i;
	return *this;
}

Query&
Query::operator<<(long l)
{
	m_sql << l;
	return *this;
}

Query&
Query::operator<<(float f)
{
	m_sql << f;
	return *this;
}

Query&
Query::operator<<(double d)
{
	m_sql << d;
	return *this;
}

Query&
Query::operator<<(char c)
{
	m_sql << c;
	return *this;
}
